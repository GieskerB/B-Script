
#include <iostream>
#include "DataTypes/Numbers.hpp"
#include "DataTypes/NumberPrinter.hpp"


int main() {

//    num::Integer i("420", num::Size::SHORT, true), j ("-69", num::Size::BYTE, false);
//
//    num::NumberPrinter::print_int(i);
//    std::cout << std::endl;
//    num::NumberPrinter::print_int(j);
//    std::cout << std::endl;
//
//    num::Integer res = i - j;
//
//    num::NumberPrinter::print_int(res);
//    std::cout << std::endl;


    std::string lit = "0.";

    for(int i = 0; i< 64; ++i) {
        std::cout << i << " ";
        num::Decimal s = num::Decimal(lit, num::Size::LONG,32);
        num::NumberPrinter::print_dec(s);
        std::cout << std::endl;
        lit.push_back('3');
    }


    for(int i: num::CONSTANTS.MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH) {
        std::cout << i << " ";
    }

    return 0;
}

