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

        return Token{TokenType::VALUE, start, m_pos, number_string};
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

    Token Lexer::make_two_char_token(char first_char, char second_char, TokenType single_token_type,
                                     TokenType double_token_type) {
        auto start = Position(m_pos);
        if (m_current_char != first_char) {
            throw std::runtime_error("first Character does not match the expectation in make_two_char_token()");
        }
        advance();

        if (m_current_char == second_char) {
            advance();
            std::string repr{};
            repr.push_back(first_char);
            repr.push_back(second_char);
            return Token{double_token_type, start, m_pos, repr};
        } else if (single_token_type == TokenType::NONE) {
            throw err::IllegalCharError(m_pos, "Expected '" + std::to_string(second_char) + "' (after '" +
                                               std::to_string(first_char) + "')");
        }
        return Token{single_token_type, start, m_pos, std::to_string(first_char)};


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
                tokens.emplace_back(TokenType::MULTIPLY, m_pos);
                advance();
            } else if (m_current_char == '/') {
                tokens.emplace_back(TokenType::DIVIDE, m_pos);
                advance();
            } else if (m_current_char == '(') {
                tokens.emplace_back(TokenType::LEFT_PARENTHESES, m_pos);
                advance();
            } else if (m_current_char == ')') {
                tokens.emplace_back(TokenType::RIGHT_PARENTHESES, m_pos);
                advance();
            } else if (m_current_char == ';') {
                tokens.emplace_back(TokenType::END_OF_LINE, m_pos);
                advance();
            } else if (m_current_char == '!') {
                tokens.push_back(make_two_char_token('!', '=', TokenType::LOGIC_NOT, TokenType::NOT_EQUALS));
            } else if (m_current_char == '=') {
                tokens.push_back(make_two_char_token('=', '=', TokenType::EQUALS, TokenType::DOUBLE_EQUALS));
            } else if (m_current_char == '<') {
                tokens.push_back(make_two_char_token('<', '=', TokenType::LESS_THEN, TokenType::LESS_THEN_OR_EQUALS));
            } else if (m_current_char == '>') {
                tokens.push_back(
                        make_two_char_token('>', '=', TokenType::GREATER_THEN, TokenType::GREATER_THEN_OR_EQUALS));
            } else if (m_current_char == '&') {
                tokens.push_back(make_two_char_token('&', '&', TokenType::NONE, TokenType::LOGIC_AND));
            } else if (m_current_char == '|') {
                tokens.push_back(make_two_char_token('|', '|', TokenType::NONE, TokenType::LOGIC_OR));
            } else {
                throw err::IllegalCharError(m_pos, "Character " + std::string{m_current_char} + " not allowed here");
            }
        }

        return tokens;
    }


}

// lex