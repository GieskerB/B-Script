//
// Created by bjarn on 08.06.2024.
//

#include "NumberPrinter.hpp"
#include <iostream>
#include <ranges>
#include <vector>
#include <bitset>
#include <numeric>

namespace num {


    std::string NumberPrinter::number_to_string(uint64 number, bool is_positive) {
        std::vector<char> digits;

        if (number == 0) {
            digits.push_back('0');
        }
        while (number != 0) {
            unsigned char digit = number % 10;
            number /= 10;
            digits.push_back(static_cast<char>(digit + '0'));
        }
        if (!is_positive) {
            digits.push_back(static_cast<char>('-'));
        }

        // TODO: Use string stream here!
        std::string result{};
        for (char &digit: std::ranges::reverse_view(digits)) {
            result.push_back( digit);
        }
        return result;
    }

    void NumberPrinter::print_int(const num::Integer &integer) {
        std::cout << NumberPrinter::number_to_string(integer.m_storage, integer.m_is_positive);
    }


    void NumberPrinter::print_dec(const num::Decimal &decimal) {
        const uint64 DECIMAL_BIT_MAP = (1ULL << decimal.c_SCALING_FACTOR)-1;
        uint64 pre_decimal_part = decimal.m_storage >> decimal.c_SCALING_FACTOR;
        uint64 decimal_part = decimal.m_storage & DECIMAL_BIT_MAP;
        std::cout << NumberPrinter::number_to_string(pre_decimal_part, decimal.m_is_positive);
        std::cout << '.';

        uint64_t numerator = decimal_part;
        uint64_t denominator = 1ULL << decimal.c_SCALING_FACTOR;

        // Bruch kürzen
        uint64_t divisor = std::gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        // Konvertiere Bruch in Dezimalstring
        for (int i = 0; i < decimal.c_SCALING_FACTOR; ++i) {
            numerator *= 10;
            std::cout << (numerator / denominator);
            numerator %= denominator;
        }

    }

} // num