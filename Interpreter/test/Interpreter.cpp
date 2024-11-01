#include "Interpreter.hpp"
#include "../../Parser/test/Expression.hpp"

dat::VariantTypes evaluate_binary_node(const BinaryExpression& bin_expr,const itp::Context& context) {
    auto left_value = evaluate_statement(bin_expr.c_left, context);
    auto right_value = evaluate_statement(bin_expr.c_right, context);
    if (bin_expr.c_operator.c_type == lex::TokenType::PLUS) {
        return left_value + right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::MINUS) {
        return left_value - right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::MULTIPLY) {
        return left_value * right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::DIVIDE) {
        return left_value / right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::LESS_THEN) {
        return left_value < right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::LESS_THEN_OR_EQUALS) {
        return left_value <= right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::GREATER_THEN) {
        return left_value > right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::GREATER_THEN_OR_EQUALS) {
        return left_value >= right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::DOUBLE_EQUALS) {
        return left_value == right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::NOT_EQUALS) {
        return left_value != right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::LOGIC_AND) {
        return left_value && right_value;
    } else if (bin_expr.c_operator.c_type == lex::TokenType::LOGIC_OR) {
        return left_value || right_value;
    } else {
        throw std::runtime_error("Unexpected token in Interpreter visit_binary_node()!");
    }
}

dat::VariantTypes evaluate_program(const Program& program) {
    std::shared_ptr<dat::VariantTypes> type_ptr;
    for(const auto& statement: program.statements()) {
        type_ptr = std::make_shared<dat::VariantTypes>(evaluate_statement(statement, program.context()));
    }
    return *type_ptr;
}


dat::VariantTypes evaluate_statement(const std::shared_ptr<Statement>& statement,const itp::Context& context) {
    dat::VariantTypes value = dat::Integer("0");
    std::cout << (int)statement->get_type() << "---";
    switch (statement->get_type()) {
        case BINARY:
           value = evaluate_binary_node(*std::dynamic_pointer_cast<BinaryExpression>(statement), context);
            break;
        case UNARY:
            break;
        case VALUE:
            break;
        case VARIABLE_ACCESS:
            break;
        case VARIABLE_ASSIGN:
            break;
        case PROGRAM:
            break;
    }
    return value;
}