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
//#include "Utility.hpp"

namespace dat {

    typedef std::variant<Boolean, Integer, Decimal, String> VariantTypes;

    class String : public DataType {

        static const uint64 MAX_LENGTH;

        std::string m_storage;

    public:

        String() = delete;
        String(const String&) = delete;
        String(const String&&) noexcept;

        explicit String(const std::string&);

        static String copy(const String& other);

        static String cast(const Boolean& other);
        static String cast(const Integer& other);
        static String cast(const Decimal& other);

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
