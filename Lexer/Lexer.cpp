#include <stdexcept>
#include <iostream>
#include "Lexer.hpp"

namespace lex {

    bool Lexer::is_digit() const {
        return '0' <= m_current_char and m_current_char <= '9';
    }


    Token Lexer::make_number_token() {
        std::string number_string;
        char dot_count = 0;

        while (m_current_char != '\0' and (is_digit() or m_current_char == '.')) {
            std::cerr << "["<<m_pos<<"]";
            if (m_current_char == '.') {
                if (dot_count == 1) {
                    throw std::runtime_error("To many dots in number");
                }
                number_string.push_back('.');
                ++dot_count;
            }
            number_string.push_back(m_current_char);
            advance();
        }

        if (dot_count == 0) {
            return {TokenType::INT, number_string};
        } else {
            return {TokenType::DEC, number_string};
        }
    }

    Lexer::Lexer(std::string text) : m_text(std::move(text)), m_pos(-1), m_current_char('\0') {
        advance();
    }

    void Lexer::advance() {
        ++m_pos;
        if (m_pos < m_text.size()) {
            m_current_char = m_text[m_pos];
        } else {
            m_current_char = '\0';
        }
    }

    std::vector<Token> Lexer::make_token() {
        std::vector<Token> tokens;
        while (m_current_char != '\0') {
            std::cerr << m_pos << " ";

            if (is_digit()) {
                tokens.push_back(make_number_token());
            } else if (m_current_char == '+') {
                tokens.emplace_back(TokenType::PLUS);
            } else if (m_current_char == '-') {
                tokens.emplace_back(TokenType::MINUS);
            } else if (m_current_char == '*') {
                tokens.emplace_back(TokenType::MUL);
            } else if (m_current_char == '/') {
                tokens.emplace_back(TokenType::DIV);
            } else if (m_current_char == '(') {
                tokens.emplace_back(TokenType::LPAREN);
            } else if (m_current_char == ')') {
                tokens.emplace_back(TokenType::RPAREN);
            } else if (!(m_current_char == ' ' or m_current_char == '\t')) {
                //TODO: Custom Error here!
                throw std::runtime_error("Unknown Digit!");
            }
            advance();
        }
        return tokens;
    }

}

// lex