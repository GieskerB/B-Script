#include "Token.hpp"

#include <utility>

namespace lex {

    const Token Token::NULL_TOKEN(TokenType::NONE);

    Token::Token(TokenType token_type, std::string value) : m_type(token_type), m_value(std::move(value)) {}

    std::ostream& operator<<(std::ostream & os, const Token & token) {
        std::string temp_string;
        const std::string open{'{'}, close{'}'};
        os << open;
        switch (token.m_type){
            case INT:
                temp_string = "INT:";
                os << temp_string << token.m_value;
                break;
            case DEC:
                temp_string = "DEC:";
                os << temp_string << token.m_value;
                break;
            case PLUS:
            case MINUS:
            case MUL:
            case DIV:
            case LPAREN:
            case RPAREN:
                temp_string = static_cast<char>(token.m_type);
                os << temp_string;
                break;
        }
        os << close;
        return os;
    }


} // lex