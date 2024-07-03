#ifndef B_SHARP_INTERPRETER_HPP
#define B_SHARP_INTERPRETER_HPP

#include <memory>

#include "../DataTypes/Numbers.hpp"
#include "../Parser/Nodes.hpp"

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

        static std::shared_ptr<num::Number> visit_number_node(const std::shared_ptr<par::NumberNode> &);
        static std::shared_ptr<num::Number> visit_unary_node(const std::shared_ptr<par::UnaryOperatorNode> &);
        static std::shared_ptr<num::Number> visit_binary_node(const std::shared_ptr<par::BinaryOperatorNode> &);

    public:

        static std::shared_ptr<num::Number> visit(const std::shared_ptr<par::Node> &);

    };

} // itp

#endif //B_SHARP_INTERPRETER_HPP
