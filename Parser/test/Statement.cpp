#include "Statement.hpp"

Statement::Statement(const NodeType &type): c_type(type) {}

NodeType Statement::get_type() const {
    return c_type;
}
