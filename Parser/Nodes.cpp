#include <iostream>
#include <utility>
#include "Nodes.hpp"

namespace par {

    Node::Node(NodeType nodeType, const lex::Position &start, const lex::Position &end) : NODE_TYPE(nodeType),
                                                                                          pos_start(start),
                                                                                          pos_end(end) {}

    NumberNode::NumberNode(lex::Token tok) : Node(NodeType::NUMBER, tok.c_start_pos, tok.c_end_pos),
                                             num_token(std::move(tok)) {}

    void NumberNode::print() {
        std::cout << num_token;
    }

    UnaryOperatorNode::UnaryOperatorNode(lex::Token tok, const std::shared_ptr<Node> &node) : Node(NodeType::UNARY,
                                                                                                   tok.c_start_pos,
                                                                                                   node->pos_end),
                                                                                              op_token(std::move(tok)),
                                                                                              right_node(node) {}

    void UnaryOperatorNode::print() {
        std::cout << ' ' << op_token;
        right_node->print();
    }

    BinaryOperatorNode::BinaryOperatorNode(const std::shared_ptr<Node> &l_node, lex::Token tok,
                                           const std::shared_ptr<Node> &r_node) : Node(NodeType::BINARY,
                                                                                       l_node->pos_start,
                                                                                       r_node->pos_end),
                                                                                  left_node(l_node),
                                                                                  op_token(std::move(tok)),
                                                                                  right_node(r_node) {}

    void BinaryOperatorNode::print() {
        std::cout << '(';
        left_node->print();
        std::cout << op_token;
        right_node->print();
        std::cout << ')';
    }

} // par