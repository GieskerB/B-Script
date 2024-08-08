#include "Token.hpp"

#include <utility>

namespace lex {

    const Token Token::NULL_TOKEN;

    Token::Token():Token(TokenType::NONE,Position::NULL_POSITION) {}

    Token::Token(TokenType token_type, const Position& start, const Position& end, std::string value) : c_type(token_type),
                                                                                                        c_value(std::move(value)),
                                                                                                        c_start_pos(start),
                                                                                                        c_end_pos(end){
        if(c_end_pos == Position::NULL_POSITION) {
            c_end_pos = Position(c_start_pos);
            c_end_pos.advance();
        }
    }


    std::ostream &operator<<(std::ostream &os, const Token &token) {
        std::string temp_string;
        const std::string open{'{'}, close{'}'};
        switch (token.c_type) {
            case VALUE:
                temp_string = "VALUE:";
                os<< open << temp_string << token.c_value<< close;
                break;
            case VAR_KEYWORD:
                temp_string = "VAR_KEYWORD:";
                os<< open << temp_string << token.c_value<< close;
                break;
            case IDENTIFIER:
                temp_string = "IDENTIFIER:";
                os<< open<< temp_string << token.c_value<< close;
                break;
            case PLUS:
            case MINUS:
            case MULTIPLY:
            case DIVIDE:
            case EQUALS:
            case LESS_THEN:
            case GREATER_THEN:
            case LOGIC_NOT:
            case END_OF_LINE:
                temp_string = static_cast<char>(token.c_type);
                os << temp_string;
                break;
            case LEFT_ROUND_PARENTHESES:
            case RIGHT_ROUND_PARENTHESES:
            case LEFT_CURVED_PARENTHESES:
            case RIGHT_CURVED_PARENTHESES:
            case LEFT_SQUARED_PARENTHESES:
            case RIGHT_SQUARED_PARENTHESES:
                temp_string = static_cast<char>(token.c_type - 'p');
                os << " " <<temp_string<<" ";
                break;
                break;
            case LOGIC_AND:
            case LOGIC_OR:
                temp_string = static_cast<char>(token.c_type / 2);
                os << temp_string << temp_string;
                break;
            case DOUBLE_EQUALS:
            case LESS_THEN_OR_EQUALS:
            case GREATER_THEN_OR_EQUALS:
            case NOT_EQUALS:
                temp_string = static_cast<char>(token.c_type - '=');
                os << temp_string << '=';
                break;
            case IF:
                temp_string = "IF";
                os << temp_string;
                break;
            case NONE:
                temp_string = "NULL";
                os<< open << temp_string << token.c_value<< close;
                break;
        }
        return os;
    }

} // lex