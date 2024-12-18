#include <cassert>
#include "Interpreter.hpp"
#include "Context.hpp"
#include "../DataTypes/Utility.hpp"
#include "../Error/Error.hpp"

namespace itp {

    VariantTypes Interpreter::visit(const par::MegaNode &node, Context &context) {
        switch (node.get_node_type()) {
            case par::NodeType::BINARY:
                return visit_binary_node(node, context);
            case par::NodeType::UNARY:
                return visit_unary_node(node, context);
            case par::NodeType::VALUE:
                return visit_value_node(node, context);
            case par::NodeType::VARIABLE_ACCESS:
                return visit_variable_access_node(node, context);
            case par::NodeType::VARIABLE_ASSIGN:
                return visit_variable_assign_node(node, context);
            case par::NodeType::IF_CONDITION:
                return visit_if_condition_node(node, context);
            default:
                throw std::runtime_error("Invalid NodeType in Interpreter::visit()");
        }
    }

    VariantTypes Interpreter::visit_if_condition_node(const par::MegaNode &node, itp::Context &context) {

    }

    VariantTypes Interpreter::visit_variable_access_node(const par::MegaNode &node, Context &context) {
        auto var_name = node.get_token().c_value;
        try {
            VariantTypes &var_value = context.get_symbole_table().get(var_name);
            get_variant_content(var_value).set_position(node.get_start_position(), node.get_end_position());
            return std::move(var_value);
        } catch (std::runtime_error &error) {
            throw err::RuntimeError(node.get_start_position(), node.get_end_position(),
                                    "'" + var_name + "' is not defined.", context);
        }
    }

    VariantTypes Interpreter::visit_variable_assign_node(const par::MegaNode &node, Context &context) {
        std::string var_name = node.get_token().c_value;
        VariantTypes var_value = visit(node.get_right(), context);
        context.get_symbole_table().set(var_name, var_value);
        return var_value;
    }

    VariantTypes Interpreter::visit_value_node(const par::MegaNode &node, Context &context) {
        if (node.get_token().c_type == lex::TokenType::VALUE) {
            auto result = dat::create_datatype_form_string(node.get_token());

            auto start = node.get_start_position();
            auto end = node.get_end_position();

            auto set_position = [&](auto &datatype) {
                datatype.set_position(start, end);
            };
            auto set_context = [&](auto &datatype) {
                datatype.set_context(context);
            };

            std::visit(set_position, result);
            std::visit(set_context, result);
            return std::move(result);
        } else {
            throw std::runtime_error("Unexpected token in Interpreter visit_value_node()!");
        }
    }


    VariantTypes Interpreter::visit_unary_node(const par::MegaNode &node, Context &context) {
        auto value = visit(node.get_right(), context);
        if (node.get_token().c_type == lex::TokenType::PLUS) {
            return +value;
        } else if (node.get_token().c_type == lex::TokenType::MINUS) {
            return -value;
        } else if (node.get_token().c_type == lex::TokenType::LOGIC_NOT) {
            return !value;
        }
        throw std::runtime_error("Unexpected token in Interpreter visit_unary_node()!");
    }

    VariantTypes Interpreter::visit_binary_node(const par::MegaNode &node, Context &context) {
        auto left_value = visit(node.get_left(), context);
        auto right_value = visit(node.get_right(), context);
        if (node.get_token().c_type == lex::TokenType::PLUS) {
            return left_value + right_value;
        } else if (node.get_token().c_type == lex::TokenType::MINUS) {
            return left_value - right_value;
        } else if (node.get_token().c_type == lex::TokenType::MULTIPLY) {
            return left_value * right_value;
        } else if (node.get_token().c_type == lex::TokenType::DIVIDE) {
            return left_value / right_value;
        } else if (node.get_token().c_type == lex::TokenType::LESS_THEN) {
            return left_value < right_value;
        } else if (node.get_token().c_type == lex::TokenType::LESS_THEN_OR_EQUALS) {
            return left_value <= right_value;
        } else if (node.get_token().c_type == lex::TokenType::GREATER_THEN) {
            return left_value > right_value;
        } else if (node.get_token().c_type == lex::TokenType::GREATER_THEN_OR_EQUALS) {
            return left_value >= right_value;
        } else if (node.get_token().c_type == lex::TokenType::DOUBLE_EQUALS) {
            return left_value == right_value;
        } else if (node.get_token().c_type == lex::TokenType::NOT_EQUALS) {
            return left_value != right_value;
        } else if (node.get_token().c_type == lex::TokenType::LOGIC_AND) {
            return left_value && right_value;
        } else if (node.get_token().c_type == lex::TokenType::LOGIC_OR) {
            return left_value || right_value;
        } else {
            throw std::runtime_error("Unexpected token in Interpreter visit_binary_node()!");
        }
    }

} // itp