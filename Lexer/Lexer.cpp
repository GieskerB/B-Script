#include <stdexcept>
#include "Lexer.hpp"
#include "../FileReader/FileReader.hpp"
#include "../Error/Error.hpp"

namespace lex {

    bool Lexer::is_digit() const {
        return '0' <= m_current_char and m_current_char <= '9';
    }

    bool Lexer::is_letter() const {
        return ('a' <= m_current_char and m_current_char <= 'z') or ('A' <= m_current_char and m_current_char <= 'Z') or
               '_' == m_current_char;
    }

    /**
     * From a sequence of digits and at mose one dot create a number token.
     */
    Token Lexer::make_number_token() {
        std::string number_string;
        char dot_count = 0;

        Position start = Position(m_pos);
        while (m_current_char != '\0' and (is_digit() or m_current_char == '.')) {
            if (m_current_char == '.') {
                if (dot_count == 1) {
                    throw err::InvalidSyntaxError(start, m_pos, "Too many dots in literal.");
                }
                ++dot_count;
            }
            number_string.push_back(m_current_char);
            advance();
        }

        if (dot_count == 0) {
            return Token{TokenType::INT, start, m_pos, number_string};
        } else {
            return Token{TokenType::DEC, start, m_pos, number_string};
        }
    }


    Token Lexer::make_word_token() {
        std::string word_string;
        Position start = Position(m_pos);

        while(m_current_char != '\0' and (is_digit() or is_letter())) {
            word_string.push_back(m_current_char);
            advance();
        }
    }

    Lexer::Lexer(const std::string &file_name) : m_pos{-1, 0, -1, file_name}, m_current_char('\0') {

        FileReader fr{};
        fr.open_file(file_name);

        while (fr.can_read()) {
            m_text += (fr.read_line() + '\n');
        }

        advance();
    }


    void Lexer::advance() {
        m_pos.advance(m_current_char);
        if (m_pos.index() < m_text.size()) {
            m_current_char = m_text[m_pos.index()];
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
            } else if (is_letter()) {
                tokens.push_back(make_word_token());
            } else if (m_current_char == '+') {
                tokens.emplace_back(TokenType::PLUS, m_pos);
                advance();
            } else if (m_current_char == '-') {
                tokens.emplace_back(TokenType::MINUS, m_pos);
                advance();
            } else if (m_current_char == '*') {
                tokens.emplace_back(TokenType::MUL, m_pos);
                advance();
            } else if (m_current_char == '/') {
                tokens.emplace_back(TokenType::DIV, m_pos);
                advance();
            } else if (m_current_char == '(') {
                tokens.emplace_back(TokenType::LPAREN, m_pos);
                advance();
            } else if (m_current_char == ')') {
                tokens.emplace_back(TokenType::RPAREN, m_pos);
                advance();
            } else if (m_current_char == ';') {
                tokens.emplace_back(TokenType::EOL, m_pos);
                advance();
            } else if (m_current_char == '=') {
                tokens.emplace_back(TokenType::EQUALS, m_pos);
                advance();
            } else {
                throw err::IllegalCharError(m_pos, "Character " + std::string{m_current_char} + " not allowed here");
            }
        }

        return tokens;
    }


}

// lex