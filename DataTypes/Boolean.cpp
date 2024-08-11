#include "Boolean.hpp"
#include "../Error/Error.hpp"

namespace dat {

    Boolean::Boolean(const Boolean &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                             m_storage(other.m_storage) {}

    Boolean::Boolean(const Integer &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                             m_storage(other.is_zero() ? TriState::FALSE : TriState::TRUE) {}

    Boolean::Boolean(const Decimal &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                             m_storage(other.is_zero() ? TriState::FALSE : TriState::TRUE) {}

    Boolean::Boolean(const String &other) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                     nullptr), m_storage(TriState::NEUTRAL) {
        throw err::RuntimeError(other.get_position().first, other.get_position().second,
                                "Casting error form String to Boolean.",
                                other.get_context());
    }

    Boolean::Boolean(TriState value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                nullptr), m_storage(value) {}

    Boolean::Boolean(bool value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                            nullptr), m_storage(value ? TriState::TRUE : TriState::FALSE) {}

    Boolean::Boolean(const std::string &value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                          nullptr) {
        if (value == "true") {
            m_storage = TriState::TRUE;
        } else if (value == "false") {
            m_storage = TriState::FALSE;
        } else if (value == "neutral") {
            m_storage = TriState::NEUTRAL;
        } else {
            throw std::runtime_error("Invalid boolean format: " + value);
        }
    }

    Boolean::Boolean(const Boolean &&other) noexcept: DataType(std::move(other)), m_storage(other.m_storage) {}


    Boolean Boolean::copy(const Boolean &other) {
        return Boolean(other);
    }
    Boolean Boolean::cast(const dat::Integer & other) {
        return Boolean(other);
    }
    Boolean Boolean::cast(const dat::Decimal & other) {
        return Boolean(other);
    }
    Boolean Boolean::cast(const dat::String & other) {
        return Boolean(other);
    }

    Boolean Boolean::cast(const VariantTypes &other) {
        switch (other.index()) {
            case 0 :
                return Boolean::copy(std::get<Boolean>(other));
            case 1 :
                return Boolean::cast(std::get<Integer>(other));
            case 2 :
                return Boolean::cast(std::get<Decimal>(other));
            case 3 :
                return Boolean::cast(std::get<String>(other));
            default:
                throw std::runtime_error("Error in Boolean cast: Unexpected DataType");
        }
    }


    std::string Boolean::to_string() const {
        switch (m_storage) {
            case TRUE:
                return "true";
            case FALSE:
                return "false";
            case NEUTRAL:
                return "neutral";
        }

    }

    void Boolean::print(std::ostream &os) const {
        os << to_string();
    }

} // dat