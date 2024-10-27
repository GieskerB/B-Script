#include <iostream>
#include "../Number.hpp"
#include "../../Error/Error.hpp"

#include "../Boolean.hpp"
#include "../Integer.hpp"
#include "../Decimal.hpp"
#include "../String.hpp"
#include "../Utility.hpp"

namespace dat {

    VariantTypes String::operator+(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // String + Boolean -> String + String = String
            }
            case 1: /* === Integer === */ {
                // String + Integer = String + String = String
            }
            case 2: /* === Decimal === */ {
                // String + Decimal -> String + String = String
            }
            case 3: /* === String === */ {
                // String + String = String
                const auto& right = std::get<String>(right_variant);
//                auto temp = m_storage.append(right.m_storage);
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
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

    Boolean String::operator<( const VariantTypes& other) const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator>( const VariantTypes& other) const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator<=( const VariantTypes& other) const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator>=( const VariantTypes& other) const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator==( const VariantTypes& other) const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator!=( const VariantTypes& other) const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator&&( const VariantTypes& other) const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
    Boolean String::operator||( const VariantTypes& other) const{
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }
}
