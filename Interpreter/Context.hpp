//
// Created by bjarn on 03.07.2024.
//

#ifndef B_SHARP_CONTEXT_HPP
#define B_SHARP_CONTEXT_HPP

#include "../Lexer/Position.hpp"

namespace itp {

    class Context {

        std::string m_display_name;
        Context* p_parent;
        lex::Position m_parent_entry;

    public:

        static const Context NULL_CONTEXT;

        Context() =delete;
        explicit Context(std::string display_name);
        Context(std::string display_name, Context* parent, const lex::Position& parent_entry);

        std::string get_display_name() const;
        Context* get_parent() const;
        lex::Position get_position() const;

    };

} // itp

#endif //B_SHARP_CONTEXT_HPP
