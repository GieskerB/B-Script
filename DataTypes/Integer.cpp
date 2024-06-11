//
// Created by bjarn on 07.06.2024.
//

#include <stdexcept>
#include "Numbers.hpp"
#include "NumberPrinter.hpp"

namespace num {


//    Integer::Integer(Size size, bool is_signed) : Integer("", size, is_signed) {}

    Integer::Integer(std::string str_repr, Size size, bool is_signed) : Number(size,
                                                                               str_repr.empty() or str_repr[0] != '-'),
                                                                        c_IS_SIGNED(is_signed) {
        if (str_repr.empty()) {
            return;
        }

        if (!m_is_positive and str_repr.size() == 1) {
            throw std::runtime_error("Invalid number format1: '" + str_repr + "'\n");
        }
        m_storage = string_to_number(str_repr,c_SIZE * 8);
        clap_to_size();
    }


} // num