#ifndef B_SHARP_TOKEN_HPP
#define B_SHARP_TOKEN_HPP

#include <string>

namespace lex {

    enum TokenType {
        NONE,
        INT,
        DEC,
        PLUS = '+',
        MINUS = '-',
        MUL = '*',
        DIV = '/',
        LPAREN = '(',
        RPAREN = ')'
    };

    class Token {


    public:

        TokenType c_type;
        std::string c_value;

        static const Token NULL_TOKEN;

        Token() = default;
        Token(TokenType, std::string = "");

        friend std::ostream& operator<< (std::ostream &, const Token&);

    };

} // lex

#endif //B_SHARP_TOKEN_HPP
