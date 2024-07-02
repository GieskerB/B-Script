#ifndef B_SHARP_INTERPRETER_HPP
#define B_SHARP_INTERPRETER_HPP

#include "../DataTypes/Numbers.hpp"
#include "../Parser/Nodes.hpp"

namespace itp {

    class Interpreter {

        static num::Number* add_numbers(num::Number*,num::Number*);
        static num::Number* sub_numbers(num::Number*,num::Number*);
        static num::Number* mul_numbers(num::Number*,num::Number*);
        static num::Number* div_numbers(num::Number*,num::Number*);

        static num::Number* visit_number_node (par::NumberNode*);
        static num::Number* visit_unary_node (par::UnaryOperatorNode*);
        static num::Number* visit_binary_node (par::BinaryOperatorNode*);

    public:

        static num::Number* visit (par::Node*);

    };

} // itp

#endif //B_SHARP_INTERPRETER_HPP
