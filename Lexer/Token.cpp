#include "Token.hpp"

#include <utility>

namespace lex {

    const Token Token::NULL_TOKEN(TokenType::NONE);

    Token::Token(TokenType token_type, std::string value) : c_type(token_type), c_value(std::move(value)) {}

    std::ostream& operator<<(std::ostream & os, const Token & token) {
        std::string temp_string;
        const std::string open{'{'}, close{'}'};
        os << open;
        switch (token.c_type){
            case INT:
                temp_string = "INT:";
                os << temp_string << token.c_value;
                break;
            case DEC:
                temp_string = "DEC:";
                os << temp_string << token.c_value;
                break;
            case PLUS:
            case MINUS:
            case MUL:
            case DIV:
            case LPAREN:
            case RPAREN:
                temp_string = static_cast<char>(token.c_type);
                os << temp_string;
                break;
        }
        os << close;
        return os;
    }


} // lex