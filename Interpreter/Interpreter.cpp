#include "Interpreter.hpp"

namespace itp {


    num::Number *Interpreter::add_numbers(num::Number *left_number, num::Number *right_number) {
        if(left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter add_numbers()!");
        }
        if(left_number->c_NUMBER_TYPE == num::NumberType::INT and right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto* left = dynamic_cast<num::Integer*>(left_number);
            auto* right = dynamic_cast<num::Integer*>(right_number);
            *left += *right;
            left_number = left;
            delete right_number;
        } else if(left_number->c_NUMBER_TYPE == num::NumberType::INT){
            auto* left = dynamic_cast<num::Integer*>(left_number);
            auto* right = dynamic_cast<num::Decimal*>(right_number);
            *left += *right;
            left_number = left;
            delete right_number;
        } else if (right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto* left = dynamic_cast<num::Decimal*>(left_number);
            auto* right = dynamic_cast<num::Integer*>(right_number);
            *left += *right;
            left_number = left;
            delete right_number;
        } else {
            auto* left = dynamic_cast<num::Decimal*>(left_number);
            auto* right = dynamic_cast<num::Decimal*>(right_number);
            *left += *right;
            left_number = left;
            delete right_number;
        }
        return left_number;
    }

    num::Number *Interpreter::sub_numbers(num::Number *left_number, num::Number *right_number) {
        if(left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter sub_numbers()!");
        }
        if(left_number->c_NUMBER_TYPE == num::NumberType::INT and right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto* left = dynamic_cast<num::Integer*>(left_number);
            auto* right = dynamic_cast<num::Integer*>(right_number);
            *left -= *right;
            left_number = left;
            delete right_number;
        } else if(left_number->c_NUMBER_TYPE == num::NumberType::INT){
            auto* left = dynamic_cast<num::Integer*>(left_number);
            auto* right = dynamic_cast<num::Decimal*>(right_number);
            *left -= *right;
            left_number = left;
            delete right_number;
        } else if (right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto* left = dynamic_cast<num::Decimal*>(left_number);
            auto* right = dynamic_cast<num::Integer*>(right_number);
            *left -= *right;
            left_number = left;
            delete right_number;
        } else {
            auto* left = dynamic_cast<num::Decimal*>(left_number);
            auto* right = dynamic_cast<num::Decimal*>(right_number);
            *left -= *right;
            left_number = left;
            delete right_number;
        }
        return left_number;
    }

    num::Number *Interpreter::mul_numbers(num::Number *left_number, num::Number *right_number) {
        if(left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter mul_numbers()!");
        }
        if(left_number->c_NUMBER_TYPE == num::NumberType::INT and right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto* left = dynamic_cast<num::Integer*>(left_number);
            auto* right = dynamic_cast<num::Integer*>(right_number);
            *left *= *right;
            left_number = left;
            delete right_number;
        } else if(left_number->c_NUMBER_TYPE == num::NumberType::INT){
            auto* left = dynamic_cast<num::Integer*>(left_number);
            auto* right = dynamic_cast<num::Decimal*>(right_number);
            *left *= *right;
            left_number = left;
            delete right_number;
        } else if (right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto* left = dynamic_cast<num::Decimal*>(left_number);
            auto* right = dynamic_cast<num::Integer*>(right_number);
            *left *= *right;
            left_number = left;
            delete right_number;
        } else {
            auto* left = dynamic_cast<num::Decimal*>(left_number);
            auto* right = dynamic_cast<num::Decimal*>(right_number);
            *left *= *right;
            left_number = left;
            delete right_number;
        }
        return left_number;
    }

    num::Number *Interpreter::div_numbers(num::Number *left_number, num::Number *right_number) {
        if(left_number == nullptr or right_number == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter div_numbers()!");
        }
        if(left_number->c_NUMBER_TYPE == num::NumberType::INT and right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto* left = dynamic_cast<num::Integer*>(left_number);
            auto* right = dynamic_cast<num::Integer*>(right_number);
            *left /= *right;
            left_number = left;
            delete right_number;
        } else if(left_number->c_NUMBER_TYPE == num::NumberType::INT){
            auto* left = dynamic_cast<num::Integer*>(left_number);
            auto* right = dynamic_cast<num::Decimal*>(right_number);
            *left /= *right;
            left_number = left;
            delete right_number;
        } else if (right_number->c_NUMBER_TYPE == num::NumberType::INT) {
            auto* left = dynamic_cast<num::Decimal*>(left_number);
            auto* right = dynamic_cast<num::Integer*>(right_number);
            *left /= *right;
            left_number = left;
            delete right_number;
        } else {
            auto* left = dynamic_cast<num::Decimal*>(left_number);
            auto* right = dynamic_cast<num::Decimal*>(right_number);
            *left /= *right;
            left_number = left;
            delete right_number;
        }
        return left_number;
    }

    num::Number *Interpreter::visit(par::Node *node) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit()!");
        }
        num::Number* result;
        switch (node->NODE_TYPE) {

            case par::NUMBER:
                result= visit_number_node(dynamic_cast<par::NumberNode *>(node));
                break;
            case par::UNARY:
                result= visit_unary_node(dynamic_cast<par::UnaryOperatorNode *>(node));
                break;
            case par::BINARY:
                result= visit_binary_node(dynamic_cast<par::BinaryOperatorNode *>(node));
                break;
            default:
                throw std::runtime_error("Unknown Node in Interpreter visit()!");
        }
        return result;
    }

    num::Number *Interpreter::visit_number_node(par::NumberNode *node) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit_number_node()!");
        }
        if (node->num_token.c_type == lex::TokenType::INT) {
            return new num::Integer(node->num_token.c_value);
        } else if (node->num_token.c_type == lex::TokenType::DEC) {
            return new num::Decimal(node->num_token.c_value);
        } else {
            throw std::runtime_error("Unexpected token in Interpreter visit_number_node()!");
        }
    }

    num::Number *Interpreter::visit_unary_node(par::UnaryOperatorNode *node) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit_unary_node()!");
        }
        auto number = visit(node->right_node);
        if (node->op_token.c_type == lex::TokenType::MINUS) {
            number->invert();
        } else if (node->op_token.c_type != lex::TokenType::PLUS) {
            delete number;
            throw std::runtime_error("Unexpected token in Interpreter visit_unary_node()!");
        }
        return number;
    }

    num::Number *Interpreter::visit_binary_node(par::BinaryOperatorNode *node) {
        if (node == nullptr) {
            throw std::runtime_error("Null pointer in Interpreter visit_binary_node()!");
        }
        auto left_number = visit(node->left_node);
        auto right_number = visit(node->right_node);
        if (node->op_token.c_type == lex::TokenType::PLUS) {
            left_number = add_numbers(left_number,right_number);
        }else if (node->op_token.c_type == lex::TokenType::MINUS) {
            left_number = sub_numbers(left_number,right_number);
        }else if (node->op_token.c_type == lex::TokenType::MUL) {
            left_number = mul_numbers(left_number,right_number);
        }else if (node->op_token.c_type == lex::TokenType::DIV) {
            left_number = div_numbers(left_number,right_number);
        } else {
            delete left_number;
            delete right_number;
            throw std::runtime_error("Unexpected token in Interpreter visit_binary_node()!");
        }
        return left_number;
    }

} // itp