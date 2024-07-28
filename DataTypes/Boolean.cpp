#include "Boolean.hpp"

namespace dat {
    Boolean::Boolean(bool value) : DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION, nullptr),
                                   m_storage(value) {}

    Boolean::Boolean(const Boolean &&other) noexcept: DataType(std::move(other)), m_storage(other.m_storage) {}

    void Boolean::print(std::ostream &os) const {

    }

    Boolean Boolean::copy(const Boolean& other) {
        return Boolean(other.m_storage);
    }

} // dat