#ifndef B_SHARP_NODES_HPP
#define B_SHARP_NODES_HPP

#include <utility>
#include <memory>

#include "../Lexer/Token.hpp"

namespace par {

    enum NodeType {
        NUMBER,
        UNARY,
        BINARY
    };

    struct Node {

        const NodeType NODE_TYPE;

        lex::Position pos_start,pos_end;

        Node() = delete;
        explicit Node(NodeType, const lex::Position& , const lex::Position&);

        virtual void print() = 0;

    };

    struct NumberNode: public Node {
        lex::Token num_token;

        NumberNode() = delete;
        explicit NumberNode(lex::Token );
        void print() override;
    };

    struct UnaryOperatorNode: public Node {
        std::shared_ptr<Node> right_node;
        lex::Token op_token;

        UnaryOperatorNode() = delete;
        UnaryOperatorNode( lex::Token, const std::shared_ptr<Node>& );
        void print() override;
    };

    struct BinaryOperatorNode: public Node {
        std::shared_ptr<Node> left_node,right_node;
        lex::Token op_token;

        BinaryOperatorNode() = delete;
        explicit BinaryOperatorNode(const std::shared_ptr<Node>& , lex::Token  , const std::shared_ptr<Node>&  ) ;
        void print() override;
    };



} // par



#endif //B_SHARP_NODES_HPP
