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
        friend class Boolean;
        friend class Integer;
        friend class Decimal;

        static const uint64 MAX_LENGTH;
        std::string m_storage;


    public:

        String() = delete;
        String(const String&) = default;
        explicit String(const std::string&);
        explicit String(const Boolean&);
        explicit String(const Integer&);
        explicit String(const Decimal&);

        [[nodiscard]] std::string to_string() const;
        void print(std::ostream& os) const override;

        operator Boolean() const;
        operator Integer() const;
        operator Decimal() const;

        String operator+(const String &) const;
        String operator-(const String &) const;
        String operator*(const String &) const;
        String operator/(const String &) const;

        String operator+() const;
        String operator-() const;
        String operator!() const;

        Boolean operator<( const String&) const;
        Boolean operator>( const String&) const;
        Boolean operator<=( const String&) const;
        Boolean operator>=( const String&) const;
        Boolean operator==( const String&) const;
        Boolean operator!=( const String&) const;
        Boolean operator&&( const String&) const;
        Boolean operator||( const String&) const;
    };

} // dat

#endif //B_SHARP_STRING_HPP
