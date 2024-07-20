#include "DataTypes.hpp"

namespace dat {

    Character::Character(char value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION, nullptr,
                                            DataTypeType::CHARACTER), m_storage(value & 0b1111111) {}


}