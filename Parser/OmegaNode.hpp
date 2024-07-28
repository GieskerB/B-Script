#ifndef B_SHARP_OMEGANODE_HPP
#define B_SHARP_OMEGANODE_HPP

#include <memory>

#include "../Lexer/Position.hpp"
#include "../Lexer/Token.hpp"

namespace par {

    enum NodeType: char {
        NONE,BINARY, UNARY,VALUE, VARIABLE_ACCESS, VARIABLE_ASSIGN
    };

    class OmegaNode {

        NodeType c_NODE_TYPE;
        lex::Position m_start_position,m_end_position;
        lex::Token m_token;
        std::shared_ptr<OmegaNode> p_left_node, p_right_node;
        short m_variable_key;

    public:

        OmegaNode();
        OmegaNode(NodeType, lex::Token);
        OmegaNode(NodeType, lex::Token , short);
        OmegaNode(NodeType, lex::Token , const OmegaNode&);
        OmegaNode(NodeType, lex::Token , const OmegaNode&, const OmegaNode&);

        void print() const;

        [[nodiscard]] NodeType get_node_type() const;
        [[nodiscard]] lex::Position get_start_position() const;
        [[nodiscard]] lex::Position get_end_position() const;
        [[nodiscard]] lex::Token get_token() const;
        [[nodiscard]] OmegaNode get_left() const;
        [[nodiscard]] OmegaNode get_right() const;
        [[nodiscard]] short get_variable_key() const;


    };

} // par

#endif //B_SHARP_OMEGANODE_HPP
