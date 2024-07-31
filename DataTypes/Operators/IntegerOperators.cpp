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
    * All Operators for Integer 'op' ***
    * - Integer 'op' Boolean will be changed to Boolean 'op' Integer
    */

    VariantTypes Integer::operator+(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = (std::get<Integer>(other));
                auto result = storage_addition(copy.m_storage, other_integer.m_storage, copy.m_is_positive,
                                               other_integer.m_is_positive);
                copy.m_storage = result.first;
                copy.m_is_positive = result.second;
                copy.clap_to_size();
                return copy;
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                Decimal casted_decimal = Decimal::cast(*this, other_decimal.c_SCALING_FACTOR);
                return casted_decimal + std::move(other_decimal);
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");

        }
    }

    VariantTypes Integer::operator-(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                Integer other_integer = Integer::copy(std::get<Integer>(other));
                other_integer.m_is_positive = !other_integer.m_is_positive;
                return copy + std::move(other_integer);
            }
            case 2: /* === Decimal === */ {
                Decimal other_decimal = Decimal::copy(std::get<Decimal>(other));
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

    VariantTypes Integer::operator*(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                // neg times neg = pos
                copy.m_is_positive ^= ~other_integer.m_is_positive;
                copy.m_storage *= other_integer.m_storage;
                copy.clap_to_size();
                return copy;
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const auto &casted_decimal = Decimal::cast(*this, other_decimal.c_SCALING_FACTOR);
                return casted_decimal * std::move(other_decimal);
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    VariantTypes Integer::operator/(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                if (other_integer.is_zero()) {
                    throw err::RuntimeError(other_integer.m_position_start, other_integer.m_position_end,
                                            "Division by 0 is not allowed!", *other_integer.p_context);
                }
                // neg times neg = pos
                copy.m_is_positive ^= ~other_integer.m_is_positive;

                copy.m_storage /= other_integer.m_storage;

                copy.clap_to_size();
                return copy;
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                Decimal casted_decimal = Decimal::cast(*this, other_decimal.c_SCALING_FACTOR);
                return casted_decimal / std::move(other_decimal);
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }


    VariantTypes Integer::operator+() const{
        return Integer::copy(*this);
    }
    VariantTypes Integer::operator-() const{
        auto copy = Integer::copy(*this);
        copy.invert();
        return copy;
    }
    VariantTypes Integer::operator!() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    // TODO ACHTUNG pos vs. neg !

    Boolean Integer::operator<( const VariantTypes& other){
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto & other_integer = std::get<Integer>(other);
                return Boolean(m_storage < other_integer.m_storage);
            }
            case 2: /* === Decimal === */ {
                const auto & other_decimal = std::get<Decimal>(other);
                if(copy.m_is_positive != other_decimal.m_is_positive) {
                    return Boolean(false);
                }
                return Boolean(m_storage < other_decimal.m_storage);
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    Boolean Integer::operator>( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Integer::operator<=( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Integer::operator>=( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Integer::operator==( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Integer::operator!=( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Integer::operator&&( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean Integer::operator||( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    
}

