//
// Created by bjarn on 08.06.2024.
//

#ifndef B_SHARP_NUMBERPRINTER_HPP
#define B_SHARP_NUMBERPRINTER_HPP

#include "Numbers.hpp"

namespace num {

    class NumberPrinter {
    public:
        static void print_int(const Integer& number);
        static void print_dec(const Integer& number);
    };

} // num

#endif //B_SHARP_NUMBERPRINTER_HPP
