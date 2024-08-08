#include "OmegaNode.hpp"

#include <utility>

namespace par {

    OmegaNode::OmegaNode() : c_NODE_TYPE(NodeType::NONE), m_start_position(lex::Position::NULL_POSITION),
                             m_end_position(lex::Position::NULL_POSITION), m_token(lex::Token::NULL_TOKEN),
                             m_variable_key(0) {}


    OmegaNode::OmegaNode(NodeType node_type, lex::Token token) : c_NODE_TYPE(node_type),
                                                                 m_start_position(lex::Position::NULL_POSITION),
                                                                 m_end_position(lex::Position::NULL_POSITION),
                                                                 m_token(std::move(token)), m_variable_key(0) {}

    OmegaNode::OmegaNode(NodeType node_type, lex::Token token, short key) : c_NODE_TYPE(node_type), m_start_position(
            lex::Position::NULL_POSITION), m_end_position(lex::Position::NULL_POSITION), m_token(std::move(token)),
                                                                            m_variable_key(key) {}

    OmegaNode::OmegaNode(NodeType node_type, lex::Token token, const OmegaNode &next) : c_NODE_TYPE(node_type),
                                                                                        m_start_position(
                                                                                                lex::Position::NULL_POSITION),
                                                                                        m_end_position(
                                                                                                lex::Position::NULL_POSITION),
                                                                                        m_token(std::move(token)),
                                                                                        p_right_node(
                                                                                                std::make_shared<OmegaNode>(
                                                                                                        next)),
                                                                                        m_variable_key(0) {}

    OmegaNode::OmegaNode(NodeType node_type, lex::Token token, const OmegaNode &left, const OmegaNode &right)
            : c_NODE_TYPE(node_type), m_start_position(lex::Position::NULL_POSITION),
              m_end_position(lex::Position::NULL_POSITION), m_token(std::move(token)),
              p_left_node(std::make_shared<OmegaNode>(left)), p_right_node(std::make_shared<OmegaNode>(right)),
              m_variable_key(0) {}

    void OmegaNode::print() const {
        std::cout << "\\/NODE PRINT NOT IMPLEMENTED\\/\n";
    }

    NodeType OmegaNode::get_node_type() const {
        return c_NODE_TYPE;
    }

    lex::Position OmegaNode::get_start_position() const {
        return m_start_position;
    }

    lex::Position OmegaNode::get_end_position() const {
        return m_end_position;
    }

    lex::Token OmegaNode::get_token() const {
        return m_token;
    }

    OmegaNode OmegaNode::get_left() const {
        return *p_left_node;
    }

    OmegaNode OmegaNode::get_right() const {
        return *p_right_node;
    }

    short OmegaNode::get_variable_key() const {
        return m_variable_key;
    }

} // par