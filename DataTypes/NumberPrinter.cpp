//
// Created by bjarn on 08.06.2024.
//

#include "NumberPrinter.hpp"
#include <iostream>
#include <ranges>
#include <vector>
#include <bitset>
#include <numeric>
#include <sstream>

namespace num {

    void NumberPrinter::print_int(const num::Integer &integer) {
        std::cout << number_to_string(integer.m_storage, integer.m_is_positive);
    }


    void NumberPrinter::print_dec(const num::Decimal &decimal) {
        const uint64 DECIMAL_BIT_MAP = (1ULL << decimal.c_SCALING_FACTOR)-1;
        uint64 pre_decimal_part = decimal.m_storage >> decimal.c_SCALING_FACTOR;
        uint64 decimal_part = decimal.m_storage & DECIMAL_BIT_MAP;
        std::cout << number_to_string(pre_decimal_part, decimal.m_is_positive);
        std::cout << '.';

        uint64_t numerator = decimal_part;
        uint64_t denominator = 1ULL << decimal.c_SCALING_FACTOR;

        // Bruch kürzen
        uint64_t divisor = std::gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        std::stringstream temporary_storage;
        // Konvertiere Bruch in Dezimalstring
        for (int i = 0; i < decimal.c_SCALING_FACTOR; ++i) {
            numerator *= 10;
            temporary_storage << (numerator / denominator);
            numerator %= denominator;
        }
        int num_of_consecutive_nines {0};
       std::string fractional_part = temporary_storage.str();
        for (int i = fractional_part.size()-1; i>= 0; --i) {
            if(fractional_part[i] == '9') {
                ++num_of_consecutive_nines;
            } else {
                if(num_of_consecutive_nines >= 3) {
                    fractional_part[i] = static_cast<char>(fractional_part[i])+1;
                    fractional_part= fractional_part.substr(0, i+1);
                    break;
                } else {
                num_of_consecutive_nines = 0;
                }
            }
        }
        std::cout << fractional_part;

    }

} // num