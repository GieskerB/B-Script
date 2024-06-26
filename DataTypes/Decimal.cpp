#include <stdexcept>
#include <bitset>
#include "Numbers.hpp"

namespace num {

    /*
     * A simple helper function to finde the decimal point in the string representation of the number.
     * If point does not exist return -1
     */
    int find_decimal_point(const std::string &string) {
        int point_index = 0;
        while (point_index < string.size()) {
            if (string[point_index] == '.') {
                return point_index;
            } else {
                ++point_index;
            }
        }
        return -1;
    }

    /*
     * Another helper function for fast computation of powers with base ten.
     */
    uint64 pow_base_10(int exponent) {
        uint64 base = 1;
        for (int i{0}; i < exponent; ++i) {
            base *= 10;
        }
        return base;
    }

    /*
     * Splits the string representation of the number at the decimal point and returns both parts (integer & fraction)
     */
    std::pair<std::string,std::string> Decimal::slip(const std::string &str_repr) {
        const int point_index = find_decimal_point(str_repr);

        std::pair<std::string,std::string> result{};
        // Integer part is the easiest. Zero to decimal point index. If not existent until the end!
        result.first = str_repr.substr(0, point_index);
        // Fraction part is simply everything after the decimal point.
        if (point_index == -1) {
            result.second= "";
        } else {
            result.second = str_repr.substr(point_index + 1, str_repr.size() - point_index);
        }
        return result;
    }

    /*
     * Since there is a limit to how much information fits into a given amount of bits and base 10 numbers have a more
     * than 3 times higher information amount per digit then base 2 number, too large or too small numbers will be cut.
     */
    void Decimal::fit_string(std::pair<std::string,std::string> &string_pair) {
        const int MAX_INTEGER_PART_SIZE = CONSTANTS.INFORMATION_LIMIT_PER_NUMER_OF_BTIS[c_SIZE * 8 -
                                                                                        c_SCALING_FACTOR];
        const int MAX_FRACTION_PART_SIZE = CONSTANTS.INFORMATION_LIMIT_PER_NUMER_OF_BTIS[c_SCALING_FACTOR];
        if (string_pair.first.size() > MAX_INTEGER_PART_SIZE) {
            // If string representation for integer part is too big, clap it to the max size and set all digits to 9.
            string_pair.first = std::string("9", MAX_INTEGER_PART_SIZE);
        }
        if (string_pair.second.size() > MAX_INTEGER_PART_SIZE) {
            // If string representation for fraction part is too long, cut the rest.
            // TODO Maybe add rounding here
            string_pair.second = string_pair.second.substr(0, MAX_FRACTION_PART_SIZE);
        }

    }

    Decimal::Decimal() : Number(Size::LONG, true), c_SCALING_FACTOR(c_SIZE * 4) {}

    Decimal::Decimal(const Integer &other, unsigned scaling_factor) : Number(other.c_SIZE, other.m_is_positive),
                                                                      c_SCALING_FACTOR(scaling_factor) {
        m_storage = other.m_storage << c_SCALING_FACTOR;
    }

    /*
     * Constructs a FixedPoint decimal number with variable size and accuracy!
     */
    Decimal::Decimal(std::string str_repr, Size size, unsigned char scaling_factor) : Number(size,
                                                                                             str_repr.empty() or
                                                                                             str_repr[0] != '-'),
                                                                                      c_SCALING_FACTOR(scaling_factor) {

        // Throw Error if format is wrong
        if (str_repr.empty()) {
            throw std::runtime_error("Invalid number format0: '" + str_repr + "'\n");
        } else if (!m_is_positive and str_repr.size() == 1) {
            throw std::runtime_error("Invalid number format1: '" + str_repr + "'\n");
        }

        // Prepare numbers for upcoming conversion:
        auto parts = Decimal::slip(str_repr);
        fit_string(parts);

        // At first convert the integer part into a binary number and shift it to the left to make room for the
        // fraction part.
        uint64 integer_part;
        const unsigned char INTEGER_PART_BIT_SIZE{static_cast<unsigned char>(c_SIZE * 8 - c_SCALING_FACTOR)};
        if (Number::check_overflow(parts.first, INTEGER_PART_BIT_SIZE)) {
            integer_part = string_to_number(parts.first, INTEGER_PART_BIT_SIZE) << c_SCALING_FACTOR;
        } else {
            integer_part = CONSTANTS.MAX_NUMBER_LIMIT[INTEGER_PART_BIT_SIZE];
        }

        uint64 numerator = string_to_number(parts.second, c_SCALING_FACTOR);
        uint64 denominator = pow_base_10(static_cast<int>(parts.second.size()));

        uint64 fraction_part{0};
        for (unsigned char i{0}; i < c_SCALING_FACTOR; ++i) {
            // Converting from fraction to binary like with pen and paper...
            numerator *= 2;
            fraction_part <<= 1;
            if (numerator >= denominator) {
                fraction_part |= 1;
                numerator -= denominator;
            }
        }

        // Finally combining both parts and clamping the number to its size just to be sure.
        m_storage = integer_part | fraction_part;
        clap_to_size();

    }
}