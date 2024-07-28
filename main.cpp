#include "DataTypes/Utility.hpp"
#include "Error/Error.hpp"
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
            for(auto& tok: tokens) {
                std::cout << tok;
            }
            parser.import_tokens(tokens);
            auto abstract_syntax_tree = parser.parse();
            abstract_syntax_tree.print();
            auto res = itp::Interpreter::visit(abstract_syntax_tree, program_context);
            std::cout << res << '\n';
        }
    } catch (err::Error &error) {
        error.print();
    }
    return 0;
}

