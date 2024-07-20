#include "DataTypes.hpp"

namespace dat {

    Boolean::Boolean(bool value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION, nullptr,
                                            DataTypeType::BOOLEAN), m_storage(value) {}

}