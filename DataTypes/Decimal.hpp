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

        unsigned char c_SCALING_FACTOR;

        static std::pair<std::string, std::string> slip(const std::string &);
        void fit_string(std::pair<std::string, std::string> &);
        bool has_decimal_places() const;

    public:
        Decimal() = delete;
        Decimal(const Decimal &) = delete;
        Decimal(const Decimal &&) noexcept ;
        explicit Decimal(std::string, Size = INTEGER, unsigned char = 16);

        static Decimal copy(const Decimal& other);
        static Decimal cast(const Boolean& other, unsigned char scaling_factor);
        static Decimal cast(const Integer& other, unsigned char scaling_factor);

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
