#include <iostream>
#include "Nodes.hpp"

namespace par {

    Node::Node(NodeType nt): nodeType(nt) {
#ifdef DEBUG
        std::cout << "Node created!\n";
#endif
    }

    Node::~Node() {
#ifdef DEBUG
        std::cout << "Node destroid!\n";
#endif
    }

    NumberNode::NumberNode(const lex::Token &tok): Node(NUMBER) {
        num_token = tok;
    }

    void NumberNode::print() {
        std::cout << num_token;
    }


    UnaryOperatorNode::UnaryOperatorNode(const lex::Token &tok, Node *node): Node(UNARY) {
        op_token = tok;
        node = node;
    }

    void UnaryOperatorNode::print() {
        std::cout << '{' << op_token;
        node->print();
        std::cout << '}';
    }

    BinaryOperatorNode::BinaryOperatorNode(Node *n1, const lex::Token &tok, Node *n2): Node(BINARY) {
        left_node = n1;
        op_token = tok;
        right_node = n2;
    }

    void BinaryOperatorNode::print() {
        std::cout << '{';
        left_node->print();
        std::cout << op_token;
        right_node->print();
        std::cout << '}';
    }
} // par