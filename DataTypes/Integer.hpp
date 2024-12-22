#ifndef B_SHARP_INTEGER_HPP
#define B_SHARP_INTEGER_HPP

namespace dat {
    class Integer;
}

#include <string>
#include <variant>
#include "Number.hpp"
#include "Boolean.hpp"
#include "Integer.hpp"
#include "Decimal.hpp"
#include "String.hpp"

namespace dat {

    typedef std::variant<Boolean, Integer, Decimal, String> VariantTypes;

    class Integer : public Number {
        friend class Boolean;
        friend class Decimal;
        friend class String;

        bool c_SIGNED;


    public:
        Integer() = delete;
        Integer(const Integer&) = default;
        explicit Integer(std::string, Size = Size::LONG, bool = true);
        explicit Integer(const Boolean&);
        explicit Integer(const Decimal&);
        explicit Integer(const String&);

        [[nodiscard]] std::string to_string() const;
        void print(std::ostream& os) const override;

        operator Boolean() const;
        operator Decimal() const;
        operator String() const;

        Integer operator+(const Integer &) const;
        Integer operator-(const Integer &) const;
        Integer operator*(const Integer &) const;
        Integer operator/(const Integer &) const;

        Integer operator+() const;
        Integer operator-() const;
        Integer operator!() const;

        Boolean operator<( const Integer&) const;
        Boolean operator>( const Integer&) const;
        Boolean operator<=( const Integer&) const;
        Boolean operator>=( const Integer&) const;
        Boolean operator==( const Integer&) const;
        Boolean operator!=( const Integer&) const;
        Boolean operator&&( const Integer&) const;
        Boolean operator||( const Integer&) const;

    };
} // dat

#endif
