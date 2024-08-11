#ifndef B_SHARP_MEGANODE_HPP
#define B_SHARP_MEGANODE_HPP

#include <memory>

#include "../Lexer/Position.hpp"
#include "../Lexer/Token.hpp"

namespace par {

    enum NodeType: char {
        NONE,BINARY, UNARY,VALUE, VARIABLE_ACCESS, VARIABLE_ASSIGN, IF_CONDITION
    };

    class MegaNode {

        NodeType c_NODE_TYPE;
        lex::Position m_start_position,m_end_position;
        lex::Token m_token;
        std::shared_ptr<MegaNode> p_left_node, p_right_node;
        std::vector<MegaNode> m_in_block_statements;
        short m_variable_key;

    public:

        MegaNode();
        MegaNode(NodeType, lex::Token);
        MegaNode(NodeType, lex::Token , short);
        MegaNode(NodeType, lex::Token , const MegaNode&);
        MegaNode(NodeType, lex::Token , const MegaNode&, const MegaNode&);
        MegaNode(NodeType, lex::Token, const MegaNode&, const std::vector<MegaNode>&);

        void print() const;

        [[nodiscard]] NodeType get_node_type() const;
        [[nodiscard]] lex::Position get_start_position() const;
        [[nodiscard]] lex::Position get_end_position() const;
        [[nodiscard]] lex::Token get_token() const;
        [[nodiscard]] MegaNode get_left() const;
        [[nodiscard]] MegaNode get_right() const;
        [[nodiscard]] std::vector<MegaNode> get_block_statements() const;
        [[nodiscard]] short get_variable_key() const;


    };

} // par

#endif //B_SHARP_MEGANODE_HPP
