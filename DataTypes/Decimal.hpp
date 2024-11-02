#ifndef B_SHARP_DECIMAL_HPP
#define B_SHARP_DECIMAL_HPP

namespace dat {
    class Decimal;
}

#include <string>
#include "Number.hpp"
#include "Boolean.hpp"
#include "Integer.hpp"
#include "Decimal.hpp"
#include "String.hpp"

namespace dat {

    typedef std::variant<Boolean, Integer, Decimal, String> VariantTypes;

    class Decimal : public Number {
        friend class Boolean;
        friend class Integer;
        friend class String;

        uint8_t c_SCALING_FACTOR;

        static std::pair<std::string, std::string> slip(const std::string &);

    public:
        Decimal() = delete;
        Decimal(const Decimal&);
        explicit Decimal(const Boolean&);
        explicit Decimal(const Integer&);
        explicit Decimal(const String&);
        explicit Decimal(std::string, Size = Size::LONG, uint8_t = 16);

        [[nodiscard]] std::string to_string() const;
        void print(std::ostream& os) const override;

        VariantTypes operator+(const VariantTypes &) const;
        VariantTypes operator-(const VariantTypes &) const;
        VariantTypes operator*(const VariantTypes &) const;
        VariantTypes operator/(const VariantTypes &) const;

        VariantTypes operator+() const;
        VariantTypes operator-() const;
        VariantTypes operator!() const;

        Boolean operator<( const VariantTypes&) const;
        Boolean operator>( const VariantTypes&) const;
        Boolean operator<=( const VariantTypes&) const;
        Boolean operator>=( const VariantTypes&) const;
        Boolean operator==( const VariantTypes&) const;
        Boolean operator!=( const VariantTypes&) const;
        Boolean operator&&( const VariantTypes&) const;
        Boolean operator||( const VariantTypes&) const;
    };
} // dat

#endif //B_SHARP_DECIMAL_HPP
