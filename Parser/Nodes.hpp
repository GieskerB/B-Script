#ifndef B_SHARP_NODES_HPP
#define B_SHARP_NODES_HPP

#include "../Lexer/Token.hpp"

namespace par {

    struct NumberNode {
        lex::Token token;
    };

    struct BinOpNode {
        lex::Token left_node, op_token, right_node;
    };
} // par



#endif //B_SHARP_NODES_HPP
