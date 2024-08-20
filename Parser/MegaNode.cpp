#include "MegaNode.hpp"

#include <utility>

namespace par {

    MegaNode::MegaNode() : c_NODE_TYPE(NodeType::NONE), m_start_position(lex::Position::NULL_POSITION),
                           m_end_position(lex::Position::NULL_POSITION), m_token(lex::Token::NULL_TOKEN) {}


    MegaNode::MegaNode(NodeType node_type, lex::Token token) : c_NODE_TYPE(node_type),
                                                               m_start_position(lex::Position::NULL_POSITION),
                                                               m_end_position(lex::Position::NULL_POSITION),
                                                               m_token(std::move(token)) {}

    MegaNode::MegaNode(NodeType node_type, lex::Token token, const MegaNode &next) : c_NODE_TYPE(node_type),
                                                                                     m_start_position(
                                                                                             lex::Position::NULL_POSITION),
                                                                                     m_end_position(
                                                                                             lex::Position::NULL_POSITION),
                                                                                     m_token(std::move(token)),
                                                                                     p_right_node(
                                                                                             std::make_shared<MegaNode>(
                                                                                                     next)){}

    MegaNode::MegaNode(NodeType node_type, lex::Token token, const MegaNode &left, const MegaNode &right)
            : c_NODE_TYPE(node_type), m_start_position(lex::Position::NULL_POSITION),
              m_end_position(lex::Position::NULL_POSITION), m_token(std::move(token)),
              p_left_node(std::make_shared<MegaNode>(left)), p_right_node(std::make_shared<MegaNode>(right)) {}

    MegaNode::MegaNode(NodeType node_type, lex::Token token, const MegaNode &condition,
                       const std::vector<MegaNode> &in_block)
            : c_NODE_TYPE(node_type), m_start_position(lex::Position::NULL_POSITION),
              m_end_position(lex::Position::NULL_POSITION), m_token(std::move(token)),
              p_left_node(std::make_shared<MegaNode>(condition)), p_right_node(nullptr),
              m_in_block_statements(in_block) {}

    void MegaNode::print() const {
        std::cout << "\\/NODE PRINT NOT IMPLEMENTED\\/\n";
    }

    NodeType MegaNode::get_node_type() const {
        return c_NODE_TYPE;
    }

    lex::Position MegaNode::get_start_position() const {
        return m_start_position;
    }

    lex::Position MegaNode::get_end_position() const {
        return m_end_position;
    }

    lex::Token MegaNode::get_token() const {
        return m_token;
    }

    MegaNode MegaNode::get_left() const {
        return *p_left_node;
    }

    MegaNode MegaNode::get_right() const {
        return *p_right_node;
    }

    std::vector<MegaNode> MegaNode::get_block_statements() const {
        return m_in_block_statements;
    }


} // par