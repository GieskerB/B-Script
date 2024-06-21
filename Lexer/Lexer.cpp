#include <stdexcept>
#include <iostream>
#include "Lexer.hpp"
#include "../FileReader/FileReader.hpp"
#include "../Error/Error.hpp"

namespace lex {

    bool Lexer::is_digit() const {
        return '0' <= m_current_char and m_current_char <= '9';
    }


    Token Lexer::make_number_token() {
        std::string number_string;
        char dot_count = 0;

        while (m_current_char != '\0' and (is_digit() or m_current_char == '.')) {
            if (m_current_char == '.') {
                if (dot_count == 1) {
                    throw std::runtime_error("To many dots in number");
                }
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

    Lexer::Lexer(const std::string &file_name) : m_pos({-1, 0, -1, file_name}), m_current_char('\0') {

        FileReader fr;
        fr.open_file(file_name);

        while (fr.can_read()) {
            m_text += (fr.read_line() + '\n');
        }

        advance();
    }

    void Position::advance(char current_char) {
        ++index;
        if (current_char == '\n') {
            ++line;
            column = 0;
        } else {
            ++column;
        }
    }

    void Lexer::advance() {
        m_pos.advance(m_current_char);
        if (m_pos.index < m_text.size()) {
            m_current_char = m_text[m_pos.index];
        } else {
            m_current_char = '\0';
        }
    }

    std::vector<Token> Lexer::make_token() {
        std::vector<Token> tokens;
        while (m_current_char != '\0') {
            if (m_current_char == ' ' or m_current_char == '\t' or m_current_char == '\n') {
                advance();
            } else if (is_digit()) {
                tokens.push_back(make_number_token());
            } else if (m_current_char == '+') {
                tokens.emplace_back(TokenType::PLUS);
                advance();
            } else if (m_current_char == '-') {
                tokens.emplace_back(TokenType::MINUS);
                advance();
            } else if (m_current_char == '*') {
                tokens.emplace_back(TokenType::MUL);
                advance();
            } else if (m_current_char == '/') {
                tokens.emplace_back(TokenType::DIV);
                advance();
            } else if (m_current_char == '(') {
                tokens.emplace_back(TokenType::LPAREN);
                advance();
            } else if (m_current_char == ')') {
                tokens.emplace_back(TokenType::RPAREN);
                advance();
            } else {
                //TODO: Custom Error here!
                throw err::IllegalCharError(
                        "in file '" + m_pos.file_name + "' at line " + std::to_string(m_pos.line) + ", column " +
                        std::to_string(m_pos.column));
            }
        }
        return tokens;
    }

}

// lex