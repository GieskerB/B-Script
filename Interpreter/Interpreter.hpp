#ifndef B_SHARP_INTERPRETER_HPP
#define B_SHARP_INTERPRETER_HPP

#include <memory>
#include <variant>

#include "Context.hpp"
#include "../Parser/MegaNode.hpp"

namespace dat {
    class DataType;
}

typedef std::variant<dat::Boolean, dat::Integer, dat::Decimal, dat::String> VariantTypes ;

namespace itp {

    class Interpreter {

        static VariantTypes visit_if_condition_node(const par::MegaNode &, itp::Context &);
        static VariantTypes visit_variable_access_node(const par::MegaNode &, itp::Context &);
        static VariantTypes visit_variable_assign_node(const  par::MegaNode &, itp::Context &);
        static VariantTypes visit_value_node(const  par::MegaNode &, itp::Context &);
        static VariantTypes visit_unary_node(const  par::MegaNode &, itp::Context &);
        static VariantTypes visit_binary_node(const  par::MegaNode &, itp::Context &);

    public:

        static VariantTypes visit(const  par::MegaNode &, itp::Context &);

    };

} // itp

#endif //B_SHARP_INTERPRETER_HPP
