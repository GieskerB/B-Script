#ifndef B_SHARP_INTERPRETER_HPP
#define B_SHARP_INTERPRETER_HPP

#include <memory>
#include <variant>

#include "Context.hpp"
#include "../Parser/OmegaNode.hpp"

namespace dat {
    class DataType;
}

typedef std::variant<dat::Boolean, dat::Integer, dat::Decimal, dat::String> VariantTypes ;

namespace itp {

    class Interpreter {

        /* static std::shared_ptr<dat::DataTypes>
         add_numbers(std::shared_ptr<dat::DataTypes> &, const std::shared_ptr<dat::DataTypes> &);

         static std::shared_ptr<dat::DataTypes>
         sub_numbers(std::shared_ptr<dat::DataTypes> &, const std::shared_ptr<dat::DataTypes> &);

         static std::shared_ptr<dat::DataTypes>
         mul_numbers(std::shared_ptr<dat::DataTypes> &, const std::shared_ptr<dat::DataTypes> &);

         static std::shared_ptr<dat::DataTypes>
         div_numbers(std::shared_ptr<dat::DataTypes> &, const std::shared_ptr<dat::DataTypes> &);*/

        static VariantTypes visit_variable_access_node(const par::OmegaNode &, itp::Context &);

        static VariantTypes visit_variable_assign_node(const  par::OmegaNode &, itp::Context &);

        static VariantTypes visit_value_node(const  par::OmegaNode &, itp::Context &);

        static VariantTypes visit_unary_node(const  par::OmegaNode &, itp::Context &);

        static VariantTypes visit_binary_node(const  par::OmegaNode &, itp::Context &);

    public:

        static VariantTypes visit(const  par::OmegaNode &, itp::Context &);

    };

} // itp

#endif //B_SHARP_INTERPRETER_HPP
