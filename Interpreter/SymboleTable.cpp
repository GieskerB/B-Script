#include "SymboleTable.hpp"

namespace itp {
    SymbolTable::SymbolTable(SymbolTable *parent) : p_parent(parent) {}

    std::variant<dat::Boolean, dat::Integer, dat::Decimal, dat::String>& SymbolTable::get(const std::string & var_name)  {
        if (!m_variables.contains(var_name)) {
            if (p_parent == nullptr) {
                throw std::runtime_error("");
            } else {
                return p_parent->get(var_name);
            }
        }
        return m_variables.at(var_name);
    }

    void SymbolTable::set(const std::string & var_name,  dat::VariantTypes & var_value) {
        m_variables.emplace(var_name,std::move(var_value));
    }
} // itp