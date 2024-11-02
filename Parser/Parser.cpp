#include <algorithm>
#include <bitset>
#include "Parser.hpp"

#include "../Error/Error.hpp"

namespace par {


    lex::Token Parser::advance() {
        ++m_index;
        if (m_index < m_tokens.size()) {
//            m_current_token = m_tokens[m_index];
        }
        return m_current_token;
    }

    char get_number_from_back(const std::string &string, int end_index) {
        std::string result_number;
        for (int i{end_index}; i > 0 and string[i] >= '0' and string[i] <= '9'; --i) {
            result_number += string[i];
        }
        if (result_number.empty()) return -1;
        std::reverse(result_number.begin(), result_number.end());
        return static_cast<char>(std::stoi(result_number));
    }

    short Parser::variable_type_to_extra(const std::string &var_type) {
        /*
         * This method will return the given size of a var_type:
         * -1 if size is not defined
         * or else a short consisting of 2 bytes. First one being the size, second the scale factor (if needed)
         */

        switch (var_type[0]) {
            case 'b': // bool
            case 's': // str
                return -1;
            case 'u': // uint__
            case 'i': { // int__
                // Neither as an impact on storing vs. creating a literal
                char size = get_number_from_back(var_type, static_cast<int>(var_type.size() - 1));
                if (size == -1) {
                    size = 32;
                }
                return static_cast<short>(size << 8);
            }
            case 'd': { // dec__(:__)
                char size;
                char scale;

                // If user writes a dec variable, there are three possibilities:
                // 1. only base type 'dec'
                if (var_type == "dec") {
                    // Since default size = 32 Bits -> scale factor will be half.
                    size = 32;
                    scale = 16;
                }
                if (var_type.find(':') == std::string::npos) {
                    // 2. only size definition
                    size = get_number_from_back(var_type, static_cast<int>(var_type.size() - 1));
                    scale = static_cast<char>(size / 2);
                } else {
                    // 3. both size  and scale factor definition
                    return get_number_from_back(var_type, static_cast<int>(var_type.size() - 1));
                }
                return static_cast<short>(size << 8 | scale);
            }
            default:
                throw std::runtime_error("Unknown variable type name in variable_type_to_extra()");
        }
    }

