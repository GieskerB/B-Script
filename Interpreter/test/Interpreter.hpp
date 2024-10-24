#ifndef B_SHARP_INTERPRETER_HPP
#define B_SHARP_INTERPRETER_HPP

#include <memory>
#include "../../Parser/test/Program.hpp"
#include "../../DataTypes/Boolean.hpp"
#include "../Interpreter.hpp"

dat::VariantTypes evaluate_program(const Program&);
dat::VariantTypes evaluate_statement(const std::shared_ptr<Statement>&, const itp::Context&);

#endif //B_SHARP_INTERPRETER_HPP
