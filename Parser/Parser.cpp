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
        for (int i{end_index}; i > 0 and string[i] >= '0' and string[i] <= '9'; --i) {
            result_number += string[i];
        }
        if (result_number.empty()) return -1;
        std::reverse(result_number.begin(), result_number.end());
        return static_cast<short>(std::stoi(result_number));
    }

    short Parser::variable_type_to_extra(const std::string &var_type) {
        switch (var_type[0]) {
            case 'b': // bool
            case 's': // str
            case 'u': // uint__
            case 'i': // int__
                // Neither as an impact on storing vs. creating a literal
                return -1;
            case 'd': { // dec__(:__)
                // If user writes a dec variable, there are three possibilities:
                // 1. only base type 'dec'
                if (var_type == "dec") {
                    return 16; // Since default size = 32 Bits -> scale factor will be half.
                }
                if (var_type.find(':') == std::string::npos) {
                    // 2. only size definition
                    return static_cast<short> ( // Again: Default scale factor is half of size.
                            get_number_from_back(var_type, static_cast<int>(var_type.size() - 1)) / 2);
                } else {
                    // 3. both size  and scale factor definition
                    return get_number_from_back(var_type, static_cast<int>(var_type.size() - 1));
                }
            }
            default:
                throw std::runtime_error("Unknown variable type name in variable_type_to_extra()");
        }
    }

    MegaNode Parser::next_statement() {
        MegaNode temp;
        switch (m_current_token.c_type) {
            case lex::VAR_KEYWORD:
                temp = declaration();
                break;
            case lex::IDENTIFIER:
                temp = assignment();
                break;
            case lex::IF:
                temp = if_block();
                break;
            default:
                temp = expression();
        }
        if (m_current_token.c_type != lex::TokenType::END_OF_LINE) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected ';' at end of expression.");
        }
        advance();
        return temp;
    }

    MegaNode Parser::next_call(NextFunctionCall next_function, short extra) {
        switch (next_function) {
            case EXPRESSION:
                return expression(extra);
            case COMP_EXPR:
                return comparison_expression(extra);
            case ARITH_EXPR:
                return arithmetic_expression(extra);
            case TERM:
                return term(extra);
            case FACTOR:
                return factor(extra);
        }
        throw std::runtime_error("Unknown next function call in next_call().");
    }

    MegaNode
    Parser::binary_operator(NextFunctionCall next_function, const std::vector<lex::TokenType> &operator_tokens,
                            short extra) {
        MegaNode left = next_call(next_function, extra);
        while (std::find(operator_tokens.begin(), operator_tokens.end(), m_current_token.c_type) !=
               operator_tokens.end()) {
            lex::Token op_token = m_current_token;
            advance();
            MegaNode right = next_call(next_function, extra);
            left = MegaNode(NodeType::BINARY, op_token, left, right);
        }
        return left;
    }

    MegaNode Parser::unary_operator(NextFunctionCall next_function, const std::vector<lex::TokenType> &operator_tokens,
                                    short extra) {
        lex::Token operator_token = m_current_token;
        if (std::find(operator_tokens.begin(), operator_tokens.end(), m_current_token.c_type) ==
            operator_tokens.end()) {
            throw std::runtime_error("Unexpected Token in unary_operator()");
        }
        advance();
        auto right = next_call(next_function, extra);
        return {NodeType::UNARY, operator_token, right};
    }


    MegaNode Parser::declaration() {
        short extra = variable_type_to_extra(m_current_token.c_value);

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
        m_key_map[ident_name] = extra;
        advance();
        if (m_current_token.c_type != lex::TokenType::EQUALS) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '=' here.");
        }
        advance();
        auto expr = expression(extra);
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
        auto expr = expression(extra);
        return {NodeType::VARIABLE_ASSIGN, identifier, expr};
    }

    MegaNode Parser::expression(short extra) {
        return binary_operator(NextFunctionCall::COMP_EXPR, {lex::TokenType::LOGIC_AND, lex::TokenType::LOGIC_OR}, extra);
    }

    MegaNode Parser::comparison_expression(short extra) {
        if (m_current_token.c_type == lex::TokenType::LOGIC_NOT) {
            return unary_operator(NextFunctionCall::COMP_EXPR, {lex::TokenType::LOGIC_NOT}, extra);
        } else {
            return binary_operator(NextFunctionCall::ARITH_EXPR,
                                   {lex::TokenType::DOUBLE_EQUALS, lex::TokenType::NOT_EQUALS,
                                    lex::TokenType::LESS_THEN, lex::TokenType::LESS_THEN_OR_EQUALS,
                                    lex::TokenType::GREATER_THEN, lex::TokenType::GREATER_THEN_OR_EQUALS,}, extra);
        }
    }

    MegaNode Parser::arithmetic_expression(short extra) {
        return binary_operator(NextFunctionCall::TERM, {lex::TokenType::PLUS, lex::TokenType::MINUS}, extra);
    }

    MegaNode Parser::term(short extra) {
        return binary_operator(NextFunctionCall::FACTOR, {lex::TokenType::MULTIPLY, lex::TokenType::DIVIDE}, extra);
    }

    MegaNode Parser::factor(short extra) {

        if (m_current_token.c_type == lex::TokenType::PLUS or m_current_token.c_type == lex::TokenType::MINUS) {
            return unary_operator(NextFunctionCall::FACTOR, {lex::TokenType::PLUS, lex::TokenType::MINUS}, extra);
        } else if (m_current_token.c_type == lex::TokenType::VALUE) {
            lex::Token temp_token = m_current_token;
            advance();
            return {NodeType::VALUE, temp_token, extra};
        } else if (m_current_token.c_type == lex::TokenType::IDENTIFIER) {
            lex::Token temp_token = m_current_token;
            advance();
            return {NodeType::VARIABLE_ACCESS, temp_token};
        } else if (m_current_token.c_type == lex::TokenType::LEFT_ROUND_PARENTHESES) {
            advance();
            MegaNode expr = expression(extra);
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

    Parser::Parser(const std::vector<lex::Token> &tokens) : m_tokens(tokens), m_current_token(lex::Token::NULL_TOKEN),
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
