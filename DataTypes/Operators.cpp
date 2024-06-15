#include <iostream>
#include "Numbers.hpp"

namespace num {

    std::pair<uint128, bool>
    storage_addition(uint128 storage1, const uint128 storage2, bool is_positive1, const bool is_positive2) {
        if (is_positive1 and is_positive2) {
            storage1 += storage2;
        } else if (is_positive1 and !is_positive2) {
            if (storage1 < storage2) {
                // Idea is: 2 - 5 = - (5 - 2)
                is_positive1 = false;
                storage1 = storage2 - storage2;
            } else {
                storage1 -= storage2;
            }
        } else if (!is_positive1 and is_positive2) {
            if (storage1 < storage2) {
                // Idea is: - 2 + 5 = 5 - 2
                is_positive1 = true;
                storage1 = storage2 - storage1;
            } else {
                // Idea is: - 5 + 2 = - (5 - 2)
                storage1 -= storage2;
            }
        } else { //!int1.m_is_positive and !int2.m_is_positive
            // Idea is: - 5 - 2 = - (5 + 2)
            storage1 += storage2;
        }
        return std::pair{storage1, is_positive1};
    }

    std::pair<uint64, bool>
    storage_addition(uint64 storage1, const uint64 storage2, bool is_positiv1, const bool is_positive2) {
        return static_cast<std::pair<uint64, bool>> (storage_addition(static_cast<uint128>(storage1),
                                                                      static_cast<uint128>(storage2),
                                                                      is_positiv1, is_positive2));
    }

    std::pair<uint128, uint128>
    shift_to_equal_size(const uint64 storage1, const uint64 storage2, const char SCALING_DELTA) {
        if (SCALING_DELTA > 0) {
            return std::pair{storage1, (static_cast<uint128> (storage2)) << SCALING_DELTA};
        } else if (SCALING_DELTA < 0) {
            return std::pair{(static_cast<uint128> (storage1)) << -SCALING_DELTA, storage2};
        } else {
            return std::pair{storage1, storage2};
        }
    }

    uint64 unshift_form_equal_size(const uint128 large_storage1, const char SCALING_DELTA) {
        if (SCALING_DELTA < 0) {
            return large_storage1 >> -SCALING_DELTA;
        } else {
            return large_storage1;
        }
    }

    Integer operator+(Integer int1, const Integer &int2) {
        Integer result(int1);
        result += int2;
        return result;
    }

    Integer operator+=(Integer &int1, const Integer &int2) {
        auto result = storage_addition(int1.m_storage, int2.m_storage, int1.m_is_positive, int2.m_is_positive);
        int1.m_storage = result.first;
        int1.m_is_positive = result.second;
        int1.clap_to_size();
        return int1;
    }

    Integer operator-(Integer int1, const Integer &int2) {
        Integer result(int1);
        result -= int2;
        return result;
    }

    Integer operator-=(Integer &int1, const Integer &int2) {
        Integer temp = int2;
        temp.m_is_positive = !temp.m_is_positive;
        return int1 += temp;
    }

    Integer operator*(Integer int1, const Integer &int2) {
        Integer result(int1);
        result *= int2;
        return result;
    }

    Integer operator*=(Integer &int1, const Integer &int2) {
        // neg times neg = pos
        int1.m_is_positive ^= ~int2.m_is_positive;

        int1.m_storage *= int2.m_storage;

        int1.clap_to_size();
        return int1;
    }

    Integer operator/(Integer int1, const Integer &int2) {
        Integer result(int1);
        result /= int2;
        return result;
    }

    Integer operator/=(Integer &int1, const Integer &int2) {
        // neg times neg = pos
        int1.m_is_positive ^= ~int2.m_is_positive;

        int1.m_storage /= int2.m_storage;

        int1.clap_to_size();
        return int1;
    }


    Decimal operator+(Decimal dec1, const Decimal &dec2) {
        Decimal result(dec1);
        result += dec2;
        return result;
    }

    Decimal operator+=(Decimal &dec1, const Decimal &dec2) {
        const char SCALING_DELTA = static_cast<char>(dec1.c_SCALING_FACTOR - dec2.c_SCALING_FACTOR);

        auto shifted_storage = shift_to_equal_size(dec1.m_storage, dec2.m_storage, SCALING_DELTA);

        auto result_shifted = storage_addition(shifted_storage.first, shifted_storage.second, dec1.m_is_positive,
                                               dec2.m_is_positive);

        dec1.m_storage = unshift_form_equal_size(result_shifted.first, SCALING_DELTA);
        dec1.m_is_positive = result_shifted.second;
        dec1.clap_to_size();
        return dec1;
    }

