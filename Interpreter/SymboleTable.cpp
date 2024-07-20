#include "SymboleTable.hpp"
namespace itp {
    SymbolTable::SymbolTable(SymbolTable *parent) : p_parent(parent) {}

    std::shared_ptr<dat::DataType> SymbolTable::get(const std::string &var_name) const{
        if (!m_variables.contains(var_name)) {
            if (p_parent == nullptr) {
                throw std::runtime_error("");
            } else {
                return p_parent->get(var_name);
            }
        }
        return m_variables.at(var_name);
    }

    void SymbolTable::set(const std::string &var_name, const std::shared_ptr<dat::DataType> &var_value) {
        m_variables[var_name] = var_value;
    }
} // itp