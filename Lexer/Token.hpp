#ifndef B_SHARP_TOKEN_HPP
#define B_SHARP_TOKEN_HPP

#include <string>

#include "Lexer.hpp"
#include "Position.hpp"

namespace lex {

    enum TokenType: unsigned short {
        NONE,
        VALUE,
        VAR_KEYWORD,
        IDENTIFIER,
        IF,
        PLUS = '+',
        MINUS = '-',
        MULTIPLY = '*',
        DIVIDE = '/',
        LEFT_ROUND_PARENTHESES = '(' + 'p', // Added a 'p' here to prevent conflicts in enum values
        RIGHT_ROUND_PARENTHESES = ')' + 'p',
        LEFT_CURVED_PARENTHESES = '{' + 'p',
        RIGHT_CURVED_PARENTHESES = '}' + 'p',
        LEFT_SQUARED_PARENTHESES = '[' + 'p',
        RIGHT_SQUARED_PARENTHESES = ']' + 'p',
        EQUALS = '=',
        END_OF_LINE = ';',
        END_OF_FILE = '\n',
        LESS_THEN = '<',
        GREATER_THEN= '>',
        NOT_EQUALS = '!' + '=',
        DOUBLE_EQUALS = '=' + '=',
        LESS_THEN_OR_EQUALS= '<' + '=',
        GREATER_THEN_OR_EQUALS= '>' + '=',
        LOGIC_AND = '&' * 2,
        LOGIC_OR = '|' * 2,
        LOGIC_NOT = '!'
    };

    class Token {
    public:
        const TokenType c_type;
        const std::string c_value;
        const short c_parameter;
        Position c_start_pos, c_end_pos;

        Token() = delete;
        explicit Token(TokenType, const Position&, const Position& = Position::NULL_POSITION, std::string = "", short = 0);

        friend std::ostream &operator<<(std::ostream &, const Token &);
    };

} // lex

#endif //B_SHARP_TOKEN_HPP
