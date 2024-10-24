#include "Expression.hpp"

#include <utility>

Expression::Expression(const NodeType &node_type) : Statement(node_type) {}

UnaryExpression::UnaryExpression(lex::Token left, const std::shared_ptr<Expression> &right) : Expression(
        NodeType::UNARY), m_operator(std::move(left)), m_expression(right) {}

BinaryExpression::BinaryExpression(const std::shared_ptr<Expression> &left, lex::Token op,
                                   const std::shared_ptr<Expression> &right) : Expression(NodeType::BINARY),
                                                                               c_left(left), c_operator(std::move(op)),
                                                                               c_right(right) {}

Identifier::Identifier(lex::Token symbol) : Expression(VARIABLE_ACCESS), m_symbol(std::move(symbol)) {}

Literal::Literal(std::string value) : Expression(NodeType::VALUE), m_value(std::move(value)){}
Literal::Literal(std::string value,std::string expect) : Expression(NodeType::VALUE), m_value(std::move(value)), m_expected_type(std::move(expect)){}
