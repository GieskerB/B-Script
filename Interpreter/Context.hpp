//
// Created by bjarn on 03.07.2024.
//

#ifndef B_SHARP_CONTEXT_HPP
#define B_SHARP_CONTEXT_HPP

#include <memory>

#include "../Lexer/Position.hpp"
#include "SymboleTable.hpp"


namespace itp {

    class SymbolTable;

    class Context {

        std::string m_display_name;
        Context* p_parent;
        lex::Position m_parent_entry;
        std::shared_ptr<SymbolTable> p_symbol_table;

    public:

        static const Context NULL_CONTEXT;

        Context() =delete;
        explicit Context(std::string );
        Context(std::string , Context* , const lex::Position& , const SymbolTable&);

        [[nodiscard]] const std::string& get_display_name()const;
        [[nodiscard]] Context* get_parent() ;
        [[nodiscard]] const  lex::Position& get_position()const ;
        [[nodiscard]] SymbolTable& get_symbole_table() ;

    };

} // itp

#endif //B_SHARP_CONTEXT_HPP
