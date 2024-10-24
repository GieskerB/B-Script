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

//    String::String(const dat::String &&other) noexcept: DataType(std::move(other)), m_storage(other.m_storage) {}

    void String::print(std::ostream &os) const {
        os << m_storage;
    }

    String String::cast(const Boolean &other) {
        return String(other);
    }
    String String::cast(const dat::Integer & other) {
        return String(other);
    }
    String String::cast(const dat::Decimal & other) {
        return String(other);
    }
    String String::copy(const dat::String & other) {
        return {other};
    }


    String String::cast(const VariantTypes &other) {
        switch (other.index()) {
            case 0 :
                return String::cast(std::get<Boolean>(other));
            case 1 :
                return String::cast(std::get<Integer>(other));
            case 2 :
                return String::cast(std::get<Decimal>(other));
            case 3 :
                return String::copy(std::get<String>(other));
            default:
                throw std::runtime_error("Error in Integer cast: Unexpected DataType");
        }
    }

} // dat