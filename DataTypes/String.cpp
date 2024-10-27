#include "String.hpp"

namespace dat {

    const uint64 String::MAX_LENGTH = ULLONG_MAX;

    String::String(const Boolean &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                           m_storage(other.to_string()) {}

    String::String(const Integer &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                           m_storage(other.to_string()) {}

    String::String(const Decimal &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                           m_storage(other.to_string()) {}

    String::String(const String &other) : DataType(other.m_position_start, other.m_position_end, other.p_context),
                                          m_storage(other.m_storage) {}

    String::String(const std::string &value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION,
                                                        nullptr), m_storage(value.substr(0, String::MAX_LENGTH)) {};

    void String::print(std::ostream &os) const {
        os << m_storage;
    }

} // dat