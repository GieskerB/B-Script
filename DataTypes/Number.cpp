#include <stdexcept>
#include <iostream>
#include <sstream>
#include "Numbers.hpp"

namespace num {

    /*
     * name is self-explanatory
     */
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

        std::stringstream result;
        for (char &digit: std::ranges::reverse_view(digits)) {
            result << digit;
        }
        return result.str();
    }

    /*
     * name is self-explanatory
     */
    uint64 string_to_number(const std::string &str_repr, unsigned char bit_length) {
        const char start = str_repr[0] == '-' ? 1 : 0;

        if (str_repr.empty() or str_repr == "0") {
            return 0;
        }

        uint64 result{0}, base{1};

        for (int i = static_cast<int>(str_repr.size() - 1); i >= start; --i) {
            char digit = str_repr[i];
            if (digit < '0' or digit > '9') {
                throw std::runtime_error("Invalid number format2: '" + str_repr + "'\n");
            }
            digit -= '0';
            if (result + digit * base < result) {
                break;
            }
            result += digit * base;
            base *= 10;
        }
        return result;
    }

    /*
     * To further make sure a number does not get too big when initialized, just compare it to the biggest number
     * possible with a given number of bits.
     */
    bool Number::check_overflow(const std::string &string, unsigned char bit_size) {
        const std::string COMPARE = CONSTANTS.MAX_NUMBER_LIMIT_STRING[bit_size];

        if (string.size() < COMPARE.size()) {
            return true;
        }
        for (int i = 0; i < COMPARE.size(); ++i) {
            if (string[i] > COMPARE[i]) {
                return false;
            } else if (string[i] < COMPARE[i]) {
                return true;
            }

        }
        // If all equals it's okay and right_node on the limit.
        return true;
    }

    /*
     * A struct to store some global constants
     */
    template<unsigned char N>
    Constants<N>::Constants() : INFORMATION_LIMIT_PER_NUMBER_OF_BITS() {
        uint64 temp_value = 1ULL;
        for (unsigned char i = 0; i != N; ++i) {
            INFORMATION_LIMIT_PER_NUMBER_OF_BITS[i] = std::ceil(i / std::log2f(10.f));
            if (i == 0) {
                MAX_NUMBER_LIMIT[i] = 0;
            } else {
                MAX_NUMBER_LIMIT[i] = temp_value;
                temp_value <<= 1;
                temp_value |= 1;
            }
            MAX_NUMBER_LIMIT_STRING[i] = number_to_string(MAX_NUMBER_LIMIT[i], true);
        }
    }

    /*
     * to make sure a number does not get too big. Just "throw away" to larger bits.
     */
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

    /*
     * Initialization of all base values.
     */
    Number::Number(Size size, bool is_positive, NumberType number_type) : c_SIZE(size), m_storage(0),
                                                                          m_is_positive(is_positive),
                                                                          c_NUMBER_TYPE(number_type) {}

    void Number::invert() {
        m_is_positive = !m_is_positive;
    }

}