#include "Error/Error.hpp"
#include "DataTypes/Numbers.hpp"
#include "DataTypes/NumberPrinter.hpp"
#include "FileReader/FileReader.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Interpreter/Interpreter.hpp"
#include "Interpreter/Context.hpp"

int main() {
//    for(auto& lol : lex::CONSTANTS.VARIABLE_KEYWORDS ){
//        std::cout << lol << std::endl;
//    }

    try {
        lex::Lexer lexer("main.bs");
        par::Parser parser{};
        itp::Context program_context("<program>");
        while(lexer.can_lex()){
            auto tokens = lexer.next_line();
            parser.import_tokens(tokens);
            auto abstract_syntax_tree = parser.parse();
            abstract_syntax_tree->print();
            auto res = itp::Interpreter::visit(abstract_syntax_tree, program_context);
            if(res->c_NUMBER_TYPE == num::NumberType::INT) {
                num::NumberPrinter::print(*std::dynamic_pointer_cast<num::Integer>(res));
            } else {
                num::NumberPrinter::print(*std::dynamic_pointer_cast<num::Decimal>(res));
            }
            std::cout << "\n";
        }
//        auto tokens = lexer.all();
//        par::Parser parser(tokens);
//        auto abstract_syntax_tree = parser.parse();
//        abstract_syntax_tree->print();
//        auto res = itp::Interpreter::visit(abstract_syntax_tree, program_context);
//        if(res->c_NUMBER_TYPE == num::NumberType::INT) {
//            num::NumberPrinter::print(*std::dynamic_pointer_cast<num::Integer>(res));
//        } else {
//            num::NumberPrinter::print(*std::dynamic_pointer_cast<num::Decimal>(res));
//        }
//        std::cout << "\n";
    } catch (err::Error &error) {
        error.print();
    }
    return 0;
}

