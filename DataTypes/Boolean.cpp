#include "Boolean.hpp"

namespace dat {

    Boolean::Boolean(TriState value): DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                               nullptr), m_storage(value) {}

    Boolean::Boolean(const std::string &value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                          nullptr) {
        if (value == "true" ) {
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

    void Boolean::print(std::ostream &os) const {
        switch (m_storage) {
            case TRUE:
                os << "true";
                break;
            case FALSE:
                os << "false";
                break;
            case NEUTRAL:
                os << "neutral";
                break;
        }
    }

    Boolean Boolean::copy(const Boolean &other) {
        Boolean result(other.m_storage);
        result.m_position_start = other.m_position_start;
        result.m_position_end = other.m_position_end;
        result.p_context = other.p_context;
        return result;
    }

    Boolean Boolean::cast(const Integer &other) {
        if(other.is_zero()) {
            return Boolean(TriState::FALSE);
        } else {
            return Boolean(TriState::TRUE);
        }
    }

    Boolean Boolean::cast(const Decimal &other) {
        if(other.is_zero()) {
            return Boolean(TriState::FALSE);
        } else {
            return Boolean(TriState::TRUE);
        }
    }

} // dat