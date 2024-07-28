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

        /* static std::shared_ptr<dat::DataType>
         add_numbers(std::shared_ptr<dat::DataType> &, const std::shared_ptr<dat::DataType> &);

         static std::shared_ptr<dat::DataType>
         sub_numbers(std::shared_ptr<dat::DataType> &, const std::shared_ptr<dat::DataType> &);

         static std::shared_ptr<dat::DataType>
         mul_numbers(std::shared_ptr<dat::DataType> &, const std::shared_ptr<dat::DataType> &);

         static std::shared_ptr<dat::DataType>
         div_numbers(std::shared_ptr<dat::DataType> &, const std::shared_ptr<dat::DataType> &);*/

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
