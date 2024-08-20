#ifndef B_SHARP_PARSER_HPP
#define B_SHARP_PARSER_HPP

#include <vector>
#include <memory>
#include <unordered_map>

#include "MegaNode.hpp"
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

        static short variable_type_to_extra(const std::string &var_type);

        MegaNode next_statement();

        MegaNode next_call(NextFunctionCall);
        MegaNode binary_operator(NextFunctionCall, const std::vector<lex::TokenType>&);
        MegaNode unary_operator(NextFunctionCall, const std::vector<lex::TokenType>&);

        MegaNode declaration();
        MegaNode assignment();
        MegaNode expression();
        MegaNode comparison_expression();
        MegaNode arithmetic_expression();
        MegaNode term();
        MegaNode factor();

        MegaNode if_block();

    public:

        Parser() = delete;
        explicit Parser(const std::vector<lex::Token>&);

        std::vector<MegaNode> parse_all();
    };
} // par

#endif //B_SHARP_PARSER_HPP
