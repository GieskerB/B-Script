//
// Created by bjarn on 21.06.2024.
//

#include "Parser.hpp"
#include "../Error/Error.hpp"


Parser::Parser(const std::vector<lex::Token> &tokens) : m_tokens(tokens), m_current_token(lex::Token::NULL_TOKEN),
                                                        m_index(-1) {
    advance();
}

lex::Token Parser::advance() {
    ++m_index;
    if (m_index < m_tokens.size()) {
        m_current_token = m_tokens[m_index];
    }
    return m_current_token;
}

par::NumberNode Parser::factor() {
    if(m_current_token.m_type == lex::TokenType::INT or m_current_token.m_type == lex::TokenType::DEC) {
        advance();
        return par::NumberNode(m_current_token);
    } else {
        throw 1; // TODO: Right Exception here
    }
}

lex::Token Parser::term() {
    auto left = factor();

    while (m_current_token.m_type == lex::TokenType::MUL or m_current_token.m_type == lex::TokenType::DIV ) {
        auto op = m_current_token;
        advance();
        auto right = factor();
        // Vid2 Minute 7:00

    }
}

lex::Token Parser::expression() {
    return lex::Token();
}

