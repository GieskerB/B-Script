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

    std::shared_ptr<Node> Parser::factor() {

        if (m_current_token.c_type == lex::TokenType::PLUS or m_current_token.c_type == lex::TokenType::MINUS) {
            lex::Token temp_token = m_current_token;
            advance();
            std::shared_ptr<Node> right = factor();
            return std::make_shared<UnaryOperatorNode>(temp_token, right);
        } else if (m_current_token.c_type == lex::TokenType::INT or m_current_token.c_type == lex::TokenType::DEC) {
            lex::Token temp_token = m_current_token;
            advance();
            return std::make_shared<NumberNode>(temp_token);
        } else if (m_current_token.c_type == lex::TokenType::IDENTIFIER) {
            lex::Token temp_token = m_current_token;
            advance();
            return std::make_shared<VariableAccessNode>(temp_token);
        }else if (m_current_token.c_type == lex::TokenType::LPAREN) {
            advance();
            std::shared_ptr<Node> expr = expression();
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

    std::shared_ptr<Node> Parser::term() {
        std::shared_ptr<Node> left = factor();

        while (m_current_token.c_type == lex::TokenType::MUL or m_current_token.c_type == lex::TokenType::DIV) {
            lex::Token op_token = m_current_token;
            advance();
            std::shared_ptr<Node> right = factor();
            left = std::make_shared<BinaryOperatorNode>(left, op_token, right);
        }

        return left;
    }

    std::shared_ptr<Node> Parser::expression() {
        if (m_current_token.c_type == lex::TokenType::VAR_KEYWORD) {
            advance();
            if (m_current_token.c_type != lex::TokenType::IDENTIFIER) {
                throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                              "Expected Identifier here.");
            }

            auto identifier = m_current_token;
            advance();
            if (m_current_token.c_type != lex::TokenType::EQUALS) {
                throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                              "Expected '=' here.");
            }
            advance();
            auto expr = expression();
            return std::make_shared<VariableAssignNode>(identifier,expr);

        }


        std::shared_ptr<Node> left = term();

        while (m_current_token.c_type == lex::TokenType::PLUS or m_current_token.c_type == lex::TokenType::MINUS) {
            lex::Token op_token = m_current_token;
            advance();
            std::shared_ptr<Node> right = term();
            left = std::make_shared<BinaryOperatorNode>(left, op_token, right);
        }

        return left;
    }


    Parser::Parser(const std::vector<lex::Token> &tokens) : m_tokens(tokens), m_current_token(lex::Token::NULL_TOKEN),
                                                            m_index(-1) {
        advance();
    }

    std::shared_ptr<Node> Parser::parse() {
        auto expr = expression();

        if (m_current_token.c_type != lex::TokenType::EOL) {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected '+', '-', '*' or '/' here.");
        }

        return expr;
    }
} // par
