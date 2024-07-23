//
// Created by bjarn on 21.06.2024.
//

#ifndef B_SHARP_PARSER_HPP
#define B_SHARP_PARSER_HPP

#include <vector>
#include <memory>

#include "../Lexer/Token.hpp"
#include "Nodes.hpp"
#include "../DataTypes/Number.hpp"

namespace par {

    enum NextFunctionCall {
        EXPRESSION,
        COMP_EXPR,
        ARITH_EXPR,
        TERM,
        FACTOR
    };

    class Parser {

        std::vector<lex::Token> m_tokens;
        lex::Token m_current_token;
        std::unordered_map<std::string,short> m_key_map;
        int m_index;

        lex::Token advance();

        static short type_to_key(const std::string&);

        std::shared_ptr<Node> next_call(NextFunctionCall,short);
        std::shared_ptr<Node> binary_operator(NextFunctionCall,const std::vector<lex::TokenType>&,short);
        std::shared_ptr<Node> unary_operator(NextFunctionCall,const std::vector<lex::TokenType>&,short);

        std::shared_ptr<Node> declaration();
        std::shared_ptr<Node> assignment();
        std::shared_ptr<Node> expression(short = 0);
        std::shared_ptr<Node> comparison_expression(short);
        std::shared_ptr<Node> arithmetic_expression(short);
        std::shared_ptr<Node> term(short);
        std::shared_ptr<Node> factor(short);


    public:

        Parser();

        void import_tokens(const std::vector<lex::Token> &);

        std::shared_ptr<Node> parse();

    };
} // par

#endif //B_SHARP_PARSER_HPP
