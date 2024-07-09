#ifndef B_SHARP_SYMBOLETABLE_HPP
#define B_SHARP_SYMBOLETABLE_HPP

#include <unordered_map>
#include <string>
#include <memory>


#include  "Context.hpp"
#include "../DataTypes/Numbers.hpp"

namespace num{
    class Number;
}

namespace itp {
    class SymbolTable {

        std::unordered_map<std::string, std::shared_ptr<num::Number>> m_variables{};
        SymbolTable *p_parent;

    public:

        explicit SymbolTable(SymbolTable *parent = nullptr);

        std::shared_ptr<num::Number> get(const std::string &) const;

        void set(const std::string &, const std::shared_ptr<num::Number> &);

    };
} // itp

#endif //B_SHARP_SYMBOLETABLE_HPP
