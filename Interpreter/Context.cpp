#include "Context.hpp"

#include <utility>

namespace itp {

    const Context Context::NULL_CONTEXT("NULL");

    Context::Context(std::string display_name) : Context(std::move(display_name), nullptr,
                                                         lex::Position::NULL_POSITION) {}

    Context::Context(std::string display_name, Context *parent, const lex::Position& parent_entry) : m_display_name(
            std::move(display_name)), p_parent(parent),
                                                                                                    m_parent_entry(
                                                                                                            parent_entry) {

    }

    std::string Context::get_display_name()  const{
        return m_display_name;
    }

    Context *Context::get_parent()  const{
        return p_parent;
    }

    lex::Position Context::get_position()  const{
        return m_parent_entry;
    }
} // itp