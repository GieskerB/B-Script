//
// Created by bjarn on 08.06.2024.
//

#include "NumberPrinter.hpp"
#include <iostream>

namespace num {

    void NumberPrinter::print_int(const num::Integer &number) {
        std::cout << number.m_storage << " " <<number.m_is_positive <<std::endl;
    }

    void NumberPrinter::print_dec(const num::Integer &number) {

    }

} // num