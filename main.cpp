
#include "DataTypes/Numbers.hpp"
#include "DataTypes/NumberPrinter.hpp"


int main() {

    num::Integer i("42", num::Size::BYTE, true), j ("-69", num::Size::BYTE, false);

    num::NumberPrinter::print_int(i);
    num::NumberPrinter::print_int(j);

    num::Integer res = i - j;

    num::NumberPrinter::print_int(res);

    return 0;
}

