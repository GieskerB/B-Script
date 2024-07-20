#ifndef B_SHARP_SYMBOLETABLE_HPP
#define B_SHARP_SYMBOLETABLE_HPP

#include <unordered_map>
#include <string>
#include <memory>


#include  "Context.hpp"

namespace dat {
    class DataType;
}

namespace itp {
    class SymbolTable {

        std::unordered_map<std::string, std::shared_ptr<dat::DataType>> m_variables{};
        SymbolTable *p_parent;

    public:

        explicit SymbolTable(SymbolTable *parent = nullptr);

        std::shared_ptr<dat::DataType> get(const std::string &) const;

        void set(const std::string &, const std::shared_ptr<dat::DataType> &);

    };
} // itp

#endif //B_SHARP_SYMBOLETABLE_HPP
