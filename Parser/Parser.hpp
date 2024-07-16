//
// Created by bjarn on 21.06.2024.
//

#ifndef B_SHARP_PARSER_HPP
#define B_SHARP_PARSER_HPP

#include <vector>
#include <memory>

#include "../Lexer/Token.hpp"
#include "Nodes.hpp"
#include "../DataTypes/Numbers.hpp"

namespace par {

    class Parser {

        std::vector<lex::Token> m_tokens;
        lex::Token m_current_token;
        int m_index;

        lex::Token advance();

        static short type_to_key(const std::string&);

        std::shared_ptr<Node> factor(short);
        std::shared_ptr<Node> term(short);
        std::shared_ptr<Node> expression(short);
        std::shared_ptr<Node> declaration(short = 0);



    public:

        Parser() = delete;

        Parser(const std::vector<lex::Token> &);

        std::shared_ptr<Node> parse();

    };
} // par

#endif //B_SHARP_PARSER_HPP
