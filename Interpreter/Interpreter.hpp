#ifndef B_SHARP_INTERPRETER_HPP
#define B_SHARP_INTERPRETER_HPP

#include <memory>

#include "../DataTypes/Number.hpp"
#include "../Parser/Nodes.hpp"
#include "Context.hpp"

namespace itp {

    class Interpreter {

        static std::shared_ptr<dat::DataType>
        add_numbers(std::shared_ptr<dat::DataType> &, const std::shared_ptr<dat::DataType> &);

        static std::shared_ptr<dat::DataType>
        sub_numbers(std::shared_ptr<dat::DataType> &, const std::shared_ptr<dat::DataType> &);

        static std::shared_ptr<dat::DataType>
        mul_numbers(std::shared_ptr<dat::DataType> &, const std::shared_ptr<dat::DataType> &);

        static std::shared_ptr<dat::DataType>
        div_numbers(std::shared_ptr<dat::DataType> &, const std::shared_ptr<dat::DataType> &);

        static std::shared_ptr<dat::DataType>
        visit_variable_access_node(const std::shared_ptr<par::VariableAccessNode> &,  itp::Context &);

        static std::shared_ptr<dat::DataType>
        visit_variable_assign_node(const std::shared_ptr<par::VariableAssignNode> &,  itp::Context &);

        static std::shared_ptr<dat::DataType>
        visit_number_node(const std::shared_ptr<par::NumberNode> &,  itp::Context &);

        static std::shared_ptr<dat::DataType>
        visit_unary_node(const std::shared_ptr<par::UnaryOperatorNode> &,  itp::Context &);

        static std::shared_ptr<dat::DataType>
        visit_binary_node(const std::shared_ptr<par::BinaryOperatorNode> &,  itp::Context &);

    public:

        static std::shared_ptr<dat::DataType> visit(const std::shared_ptr<par::Node> &,  itp::Context&);

    };

} // itp

#endif //B_SHARP_INTERPRETER_HPP
