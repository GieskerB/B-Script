
#include <iostream>
#include "DataTypes/Numbers.hpp"
#include "DataTypes/NumberPrinter.hpp"


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

    num::Decimal d1("2.5",num::Size::INTEGER, 7);
    num::Decimal d2("2.5",num::Size::INTEGER, 5);

    num::NumberPrinter::print(d1,true);
    num::NumberPrinter::print(d2,true);
    num::NumberPrinter::print(d1+d2);


//    std::cout << std::endl;
//    for(int i: num::CONSTANTS.INFORMATION_LIMIT_PER_NUMER_OF_BTIS) {
//        std::cout << i << " ";
//    }

    return 0;
}

