#ifndef B_SHARP_STRING_HPP
#define B_SHARP_STRING_HPP

namespace dat {
    class String;
}

#include <string>
#include "DataType.hpp"
#include "Boolean.hpp"
#include "Integer.hpp"
#include "Decimal.hpp"
#include "String.hpp"

namespace dat {

    typedef std::variant<Boolean, Integer, Decimal, String> VariantTypes;

    class String : public DataType {
        static const uint64 MAX_LENGTH;
        std::string m_storage;

    public:

        String() = delete;
        String(const String&);
        explicit String(const Boolean&);
        explicit String(const Integer&);
        explicit String(const Decimal&);
        explicit String(const std::string&);

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

#endif //B_SHARP_STRING_HPP
