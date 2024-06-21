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

        const TokenType m_type;
        const std::string m_value;

        static const Token NULL_TOKEN;

        Token() = delete;
        Token(TokenType, std::string = "");

        friend std::ostream& operator<< (std::ostream &, const Token&);

    };

} // lex

#endif //B_SHARP_TOKEN_HPP
