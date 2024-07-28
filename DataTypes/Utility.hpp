#ifndef B_SHARP_UTILITY_HPP
#define B_SHARP_UTILITY_HPP

#include <variant>
#include <string>

#include "Boolean.hpp"
#include "Integer.hpp"
#include "Decimal.hpp"
#include "String.hpp"

namespace dat {

    typedef std::variant<Boolean, Integer, Decimal, String> VariantTypes;

    class Utility {

    public:
        static VariantTypes create_form_key(const std::string &, short);

    };
    std::ostream & operator<<(std::ostream &, const VariantTypes&);

    VariantTypes operator+(const VariantTypes&, const VariantTypes&);
    VariantTypes operator-(const VariantTypes&, const VariantTypes&);
    VariantTypes operator*(const VariantTypes&, const VariantTypes&);
    VariantTypes operator/(const VariantTypes&, const VariantTypes&);

} // dat

#endif //B_SHARP_UTILITY_HPP
