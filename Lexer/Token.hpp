#ifndef B_SHARP_TOKEN_HPP
#define B_SHARP_TOKEN_HPP

#include <string>

namespace lex {

    enum TokenType {
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

        TokenType m_type;
        std::string m_value;

    public:

        Token() = delete;
        Token(TokenType, std::string = "");

        friend std::ostream& operator<< (std::ostream &, const Token&);

    };

} // lex

#endif //B_SHARP_TOKEN_HPP
