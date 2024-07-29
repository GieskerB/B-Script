#include <iostream>
#include "../Number.hpp"
#include "../../Error/Error.hpp"

#include "../Boolean.hpp"
#include "../Integer.hpp"
#include "../Decimal.hpp"
#include "../String.hpp"
#include "../Utility.hpp"

/*
 * All operators are commutative. Therefor A+B = B+A.
 * There are currently 4 Operators [Boolean, Integer, Decimal, String]
 * This ordner denotes the direction of implementation:
 * e.g. I'll implement Boolean + String, but if String + Boolean is called, I simply "calculate" Boolean + String!
 */

namespace dat {
/*
 * All Operators for Decimal 'op' ***
 * - Decimal 'op' Boolean will be changed to Boolean 'op' Decimal
 * - Decimal 'op' Integer will be changed to Integer 'op' Decimal
 */

    VariantTypes Decimal::operator+(const VariantTypes &other) const {
        Decimal copy = Decimal::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                return other_integer + std::move(copy);
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const char SCALING_DELTA = static_cast<char>(copy.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);

                auto shifted_storage = shift_to_equal_size(copy.m_storage, other_decimal.m_storage, SCALING_DELTA);

                auto result_shifted = storage_addition(shifted_storage.first, shifted_storage.second,
                                                       copy.m_is_positive,
                                                       other_decimal.m_is_positive);

                copy.m_storage = unshift_form_equal_size(result_shifted.first, SCALING_DELTA);
                copy.m_is_positive = result_shifted.second;
                copy.clap_to_size();
                return copy;
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    VariantTypes Decimal::operator-(const VariantTypes &other) const {
        Decimal copy = Decimal::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                return other_integer - std::move(copy);
            }
            case 2: /* === Decimal === */ {
                auto other_decimal = Decimal::copy(std::get<Decimal>(other));
                other_decimal.m_is_positive = !other_decimal.m_is_positive;
                return copy + std::move(other_decimal);
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    VariantTypes Decimal::operator*(const VariantTypes &other) const {
        Decimal copy = Decimal::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                return other_integer * std::move(copy);
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
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
                return copy;
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    VariantTypes Decimal::operator/(const VariantTypes &other) const {
        Decimal copy = Decimal::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                return other_integer * std::move(copy);
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                if (other_decimal.is_zero()) {
                    throw err::RuntimeError(other_decimal.m_position_start, other_decimal.m_position_end,
                                            "Division by 0 is not allowed!", *other_decimal.p_context);
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
                return copy;
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }


    VariantTypes Decimal::operator+() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    VariantTypes Decimal::operator-() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    VariantTypes Decimal::operator!() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    Boolean Decimal::operator<( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Decimal::operator>( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Decimal::operator<=( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Decimal::operator>=( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Decimal::operator==( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Decimal::operator!=( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Decimal::operator&&( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Decimal::operator||( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    
}
