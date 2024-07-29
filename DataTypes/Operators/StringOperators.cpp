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
 * All Operators for String 'op' ***
 * - String 'op' Boolean will be changed to Boolean 'op' String
 * - String 'op' Integer will be changed to Integer 'op' String
 * - String 'op' Decimal will be changed to Decimal 'op' String
 */

    VariantTypes String::operator+(const VariantTypes &other) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    VariantTypes String::operator-(const VariantTypes &other) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    VariantTypes String::operator*(const VariantTypes &other) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    VariantTypes String::operator/(const VariantTypes &other) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }


    VariantTypes String::operator+() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    VariantTypes String::operator-() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    VariantTypes String::operator!() const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    Boolean String::operator<( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator>( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator<=( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator>=( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator==( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator!=( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator&&( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator||( const VariantTypes& other){
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
}
