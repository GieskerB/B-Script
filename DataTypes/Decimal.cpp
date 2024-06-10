//
// Created by bjarn on 08.06.2024.
//

#include <stdexcept>
#include <bitset>
#include "Numbers.hpp"

namespace num {

    std::array<std::string,2> Decimal::slip(std::string& str_repr) {
        int point_index = 0;
        while (point_index < str_repr.size()) {
            if (str_repr[point_index] == '.') {
                break;
            } else {
                ++point_index;
            }
        }
        if (point_index == str_repr.size()) {
            str_repr.push_back('.');
        }
        std::array<std::string,2> result{};
        result[0] = str_repr.substr(0,point_index);
        result[1] = str_repr.substr(point_index+1,str_repr.size() - point_index);
        return result;
    }

    uint64 Decimal::pow_base_10(int exponent) {
        uint64 base = 1;
        for(int i {0}; i< exponent; ++i) {
            base *=10;
        }
        return base;
    }

    Decimal::Decimal(std::string str_repr, Size size, unsigned char scaling_factor) : Number(size,
                                                                                             str_repr.empty() or
                                                                                             str_repr[0] != '-'),
                                                                                      c_SCALING_FACTOR(scaling_factor) {
        if (str_repr.empty()) {
            return;
        }
        if (!m_is_positive and str_repr.size() == 1) {
            throw std::runtime_error("Invalid number format1: '" + str_repr + "'\n");
        }
        auto parts = Decimal::slip(str_repr);

        uint64 integer_part = Number::string_to_number(parts[0]) << c_SCALING_FACTOR;

        uint64 numerator = Number::string_to_number(parts[1]);
        const uint64 denominator = pow_base_10(static_cast<int>(parts[1].size()));

        uint64 decimal_part{0};
        for(unsigned char i {0}; i< c_SCALING_FACTOR; ++i ) {
            numerator *= 2;
            decimal_part <<= 1;
            if (numerator >= denominator) {
                decimal_part |= 1;
                numerator -= denominator;
            }
        }

        m_storage = integer_part | decimal_part;
        clap_to_size();

    }

}