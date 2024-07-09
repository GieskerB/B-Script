#include "Token.hpp"

#include <utility>

namespace lex {

    const Token Token::NULL_TOKEN;

    Token::Token():Token(TokenType::NONE,Position::NULL_POSITION) {}

    Token::Token(TokenType token_type, const Position& start, const Position& end, std::string value) : c_type(token_type),
                                                                                          c_value(std::move(value)),
                                                                                          c_start_pos(start),
                                                                                          c_end_pos(end) {
        if(c_end_pos == Position::NULL_POSITION) {
            c_end_pos = Position(c_start_pos);
            c_end_pos.advance();
        }
    }

    std::ostream &operator<<(std::ostream &os, const Token &token) {
        std::string temp_string;
        const std::string open{'{'}, close{'}'};
        os << open;
        switch (token.c_type) {
            case INT:
                temp_string = "INT:";
                os << temp_string << token.c_value;
                break;
            case DEC:
                temp_string = "DEC:";
                os << temp_string << token.c_value;
                break;
            case VAR_KEYWORD:
                temp_string = "VAR_KEYWORD:";
                os << temp_string << token.c_value;
                break;
            case IDENTIFIER:
                temp_string = "IDENTIFIER:";
                os << temp_string << token.c_value;
                break;
            case PLUS:
            case MINUS:
            case MUL:
            case DIV:
            case LPAREN:
            case RPAREN:
            case EQUALS:
                temp_string = static_cast<char>(token.c_type);
                os << temp_string;
                break;
            case NONE:
                temp_string = "NULL";
                os << temp_string;
                break;
            case EOL:
                temp_string = "\n";
                os << temp_string;
                break;
        }
        os << close;
        return os;
    }


} // lex