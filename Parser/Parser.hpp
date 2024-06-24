//
// Created by bjarn on 21.06.2024.
//

#ifndef B_SHARP_PARSER_HPP
#define B_SHARP_PARSER_HPP

#include <vector>
#include "../Lexer/Token.hpp"
#include "Nodes.hpp"
#include "../DataTypes/Numbers.hpp"

namespace par {

    class Parser {

        std::vector<lex::Token> m_tokens;
        lex::Token m_current_token;
        int m_index;

        lex::Token advance();

        Node* factor();

        Node* term();

        Node* expression();

    public:

        Parser() = delete;

        Parser(const std::vector<lex::Token> &);

        Node* parse();

    };
} // par

#endif //B_SHARP_PARSER_HPP
