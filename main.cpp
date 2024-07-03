
#include <iostream>
#include "Error/Error.hpp"
#include "DataTypes/Numbers.hpp"
#include "DataTypes/NumberPrinter.hpp"
#include "FileReader/FileReader.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Interpreter/Interpreter.hpp"


int main() {

    try {

        lex::Lexer lexer("main.bs");
        auto tokens = lexer.make_token();
        par::Parser parser(tokens);

        auto ast = parser.parse();
        ast->print();
        auto res = itp::Interpreter::visit(ast);
        if(res->c_NUMBER_TYPE == num::NumberType::INT) {
            num::NumberPrinter::print(*std::dynamic_pointer_cast<num::Integer>(res));
        } else {
            num::NumberPrinter::print(*std::dynamic_pointer_cast<num::Decimal>(res));
        }
    } catch (err::Error &error) {
        error.print();
    }

    return 0;
}

