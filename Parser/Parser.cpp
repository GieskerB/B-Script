#include <algorithm>
#include <bitset>
#include "Parser.hpp"

#include "../Error/Error.hpp"

namespace par {


    lex::Token Parser::advance() {
        ++m_index;
        if (m_index < m_tokens.size()) {
            m_current_token = m_tokens[m_index];
        }
        return m_current_token;
    }

    short get_number_from_back(const std::string &string, int end_index) {
        std::string result_number;
        for (int i{end_index};
             i > 0 and string[i] >= '0' and string[i] <= '9'; --i) {
            result_number += string[i];
        }
        if (result_number.empty()) return -1;
        std::reverse(result_number.begin(), result_number.end());
        return static_cast<short>(std::stoi(result_number));
    }

    short Parser::type_to_key(const std::string &var_type_name) {
        /*
         * Idea is to convert any variable type into an easy-to-read bit sequenz.
         * e: extra
         * s: Size
         * t: variable type
         *
         * Format:
         * eeeeeeee sssstttt
         */

        int key{0};
        short size_number, extra_number;
        switch (var_type_name[0]) {
            case 'u':
                key |= (1 << 8); // extra = 1 (unsigned)
            case 'i':
                size_number = get_number_from_back(var_type_name, static_cast<int>(var_type_name.size() - 1));
                if (size_number == -1) size_number = 32; // default size = int [32]
                size_number /= 8; // Convert form bits to bytes
                size_number <<= 4; // move to 'ssss' segment
                key |= size_number; // size = byte | short | int | long
                key |= 1; // type = int
                break;
            case 'd':
                size_number = get_number_from_back(var_type_name, static_cast<int>(var_type_name.size() - 1));
                if (size_number == -1) size_number = 32; // default size = int [32]
                if (var_type_name.find(':') != std::string::npos) {
                    extra_number = get_number_from_back(var_type_name, static_cast<int>(var_type_name.find(':') - 1));
                    auto swap = extra_number;
                    extra_number = size_number;
                    size_number = swap;
                } else {
                    extra_number = static_cast<short>(size_number / 2);
                }
                size_number /= 8;  // Convert form bits to bytes
                size_number <<= 4; // move to 'ssss' segment
                key |= size_number; // size = byte | short | int | long
                extra_number <<= 8; // move to 'eeeeeeee' segment
                key |= extra_number; // extra = scaling factor
                key |= 2; // type = dec
                break;
            case 'b':
                key |= 3; // type = bool
                break;
            case 's':
                key |= 4; // type = bool
                break;
            default:
                throw std::runtime_error("Unknown variable type name in type_to_key()");
        }
        return static_cast<short>(key);
    }

    OmegaNode Parser::next_call(NextFunctionCall next_function, short key) {
        switch (next_function) {
            case EXPRESSION:
                return expression(key);
            case COMP_EXPR:
                return comparison_expression(key);
            case ARITH_EXPR:
                return arithmetic_expression(key);
            case TERM:
                return term(key);
            case FACTOR:
                return factor(key);
        }
        throw std::runtime_error("Unknown next function call in next_call().");
    }

    OmegaNode
    Parser::binary_operator(NextFunctionCall next_function, const std::vector<lex::TokenType> &operator_tokens,
                            short key) {
        OmegaNode left = next_call(next_function, key);
        while (std::find(operator_tokens.begin(), operator_tokens.end(), m_current_token.c_type) !=
               operator_tokens.end()) {
            lex::Token op_token = m_current_token;
            advance();
            OmegaNode right = next_call(next_function, key);
            left = OmegaNode(NodeType::BINARY, op_token, left, right);
        }
        return left;
    }

    OmegaNode Parser::unary_operator(NextFunctionCall next_function, const std::vector<lex::TokenType> &operator_tokens,
                                     short key) {
        lex::Token operator_token = m_current_token;
        if (std::find(operator_tokens.begin(), operator_tokens.end(), m_current_token.c_type) ==
            operator_tokens.end()) {
            throw std::runtime_error("Unexpected Token in unary_operator()");
        }
        advance();
        auto right = next_call(next_function, key);
        return {NodeType::UNARY, operator_token, right};
    }


    OmegaNode Parser::declaration() {
        short key = type_to_key(m_current_token.c_value);

        advance();
        if (m_current_token.c_type != lex::TokenType::IDENTIFIER) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected Identifier here.");
        }

