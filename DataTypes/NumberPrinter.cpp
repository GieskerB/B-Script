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
        const uint64 DECIMAL_BIT_MAP = (static_cast<uint128>(1) << decimal.c_SCALING_FACTOR) - 1;
        uint64 pre_decimal_part;
        if (decimal.c_SCALING_FACTOR == decimal.c_SIZE * 8) {
            pre_decimal_part = 0;
        } else {
            pre_decimal_part = decimal.m_storage >> decimal.c_SCALING_FACTOR;
        }
        uint64 decimal_part = decimal.m_storage & DECIMAL_BIT_MAP;
        std::cout << number_to_string(pre_decimal_part, decimal.m_is_positive);
        std::cout << '.';

        uint128 numerator = decimal_part;
        uint128 denominator = static_cast<uint128>(1) << decimal.c_SCALING_FACTOR;


        std::stringstream temporary_storage;
        // Konvertiere Bruch in Dezimalstring
        for (int i = 0; i < decimal.c_SCALING_FACTOR; ++i) {
            numerator *= 10;
            temporary_storage << static_cast<uint64>(numerator / denominator);
            numerator %= denominator;
        }

        int num_of_consecutive_nines{0};
        char last_non_nine;
        int last_non_nine_index{-1};
        std::string fractional_part = temporary_storage.str();
        for (int i = 0; i < fractional_part.size(); ++i) {
            if (fractional_part[i] == '9') {
                ++num_of_consecutive_nines;
            } else {
                if (num_of_consecutive_nines > 3 and last_non_nine_index >= 0) {
                    fractional_part[last_non_nine_index] = static_cast<char> (last_non_nine + 1);
                    fractional_part = fractional_part.substr(0, last_non_nine_index + 1);
                    break;
                } else {
                    num_of_consecutive_nines = 0;
                }
                last_non_nine = fractional_part[i];
                last_non_nine_index = i;
            }
        }
        std::cout << fractional_part.substr(0,
                                            CONSTANTS.MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH[decimal.c_SCALING_FACTOR]);

    }

} // num