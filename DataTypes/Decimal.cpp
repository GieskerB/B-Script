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
    std::pair<std::string, std::string> Decimal::slip(const std::string &str_repr) {
        const int point_index = find_decimal_point(str_repr);

        std::pair<std::string, std::string> result{};
        // Integer part is the easiest. Zero to decimal point index. If not existent until the end!
        result.first = str_repr.substr(0, point_index);
        // Fraction part is simply everything after the decimal point.
        if (point_index == -1) {
            result.second = "";
        } else {
            result.second = str_repr.substr(point_index + 1, str_repr.size() - point_index);
        }
        return result;
    }

    /*
     * Since there is a limit to how much information fits into a given amount of bits and base 10 numbers have a more
     * than 3 times higher information amount per digit then base 2 number, too large or too small numbers will be cut.
     */
    void Decimal::fit_string(std::pair<std::string, std::string> &string_pair) {
        const int MAX_INTEGER_PART_SIZE = CONSTANTS.INFORMATION_LIMIT_PER_NUMBER_OF_BITS[c_SIZE * 8 -
                                                                                         c_SCALING_FACTOR];
        const int MAX_FRACTION_PART_SIZE = CONSTANTS.INFORMATION_LIMIT_PER_NUMBER_OF_BITS[c_SCALING_FACTOR];
        if (string_pair.first.size() > MAX_INTEGER_PART_SIZE) {
            // If string representation for integer part is too big, clap it to the max size and set lex_all digits to 9.
            string_pair.first = std::string("9", MAX_INTEGER_PART_SIZE);
        }
        if (string_pair.second.size() > MAX_INTEGER_PART_SIZE) {
            // If string representation for fraction part is too long, cut the rest.
            // TODO Maybe add rounding here
            string_pair.second = string_pair.second.substr(0, MAX_FRACTION_PART_SIZE);
        }

    }


    Decimal::Decimal(const Boolean &other) : Number(Size::BYTE, true), c_SCALING_FACTOR(0) {
        switch (other.m_storage) {
            case Boolean::TRUE:
                m_storage = 1;
                break;
            case Boolean::FALSE:
                m_storage = 0;
                break;
            case Boolean::NEUTRAL: {
                auto pos = other.get_position();
                throw err::RuntimeError(pos.first, pos.second, "Can not convert value 'neutral' into a number",
                                        other.get_context());
            }
        }
    }

    Decimal::Decimal(const Integer &other) : Number(other.c_SIZE, other.m_is_positive), c_SCALING_FACTOR(0) {
        m_storage = other.m_storage;
    }

    Decimal::Decimal(const Decimal &other) : Number(other.c_SIZE, other.m_is_positive),
                                             c_SCALING_FACTOR(other.c_SCALING_FACTOR) {
        m_storage = other.m_storage;
    }

    Decimal::Decimal(const String &other) : Number(Size::LONG, false), c_SCALING_FACTOR(0) {
        throw err::RuntimeError(other.get_position().first, other.get_position().second,
                                "Casting error form String to Decimal.",
                                other.get_context());
    }

    // Move Constructor
    Decimal::Decimal(const dat::Decimal &&other) noexcept: Number(std::move(other)),
                                                           c_SCALING_FACTOR(other.c_SCALING_FACTOR) {}

    // Constructs a Decimal form a string
    Decimal::Decimal(std::string str_repr, Size size, unsigned char scaling_factor) : Number(size, str_repr.empty() or
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


    Decimal Decimal::cast(const Boolean &other) {
        return Decimal(other);
    }
    Decimal Decimal::cast(const dat::Integer & other) {
        return Decimal(other);
    }
    Decimal Decimal::copy(const dat::Decimal & other) {
        return Decimal(other);
    }
    Decimal Decimal::cast(const dat::String & other) {
        return Decimal(other);
    }

    Decimal Decimal::cast(const VariantTypes &other) {
        switch (other.index()) {
                case 0 :
                    return Decimal::cast(std::get<Boolean>(other));
                case 1 :
                    return Decimal::cast(std::get<Integer>(other));
                case 2 :
                    return Decimal::copy(std::get<Decimal>(other));
                case 3 :
                    return Decimal::cast(std::get<String>(other));
                default:
                    throw std::runtime_error("Error in Decimal cast: Unexpected DataType");
        }
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
        while (index > 1 and fractional_part[index - 1] == '0') {
            --index;
        }
        fractional_part = fractional_part.substr(0, index);
        // Just like before: Reduce output limit to the important part.
        fractional_part = fractional_part.substr(0,
                                                 CONSTANTS.INFORMATION_LIMIT_PER_NUMBER_OF_BITS[c_SCALING_FACTOR]);
        result << fractional_part;
        return result.str();
    }

    void Decimal::print(std::ostream &os) const {
        os << to_string();
    }

} // dat