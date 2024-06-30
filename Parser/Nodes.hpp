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

        static int ALIVE_COUNTER;

        const NodeType m_nodeType;

        Node() = delete;
        explicit Node(NodeType);
        virtual ~Node() = 0;

        virtual void print() = 0;

    };

    struct NumberNode: public Node {
        lex::Token num_token;

        NumberNode() = delete;
        explicit NumberNode(lex::Token );
        ~NumberNode() override;
        void print() override;
    };

    struct UnaryOperatorNode: public Node {
        lex::Token op_token;
        Node* right_node;

        UnaryOperatorNode() = delete;
        UnaryOperatorNode( lex::Token  tok, Node * node );
        ~UnaryOperatorNode() override;
        void print() override;
    };

    struct BinaryOperatorNode: public Node {
        Node* left_node;
        lex::Token op_token;
        Node* right_node;

        BinaryOperatorNode() = delete;
        explicit BinaryOperatorNode(Node * l_node, lex::Token  tok, Node * r_node ) ;
        ~BinaryOperatorNode() override;
        void print() override;
    };



} // par



#endif //B_SHARP_NODES_HPP