    Decimal operator-(Decimal dec1, const Decimal &dec2) {
        Decimal result(dec1);
        result -= dec2;
        return result;
    }

    Decimal operator-=(Decimal &dec1, const Decimal &dec2) {
        Decimal temp = dec2;
        temp.m_is_positive = !temp.m_is_positive;
        dec1 += temp;
        return dec1;
    }

    Decimal operator*(Decimal dec1, const Decimal &dec2) {
        Decimal result(dec1);
        result *= dec2;
        return result;
    }

    Decimal operator*=(Decimal &dec1, const Decimal &dec2) {
        const char SCALING_DELTA = static_cast<char>(dec1.c_SCALING_FACTOR - dec2.c_SCALING_FACTOR);

        auto shifted_storage = shift_to_equal_size(dec1.m_storage, dec2.m_storage, SCALING_DELTA);

        dec1.m_is_positive ^= ~dec2.m_is_positive;

        shifted_storage.first *= shifted_storage.second;

        if (SCALING_DELTA > 0) {
            shifted_storage.first >>= dec1.c_SCALING_FACTOR;
        } else {
            shifted_storage.first >>= dec2.c_SCALING_FACTOR;
        }

        dec1.m_storage = unshift_form_equal_size(shifted_storage.first, SCALING_DELTA);
        dec1.clap_to_size();
        return dec1;
    }

    Decimal operator/(Decimal dec1, const Decimal &dec2) {
        Decimal result(dec1);
        result /= dec2;
        return result;
    }

    Decimal operator/=(Decimal &dec1, const Decimal &dec2) {
        const char SCALING_DELTA = static_cast<char>(dec1.c_SCALING_FACTOR - dec2.c_SCALING_FACTOR);

        auto shifted_storage = shift_to_equal_size(dec1.m_storage, dec2.m_storage, SCALING_DELTA);

        dec1.m_is_positive ^= ~dec2.m_is_positive;

        if (SCALING_DELTA > 0) {
            shifted_storage.first <<= dec1.c_SCALING_FACTOR;
        } else {
            shifted_storage.first <<= dec2.c_SCALING_FACTOR;
        }

        shifted_storage.first /= shifted_storage.second;

        dec1.m_storage = unshift_form_equal_size(shifted_storage.first, SCALING_DELTA);
        dec1.clap_to_size();
        return dec1;
    }


    Decimal operator+(Integer int1, const Decimal & dec2) {
        Decimal result(int1, dec2.c_SCALING_FACTOR);
        result += dec2;
        return result;
    }

    Decimal operator+(Decimal dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 += addend;
        return dec1;
    }

    Integer operator+=(Integer & int1, const Decimal &dec2) {
        Integer addend(dec2);
        int1 += addend;
        return int1;
    }
    Decimal operator+=(Decimal & dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 += addend;
        return dec1;
    }

    
    Decimal operator-(Integer int1, const Decimal & dec2) {
        Decimal result(int1, dec2.c_SCALING_FACTOR);
        result -= dec2;
        return result;
    }

    Decimal operator-(Decimal dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 -= addend;
        return dec1;
    }

    Integer operator-=(Integer & int1, const Decimal &dec2) {
        Integer addend(dec2);
        int1 -= addend;
        return int1;
    }
    Decimal operator-=(Decimal & dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 -= addend;
        return dec1;
    }
    
    
    Decimal operator*(Integer int1, const Decimal & dec2) {
        Decimal result(int1, dec2.c_SCALING_FACTOR);
        result *= dec2;
        return result;
    }

    Decimal operator*(Decimal dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 *= addend;
        return dec1;
    }

    Integer operator*=(Integer & int1, const Decimal &dec2) {
        Integer addend(dec2);
        int1 *= addend;
        return int1;
    }
    Decimal operator*=(Decimal & dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 *= addend;
        return dec1;
    }

    
    Decimal operator/(Integer int1, const Decimal & dec2) {
        Decimal result(int1, dec2.c_SCALING_FACTOR);
        result /= dec2;
        return result;
    }

    Decimal operator/(Decimal dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 /= addend;
        return dec1;
    }

    Integer operator/=(Integer & int1, const Decimal &dec2) {
        Integer addend(dec2);
        int1 /= addend;
        return int1;
    }
    Decimal operator/=(Decimal & dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 /= addend;
        return dec1;
    }
}