        auto identifier = m_current_token;
        auto ident_name = identifier.c_value;
        if (m_key_map.contains(ident_name)) {
            throw err::VariableAccessError(identifier.c_start_pos, identifier.c_end_pos,
                                          "Redefinition of variable '" + ident_name +
                                          "'.");
        }
        m_key_map[ident_name] = key;
        advance();
        if (m_current_token.c_type != lex::TokenType::EQUALS) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '=' here.");
        }
        advance();
        auto expr = expression(key);
        return {NodeType::VARIABLE_ASSIGN, identifier, expr};
    }

    OmegaNode Parser::assignment() {

        auto identifier = m_current_token;
        auto ident_name = identifier.c_value;
        if (!m_key_map.contains(ident_name)) {
            throw err::VariableAccessError(identifier.c_start_pos, identifier.c_end_pos,
                                          "Variable '" + ident_name +
                                          "' is not defined.");
        }
        short key = m_key_map[ident_name];
        advance();
        if (m_current_token.c_type != lex::TokenType::EQUALS) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '=' here.");
        }
        advance();
        auto expr = expression(key);
        return {NodeType::VARIABLE_ASSIGN, identifier, expr};
    }

    OmegaNode Parser::expression(short key) {
        return binary_operator(NextFunctionCall::COMP_EXPR, {lex::TokenType::LOGIC_AND, lex::TokenType::LOGIC_OR}, key);
    }

    OmegaNode Parser::comparison_expression(short key) {
        if (m_current_token.c_type == lex::TokenType::LOGIC_NOT) {
            return unary_operator(NextFunctionCall::COMP_EXPR, {lex::TokenType::LOGIC_NOT}, key);
        } else {
            return binary_operator(NextFunctionCall::ARITH_EXPR,
                                   {lex::TokenType::DOUBLE_EQUALS, lex::TokenType::NOT_EQUALS,
                                    lex::TokenType::LESS_THEN, lex::TokenType::LESS_THEN_OR_EQUALS,
                                    lex::TokenType::GREATER_THEN, lex::TokenType::GREATER_THEN_OR_EQUALS,}, key);
        }
    }

    OmegaNode Parser::arithmetic_expression(short key) {
        return binary_operator(NextFunctionCall::TERM, {lex::TokenType::PLUS, lex::TokenType::MINUS}, key);
    }

    OmegaNode Parser::term(short key) {
        return binary_operator(NextFunctionCall::FACTOR, {lex::TokenType::MULTIPLY, lex::TokenType::DIVIDE}, key);
    }

    OmegaNode Parser::factor(short key) {

        if (m_current_token.c_type == lex::TokenType::PLUS or m_current_token.c_type == lex::TokenType::MINUS) {
            return unary_operator(NextFunctionCall::FACTOR, {lex::TokenType::PLUS, lex::TokenType::MINUS}, key);
        } else if (m_current_token.c_type == lex::TokenType::VALUE) {
            lex::Token temp_token = m_current_token;
            advance();
            return {NodeType::VALUE, temp_token, key};
        } else if (m_current_token.c_type == lex::TokenType::IDENTIFIER) {
            lex::Token temp_token = m_current_token;
            advance();
            return {NodeType::VARIABLE_ACCESS, temp_token};
        } else if (m_current_token.c_type == lex::TokenType::LEFT_PARENTHESES) {
            advance();
            OmegaNode expr = expression(key);
            if (m_current_token.c_type == lex::TokenType::RIGHT_PARENTHESES) {
                advance();
                return expr;
            } else {
                throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                              "Expected ')' here.");
            }
        }

        throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                      "Expected INT or DEC here.");
    }


    Parser::Parser() : m_tokens(), m_current_token(lex::Token::NULL_TOKEN), m_key_map(), m_index(-1) {}

    void Parser::import_tokens(const std::vector<lex::Token> &tokens) {
        m_tokens = tokens;
        m_index = -1;
        advance();
    }

    OmegaNode Parser::parse() {
        OmegaNode abstract_syntax_tree;
        if (m_current_token.c_type == lex::TokenType::VAR_KEYWORD) {
            abstract_syntax_tree = declaration();
        } else if (m_current_token.c_type == lex::TokenType::IDENTIFIER) {
            abstract_syntax_tree = assignment();
        } else {
            abstract_syntax_tree = expression();
        }

        if (m_current_token.c_type != lex::TokenType::END_OF_LINE) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '+', '-', '*' or '/' here.");
        }

        return abstract_syntax_tree;
    }


} // par
