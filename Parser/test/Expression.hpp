#ifndef B_SHARP_EXPRESSION_HPP
#define B_SHARP_EXPRESSION_HPP

#include "Statement.hpp"
#include "../../Lexer/Token.hpp"

class Expression : public Statement {
public:
    Expression() = delete;
    virtual ~Expression() = default;
    explicit Expression(const NodeType &);
};

class UnaryExpression : public Expression {
private:
    lex::Token m_operator;
    std::shared_ptr<Expression> m_expression;

public:
    UnaryExpression() = delete;
    ~UnaryExpression() override = default;
    UnaryExpression(lex::Token, const std::shared_ptr<Expression> &);
};

class BinaryExpression : public Expression {
public:
    const lex::Token c_operator;
    const std::shared_ptr<Expression> c_left, c_right;

    BinaryExpression() = delete;
    ~BinaryExpression() override = default;
    BinaryExpression(const std::shared_ptr<Expression> &, lex::Token, const std::shared_ptr<Expression> &);
};

class Identifier : public Expression {
private:
    lex::Token m_symbol;

public:
    Identifier() = delete;
    ~Identifier() override = default;
    explicit Identifier(lex::Token);
};


class Literal : public Expression {
private:
    std::string m_value, m_expected_type;

public:
    Literal() = delete;
    ~Literal() override = default;
    explicit Literal(std::string);
    Literal(std::string,std::string);
};

#endif //B_SHARP_EXPRESSION_HPP
