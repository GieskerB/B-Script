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

        bool c_IS_SIGNED;

        explicit Integer(const Boolean&);
        explicit Integer(const Integer&);
        explicit Integer(const Decimal&);
        explicit Integer(const String&);

    public:

        Integer() = delete;
        Integer(const Integer &&) noexcept;
        explicit Integer(std::string, Size = Size::LONG, bool = false);

        static Integer cast(const Boolean& );
        static Integer copy(const Integer& );
        static Integer cast(const Decimal& );
        static Integer cast(const String& );
        static Integer cast(const VariantTypes & );

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

#endif
