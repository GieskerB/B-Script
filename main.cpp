#include "Error/Error.hpp"
#include "DataTypes/Number.hpp"
#include "FileReader/FileReader.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Interpreter/Interpreter.hpp"
#include "Interpreter/Context.hpp"
#include "Decimal.hpp"

int main() {
//    for(auto& lol : lex::CONSTANTS.VARIABLE_KEYWORDS ){
//        std::cout << lol << std::endl;
//    }

//    std::variant<>* a = nullptr;
//    std::any b;

    // TODO Keine Kopie machen! Nutze Decimal& x = ... zum Beispiel!

    /*
     * Unit Tests in c++ mit 'utest'
     */
//    dat::Decimal a("2.25", dat::INTEGER, 4);
//    std::cout << a << "\n";
//
//    dat::DataType& b = a;
//    std::cout << b << "\n";
//
//    dat::Decimal& c = dynamic_cast<dat::Decimal&>(b);
//    std::cout << c << "\n";
//
//    auto* e = dynamic_cast<dat::Decimal*>(&b);
//    std::cout << *e << "\n";
//
//    dat::Decimal& f = *e;
//    std::cout << f << "\n";

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

            std::cout << *res << '\n';

        }
//        auto tokens = lexer.all();
//        par::Parser parser(tokens);
//        auto abstract_syntax_tree = parser.parse();
//        abstract_syntax_tree->print();
//        auto res = itp::Interpreter::visit(abstract_syntax_tree, program_context);
//        if(res->c_NUMBER_TYPE == num::NumberType::INT) {
//            num::Printer::print(*std::dynamic_pointer_cast<num::Integer>(res));
//        } else {
//            num::Printer::print(*std::dynamic_pointer_cast<num::Decimal>(res));
//        }
//        std::cout << "\n";
    } catch (err::Error &error) {
        error.print();
    }
    return 0;
}

