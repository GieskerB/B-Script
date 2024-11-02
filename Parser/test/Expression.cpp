#include "Expression.hpp"

#include <utility>

Expression::Expression(const NodeType &node_type) : Statement(node_type) {}

UnaryExpression::UnaryExpression(lex::Token left, const std::shared_ptr<Expression> &right) : Expression(
        NodeType::UNARY), c_operator(std::move(left)), c_right(right) {}

BinaryExpression::BinaryExpression(const std::shared_ptr<Expression> &left, lex::Token op,
                                   const std::shared_ptr<Expression> &right) : Expression(NodeType::BINARY),
                                                                               c_left(left), c_operator(std::move(op)),
                                                                               c_right(right) {}

ValueExpression::ValueExpression(lex::Token symbol) : Expression(VALUE), c_symbol(std::move(symbol)) {}
