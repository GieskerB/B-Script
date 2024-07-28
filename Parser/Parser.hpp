#ifndef B_SHARP_PARSER_HPP
#define B_SHARP_PARSER_HPP

#include <vector>
#include <memory>
#include <unordered_map>

#include "OmegaNode.hpp"
#include "../DataTypes/Number.hpp"

namespace par {

    enum NextFunctionCall: char {
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

        OmegaNode next_call(NextFunctionCall,short);
        OmegaNode binary_operator(NextFunctionCall,const std::vector<lex::TokenType>&,short);
        OmegaNode unary_operator(NextFunctionCall,const std::vector<lex::TokenType>&,short);

        OmegaNode declaration();
        OmegaNode assignment();
        OmegaNode expression(short = 0);
        OmegaNode comparison_expression(short);
        OmegaNode arithmetic_expression(short);
        OmegaNode term(short);
        OmegaNode factor(short);


    public:

        Parser();

        void import_tokens(const std::vector<lex::Token> &);

        OmegaNode parse();

    };
} // par

#endif //B_SHARP_PARSER_HPP
