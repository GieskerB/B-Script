#include "DataTypes/Utility.hpp"
#include "Error/Error.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Interpreter/Interpreter.hpp"
#include "Interpreter/Context.hpp"
#include "Parser/test/Parser.hpp"
#include "Interpreter/test/Interpreter.hpp"

int main() {

    //TODO next: Variable assignment
    const bool new_version = true;

    if (new_version) {
        Parser pars("main.bs");
        try {
            auto prog = pars.parse_all();
            auto var = evaluate_program(prog);
            std::cout << "Result: "<< var<< "\n";
        } catch (err::Error &error) {
            error.print();
        } catch (std::runtime_error &error) {
            std::cerr << "An programming error occurred:\n" << error.what();
        }

    } else {

        try {
            // Work in 3 steps per file:
            // 1. Read content form file and let the lexer convert it into a stream of tokens:
            lex::Lexer lexer("main.bs");
            std::vector<lex::Token> tokens = lexer.lex_all();

            for (auto &tok: tokens) {
                std::cout << tok;
                if (tok.c_type == lex::TokenType::END_OF_LINE) {
                    std::cout << '\n';
                }
            }

            // 2. Break down lex_all Tokens into each single statement via the Parser.
            par::Parser parser{tokens};
            std::vector<par::MegaNode> statements = parser.parse_all();
            for (const auto &statement: statements) {
                statement.print();
            }

            // 3. Finally, the Interpreter will run the translated statement form the Parser.
            itp::Context program_context("<program>");
            for (const auto &statement: statements) {
                auto result = itp::Interpreter::visit(statement, program_context);
                std::cout << result << '\n';
            }

        } catch (err::Error &error) {
            error.print();
        } catch (std::runtime_error &error) {
            std::cerr << "An programming error occurred:\n" << error.what();
        }
    }
    return 0;
}