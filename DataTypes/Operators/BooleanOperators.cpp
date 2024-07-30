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

    VariantTypes Boolean::operator+(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */{
                const auto &other_boolean = std::get<Boolean>(other);
                const auto &copy_cast = Integer::cast(copy);
                return other_boolean + std::move(copy_cast);
            }
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                const auto &copy_cast = Integer::cast(copy);
                return other_integer + std::move(copy_cast);
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const auto &copy_cast = Integer::cast(copy);
                return other_decimal + std::move(copy_cast);
            }
            case 3: /* === String === */{
                const auto &other_string = std::get<String>(other);
                const auto &copy_cast = String::cast(copy);
                return other_string + std::move(copy_cast);
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    VariantTypes Boolean::operator-(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    VariantTypes Boolean::operator*(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    VariantTypes Boolean::operator/(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    VariantTypes Boolean::operator+() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    VariantTypes Boolean::operator-() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    VariantTypes Boolean::operator!() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    Boolean Boolean::operator<( const VariantTypes& other){
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    Boolean Boolean::operator>( const VariantTypes& other){
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    Boolean Boolean::operator<=( const VariantTypes& other){
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    Boolean Boolean::operator>=( const VariantTypes& other){
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    Boolean Boolean::operator==( const VariantTypes& other){
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    Boolean Boolean::operator!=( const VariantTypes& other){
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    Boolean Boolean::operator&&( const VariantTypes& other){
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
    Boolean Boolean::operator||( const VariantTypes& other){
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            case 1: /* === Integer === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 2: /* === Decimal === */ {
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other).second,
                                              "Operators not implemented.");
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }


}
