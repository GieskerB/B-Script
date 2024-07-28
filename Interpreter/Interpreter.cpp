#include <cassert>
#include "Interpreter.hpp"
#include "Context.hpp"
#include "../DataTypes/Utility.hpp"
#include "../Error/Error.hpp"

namespace itp {

    dat::DataType& get_variant_content(VariantTypes& variant) {
        switch (variant.index()) {
            case 0:
                return std::get<dat::Boolean>(variant);
            case 1:
                return std::get<dat::Integer>(variant);
            case 2:
                return std::get<dat::Decimal>(variant);
            case 3:
                return std::get<dat::String>(variant);
            default:
                throw std::runtime_error("std::variant error in get_variant_content()");
        }
    }

    VariantTypes Interpreter::visit(const  par::OmegaNode & node, Context & context) {
        switch (node.get_node_type()) {
            case par::NodeType::BINARY:
                return visit_binary_node(node,context);
            case par::NodeType::UNARY:
                return visit_unary_node(node,context);
            case par::NodeType::VALUE:
                return visit_value_node(node, context);
            case par::NodeType::VARIABLE_ACCESS:
                return visit_variable_access_node(node,context);
            case par::NodeType::VARIABLE_ASSIGN:
                return visit_variable_assign_node(node,context);
            default:
                throw std::runtime_error("Invalid NodeType in Interpreter::visit()");
        }
    }

    VariantTypes Interpreter::visit_variable_access_node(const par::OmegaNode & node, Context & context) {
        auto var_name = node.get_token().c_value;
        try {
            VariantTypes& var_value = context.get_symbole_table().get(var_name);
            dat::DataType& x = get_variant_content(var_value);
            x.set_position(node.get_start_position(), node.get_end_position());
            return std::move(var_value);
        } catch (std::runtime_error &error) {
            throw err::RuntimeError(node.get_start_position(), node.get_end_position(), "'" + var_name + "' is not defined.", context);
        }
    }

    VariantTypes Interpreter::visit_variable_assign_node(const par::OmegaNode & node, Context & context) {
        std::string var_name = node.get_token().c_value;
        VariantTypes var_value = visit(node.get_right(), context);
        context.get_symbole_table().set(var_name, var_value);
        return var_value;
    }

    VariantTypes Interpreter::visit_value_node(const par::OmegaNode & node, Context & context) {
        if(node.get_token().c_type == lex::TokenType::VALUE) {
            auto result = dat::Utility::create_form_key(node.get_token().c_value, node.get_variable_key());

            auto start = node.get_start_position();
            auto end = node.get_end_position();

            auto set_position = [&](auto& datatype) {
                datatype.set_position(start, end);
            };
            auto set_context = [&](auto& datatype) {
                datatype.set_context(context);
            };

            std::visit(set_position, result);
            std::visit(set_context, result);
            return std::move(result);
        } else {
            throw std::runtime_error("Unexpected token in Interpreter visit_value_node()!");
        }
    }


    VariantTypes Interpreter::visit_unary_node(const par::OmegaNode & node, Context & context) {
        auto number = visit(node.get_right(), context);
        if (node.get_token().c_type == lex::TokenType::MINUS) {
//            number->invert(); TODO
        } else if (node.get_token().c_type != lex::TokenType::PLUS) {
            throw std::runtime_error("Unexpected token in Interpreter visit_unary_node()!");
        }
        return number;
    }

    VariantTypes Interpreter::visit_binary_node(const par::OmegaNode & node, Context & context) {
        auto left_number = visit(node.get_left(), context);
        auto right_number = visit(node.get_right(), context);
        if (node.get_token().c_type == lex::TokenType::PLUS) {
            return left_number + right_number;
        } else if (node.get_token().c_type == lex::TokenType::MINUS) {
            return left_number - right_number;
        } else if (node.get_token().c_type == lex::TokenType::MULTIPLY) {
            return left_number * right_number;
        } else if (node.get_token().c_type == lex::TokenType::DIVIDE) {
            return left_number / right_number;
        } else {
            throw std::runtime_error("Unexpected token in Interpreter visit_binary_node()!");
        }
    }

} // itp