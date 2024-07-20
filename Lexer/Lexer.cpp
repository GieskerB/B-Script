#include <sstream>
#include <algorithm>

#include "Lexer.hpp"
#include "../FileReader/FileReader.hpp"
#include "../Error/Error.hpp"

namespace lex {

    bool Lexer::is_digit() const {
        return '0' <= m_current_char and m_current_char <= '9';
    }

    bool Lexer::is_letter() const {
        return ('a' <= m_current_char and m_current_char <= 'z') or ('A' <= m_current_char and m_current_char <= 'Z') or
               '_' == m_current_char or m_current_char == ':';
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

        return Token{TokenType::NUM, start, m_pos, number_string};
    }


    Token Lexer::make_word_token() {
        std::stringstream word_string_stream;
        Position start = Position(m_pos);

        bool has_colon{false};
        while (m_current_char != '\0' and (is_digit() or is_letter())) {
            if (m_current_char == ':') {
                has_colon = true;
            }
            word_string_stream << m_current_char;
            advance();
        }
        const std::string word_string = word_string_stream.str();
        if (CONSTANTS.VARIABLE_KEYWORDS.end() !=
            std::find(CONSTANTS.VARIABLE_KEYWORDS.begin(), CONSTANTS.VARIABLE_KEYWORDS.end(), word_string)) {
            return Token{TokenType::VAR_KEYWORD, start, m_pos, word_string};
        } else {
            if (has_colon) {
                throw err::IllegalCharError(m_pos, "':' not allowed in identifier");
            }
            return Token{TokenType::IDENTIFIER, start, m_pos, word_string};
        }
    }



    Token Lexer::make_not_equals_token() {
        // Expected char '=' before this call
        Position start = Position(m_pos);
        advance();

        if(m_current_char != '=') {
            throw err::IllegalCharError(m_pos,"'=' (after '!')");
        }
        return Token{TokenType::NOT_EQUALS, start,m_pos, "!="};
    }
    Token Lexer::make_equals_token() {
        // Expected char '!' before this call
        Position start = Position(m_pos);
        advance();

        if(m_current_char == '=') {
            advance();
            return Token{TokenType::DOUBLE_EQUALS, start, m_pos, "=="};
        }
        return Token{TokenType::EQUALS,start,m_pos, "="};
    }

    Token Lexer::make_less_than_token() {
        // Expected char '<' before this call
        Position start = Position(m_pos);
        advance();

        if(m_current_char == '=') {
            advance();
            return Token{TokenType::LESS_THEN_OR_EQUALS, start, m_pos, "=="};
        }
        return Token{TokenType::LESS_THEN,start,m_pos, "="};
    }

    Token Lexer::make_greater_than_token() {
        // Expected char '>' before this call
        Position start = Position(m_pos);
        advance();

        if(m_current_char == '=') {
            advance();
            return Token{TokenType::GREATER_THEN_OR_EQUALS, start, m_pos, "=="};
        }
        return Token{TokenType::GREATER_THEN,start,m_pos, "="};

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

    bool Lexer::can_lex() const {
        return m_current_char != '\0';
    }

    std::vector<Token> Lexer::all() {
        std::vector<Token> tokens;
        while (can_lex()) {
            auto line_tokens = next_line();
            tokens.insert(tokens.end(), line_tokens.begin(), line_tokens.end());
        }
        return tokens;
    }

    std::vector<Token> Lexer::next_line() {
        std::vector<Token> tokens;
        while (can_lex()) {
            if (m_current_char == '\n') {
                do {
                    advance();
                } while (m_current_char == '\n');
                return tokens;
            } else if (m_current_char == ' ' or m_current_char == '\t') {
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
            } else if (m_current_char == '!') {
                tokens.push_back(make_not_equals_token());
            } else if (m_current_char == '=') {
                tokens.push_back(make_equals_token());
            } else if (m_current_char == '<') {
                tokens.push_back(make_less_than_token());
            } else if (m_current_char == '>') {
                tokens.push_back(make_greater_than_token());
            } else {
                throw err::IllegalCharError(m_pos, "Character " + std::string{m_current_char} + " not allowed here");
            }
        }

        return tokens;
    }


}

// lex