#ifndef B_SHARP_NODES_HPP
#define B_SHARP_NODES_HPP

#include <utility>

#include "../Lexer/Token.hpp"

namespace par {

    enum NodeType {
        NUMBER,
        UNARY,
        BINARY
    };

    struct Node {

        const NodeType nodeType;

        Node() = delete;
        explicit Node(NodeType);
        ~Node();

        virtual void print() = 0;

    };

    struct NumberNode: public Node {
        lex::Token num_token;

        NumberNode() = delete;
        explicit NumberNode(const lex::Token&);
        void print() override;
    };

    struct UnaryOperatorNode: public Node {
        lex::Token op_token;
        Node* node;

        UnaryOperatorNode() = delete;
        UnaryOperatorNode( const lex::Token& tok, Node * node );
        void print() override;
    };

    struct BinaryOperatorNode: public Node {
        Node* left_node;
        lex::Token op_token;
        Node* right_node;

        BinaryOperatorNode() = delete;
        explicit BinaryOperatorNode(Node * n1, const lex::Token& tok, Node * n2 ) ;
        void print() override;
    };



} // par



#endif //B_SHARP_NODES_HPP
