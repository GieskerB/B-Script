#ifndef B_SHARP_TOKEN_HPP
#define B_SHARP_TOKEN_HPP

#include <string>

#include "Lexer.hpp"
#include "Position.hpp"

namespace lex {

    enum TokenType {
        NONE,
        INT,
        DEC,
        KEYWORD,
        IDENTIFIER,
        PLUS = '+',
        MINUS = '-',
        MUL = '*',
        DIV = '/',
        LPAREN = '(',
        RPAREN = ')',
        EQUALS = '=',
        EOL = ';'
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
