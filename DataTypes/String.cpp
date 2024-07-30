#include "String.hpp"

namespace dat {

    const uint64 String::MAX_LENGTH = ULLONG_MAX;

    String::String(const std::string &value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                        nullptr), m_storage(value.substr(0, String::MAX_LENGTH)) {};

    String::String(const dat::String &&other) noexcept: DataType(std::move(other)), m_storage(other.m_storage) {}

    void String::print(std::ostream &os) const {
        os << m_storage;
    }

    String String::copy(const String &other) {
        return String(other.m_storage);
    }

    String String::cast(const Boolean &other) {
        switch (other.m_storage) {
            case Boolean::TRUE:
                return String("true");
            case Boolean::FALSE:
                return String("false");
            default:
                return String("neutral");
        }
    }

    String String::cast(const Integer &other) {
        return String(other.to_string());
    }

    String String::cast(const Decimal &other) {
        return String(other.to_string());
    }

} // dat