#ifndef B_SHARP_SYMBOLETABLE_HPP
#define B_SHARP_SYMBOLETABLE_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <variant>

#include "../DataTypes/Utility.hpp"

namespace itp {
    class SymbolTable {
        std::unordered_map<std::string, dat::VariantTypes> m_variables{};
        SymbolTable *p_parent;

    public:
        explicit SymbolTable(SymbolTable *parent = nullptr);

        dat::VariantTypes& get(const std::string &);
        void set(const std::string &,  dat::VariantTypes &);
    };
} // itp

#endif //B_SHARP_SYMBOLETABLE_HPP
