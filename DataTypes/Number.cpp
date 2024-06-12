//
// Created by bjarn on 08.06.2024.
//

#include <stdexcept>
#include <iostream>
#include "Numbers.hpp"

namespace num {

    std::string number_to_string(uint64 number, bool is_positive) {
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

    uint64 string_to_number(const std::string & str_repr,unsigned char bit_length) {
        const char start = str_repr[0] == '-' ? 1 : 0;
//        std::string number_base_10 = str_repr.substr(start,CONSTANTS.MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH[bit_length]);

        if(str_repr.empty() or str_repr == "0") {
            return 0;
        }

        uint64 result{0},base{1};

        for (int i = static_cast<int>(str_repr.size() - 1); i >= start; --i) {
            char digit = str_repr[i];
            if (digit < '0' or digit > '9') {
                throw std::runtime_error("Invalid number format2: '" + str_repr + "'\n");
            }
            digit -= '0';
            if(result + digit * base < result) {
                break;
            }
            result += digit * base;
            base *= 10;
        }
        return result;
    }

    template<unsigned char N>
    Constants<N>::Constants() : MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH() {
        uint64 temp_value = 1ULL;
        for (unsigned char i = 0; i != N; ++i) {
            MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH[i] = std::ceil(i / std::log2f(10.f));
            if(i == 0) {
                MAX_NUMBER_LIMIT[i] = 0;
            } else {
                MAX_NUMBER_LIMIT[i] = temp_value;
                temp_value <<=1;
                temp_value|= 1;
            }
            MAX_NUMBER_LIMIT_STRING[i] = number_to_string(MAX_NUMBER_LIMIT[i],true);
        }
    }


    void Number::clap_to_size() {

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

    bool Number::check_overflow(const std::string &string, unsigned char bit_size) {
        const std::string COMPARE = CONSTANTS.MAX_NUMBER_LIMIT_STRING[bit_size];

        if(string.size() < COMPARE.size()) {
            return true;
        }
        for(int i = 0; i< COMPARE.size();++i) {
            if(string[i] > COMPARE[i]) {
                return  false;
            } else if (string[i] < COMPARE[i]) {
                return true;
            }

        }

        return true;
    }

    Number::Number(Size size, bool is_positive) : c_SIZE(size), m_storage(0), m_is_positive(is_positive) {}

}