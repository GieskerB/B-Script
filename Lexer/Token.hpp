#ifndef B_SHARP_TOKEN_HPP
#define B_SHARP_TOKEN_HPP

#include <string>

#include "Lexer.hpp"
#include "Position.hpp"

namespace lex {

    enum TokenType: unsigned short {
        NONE,
        NUMBER,
        VAR_KEYWORD,
        IDENTIFIER,
        PLUS = '+',
        MINUS = '-',
        MULTIPLY = '*',
        DIVIDE = '/',
        LEFT_PARENTHESES = '(',
        RIGHT_PARENTHESES = ')',
        EQUALS = '=',
        END_OF_LINE = ';',
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

        TokenType c_type;
        std::string c_value;
        Position c_start_pos, c_end_pos;

        static const Token NULL_TOKEN;

        Token();
        explicit Token(TokenType, const Position&, const Position& = Position::NULL_POSITION, std::string = "");

        friend std::ostream &operator<<(std::ostream &, const Token &);

    };

} // lex

#endif //B_SHARP_TOKEN_HPP
