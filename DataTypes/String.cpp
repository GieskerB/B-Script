#include "String.hpp"

namespace dat {

    const uint64 String::MAX_LENGTH = ULLONG_MAX;

    String::String(const Boolean &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                           m_storage(other.to_string()) {}

    String::String(const Integer &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                           m_storage(other.to_string()) {}

    String::String(const Decimal &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                           m_storage(other.to_string()) {}

    String::String(const std::string &value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                        nullptr), m_storage(value.substr(0, String::MAX_LENGTH)) {};

    std::string String::to_string() const {
        return m_storage;
    }
    void String::print(std::ostream &os) const {
        os << m_storage;
    }

    String::operator Boolean() const {
        return Boolean{*this};
    }
    String::operator Integer() const {
        return Integer{*this};
    }
    String::operator Decimal() const {
        return Decimal{*this};
    }

    String String::operator+(const String &other) const {
        return String(std::string{"0"});
    }

    String String::operator-(const String &other) const {
        return String{std::string{"0"}};
    }

    String String::operator*(const String &other) const {
        return String{std::string{"0"}};
    }

    String String::operator/(const String &) const {
        throw std::runtime_error("Binary Operator with a Boolean in the denominator is not defined!");
    }

    String String::operator+() const { return String{std::string{"0"}}; }
    String String::operator-() const { return String{std::string{"0"}}; }
    String String::operator!() const { return String{std::string{"0"}}; }

    Boolean String::operator<(const String &) const { return false; }
    Boolean String::operator>(const String &) const { return false; }
    Boolean String::operator<=(const String &) const { return false; }
    Boolean String::operator>=(const String &) const { return false; }
    Boolean String::operator==(const String &) const { return false; }
    Boolean String::operator!=(const String &) const { return false; }
    Boolean String::operator&&(const String &) const { return false; }
    Boolean String::operator||(const String &) const { return false; }
    

} // dat