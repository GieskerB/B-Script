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


    public:
        Decimal() = delete;
        Decimal(const Decimal&) = default;
        explicit Decimal(std::string, Size = Size::LONG, uint8_t = 16);
        explicit Decimal(const Boolean&);
        explicit Decimal(const Integer&);
        explicit Decimal(const String&);

        [[nodiscard]] std::string to_string() const;
        void print(std::ostream& os) const override;

        operator Boolean() const;
        operator Integer() const;
        operator String() const;
        
        Decimal operator+(const Decimal &) const;
        Decimal operator-(const Decimal &) const;
        Decimal operator*(const Decimal &) const;
        Decimal operator/(const Decimal &) const;

        Decimal operator+() const;
        Decimal operator-() const;
        Decimal operator!() const;

        Boolean operator<( const Decimal&) const;
        Boolean operator>( const Decimal&) const;
        Boolean operator<=( const Decimal&) const;
        Boolean operator>=( const Decimal&) const;
        Boolean operator==( const Decimal&) const;
        Boolean operator!=( const Decimal&) const;
        Boolean operator&&( const Decimal&) const;
        Boolean operator||( const Decimal&) const;
    };
} // dat

#endif //B_SHARP_DECIMAL_HPP
