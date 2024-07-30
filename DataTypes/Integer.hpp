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
//#include "Utility.hpp"

namespace dat {

    typedef std::variant<Boolean, Integer, Decimal, String> VariantTypes;

    class Integer : public Number {

        friend class Printer;
        friend class Decimal;

        bool c_IS_SIGNED;

        void fit_string(std::string &);

    public:

        Integer() = delete;
        Integer(const Integer &)= delete;
        Integer(const Integer &&) noexcept;
        explicit Integer(std::string, Size = INTEGER, bool = false);

        static Integer copy(const Integer& other);

        static Integer cast(const Boolean& other);
        static Integer cast(const Decimal& other);
        static Integer cast(const String& other);

        [[nodiscard]] std::string to_string() const;
        void print(std::ostream& os) const override;

        VariantTypes operator+(const VariantTypes &) const;
        VariantTypes operator-(const VariantTypes &) const;
        VariantTypes operator*(const VariantTypes &) const;
        VariantTypes operator/(const VariantTypes &) const;

        VariantTypes operator+() const;
        VariantTypes operator-() const;
        VariantTypes operator!() const;

        Boolean operator<( const VariantTypes&);
        Boolean operator>( const VariantTypes&);
        Boolean operator<=( const VariantTypes&);
        Boolean operator>=( const VariantTypes&);
        Boolean operator==( const VariantTypes&);
        Boolean operator!=( const VariantTypes&);
        Boolean operator&&( const VariantTypes&);
        Boolean operator||( const VariantTypes&);

    };
} // dat

#endif
