#include "Boolean.hpp"
#include "../Error/Error.hpp"

namespace dat {

    const std::string Boolean::TRUE = "true";
    const std::string Boolean::FALSE = "false";
    const std::string Boolean::NEUTRAL = "neutral";

    Boolean::Boolean(const Integer &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                             m_storage(other.is_zero() ? TriState::FALSE : TriState::TRUE) {}

    Boolean::Boolean(const Decimal &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                             m_storage(other.is_zero() ? TriState::FALSE : TriState::TRUE) {}

    Boolean::Boolean(const String &other) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                     nullptr), m_storage(TriState::NEUTRAL) {
        throw err::RuntimeError(other.position().first, other.position().second,
                                "Casting error form String to Boolean.",
                                other.context());
    }

    Boolean::Boolean(TriState value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                nullptr), m_storage(value) {}

    Boolean::Boolean(bool value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                            nullptr), m_storage(value ? TriState::TRUE : TriState::FALSE) {}

    Boolean::Boolean(const std::string &value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                          nullptr) {
        if (value == Boolean::TRUE) {
            m_storage = TriState::TRUE;
        } else if (value == Boolean::FALSE) {
            m_storage = TriState::FALSE;
        } else if (value == Boolean::NEUTRAL) {
            m_storage = TriState::NEUTRAL;
        } else {
            throw std::runtime_error("Invalid boolean format: " + value);
        }
    }

    std::string Boolean::to_string() const {
        switch (m_storage) {
            case TriState::TRUE:
                return Boolean::TRUE;
            case TriState::FALSE:
                return Boolean::FALSE;
            case TriState::NEUTRAL:
                return Boolean::NEUTRAL;
            default:
                throw std::runtime_error("Unknown Tri-State in Boolean::to_string");
        }
    }

    void Boolean::print(std::ostream &os) const {
        os << to_string();
    }

    Boolean::operator Integer() const {
        return Integer{*this};
    }

    Boolean::operator Decimal() const {
        return Decimal{*this};
    }

    Boolean::operator String() const {
        return String{*this};
    }

    Boolean Boolean::operator+(const Boolean &other) const {
        return static_cast<Integer>(*this) + static_cast<Integer>(other);
    }

    Boolean Boolean::operator-(const Boolean &other) const {
        return static_cast<Integer>(*this) - static_cast<Integer>(other);
    }

    Boolean Boolean::operator*(const Boolean &other) const {
        return static_cast<Integer>(*this) * static_cast<Integer>(other);
    }

    Boolean Boolean::operator/(const Boolean &) const {
        throw std::runtime_error("Binary Operator with a Boolean in the denominator is not defined!");
    }

    Boolean Boolean::operator+() const { return false; }
    Boolean Boolean::operator-() const { return false; }
    Boolean Boolean::operator!() const { return false; }

    Boolean Boolean::operator<(const Boolean &) const { return false; }
    Boolean Boolean::operator>(const Boolean &) const { return false; }
    Boolean Boolean::operator<=(const Boolean &) const { return false; }
    Boolean Boolean::operator>=(const Boolean &) const { return false; }
    Boolean Boolean::operator==(const Boolean &) const { return false; }
    Boolean Boolean::operator!=(const Boolean &) const { return false; }
    Boolean Boolean::operator&&(const Boolean &) const { return false; }
    Boolean Boolean::operator||(const Boolean &) const { return false; }


} // dat