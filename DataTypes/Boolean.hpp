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

        bool m_storage;

    public:

        Boolean() = delete;
        Boolean(const Boolean&) = delete;
        Boolean(const Boolean&&) noexcept;

        explicit Boolean(bool);

        static Boolean copy(const Boolean& other);

        static Boolean cast(const Integer& other);
        static Boolean cast(const Decimal& other);
        static Boolean cast(const String& other);

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

#endif //B_SHARP_BOOLEAN_HPP
