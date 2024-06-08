//
// Created by bjarn on 07.06.2024.
//

#include <stdexcept>
#include "Numbers.hpp"
#include "NumberPrinter.hpp"

namespace num {

    const Integer Integer::LITERALS[] = {Integer(0), Integer(1), Integer(2),
                                         Integer(3), Integer(4), Integer(5),
                                         Integer(6), Integer(7), Integer(8),
                                         Integer(9), Integer(10)};

    Integer::Integer(unsigned char number) : Number(Size::LONG, true), c_is_signed(true) {
        m_storage = number;
    }


    Integer::Integer(Size size, bool is_signed) : Integer("", size, is_signed) {}

    Integer::Integer(std::string str_repr, Size size, bool is_signed) : Number(size,
                                                                               str_repr.empty() or str_repr[0] != '-'),
                                                                        c_is_signed(is_signed) {
        if (str_repr.empty()) {
            return;
        }

        if (!m_is_positive and str_repr.size() == 1) {
            throw std::runtime_error("Invalid number format1: '" + str_repr + "'\n");
        }
        int start = m_is_positive ? 0 : 1;

//        Integer base = Integer::LITERALS[1];
//        for (int i = str_repr.size() - 1; i >= start; --i) {
//            char digit = str_repr[i];
//            if (digit < '0' or digit > '9') {
//                throw std::runtime_error("Invalid number format2: '" + str_repr + "'\n");
//            }
//            digit -= '0';
//
//            Integer multiplier = Integer::LITERALS[digit] * base;
//
//            operator+=(*this, multiplier);
//
//            base = base * Integer::LITERALS[10];
//        }

        unsigned long long base = 1;
        for (int i = str_repr.size() - 1; i >= start; --i) {
            char digit = str_repr[i];
            if (digit < '0' or digit > '9') {
                throw std::runtime_error("Invalid number format2: '" + str_repr + "'\n");
            }
            digit -= '0';
            m_storage += digit * base;
            base *= 10;
        }
        clap_to_size();
    }

    void Integer::clap_to_size() {

        switch (c_SIZE) {

            case BYTE:
                m_storage &= 0xFF;
                break;
            case SHORT:
                m_storage &= 0xFFFF;
                break;
            case INTEGER:
                m_storage &= 0xFFFFFFFF;
                break;
            case LONG:
                m_storage &= 0xFFFFFFFFFFFFFFFF;
                break;
        }

    }


} // num