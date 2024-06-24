//
// Created by bjarn on 21.06.2024.
//

#include <iostream>
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

    Node* Parser::factor() {
        if(m_current_token.c_type == lex::TokenType::INT or m_current_token.c_type == lex::TokenType::DEC) {
           lex::Token temp_token = m_current_token;
            advance();
            return new NumberNode(temp_token);
        }
        throw 1; // TODO:: Custom Error here!
    }

    Node* Parser::term() {
        Node* left = factor();

        while (m_current_token.c_type == lex::TokenType::MUL or m_current_token.c_type == lex::TokenType::DIV){
            lex::Token op_token= m_current_token;
            advance();
            Node * right = factor();
            left = new BinaryOperatorNode(left,op_token,right);
        }

        return left;
    }

    Node* Parser::expression() {
        Node* left = term();

        while (m_current_token.c_type == lex::TokenType::PLUS or m_current_token.c_type == lex::TokenType::MINUS){
            lex::Token op_token= m_current_token;
            advance();
            Node * right = term();
            left = new BinaryOperatorNode(left,op_token,right);
        }

        return left;
    }


    Parser::Parser(const std::vector<lex::Token> &tokens) : m_tokens(tokens), m_current_token(lex::Token::NULL_TOKEN),
                                                            m_index(-1) {
        advance();
    }

    Node *Parser::parse() {
        return expression();
    }
} // par
