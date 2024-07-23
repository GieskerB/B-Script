#include "Interpreter.hpp"
#include "../Error/Error.hpp"

namespace itp {


    std::shared_ptr<dat::DataType>
    Interpreter::add_numbers(std::shared_ptr<dat::DataType> &left_number,
                             const std::shared_ptr<dat::DataType> &right_number) {
        if (left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter add_numbers()!");
        }

        left_number =  left_number + right_number;

//        if (left_number->c_NUMBER_TYPE == dat::NumberType::INT and
//            right_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Integer>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Integer>(right_number);
//            *left += *right;
//            left_number = left;
//        } else if (left_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Integer>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Decimal>(right_number);
//            *left += *right;
//            left_number = left;
//        } else if (right_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Decimal>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Integer>(right_number);
//            *left += *right;
//            left_number = left;
//        } else {
//            auto left = std::dynamic_pointer_cast<dat::Decimal>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Decimal>(right_number);
//            *left += *right;
//            left_number = left;
//        }
        return left_number;
    }

    std::shared_ptr<dat::DataType>
    Interpreter::sub_numbers(std::shared_ptr<dat::DataType> &left_number,
                             const std::shared_ptr<dat::DataType> &right_number) {
        if (left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter add_numbers()!");
        }
        left_number =  left_number - right_number;

//        std::shared_ptr<dat::Number> result;
//        if (left_number->c_NUMBER_TYPE == dat::NumberType::INT and
//            right_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Integer>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Integer>(right_number);
//            result = std::make_shared<dat::Integer> (*left - *right);
//        } else if (left_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Integer>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Decimal>(right_number);
//            result = std::make_shared<dat::Decimal> (*left - *right);
//        } else if (right_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Decimal>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Integer>(right_number);
//            result = std::make_shared<dat::Decimal> (*left - *right);
//        } else {
//            auto left = std::dynamic_pointer_cast<dat::Decimal>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Decimal>(right_number);
//            result = std::make_shared<dat::Decimal> (*left - *right);
//        }
        return left_number;
    }

    std::shared_ptr<dat::DataType>
    Interpreter::mul_numbers(std::shared_ptr<dat::DataType> &left_number,
                             const std::shared_ptr<dat::DataType> &right_number) {
        if (left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter add_numbers()!");
        }
        left_number =  left_number * right_number;

//        if (left_number->c_NUMBER_TYPE == dat::NumberType::INT and
//            right_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Integer>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Integer>(right_number);
//            *left *= *right;
//            left_number = left;
//        } else if (left_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Integer>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Decimal>(right_number);
//            *left *= *right;
//            left_number = left;
//        } else if (right_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Decimal>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Integer>(right_number);
//            *left *= *right;
//            left_number = left;
//        } else {
//            auto left = std::dynamic_pointer_cast<dat::Decimal>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Decimal>(right_number);
//            *left *= *right;
//            left_number = left;
//        }
        return left_number;
    }

    std::shared_ptr<dat::DataType>
    Interpreter::div_numbers(std::shared_ptr<dat::DataType> &left_number,
                             const std::shared_ptr<dat::DataType> &right_number) {
        if (left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter add_numbers()!");
        }
        left_number =  left_number / right_number;
//        if (left_number->c_NUMBER_TYPE == dat::NumberType::INT and
//            right_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Integer>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Integer>(right_number);
//            *left /= *right;
//            left_number = left;
//        } else if (left_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Integer>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Decimal>(right_number);
//            *left /= *right;
//            left_number = left;
//        } else if (right_number->c_NUMBER_TYPE == dat::NumberType::INT) {
//            auto left = std::dynamic_pointer_cast<dat::Decimal>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Integer>(right_number);
//            *left /= *right;
//            left_number = left;
//        } else {
//            auto left = std::dynamic_pointer_cast<dat::Decimal>(left_number);
//            auto right = std::dynamic_pointer_cast<dat::Decimal>(right_number);
//            *left /= *right;
//            left_number = left;
//        }
        return left_number;
    }

