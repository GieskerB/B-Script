#include "String.hpp"

namespace dat {

    String::String(const std::string&): DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION, nullptr){};

    String::String(const dat::String && other) noexcept : DataType(std::move(other)){}

    void String::print(std::ostream &os) const {

    }
} // dat