#include <iostream>
#include "Numbers.hpp"

namespace num {

    Integer operator+(Integer int1, const Integer &int2) {
        Integer result(int1);
        result += int2;
        return result;
    }

    Integer operator+=(Integer &int1, const Integer &int2) {
        if (int1.m_is_positive and int2.m_is_positive) {
            int1.m_storage += int2.m_storage;
        } else if (int1.m_is_positive and !int2.m_is_positive) {
            if (int1.m_storage < int2.m_storage) {
                // Idea is: 2 - 5 = - (5 - 2)
                int1.m_is_positive = false;
                int1.m_storage = int2.m_storage - int1.m_storage;
            } else {
                int1.m_storage -= int2.m_storage;
            }
        } else if (!int1.m_is_positive and int2.m_is_positive) {
            if (int1.m_storage < int2.m_storage) {
                // Idea is: - 2 + 5 = 5 - 2
                int1.m_is_positive = true;
                int1.m_storage = int2.m_storage - int1.m_storage;
            } else {
                // Idea is: - 5 + 2 = - (5 - 2)
                int1.m_storage -= int2.m_storage;
            }
        } else { //!int1.m_is_positive and !int2.m_is_positive
            // Idea is: - 5 - 2 = - (5 + 2)
            int1.m_storage += int2.m_storage;
        }
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

        uint128 dec1_large_storage, dec2_large_storage;
        if (SCALING_DELTA > 0) {
            dec1_large_storage = dec1.m_storage;
            dec2_large_storage = (static_cast<uint128> (dec2.m_storage)) << SCALING_DELTA;
        } else if (SCALING_DELTA < 0) {
            dec1_large_storage = (static_cast<uint128> (dec1.m_storage)) << -SCALING_DELTA;
            dec2_large_storage = dec2.m_storage;
        } else {
            dec1_large_storage = dec1.m_storage;
            dec2_large_storage = dec2.m_storage;
        }

        if (dec1.m_is_positive and dec2.m_is_positive) {
            dec1_large_storage += dec2_large_storage;
        } else if (dec1.m_is_positive and !dec2.m_is_positive) {
            if (dec1_large_storage < dec2_large_storage) {
                // Idea is: 2 - 5 = - (5 - 2)
                dec1.m_is_positive = false;
                dec1_large_storage = dec2_large_storage - dec2_large_storage;
            } else {
                dec1_large_storage -= dec2_large_storage;
            }
        } else if (!dec1.m_is_positive and dec2.m_is_positive) {
            if (dec1_large_storage < dec2_large_storage) {
                // Idea is: - 2 + 5 = 5 - 2
                dec1.m_is_positive = true;
                dec1_large_storage = dec2_large_storage - dec1_large_storage;
            } else {
                // Idea is: - 5 + 2 = - (5 - 2)
                dec1_large_storage -= dec2_large_storage;
            }
        } else { //!int1.m_is_positive and !int2.m_is_positive
            // Idea is: - 5 - 2 = - (5 + 2)
            dec1_large_storage += dec2_large_storage;
        }

        if (SCALING_DELTA < 0) {
            dec1.m_storage = dec1_large_storage >> -SCALING_DELTA;
        } else {
            dec1.m_storage = dec1_large_storage;
        }
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
        return dec1 += temp;
    }

}