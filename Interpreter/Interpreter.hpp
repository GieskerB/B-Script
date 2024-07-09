#ifndef B_SHARP_INTERPRETER_HPP
#define B_SHARP_INTERPRETER_HPP

#include <memory>

#include "../DataTypes/Numbers.hpp"
#include "../Parser/Nodes.hpp"
#include "Context.hpp"

namespace itp {

    class Interpreter {

        static std::shared_ptr<num::Number>
        add_numbers(std::shared_ptr<num::Number> &, const std::shared_ptr<num::Number> &);

        static std::shared_ptr<num::Number>
        sub_numbers(std::shared_ptr<num::Number> &, const std::shared_ptr<num::Number> &);

        static std::shared_ptr<num::Number>
        mul_numbers(std::shared_ptr<num::Number> &, const std::shared_ptr<num::Number> &);

        static std::shared_ptr<num::Number>
        div_numbers(std::shared_ptr<num::Number> &, const std::shared_ptr<num::Number> &);

        static std::shared_ptr<num::Number>
        visit_variable_access_node(const std::shared_ptr<par::VariableAccessNode> &,  itp::Context &);

        static std::shared_ptr<num::Number>
        visit_variable_assign_node(const std::shared_ptr<par::VariableAssignNode> &,  itp::Context &);

        static std::shared_ptr<num::Number>
        visit_number_node(const std::shared_ptr<par::NumberNode> &,  itp::Context &);

        static std::shared_ptr<num::Number>
        visit_unary_node(const std::shared_ptr<par::UnaryOperatorNode> &,  itp::Context &);

        static std::shared_ptr<num::Number>
        visit_binary_node(const std::shared_ptr<par::BinaryOperatorNode> &,  itp::Context &);

    public:

        static std::shared_ptr<num::Number> visit(const std::shared_ptr<par::Node> &,  itp::Context&);

    };

} // itp

#endif //B_SHARP_INTERPRETER_HPP
