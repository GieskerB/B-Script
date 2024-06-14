#include "NumberPrinter.hpp"

#include <iostream>
#include <bitset>
#include <sstream>

namespace num {

    /*
     * In case of Integers simply print the number with help of the number_to_string method!
     */
    void NumberPrinter::print(const Integer &integer, bool line_break) {
        std::cout << number_to_string(integer.m_storage, integer.m_is_positive);
        if (line_break) std::cout << std::endl;
    }

    /*
     * In case of Decimal... Print the integer part like an integer and the reconstruct the fraction part.
     */
    void NumberPrinter::print(const Decimal &decimal, bool line_break) {
        // Use the right bits to the right part when printing!
        const uint64 DECIMAL_BIT_MAP = (static_cast<uint128>(1) << decimal.c_SCALING_FACTOR) - 1;
        uint64 pre_decimal_part;
        if (decimal.c_SCALING_FACTOR == decimal.c_SIZE * 8) {
            pre_decimal_part = 0;
        } else {
            pre_decimal_part = decimal.m_storage >> decimal.c_SCALING_FACTOR;
        }
        uint64 decimal_part = decimal.m_storage & DECIMAL_BIT_MAP;

        // Simply print the integer part:
        std::cout << number_to_string(pre_decimal_part, decimal.m_is_positive);
        std::cout << '.';

        // Converts the fraction step by step into a decimal number
        uint128 numerator = decimal_part;
        uint128 denominator = static_cast<uint128>(1) << decimal.c_SCALING_FACTOR;

        std::stringstream temporary_storage;
        for (int i = 0; i < decimal.c_SCALING_FACTOR; ++i) {
            numerator *= 10;
            temporary_storage << static_cast<uint64>(numerator / denominator);
            numerator %= denominator;
        }

        // Use some clever techniques and round a bit to reduce confusion when printing.
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
        int index{static_cast<int>(fractional_part.size())};
        while( index >1 and fractional_part[index-1] == '0') {
            --index;
        }
        fractional_part = fractional_part.substr(0,index);
        // Just like before: Reduce output limit to the important part.
        fractional_part = fractional_part.substr(0,
                                            CONSTANTS.INFORMATION_LIMIT_PER_NUMER_OF_BTIS[decimal.c_SCALING_FACTOR]);
        std::cout << fractional_part;
        if (line_break) std::cout << std::endl;
    }

} // num