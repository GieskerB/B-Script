#include "Context.hpp"
#include "SymboleTable.hpp"

#include <utility>

namespace itp {

    const Context Context::NULL_CONTEXT("NULL");

    Context::Context(std::string display_name) : Context(std::move(display_name), nullptr,
                                                         lex::Position::NULL_POSITION, SymbolTable()) {}

    Context::Context(std::string display_name, Context *parent, const lex::Position &parent_entry,
                     SymbolTable symbole_table) : m_display_name(
            std::move(display_name)), p_parent(parent), m_parent_entry(parent_entry)
            ,p_symbol_table(std::move(symbole_table))
            {}

    const std::string &Context::get_display_name() const {
        return m_display_name;
    }

    Context *Context::get_parent() {
        return p_parent;
    }

    const lex::Position &Context::get_position() const {
        return m_parent_entry;
    }

    SymbolTable &Context::get_symbole_table() {
        return p_symbol_table;
    }

} // itp