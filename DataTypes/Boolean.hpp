#ifndef B_SHARP_BOOLEAN_HPP
#define B_SHARP_BOOLEAN_HPP

namespace dat {
    class Boolean;
}

#include "DataType.hpp"
#include "Boolean.hpp"
#include "Integer.hpp"
#include "Decimal.hpp"
#include "String.hpp"
//#include "Utility.hpp"

namespace dat {

    typedef std::variant<Boolean, Integer, Decimal, String> VariantTypes;

    class Boolean : public DataType {

        friend class Integer;
        friend class Decimal;
        friend class String;

        enum TriState: char {
            TRUE = 1, FALSE = 0, NEUTRAL = -1
        };

        TriState m_storage;

        explicit Boolean(const Boolean&);
        explicit Boolean(const Integer&);
        explicit Boolean(const Decimal&);
        explicit Boolean(const String&);

        explicit Boolean(TriState);
        explicit Boolean(bool);

    public:

        Boolean() = delete;
        Boolean(const Boolean&&) noexcept;
        explicit Boolean(const std::string&);

        static Boolean copy(const Boolean& );
        static Boolean cast(const Integer&);
        static Boolean cast(const Decimal&);
        static Boolean cast(const String&);
        static Boolean cast(const VariantTypes& );

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

#endif //B_SHARP_BOOLEAN_HPP