    MegaNode Parser::next_statement() {
        MegaNode temp;
        switch (m_current_token.c_type) {
            case lex::VAR_KEYWORD:
//                temp = declaration();
                __asm("nop");
                break;
            case lex::IDENTIFIER:
//                temp = assignment();
                break;
            case lex::IF:
//                temp = if_block();
                break;
            default:
                __asm("nop");
//                temp = expression();
        }
        if (m_current_token.c_type != lex::TokenType::END_OF_LINE) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected ';' at end of expression");
        }
        advance();
        return temp;
    }

    MegaNode Parser::next_call(NextFunctionCall next_function ) {
        switch (next_function) {
            case EXPRESSION:
                return expression();
            case COMP_EXPR:
                return comparison_expression();
            case ARITH_EXPR:
                return arithmetic_expression();
            case TERM:
                return term();
            case FACTOR:
                return factor();
        }
        throw std::runtime_error("Unknown next function call in next_call().");
    }

    MegaNode
    Parser::binary_operator(NextFunctionCall next_function, const std::vector<lex::TokenType> &operator_tokens) {
        MegaNode left = next_call(next_function);
        while (std::find(operator_tokens.begin(), operator_tokens.end(), m_current_token.c_type) !=
               operator_tokens.end()) {
            lex::Token op_token = m_current_token;
            advance();
            MegaNode right = next_call(next_function);
//            left = MegaNode(NodeType::BINARY, op_token, left, right);
        }
        return left;
    }

    MegaNode Parser::unary_operator(NextFunctionCall next_function, const std::vector<lex::TokenType> &operator_tokens) {
        lex::Token operator_token = m_current_token;
        if (std::find(operator_tokens.begin(), operator_tokens.end(), m_current_token.c_type) ==
            operator_tokens.end()) {
            throw std::runtime_error("Unexpected Token in unary_operator()");
        }
        advance();
        auto right = next_call(next_function);
        return {NodeType::UNARY, operator_token, right};
    }


    MegaNode Parser::declaration() {
        short extra = variable_type_to_extra(m_current_token.c_value);

        advance();
        if (m_current_token.c_type != lex::TokenType::IDENTIFIER) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected ValueExpression here.");
        }

        auto identifier = m_current_token;
        auto ident_name = identifier.c_value;
        if (m_key_map.contains(ident_name)) {
            throw err::VariableAccessError(identifier.c_start_pos, identifier.c_end_pos,
                                           "Redefinition of variable '" + ident_name +
                                           "'.");
        }
        m_key_map[ident_name] = extra;
        advance();
        if (m_current_token.c_type != lex::TokenType::EQUALS) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '=' here.");
        }
        advance();
        auto expr = expression();
        return {NodeType::VARIABLE_ASSIGN, identifier, expr};
    }

    MegaNode Parser::assignment() {

        auto identifier = m_current_token;
        auto ident_name = identifier.c_value;
        if (!m_key_map.contains(ident_name)) {
            throw err::VariableAccessError(identifier.c_start_pos, identifier.c_end_pos,
                                           "Variable '" + ident_name +
                                           "' is not defined.");
        }
        short extra = m_key_map[ident_name];
        advance();
        if (m_current_token.c_type != lex::TokenType::EQUALS) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '=' here.");
        }
        advance();
        auto expr = expression();
        return {NodeType::VARIABLE_ASSIGN, identifier, expr};
    }

    MegaNode Parser::expression() {
        return binary_operator(NextFunctionCall::COMP_EXPR, {lex::TokenType::LOGIC_AND, lex::TokenType::LOGIC_OR});
    }

    MegaNode Parser::comparison_expression() {
        if (m_current_token.c_type == lex::TokenType::LOGIC_NOT) {
            return unary_operator(NextFunctionCall::COMP_EXPR, {lex::TokenType::LOGIC_NOT});
        } else {
            return binary_operator(NextFunctionCall::ARITH_EXPR,
                                   {lex::TokenType::DOUBLE_EQUALS, lex::TokenType::NOT_EQUALS,
                                    lex::TokenType::LESS_THEN, lex::TokenType::LESS_THEN_OR_EQUALS,
                                    lex::TokenType::GREATER_THEN, lex::TokenType::GREATER_THEN_OR_EQUALS,});
        }
    }

    MegaNode Parser::arithmetic_expression() {
        return binary_operator(NextFunctionCall::TERM, {lex::TokenType::PLUS, lex::TokenType::MINUS});
    }

    MegaNode Parser::term() {
        return binary_operator(NextFunctionCall::FACTOR, {lex::TokenType::MULTIPLY, lex::TokenType::DIVIDE});
    }

    MegaNode Parser::factor() {

        if (m_current_token.c_type == lex::TokenType::PLUS or m_current_token.c_type == lex::TokenType::MINUS) {
            return unary_operator(NextFunctionCall::FACTOR, {lex::TokenType::PLUS, lex::TokenType::MINUS});
        } else if (m_current_token.c_type == lex::TokenType::VALUE) {
            lex::Token temp_token = m_current_token;
            advance();
            return {NodeType::VALUE, temp_token};
        } else if (m_current_token.c_type == lex::TokenType::IDENTIFIER) {
            lex::Token temp_token = m_current_token;
            advance();
            return {NodeType::VARIABLE_ACCESS, temp_token};
        } else if (m_current_token.c_type == lex::TokenType::LEFT_ROUND_PARENTHESES) {
            advance();
            MegaNode expr = expression();
            if (m_current_token.c_type == lex::TokenType::RIGHT_ROUND_PARENTHESES) {
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

    MegaNode Parser::if_block() {
        lex::Token if_token = m_current_token;
        advance();
        auto condition = expression();
        advance();
        if (m_current_token.c_type != lex::TokenType::LEFT_CURVED_PARENTHESES) {
            throw err::InvalidSyntaxError(if_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '{' after if statement");
        }
        advance();
        std::vector<MegaNode> in_block_statements;
        while (m_current_token.c_type != lex::TokenType::RIGHT_CURVED_PARENTHESES) {
            in_block_statements.push_back(next_statement());
        }
        return {NodeType::IF_CONDITION, if_token, condition, in_block_statements};
    }

    Parser::Parser(const std::vector<lex::Token> &tokens) : m_tokens(tokens), m_current_token(lex::TokenType::NONE,lex::Position::NULL_POSITION),
                                                            m_key_map(), m_index(-1) {
        advance();
    }

    std::vector<MegaNode> Parser::parse_all() {
        std::vector<MegaNode> statements;
        while (m_index < m_tokens.size()) {
            statements.push_back(next_statement());
        }
        return statements;
    }

} // par
