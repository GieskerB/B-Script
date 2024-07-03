#include "Interpreter.hpp"
#include "../Error/Error.hpp"

namespace itp {


    std::shared_ptr<num::Number>
    Interpreter::add_numbers(std::shared_ptr<num::Number> &left_number,
                             const std::shared_ptr<num::Number> &right_number) {
        if (left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter add_numbers()!");
        }
        if (left_number->c_NUMBER_TYPE == num::NumberType::INT and
            right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Integer>(left_number);
            auto right = std::dynamic_pointer_cast<num::Integer>(right_number);
            *left += *right;
            left_number = left;
        } else if (left_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Integer>(left_number);
            auto right = std::dynamic_pointer_cast<num::Decimal>(right_number);
            *left += *right;
            left_number = left;
        } else if (right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Decimal>(left_number);
            auto right = std::dynamic_pointer_cast<num::Integer>(right_number);
            *left += *right;
            left_number = left;
        } else {
            auto left = std::dynamic_pointer_cast<num::Decimal>(left_number);
            auto right = std::dynamic_pointer_cast<num::Decimal>(right_number);
            *left += *right;
            left_number = left;
        }
        return left_number;
    }

    std::shared_ptr<num::Number>
    Interpreter::sub_numbers(std::shared_ptr<num::Number> &left_number,
                             const std::shared_ptr<num::Number> &right_number) {
        if (left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter add_numbers()!");
        }
        if (left_number->c_NUMBER_TYPE == num::NumberType::INT and
            right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Integer>(left_number);
            auto right = std::dynamic_pointer_cast<num::Integer>(right_number);
            *left -= *right;
            left_number = left;
        } else if (left_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Integer>(left_number);
            auto right = std::dynamic_pointer_cast<num::Decimal>(right_number);
            *left -= *right;
            left_number = left;
        } else if (right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Decimal>(left_number);
            auto right = std::dynamic_pointer_cast<num::Integer>(right_number);
            *left -= *right;
            left_number = left;
        } else {
            auto left = std::dynamic_pointer_cast<num::Decimal>(left_number);
            auto right = std::dynamic_pointer_cast<num::Decimal>(right_number);
            *left -= *right;
            left_number = left;
        }
        return left_number;
    }

    std::shared_ptr<num::Number>
    Interpreter::mul_numbers(std::shared_ptr<num::Number> &left_number,
                             const std::shared_ptr<num::Number> &right_number) {
        if (left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter add_numbers()!");
        }
        if (left_number->c_NUMBER_TYPE == num::NumberType::INT and
            right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Integer>(left_number);
            auto right = std::dynamic_pointer_cast<num::Integer>(right_number);
            *left *= *right;
            left_number = left;
        } else if (left_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Integer>(left_number);
            auto right = std::dynamic_pointer_cast<num::Decimal>(right_number);
            *left *= *right;
            left_number = left;
        } else if (right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Decimal>(left_number);
            auto right = std::dynamic_pointer_cast<num::Integer>(right_number);
            *left *= *right;
            left_number = left;
        } else {
            auto left = std::dynamic_pointer_cast<num::Decimal>(left_number);
            auto right = std::dynamic_pointer_cast<num::Decimal>(right_number);
            *left *= *right;
            left_number = left;
        }
        return left_number;
    }

    std::shared_ptr<num::Number>
    Interpreter::div_numbers(std::shared_ptr<num::Number> &left_number,
                             const std::shared_ptr<num::Number> &right_number) {
        if (left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter add_numbers()!");
        }
        if (left_number->c_NUMBER_TYPE == num::NumberType::INT and
            right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Integer>(left_number);
            auto right = std::dynamic_pointer_cast<num::Integer>(right_number);
            *left /= *right;
            left_number = left;
        } else if (left_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Integer>(left_number);
            auto right = std::dynamic_pointer_cast<num::Decimal>(right_number);
            *left /= *right;
            left_number = left;
        } else if (right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto left = std::dynamic_pointer_cast<num::Decimal>(left_number);
            auto right = std::dynamic_pointer_cast<num::Integer>(right_number);
            *left /= *right;
            left_number = left;
        } else {
            auto left = std::dynamic_pointer_cast<num::Decimal>(left_number);
            auto right = std::dynamic_pointer_cast<num::Decimal>(right_number);
            *left /= *right;
            left_number = left;
        }
        return left_number;
    }

    std::shared_ptr<num::Number> Interpreter::visit(const std::shared_ptr<par::Node> &node) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit()!");
        }
        std::shared_ptr<num::Number> result;
        switch (node->NODE_TYPE) {

            case par::NUMBER:
                result = visit_number_node(std::dynamic_pointer_cast<par::NumberNode>(node));
                break;
            case par::UNARY:
                result = visit_unary_node(std::dynamic_pointer_cast<par::UnaryOperatorNode>(node));
                break;
            case par::BINARY:
                result = visit_binary_node(std::dynamic_pointer_cast<par::BinaryOperatorNode>(node));
                break;
            default:
                throw std::runtime_error("Unknown Node in Interpreter visit()!");
        }
        return result;
    }

    std::shared_ptr<num::Number> Interpreter::visit_number_node(const std::shared_ptr<par::NumberNode> &node) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit_number_node()!");
        }
        if (node->num_token.c_type == lex::TokenType::INT) {
            auto result =  std::make_shared<num::Integer>(node->num_token.c_value);
            result->set_position(node->pos_start,node->pos_end);
            return result;
        } else if (node->num_token.c_type == lex::TokenType::DEC) {
            auto result = std::make_shared<num::Decimal>(node->num_token.c_value);
            result->set_position(node->pos_start,node->pos_end);
            return result;
        } else {
            throw std::runtime_error("Unexpected token in Interpreter visit_number_node()!");
        }
    }

    std::shared_ptr<num::Number> Interpreter::visit_unary_node(const std::shared_ptr<par::UnaryOperatorNode> &node) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit_unary_node()!");
        }
        auto number = visit(node->right_node);
        if (node->op_token.c_type == lex::TokenType::MINUS) {
            number->invert();
        } else if (node->op_token.c_type != lex::TokenType::PLUS) {
            throw std::runtime_error("Unexpected token in Interpreter visit_unary_node()!");
        }
        return number;
    }

    std::shared_ptr<num::Number> Interpreter::visit_binary_node(const std::shared_ptr<par::BinaryOperatorNode> &node) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit_binary_node()!");
        }
        auto left_number = visit(node->left_node);
        auto right_number = visit(node->right_node);
        if (node->op_token.c_type == lex::TokenType::PLUS) {
            left_number = add_numbers(left_number, right_number);
        } else if (node->op_token.c_type == lex::TokenType::MINUS) {
            left_number = sub_numbers(left_number, right_number);
        } else if (node->op_token.c_type == lex::TokenType::MUL) {
            left_number = mul_numbers(left_number, right_number);
        } else if (node->op_token.c_type == lex::TokenType::DIV) {
            left_number = div_numbers(left_number, right_number);
        } else {
            throw std::runtime_error("Unexpected token in Interpreter visit_binary_node()!");
        }
        return left_number;
    }

} // itp