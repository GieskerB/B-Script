#include <iostream>
#include "Number.hpp"
#include "../Error/Error.hpp"

#include "Boolean.hpp"
#include "Integer.hpp"
#include "Decimal.hpp"
#include "String.hpp"

/*
 * All operators are commutative. Therefor A+B = B+A.
 * There are currently 4 Operators [Boolean, Integer, Decimal, String]
 * This ordner denotes the direction of implementation:
 * e.g. I'll implment Boolean + String, but if String + Boolean is called, I simply "calculate" Boolean + String!
 */

namespace dat {

    std::pair<uint128, bool>
    storage_addition(uint128 storage1, const uint128 storage2, bool is_positive1, const bool is_positive2) {
        if ((is_positive1 and is_positive2) or (!is_positive1 and !is_positive2)) {
            // Idea is: +5 + 2 = +(5 + 2)
            // And: -5 - 2 = -(5 + 2)
            storage1 += storage2;
        } else if (is_positive1) { // 1 is pos but 2 is neg
            if (storage1 < storage2) {
                // Idea is: 2 - 5 = - (5 - 2)
                is_positive1 = false;
                storage1 = storage2 - storage2;
            } else {
                storage1 -= storage2;
            }
        } else { // 1 ist neg and 2 is pos
            if (storage1 < storage2) {
                // Idea is: - 2 + 5 = 5 - 2
                is_positive1 = true;
                storage1 = storage2 - storage1;
            } else {
                // Idea is: - 5 + 2 = - (5 - 2)
                storage1 -= storage2;
            }
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

    /*
     * All Operators for Boolean 'op' ***
     */

    std::shared_ptr<DataType> Boolean::operator+(const DataType &other) {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    std::shared_ptr<DataType> Boolean::operator-(const DataType &other) {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    std::shared_ptr<DataType> Boolean::operator*(const DataType &other) {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    std::shared_ptr<DataType> Boolean::operator/(const DataType &other) {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    /*
     * All Operators for Integer 'op' ***
     * - Integer 'op' Boolean will be changed to Boolean 'op' Integer
     */

    std::shared_ptr<DataType> Integer::operator+(const DataType &other) {
        Integer copy = Integer(*this);
        if (typeid(other) == typeid(Boolean)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else if (typeid(other) == typeid(Integer)) {
            auto other_integer = dynamic_cast<const Integer &>(other);
            auto result = storage_addition(copy.m_storage, other_integer.m_storage, copy.m_is_positive,
                                           other_integer.m_is_positive);
            copy.m_storage = result.first;
            copy.m_is_positive = result.second;
            copy.clap_to_size();
            return std::make_shared<Integer>(copy);
        } else if (typeid(other) == typeid(Decimal)) {
            auto other_decimal = dynamic_cast<const Decimal &>(other);
            Decimal casted_decimal(*this, other_decimal.c_SCALING_FACTOR);
            return casted_decimal + other_decimal;
        } else if (typeid(other) == typeid(String)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else {
            throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    std::shared_ptr<DataType> Integer::operator-(const DataType &other) {
        Integer copy = Integer(*this);
        if (typeid(other) == typeid(Boolean)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else if (typeid(other) == typeid(Integer)) {
            auto other_integer = dynamic_cast<const Integer &>(other);
            other_integer.m_is_positive = !other_integer.m_is_positive;
            return copy + other_integer;
        } else if (typeid(other) == typeid(Decimal)) {
            auto other_decimal = dynamic_cast<const Decimal &>(other);
            other_decimal.m_is_positive = !other_decimal.m_is_positive;
            return copy + other_decimal;
        } else if (typeid(other) == typeid(String)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else {
            throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    std::shared_ptr<DataType> Integer::operator*(const DataType &other) {
        Integer copy = Integer(*this);
        if (typeid(other) == typeid(Boolean)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else if (typeid(other) == typeid(Integer)) {
            auto other_integer = dynamic_cast<const Integer &>(other);
            // neg times neg = pos
            copy.m_is_positive ^= ~other_integer.m_is_positive;
            copy.m_storage *= other_integer.m_storage;
            copy.clap_to_size();
            return std::make_shared<Integer>(copy);
        } else if (typeid(other) == typeid(Decimal)) {
            auto other_decimal = dynamic_cast<const Decimal &>(other);
            Decimal casted_decimal(*this, other_decimal.c_SCALING_FACTOR);
            return casted_decimal * other_decimal;
        } else if (typeid(other) == typeid(String)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else {
            throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    std::shared_ptr<DataType> Integer::operator/(const DataType &other) {
        Integer copy = Integer(*this);
        if (typeid(other) == typeid(Boolean)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else if (typeid(other) == typeid(Integer)) {
            auto other_integer = dynamic_cast<const Integer &>(other);
            if(other_integer.is_zero()) {
                throw err::RuntimeError(other_integer.m_position_start, other_integer.m_position_end,"Division by 0 is not allowed!",*other_integer.p_context);
            }
            // neg times neg = pos
            copy.m_is_positive ^= ~other_integer.m_is_positive;

            copy.m_storage /= other_integer.m_storage;

            copy.clap_to_size();
            return std::make_shared<Integer>(copy);
        } else if (typeid(other) == typeid(Decimal)) {
            auto other_decimal = dynamic_cast<const Decimal &>(other);
            Decimal casted_decimal(*this, other_decimal.c_SCALING_FACTOR);
            return casted_decimal / other_decimal;
        } else if (typeid(other) == typeid(String)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else {
            throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    /*
     * All Operators for Decimal 'op' ***
     * - Decimal 'op' Boolean will be changed to Boolean 'op' Decimal
     * - Decimal 'op' Integer will be changed to Integer 'op' Decimal
     */

    std::shared_ptr<DataType> Decimal::operator+(const DataType &other) {
        Decimal copy = Decimal(*this);
        if (typeid(other) == typeid(Boolean)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else if (typeid(other) == typeid(Integer)) {
            auto other_integer = dynamic_cast<const Integer &>(other);
            return other_integer + copy;
        } else if (typeid(other) == typeid(Decimal)) {
            auto other_decimal = dynamic_cast<const Decimal &>(other);
            const char SCALING_DELTA = static_cast<char>(copy.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);

            auto shifted_storage = shift_to_equal_size(copy.m_storage, other_decimal.m_storage, SCALING_DELTA);

            auto result_shifted = storage_addition(shifted_storage.first, shifted_storage.second, copy.m_is_positive,
                                                   other_decimal.m_is_positive);

            copy.m_storage = unshift_form_equal_size(result_shifted.first, SCALING_DELTA);
            copy.m_is_positive = result_shifted.second;
            copy.clap_to_size();
            return std::make_shared<Decimal>(copy);
        } else if (typeid(other) == typeid(String)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else {
            throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    std::shared_ptr<DataType> Decimal::operator-(const DataType &other) {
        Decimal copy = Decimal(*this);
        if (typeid(other) == typeid(Boolean)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else if (typeid(other) == typeid(Integer)) {
            auto other_integer = dynamic_cast<const Integer &>(other);
            return other_integer - copy;
        } else if (typeid(other) == typeid(Decimal)) {
            auto other_decimal = dynamic_cast<const Decimal &>(other);
            other_decimal.m_is_positive = !other_decimal.m_is_positive;
            return copy + other_decimal;
        } else if (typeid(other) == typeid(String)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else {
            throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    std::shared_ptr<DataType> Decimal::operator*(const DataType &other) {
        Decimal copy = Decimal(*this);
        if (typeid(other) == typeid(Boolean)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else if (typeid(other) == typeid(Integer)) {
            auto other_integer = dynamic_cast<const Integer &>(other);
            return other_integer * copy;
        } else if (typeid(other) == typeid(Decimal)) {
            auto other_decimal = dynamic_cast<const Decimal &>(other);
            const char SCALING_DELTA = static_cast<char>(copy.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);

            auto shifted_storage = shift_to_equal_size(copy.m_storage, other_decimal.m_storage, SCALING_DELTA);

            copy.m_is_positive ^= ~other_decimal.m_is_positive;

            shifted_storage.first *= shifted_storage.second;

            if (SCALING_DELTA > 0) {
                shifted_storage.first >>= copy.c_SCALING_FACTOR;
            } else {
                shifted_storage.first >>= other_decimal.c_SCALING_FACTOR;
            }

            copy.m_storage = unshift_form_equal_size(shifted_storage.first, SCALING_DELTA);
            copy.clap_to_size();
            return std::make_shared<Decimal>(copy);
        } else if (typeid(other) == typeid(String)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else {
            throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    std::shared_ptr<DataType> Decimal::operator/(const DataType &other) {
        Decimal copy = Decimal(*this);
        if (typeid(other) == typeid(Boolean)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else if (typeid(other) == typeid(Integer)) {
            auto other_integer = dynamic_cast<const Integer &>(other);
            return other_integer * copy;
        } else if (typeid(other) == typeid(Decimal)) {
            const Decimal& other_decimal = dynamic_cast<const Decimal &>(other);
            if(other_decimal.is_zero()) {
                throw err::RuntimeError(other_decimal.m_position_start, other_decimal.m_position_end,"Division by 0 is not allowed!",*other_decimal.p_context);
            }

            const char SCALING_DELTA = static_cast<char>(copy.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);

            auto shifted_storage = shift_to_equal_size(copy.m_storage, other_decimal.m_storage, SCALING_DELTA);

            copy.m_is_positive ^= ~other_decimal.m_is_positive;

            if (SCALING_DELTA > 0) {
                shifted_storage.first <<= copy.c_SCALING_FACTOR;
            } else {
                shifted_storage.first <<= other_decimal.c_SCALING_FACTOR;
            }

            shifted_storage.first /= shifted_storage.second;

            copy.m_storage = unshift_form_equal_size(shifted_storage.first, SCALING_DELTA);
            copy.clap_to_size();
            return std::make_shared<Decimal>(copy);
        } else if (typeid(other) == typeid(String)) {
            throw err::InvalidSyntaxError(m_position_start, other.get_position().second,"Operator not implemented.");
        } else {
            throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    /*
     * All Operators for String 'op' ***
     * - String 'op' Boolean will be changed to Boolean 'op' String
     * - String 'op' Integer will be changed to Integer 'op' String
     * - String 'op' Decimal will be changed to Decimal 'op' String
     */

    std::shared_ptr<DataType> String::operator+(const DataType &other) {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    std::shared_ptr<DataType> String::operator-(const DataType &other) {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    std::shared_ptr<DataType> String::operator*(const DataType &other) {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    std::shared_ptr<DataType> String::operator/(const DataType &other) {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
/*
    Integer operator+(const Integer& int1, const Integer &int2) {
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

    Integer operator-(const Integer& int1, const Integer &int2) {
        Integer result(int1);
        result -= int2;
        return result;
    }

    Integer operator-=(Integer &int1, const Integer &int2) {
        Integer temp = int2;
        temp.m_is_positive = !temp.m_is_positive;
        return int1 += temp;
    }

    Integer operator*(const Integer& int1, const Integer &int2) {
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

    Integer operator/(const Integer& int1, const Integer &int2) {
        Integer result(int1);
        result /= int2;
        return result;
    }

    Integer operator/=(Integer &int1, const Integer &int2) {
        if(int2.is_zero()) {
            throw err::RuntimeError(int2.m_position_start, int2.m_position_end,"Division by 0 is not allowed!",*int2.p_context);
        }
        // neg times neg = pos
        int1.m_is_positive ^= ~int2.m_is_positive;

        int1.m_storage /= int2.m_storage;

        int1.clap_to_size();
        return int1;
    }


    Decimal operator+(const Decimal& dec1, const Decimal &dec2) {
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

    Decimal operator-(const Decimal& dec1, const Decimal &dec2) {
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

    Decimal operator*(const Decimal& dec1, const Decimal &dec2) {
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

    Decimal operator/(const Decimal& dec1, const Decimal &dec2) {
        Decimal result(dec1);
        result /= dec2;
        return result;
    }

    Decimal operator/=(Decimal &dec1, const Decimal &dec2) {
        if(dec2.is_zero()) {
            throw err::RuntimeError(dec2.m_position_start, dec2.m_position_end,"Division by 0 is not allowed!",*dec2.p_context);
        }

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


    Decimal operator+(const Integer& int1, const Decimal & dec2) {
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
        Decimal addend(int1,dec2.c_SCALING_FACTOR);
        addend += dec2;
        int1 = Integer(addend);
        return int1;
    }
    Decimal operator+=(Decimal & dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 += addend;
        return dec1;
    }

    
    Decimal operator-(const Integer& int1, const Decimal & dec2) {
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
        Decimal addend(int1,dec2.c_SCALING_FACTOR);
        addend -= dec2;
        int1 = Integer(addend);
        return int1;
    }
    Decimal operator-=(Decimal & dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 -= addend;
        return dec1;
    }
    
    
    Decimal operator*(const Integer& int1, const Decimal & dec2) {
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
        Decimal addend(int1,dec2.c_SCALING_FACTOR);
        addend *= dec2;
        int1 = Integer(addend);
        return int1;
    }
    Decimal operator*=(Decimal & dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 *= addend;
        return dec1;
    }

    
    Decimal operator/(const Integer& int1, const Decimal & dec2) {
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
        Decimal addend(int1,dec2.c_SCALING_FACTOR);
        addend /= dec2;
        int1 = Integer(addend);
        return int1;
    }
    Decimal operator/=(Decimal & dec1, const Integer &int2) {
        Decimal addend(int2, dec1.c_SCALING_FACTOR);
        dec1 /= addend;
        return dec1;
    }*/

}