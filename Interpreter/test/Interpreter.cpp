#include "Interpreter.hpp"
#include "../../Parser/test/Expression.hpp"


dat::VariantTypes evaluate_program(const Program& program) {
    std::shared_ptr<dat::VariantTypes> type_ptr;
    for(const auto& statement: program.statements()) {
        type_ptr = std::make_shared<dat::VariantTypes>(evaluate_statement(statement, program.context()));
    }
    return *type_ptr;
}

dat::VariantTypes eval_unary_node(const UnaryExpression& un_expr, const itp::Context& context) {
    auto right_variant = evaluate_statement(un_expr.c_right,context);
    switch (un_expr.c_operator.c_type) {
        case lex::TokenType::PLUS:
            return +right_variant;
        case lex::TokenType::MINUS:
            return -right_variant;
        case lex::TokenType::LOGIC_NOT:
            return !right_variant;
        default:
            throw std::runtime_error("Unexpected token in Interpreter eval_unary_node()!");
    }
}

dat::VariantTypes eval_binary_node(const BinaryExpression& bin_expr, const itp::Context& context) {
    auto left_value = evaluate_statement(bin_expr.c_left, context);
    auto right_value = evaluate_statement(bin_expr.c_right, context);
    switch (bin_expr.c_operator.c_type) {
        case lex::TokenType::PLUS:
            return left_value + right_value;
        case lex::TokenType::MINUS:
            return left_value - right_value;
        case lex::TokenType::MULTIPLY:
            return left_value * right_value;
        case lex::TokenType::DIVIDE:
            return left_value / right_value;
        case lex::TokenType::LESS_THEN:
            return left_value < right_value;
        case lex::TokenType::LESS_THEN_OR_EQUALS:
            return left_value <= right_value;
        case lex::TokenType::GREATER_THEN:
            return left_value > right_value;
        case lex::TokenType::GREATER_THEN_OR_EQUALS:
            return left_value >= right_value;
        case lex::TokenType::DOUBLE_EQUALS:
            return left_value == right_value;
        case lex::TokenType::NOT_EQUALS:
            return left_value != right_value;
        case lex::TokenType::LOGIC_AND:
            return left_value && right_value;
        case lex::TokenType::LOGIC_OR:
            return left_value || right_value;
        default:
            throw std::runtime_error("Unexpected token in Interpreter eval_binary_node()!");
    }
}

dat::VariantTypes eval_value_node(const ValueExpression&  val_expr, const itp::Context& context) {
    if (val_expr.c_symbol.c_type == lex::TokenType::VALUE) {
        auto result = dat::create_datatype_form_string(val_expr.c_symbol);
//        auto start = val_expr.get_start_position();
//        auto end = val_expr.get_end_position();
//        auto set_position = [&](auto &datatype) {
//            datatype.set_position(start, end);
//        };
//        auto set_context = [&](auto &datatype) {
//            datatype.set_context(context);
//        };
//        std::visit(set_position, result);
//        std::visit(set_context, result);
        return result;
    } else {
        throw std::runtime_error("Unexpected token in Interpreter visit_value_node()!");
    }
}

dat::VariantTypes evaluate_statement(const std::shared_ptr<Statement>& statement,const itp::Context& context) {
    dat::VariantTypes value = dat::Integer("0");
    switch (statement->get_type()) {
        case PROGRAM:
            value = evaluate_program(*std::dynamic_pointer_cast<Program>(statement));
            break;
        case UNARY:
            value = eval_unary_node(*std::dynamic_pointer_cast<UnaryExpression>(statement),context);
            break;
        case BINARY:
            value = eval_binary_node(*std::dynamic_pointer_cast<BinaryExpression>(statement), context);
            break;
        case VARIABLE_ACCESS:
            break;
        case VARIABLE_ASSIGN:
            break;
        case VALUE:
            value = eval_value_node(*std::dynamic_pointer_cast<ValueExpression>(statement),context);
            break;
    }
    return value;
}