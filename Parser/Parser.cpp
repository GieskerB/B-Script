#include <algorithm>
#include <bitset>
#include "Parser.hpp"

#include "../Lexer/Token.hpp"
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
            default:
                throw std::runtime_error("Unknown variable type name in type_to_key()");
        }
        return static_cast<short>(key);
    }

    std::shared_ptr<Node> Parser::factor(short key) {

        if (m_current_token.c_type == lex::TokenType::PLUS or m_current_token.c_type == lex::TokenType::MINUS) {
            lex::Token temp_token = m_current_token;
            advance();
            std::shared_ptr<Node> right = factor(key);
            return std::make_shared<UnaryOperatorNode>(temp_token, right);
        } else if (m_current_token.c_type == lex::TokenType::NUM) {
            lex::Token temp_token = m_current_token;
            advance();
            return std::make_shared<NumberNode>(temp_token, key);
        } else if (m_current_token.c_type == lex::TokenType::IDENTIFIER) {
            lex::Token temp_token = m_current_token;
            advance();
            return std::make_shared<VariableAccessNode>(temp_token);
        } else if (m_current_token.c_type == lex::TokenType::LPAREN) {
            advance();
            std::shared_ptr<Node> expr = expression(key);
            if (m_current_token.c_type == lex::TokenType::RPAREN) {
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

    std::shared_ptr<Node> Parser::term(short key) {
        std::shared_ptr<Node> left = factor(key);

        while (m_current_token.c_type == lex::TokenType::MUL or m_current_token.c_type == lex::TokenType::DIV) {
            lex::Token op_token = m_current_token;
            advance();
            std::shared_ptr<Node> right = factor(key);
            left = std::make_shared<BinaryOperatorNode>(left, op_token, right);
        }

        return left;
    }

    std::shared_ptr<Node> Parser::expression(short key) {
        std::shared_ptr<Node> left = term(key);

        while (m_current_token.c_type == lex::TokenType::PLUS or m_current_token.c_type == lex::TokenType::MINUS) {
            lex::Token op_token = m_current_token;
            advance();
            std::shared_ptr<Node> right = term(key);
            left = std::make_shared<BinaryOperatorNode>(left, op_token, right);
        }

        return left;
    }

    std::shared_ptr<Node> Parser::declaration(short key) {
        key = type_to_key(m_current_token.c_value);

        advance();
        if (m_current_token.c_type != lex::TokenType::IDENTIFIER) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected Identifier here.");
        }

        auto identifier = m_current_token;
        auto ident_name = identifier.c_value;
        if (m_key_map.contains(ident_name)) {
            throw err::InvalidSyntaxError(identifier.c_start_pos, identifier.c_end_pos,
                                          "Redefinition of variable '" + ident_name +
                                          "'."); //TODO CUSTOM ERROR HERE
        }
        m_key_map[ident_name] = key;
        advance();
        if (m_current_token.c_type != lex::TokenType::EQUALS) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '=' here.");
        }
        advance();
        auto expr = expression(key);
        return std::make_shared<VariableAssignNode>(identifier, expr);
    }

    std::shared_ptr<Node> Parser::assignment(short key) {

        auto identifier = m_current_token;
        auto ident_name = identifier.c_value;
        if (!m_key_map.contains(ident_name)) {
            throw err::InvalidSyntaxError(identifier.c_start_pos, identifier.c_end_pos,
                                          "Variable '" + ident_name +
                                          "' is not defined."); //TODO CUSTOM ERROR HERE
        }
        key = m_key_map[ident_name];
        advance();
        if (m_current_token.c_type != lex::TokenType::EQUALS) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '=' here.");
        }
        advance();
        auto expr = expression(key);
        return std::make_shared<VariableAssignNode>(identifier, expr);
    }

    Parser::Parser() : m_tokens(), m_current_token(lex::Token::NULL_TOKEN), m_key_map(), m_index(-1) {}

//    Parser::Parser(const std::vector<lex::Token> &tokens) : m_tokens(tokens), m_current_token(lex::Token::NULL_TOKEN),
//                                                            m_index(-1) {
//        advance();
//    }

    void Parser::import_tokens(const std::vector<lex::Token> &tokens) {
        m_tokens = tokens;
        m_index = -1;
        advance();
    }

    std::shared_ptr<Node> Parser::parse() {
        std::shared_ptr<Node> abstract_syntax_tree;
        if (m_current_token.c_type == lex::TokenType::VAR_KEYWORD) {
            abstract_syntax_tree = declaration(0);
        } else if (m_current_token.c_type == lex::TokenType::IDENTIFIER) {
            abstract_syntax_tree = assignment(0);
        } else {
            abstract_syntax_tree = expression(0);
        }

        if (m_current_token.c_type != lex::TokenType::EOL) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '+', '-', '*' or '/' here.");
        }

        return abstract_syntax_tree;
    }

} // par
