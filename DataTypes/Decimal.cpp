//
// Created by bjarn on 08.06.2024.
//

#include <stdexcept>
#include <bitset>
#include <iostream>
#include "Numbers.hpp"

namespace num {

    int find_decimal_point(const std::string &string) {
        int point_index = 0;
        while (point_index < string.size()) {
            if (string[point_index] == '.') {
                break;
            } else {
                ++point_index;
            }
        }
        if (point_index == string.size()) {
            return -1;
        }
        return point_index;
    }

    std::array<std::string, 2> Decimal::slip(const std::string &str_repr) {
        int point_index = find_decimal_point(str_repr);

        std::array<std::string, 2> result{};
        result[0] = str_repr.substr(0, point_index);
        if (point_index == -1) {
            result[1] = "";
        } else {
            result[1] = str_repr.substr(point_index + 1, str_repr.size() - point_index);
        }
        return result;
    }

    uint64 Decimal::pow_base_10(int exponent) {
        uint64 base = 1;
        for (int i{0}; i < exponent; ++i) {
            base *= 10;
        }
        return base;
    }


    void Decimal::fit_string(std::array<std::string, 2> &string_pair) {
        const int MAX_WHOLE_PART_SIZE = CONSTANTS.MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH[c_SIZE * 8 -
                                                                                       c_SCALING_FACTOR];
        const int MAX_DEC_PART_SIZE = CONSTANTS.MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH[c_SCALING_FACTOR];
        if (string_pair[0].size() > MAX_WHOLE_PART_SIZE) {
            string_pair[0] = std::string("9", MAX_WHOLE_PART_SIZE);
        }
        if (string_pair[1].size() > MAX_WHOLE_PART_SIZE) {
            string_pair[1] = string_pair[1].substr(0, MAX_DEC_PART_SIZE);
            // Maybe add rounding here
        }

    }

    Decimal::Decimal(std::string str_repr, Size size, unsigned char scaling_factor) : Number(size,
                                                                                             str_repr.empty() or
                                                                                             str_repr[0] != '-'),
                                                                                      c_SCALING_FACTOR(scaling_factor) {

        if (str_repr.empty()) {
            throw std::runtime_error("Invalid number format0: '" + str_repr + "'\n");
        } else if (!m_is_positive and str_repr.size() == 1) {
            throw std::runtime_error("Invalid number format1: '" + str_repr + "'\n");
        }
        auto parts = Decimal::slip(str_repr);

        fit_string(parts);

        uint64 integer_part;
        const unsigned char INTEGER_PART_BIT_SIZE{static_cast<unsigned char>(c_SIZE * 8 - c_SCALING_FACTOR)};
        if (check_overflow(parts[0], INTEGER_PART_BIT_SIZE)) {
            integer_part = string_to_number(parts[0], INTEGER_PART_BIT_SIZE) << c_SCALING_FACTOR;
        } else {
            integer_part = CONSTANTS.MAX_NUMBER_LIMIT[INTEGER_PART_BIT_SIZE];
        }

        uint64 numerator = string_to_number(parts[1], c_SCALING_FACTOR);
        const uint64 denominator = pow_base_10(static_cast<int>(parts[1].size()));

        uint64 decimal_part{0};
        for (unsigned char i{0}; i < c_SCALING_FACTOR; ++i) {

            numerator *= 2;
            decimal_part <<= 1;
            if (numerator >= denominator) {
                decimal_part |= 1;
                numerator -= denominator;
            }
        }
//        std::cout << "-"<< std::bitset<64>(decimal_part)<< "\n";

        m_storage = integer_part | decimal_part;
        clap_to_size();

    }
    // 100110011001100110011001100110011001100110011001100110011001
    // 10011001100110011001100110011001100110011001100110011001100
}