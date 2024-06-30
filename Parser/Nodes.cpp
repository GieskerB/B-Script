#include <iostream>
#include <utility>
#include "Nodes.hpp"

namespace par {

    int Node::ALIVE_COUNTER = 0;

    Node::Node(NodeType nodeType) : m_nodeType(nodeType) {
        // TODO: Debug Print here
        ++Node::ALIVE_COUNTER;
    }

    Node::~Node() {
        // TODO: Debug Print here
        --Node::ALIVE_COUNTER;
    }

    NumberNode::NumberNode(lex::Token tok) : Node(NUMBER), num_token(std::move(tok)) {}

    NumberNode::~NumberNode() = default;

    void NumberNode::print() {
        std::cout << num_token;
    }


    UnaryOperatorNode::UnaryOperatorNode(lex::Token tok, Node *node) : Node(UNARY), op_token(std::move(tok)),
                                                                       right_node(node) {}

    UnaryOperatorNode::~UnaryOperatorNode(){
        delete right_node;
    }

    void UnaryOperatorNode::print() {
        std::cout << ' ' << op_token;
        right_node->print();
        std::cout ;
    }

    BinaryOperatorNode::BinaryOperatorNode(Node *l_node, lex::Token tok, Node *r_node) : Node(BINARY),
                                                                                         left_node(l_node),
                                                                                         op_token(std::move(tok)),
                                                                                         right_node(r_node) {}

    BinaryOperatorNode::~BinaryOperatorNode(){
        delete left_node;
        delete right_node;
    }

    void BinaryOperatorNode::print() {
        std::cout << '(';
        left_node->print();
        std::cout << op_token;
        right_node->print();
        std::cout << ')';
    }
} // par