//
// Created by bjarn on 21.06.2024.
//

#ifndef B_SHARP_PARSER_HPP
#define B_SHARP_PARSER_HPP

#include <vector>
#include "../Lexer/Token.hpp"
#include "Nodes.hpp"

class Parser {

    std::vector<lex::Token> m_tokens;
    lex::Token m_current_token;
    int m_index;

public:

    Parser() = delete;
    Parser(const std::vector<lex::Token>&);

    lex::Token advance();

    par::NumberNode factor();
    lex::Token term();
    lex::Token expression();

};


#endif //B_SHARP_PARSER_HPP
