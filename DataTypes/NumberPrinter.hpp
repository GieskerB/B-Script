//
// Created by bjarn on 08.06.2024.
//

#ifndef B_SHARP_NUMBERPRINTER_HPP
#define B_SHARP_NUMBERPRINTER_HPP

#include "Numbers.hpp"

namespace num {

    class NumberPrinter {

        static std::string number_to_string(uint64, bool);

    public:
        static void print_int(const Integer&);
        static void print_dec(const Decimal&);
    };

} // num

#endif //B_SHARP_NUMBERPRINTER_HPP
