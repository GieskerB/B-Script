#include <sstream>

#include "Integer.hpp"
#include "Decimal.hpp"
#include "Utility.hpp"
#include "../Error/Error.hpp"

namespace dat {
    /*
     * A simple helper function to finde the decimal point in the string representation of the number.
     * If point does not exist return -1
     */
    int find_decimal_point(const std::string &string) {
        int point_index{0};
        while (point_index < string.size()) {
            if (string[point_index] == '.') {
                return point_index;
            }
            ++point_index;
        }
        return -1;
    }

    /*
     * Another helper function for fast computation of powers with base ten.
     */
    uint64 pow_base_10(size_t exponent) {
        uint64 base = 1;
        for (size_t i{0}; i < exponent; ++i) {
            base *= 10;
        }
        return base;
    }

    /*
     * Splits the string representation of the number at the decimal point and returns both parts (integer & fraction)
     */
    std::pair<std::string, std::string> Decimal::slip(const std::string &str_repr) {
        const int point_index = find_decimal_point(str_repr);

        std::pair<std::string, std::string> result{};
        // Integer part is the easiest. Zero to decimal point index. If not existent until the end!
        result.first = str_repr.substr(0, point_index);
        // Fraction part is simply everything after the decimal point.
        if (point_index != -1) {
            result.second = str_repr.substr(point_index + 1, str_repr.size());
        }
        return result;
    }


    Decimal::Decimal(const Boolean &other) : Number(Size::BYTE, true), c_SCALING_FACTOR(0) {
        switch (other.m_storage) {
            case Boolean::TriState::TRUE:
                m_storage = 1;
                break;
            case Boolean::TriState::FALSE:
                m_storage = 0;
                break;
            case Boolean::TriState::NEUTRAL: {
                auto pos = other.position();
                throw err::RuntimeError(pos.first, pos.second, "Can not convert m_value 'neutral' into a number",
                                        other.context());
            }
        }
    }

    Decimal::Decimal(const Integer &other) : Number(other.c_SIZE, other.m_is_positive), c_SCALING_FACTOR(0) {
        m_storage = other.m_storage;
        // https://stackoverflow.com/questions/671815/what-is-the-fastest-most-efficient-way-to-find-the-highest-set-bit-msb-in-an-i
        // __builtin_clzll Returns the number of leading 0-bits in X, starting at the most significant bit position.
         c_SCALING_FACTOR = m_storage == 0 ? 64 : __builtin_clzll(other.m_storage);
         m_storage <<= c_SCALING_FACTOR;
    }

    Decimal::Decimal(const Decimal &other) : Number(other.c_SIZE, other.m_is_positive),
                                             c_SCALING_FACTOR(other.c_SCALING_FACTOR) {
        m_storage = other.m_storage;
    }

    Decimal::Decimal(const String &other) : Number(Size::LONG, false), c_SCALING_FACTOR(0) {
        throw err::RuntimeError(other.position().first, other.position().second,
                                "Casting error form String to Decimal.",
                                other.context());
    }


    // Constructs a Decimal form a string
    Decimal::Decimal(std::string str_repr, Size size, uint8_t scaling_factor) : Number(size, str_repr.empty() or
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

        // Converts string to number and limits it to its given size, as well as shifting it to make room for the
        // decimal part.
        uint64 integer_part = string_to_number(parts.first);
        uint64 integer_bitmap = ((1ULL << (c_SIZE * 8 - scaling_factor)) - 1);
        integer_part &= integer_bitmap;
        integer_part <<= c_SCALING_FACTOR;

        uint64 decimal_part{0};
        uint64 decimal_bitmap = ((1ULL << scaling_factor) - 1);
        uint64 numerator = string_to_number(parts.second);
        uint64 denominator = pow_base_10(parts.second.size());
        for (uint8_t i{0}; i < c_SCALING_FACTOR; ++i) {
            // Converting from fraction to binary like with pen and paper...
            numerator *= 2;
            decimal_part <<= 1;
            if (numerator >= denominator) {
                decimal_part |= 1;
                numerator -= denominator;
            }
        }
        decimal_part &= decimal_bitmap;

        // Finally combining both parts and clamping the number to its size just to be sure.
        m_storage = integer_part | decimal_part;
    }


    /*
     * In case of Decimal... Print the integer part like an integer and the reconstructed the fraction part.
     */
    std::string Decimal::to_string() const {
        // Use the right_node bits to the right_node part when printing!
        const uint64 DECIMAL_BIT_MAP = (static_cast<uint128>(1) << c_SCALING_FACTOR) - 1;
        uint64 pre_decimal_part;
        if (c_SCALING_FACTOR == c_SIZE * 8) {
            pre_decimal_part = 0;
        } else {
            pre_decimal_part = m_storage >> c_SCALING_FACTOR;
        }

        uint64 decimal_part = m_storage & DECIMAL_BIT_MAP;

        // Simply print the integer part:
        std::stringstream result;
        result << number_to_string(pre_decimal_part, m_is_positive);
        result << '.';

        // Converts the fraction step by step into a decimal number
        uint128 numerator = decimal_part;
        uint128 denominator = static_cast<uint128>(1) << c_SCALING_FACTOR;

        std::stringstream temporary_storage;
        for (int i = 0; i < c_SCALING_FACTOR; ++i) {
            numerator *= 10;
            temporary_storage << static_cast<uint64>(numerator / denominator);
            numerator %= denominator;
        }

        // Reduce output limit to the important part.
        std::string fractional_part = temporary_storage.str();
//        std::cerr << fractional_part<<"->" << (int) c_SCALING_FACTOR<<"\n";
        fractional_part = fractional_part.substr(0, LookUp::log_base_10_of_2_to_x[c_SCALING_FACTOR]);


        // Strip zeros from end
        size_t index = fractional_part.size();
        while (index > 1 and fractional_part[index - 1] == '0') {
            --index;
        }
        fractional_part = fractional_part.substr(0, index);

        if (fractional_part.empty()) {
            fractional_part = "0";
        }

        result << fractional_part;
        return result.str();
    }

    void Decimal::print(std::ostream &os) const {
        os << to_string();
    }

} // dat