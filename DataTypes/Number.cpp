//
// Created by bjarn on 08.06.2024.
//

#include <stdexcept>
#include "Numbers.hpp"

namespace num {

    uint64 Number::string_to_number(const std::string & str_repr) {
        const char start = str_repr[0] == '-' ? 1 : 0;
        uint64 result{0},base{1};

        for (int i = static_cast<int>(str_repr.size() - 1); i >= start; --i) {
            char digit = str_repr[i];
            if (digit < '0' or digit > '9') {
                throw std::runtime_error("Invalid number format2: '" + str_repr + "'\n");
            }
            digit -= '0';
            result += digit * base;
            base *= 10;
        }
        return result;
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

    Number::Number(Size size, bool is_positive) : c_SIZE(size), m_storage(0), m_is_positive(is_positive) {}

}