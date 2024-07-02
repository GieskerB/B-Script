
#define DEBUG

#include <iostream>
#include "Error/Error.hpp"
#include "DataTypes/Numbers.hpp"
#include "DataTypes/NumberPrinter.hpp"
#include "FileReader/FileReader.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "Interpreter/Interpreter.hpp"


int main() {


//    num::Integer i("420", num::Size::SHORT, true), j ("-69", num::Size::BYTE, false);
//
//    num::NumberPrinter::print(i);
//    std::cout << std::endl;
//    num::NumberPrinter::print(j);
//    std::cout << std::endl;
//
//    num::Integer res = i - j;
//
//    num::NumberPrinter::print(res);
//    std::cout << std::endl;

//    std::string lit = "0.";

//    for(int i = 0; i< 20; ++i) {
//        std::cout << i << " ";
//        num::Decimal s = num::Decimal(lit, num::Size::LONG,64);
//        num::NumberPrinter::print(s);
//        std::cout << std::endl;
//        lit.push_back('3');

//    num::Integer i1("12",num::Size::LONG,false);
//
//    num::Decimal d1("0.5",num::Size::INTEGER,20);
//    num::Decimal d2("5.5",num::Size::INTEGER,23);
//
//    num::NumberPrinter::print(d1,true);
//    num::NumberPrinter::print(d2,true);
//    num::NumberPrinter::print(i1*=d1,true);

//    std::cout << std::endl;
//    for(int i: num::CONSTANTS.INFORMATION_LIMIT_PER_NUMBER_OF_BITS) {
//        std::cout << i << " ";
//    }



    lex::Lexer lexer("main.bs");
    auto tokens = lexer.make_token();
    par::Parser parser(tokens);

    try {
        auto ast = parser.parse();
        ast->print();
        delete ast;
        itp::Interpreter::visit(ast);
    } catch (err::Error &error) {
        error.print();
    }


    std::cout << "Number of leaked memory Nodes: "<< par::Node::ALIVE_COUNTER << '\n';

    return 0;
}

