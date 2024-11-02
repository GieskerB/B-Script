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
public:
    const lex::Token c_operator;
    const std::shared_ptr<Expression> c_right;

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

class ValueExpression : public Expression {
public:
    const lex::Token c_symbol;

    ValueExpression() = delete;
    ~ValueExpression() override = default;
    explicit ValueExpression(lex::Token);
};



#endif //B_SHARP_EXPRESSION_HPP
