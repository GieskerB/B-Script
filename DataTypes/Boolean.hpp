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

        enum class TriState: char {
            TRUE = 1, FALSE = 0, NEUTRAL = -1
        };

        TriState m_storage;

        Boolean(TriState);
        Boolean(bool);


    public:

        static const std::string TRUE;
        static const std::string FALSE;
        static const std::string NEUTRAL;

        Boolean() = delete;
        Boolean(const Boolean&) = default;
        explicit Boolean(const std::string &);
        explicit Boolean(const Integer&);
        explicit Boolean(const Decimal&);
        explicit Boolean(const String&);

        [[nodiscard]] std::string to_string() const;
        void print(std::ostream &os) const override;

        operator Integer() const;
        operator Decimal() const;
        operator String() const;

        Boolean operator+(const Boolean &) const;
        Boolean operator-(const Boolean &) const;
        Boolean operator*(const Boolean &) const;
        Boolean operator/(const Boolean &) const;

        Boolean operator+() const;
        Boolean operator-() const;
        Boolean operator!() const;

        Boolean operator<(const Boolean&) const;
        Boolean operator>(const Boolean&) const;
        Boolean operator<=(const Boolean&) const;
        Boolean operator>=(const Boolean&) const;
        Boolean operator==(const Boolean&) const;
        Boolean operator!=(const Boolean&) const;
        Boolean operator&&(const Boolean&) const;
        Boolean operator||(const Boolean&) const;
    };

} // dat

#endif //B_SHARP_BOOLEAN_HPP