    std::shared_ptr<dat::DataType>
    Interpreter::visit(const std::shared_ptr<par::Node> &node, itp::Context &context) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit()!");
        }
        std::shared_ptr<dat::DataType> result;
        switch (node->NODE_TYPE) {

            case par::NUMBER:
                result = visit_number_node(std::dynamic_pointer_cast<par::NumberNode>(node), context);
                break;
            case par::UNARY:
                result = visit_unary_node(std::dynamic_pointer_cast<par::UnaryOperatorNode>(node), context);
                break;
            case par::BINARY:
                result = visit_binary_node(std::dynamic_pointer_cast<par::BinaryOperatorNode>(node), context);
                break;
            case par::VAR_ASSIGN:
                result = visit_variable_assign_node(std::dynamic_pointer_cast<par::VariableAssignNode>(node), context);
                break;
            case par::VAR_ACCESS:
                result = visit_variable_access_node(std::dynamic_pointer_cast<par::VariableAccessNode>(node), context);
                break;
            default:
                throw std::runtime_error("Unknown Node in Interpreter visit()!");
        }
        return result;
    }


    std::shared_ptr<dat::DataType>
    Interpreter::visit_variable_access_node(const std::shared_ptr<par::VariableAccessNode> &node,
                                            itp::Context &context) {
        auto var_name = node->identifier_token.c_value;
        try {
            auto var_value = context.get_symbole_table().get(var_name);
            var_value->set_position(node->pos_start, node->pos_end);
            return std::dynamic_pointer_cast<dat::Number>(var_value);
        } catch (std::runtime_error &error) {
            throw err::RuntimeError(node->pos_start, node->pos_start, "'" + var_name + "' is not defined.", context);
        }

    }

    std::shared_ptr<dat::DataType>
    Interpreter::visit_variable_assign_node(const std::shared_ptr<par::VariableAssignNode> &node,
                                            itp::Context &context) {
        auto var_name = node->identifier_token.c_value;
        auto var_value = visit(node->value_node, context);
        context.get_symbole_table().set(var_name, var_value);
        return var_value;
    }

    std::shared_ptr<dat::DataType>
    Interpreter::visit_number_node(const std::shared_ptr<par::NumberNode> &node, itp::Context &context) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit_number_node()!");
        }
        if(node->num_token.c_type == lex::TokenType::NUMBER) {
            auto result = dat::Number::create_form_key(node->num_token.c_value, node->key);
            result->set_position(node->pos_start, node->pos_end);
            result->set_context(context);
            return result;
        } else {
            throw std::runtime_error("Unexpected token in Interpreter visit_number_node()!");
        }
    }

    std::shared_ptr<dat::DataType>
    Interpreter::visit_unary_node(const std::shared_ptr<par::UnaryOperatorNode> &node, itp::Context &context) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit_unary_node()!");
        }
        auto number = visit(node->right_node, context);
        if (node->op_token.c_type == lex::TokenType::MINUS) {
//            number->invert(); TODO
        } else if (node->op_token.c_type != lex::TokenType::PLUS) {
            throw std::runtime_error("Unexpected token in Interpreter visit_unary_node()!");
        }
        return number;
    }

    std::shared_ptr<dat::DataType>
    Interpreter::visit_binary_node(const std::shared_ptr<par::BinaryOperatorNode> &node, itp::Context &context) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit_binary_node()!");
        }
        auto left_number = visit(node->left_node, context);
        auto right_number = visit(node->right_node, context);
        if (node->op_token.c_type == lex::TokenType::PLUS) {
            left_number = add_numbers(left_number, right_number);
        } else if (node->op_token.c_type == lex::TokenType::MINUS) {
            left_number = sub_numbers(left_number, right_number);
        } else if (node->op_token.c_type == lex::TokenType::MULTIPLY) {
            left_number = mul_numbers(left_number, right_number);
        } else if (node->op_token.c_type == lex::TokenType::DIVIDE) {
            left_number = div_numbers(left_number, right_number);
        } else {
            throw std::runtime_error("Unexpected token in Interpreter visit_binary_node()!");
        }
        return left_number;
    }

} // itp