//
// Created by bjarn on 08.06.2024.
//

#include <stdexcept>
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

    Decimal::Decimal(std::string str_repr, Size size, unsigned char scaling_factor) : Number(size,
                                                                                             str_repr.empty() or
                                                                                             str_repr[0] != '-'),
                                                                                      c_SCALING_FACTOR(scaling_factor),
                                                                                      m_extended_storage(0) {
        if (str_repr.empty()) {
            return;
        }
        if (!m_is_positive and str_repr.size() == 1) {
            throw std::runtime_error("Invalid number format1: '" + str_repr + "'\n");
        }
        auto parts = Decimal::slip(str_repr);

        int start = m_is_positive ? 0 : 1;

        uint64 base = 1;
        for (int i = static_cast<int>(parts[0].size() - 1); i >= start; --i) {
            char digit = str_repr[i];
            if (digit < '0' or digit > '9') {
                throw std::runtime_error("Invalid number format2: '" + str_repr + "'\n");
            }
            digit -= '0';
            m_storage += digit * base;
            base *= 10;
        }
        m_storage <<= c_SCALING_FACTOR;

        for(int i = c_SCALING_FACTOR; i >= 0; --i);

        // Idea: Convert form Fraction part to uint64. and then tak the upper 'scaling factor' bits to and put them at
        // the back form m_storage.

    }

}