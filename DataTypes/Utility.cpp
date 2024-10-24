#include <iostream>
#include <vector>
#include <sstream>
#include <ranges>
#include <algorithm>

#include "Utility.hpp"

namespace dat {


    DataType &get_variant_content(VariantTypes &variant) {
        switch (variant.index()) {
            case 0:
                return std::get<dat::Boolean>(variant);
            case 1:
                return std::get<dat::Integer>(variant);
            case 2:
                return std::get<dat::Decimal>(variant);
            case 3:
                return std::get<dat::String>(variant);
            default:
                throw std::runtime_error("std::variant error in get_variant_content()");
        }
    }

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

    uint64 string_to_number(const std::string &str_repr) {
        const int start = str_repr[0] == '-' ? 1 : 0;

        if (str_repr.empty()) {
            return 0;
        }

        uint64 result{0}, base{1};

        for (size_t i = str_repr.size() - 1; i >= start and i < str_repr.size(); --i) {
            char digit = str_repr[i];
            if (digit < '0' or digit > '9') {
                throw std::runtime_error(
                        "Invalid digit '" + std::to_string(digit) + "' in string \"" + str_repr + "\" at index " +
                        std::to_string(i) + "\n");
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

    VariantTypes create_datatype_form_string(const std::string &string) {
        if (string[0] == '"') {
            return String(string);
        } else if (string == Boolean::TRUE or string == Boolean::FALSE or string == Boolean::NEUTRAL) {
            return Boolean(string);
        }

        bool has_decimal_point = std::find(string.begin(), string.end(), '.') != string.end();
        if (!has_decimal_point) {
            return Integer(string);
        } else {
            std::stringstream string_stream{string};
            std::pair<std::string, std::string> split;
            std::getline(string_stream, split.first, '.');
            std::getline(string_stream, split.second);


            char required_bits_int_part = split.first.size() > 20 ? LookUp::log_base_2_of_10_to_x[20]
                                                                  : LookUp::log_base_2_of_10_to_x[split.first.size()];
            char required_bits_dec_part = split.second.size() > 20 ? LookUp::log_base_2_of_10_to_x[20]
                                                                   : LookUp::log_base_2_of_10_to_x[split.second.size()];

//            required_bits_dec_part = split.second.size() * 4 +1;

            if (required_bits_int_part + required_bits_dec_part > 64) {
                required_bits_dec_part = static_cast<char> (64 - required_bits_int_part);
            }
//            required_bits_dec_part /= 2;
//            required_bits_dec_part += 20;
            return Decimal(string, Size::LONG, required_bits_dec_part);

//
//            char index = static_cast<char> (CONSTANTS.SIZE -1);
//            while (CONSTANTS.log_base_2_of_10_to_x[index] > int_part_size and index >= 0) {
//                --index;
//            }
//            required_bits_int_part =index;
//
//            index = static_cast<char> (CONSTANTS.SIZE -1);
//            while (CONSTANTS.log_base_2_of_10_to_x[index] > dec_part_size and index >= 0) {
//                --index;
//            }
//            required_bits_dec_part = index +10;
//
//            if (required_bits_int_part + required_bits_dec_part > 64) {
//                required_bits_dec_part = 64 -required_bits_int_part;
//            }
//            std::cerr << (int)required_bits_dec_part;
//            return Decimal(string, Size::LONG, required_bits_dec_part);
        }
    }

    std::pair<uint128, bool>
    storage_addition(uint128 storage1, const uint128 storage2, bool is_positive1, const bool is_positive2) {
        if ((is_positive1 and is_positive2) or (!is_positive1 and !is_positive2)) {
            // Idea is: +5 + 2 = +(5 + 2)
            // And: -5 - 2 = -(5 + 2)
            storage1 += storage2;
        } else if (is_positive1) { // 1 is pos but 2 is neg
            if (storage1 < storage2) {
                // Idea is: 2 - 5 = - (5 - 2)
                is_positive1 = false;
                storage1 = storage2 - storage1;
            } else {
                storage1 -= storage2;
            }
        } else { // 1 ist neg and 2 is pos
            if (storage1 < storage2) {
                // Idea is: - 2 + 5 = 5 - 2
                is_positive1 = true;
                storage1 = storage2 - storage1;
            } else {
                // Idea is: - 5 + 2 = - (5 - 2)
                storage1 -= storage2;
            }
        }
        return std::pair{storage1, is_positive1};
    }

    std::pair<uint64, bool>
    storage_addition(uint64 storage1, const uint64 storage2, bool is_positiv1, const bool is_positive2) {
        return static_cast<std::pair<uint64, bool>> (storage_addition(static_cast<uint128>(storage1),
                                                                      static_cast<uint128>(storage2),
                                                                      is_positiv1, is_positive2));
    }

    std::tuple<bool, bool, bool>
    storage_comparison(const uint128 storage1, const uint128 storage2, const bool is_positiv1, const bool is_positiv2) {
        bool is_smaller, is_equals, is_bigger;
        is_smaller = (!is_positiv1 and is_positiv2) or (is_positiv1 == is_positiv2 and storage1 < storage2);
        is_equals = storage1 == storage2 and is_positiv1 == is_positiv2;
        is_bigger = (is_positiv1 and !is_positiv2) or (is_positiv1 == is_positiv2 and storage1 > storage2);

        return std::tuple{is_smaller, is_equals, is_bigger};
    }

    std::tuple<bool, bool, bool>
    storage_comparison(const uint64 storage1, const uint64 storage2, const bool is_positiv1, const bool is_positiv2) {
        return storage_comparison(static_cast<uint128>(storage1), static_cast<uint128>(storage2), is_positiv1,
                                  is_positiv2);
    }

    std::pair<uint128, uint128>
    shift_to_equal_size(const uint64 storage1, const uint64 storage2, const char SCALING_DELTA) {
        if (SCALING_DELTA > 0) {
            return std::pair{storage1, (static_cast<uint128> (storage2)) << SCALING_DELTA};
        } else if (SCALING_DELTA < 0) {
            return std::pair{(static_cast<uint128> (storage1)) << -SCALING_DELTA, storage2};
        } else {
            return std::pair{storage1, storage2};
        }
    }

    uint64 unshift_form_equal_size(const uint128 large_storage1, const char SCALING_DELTA) {
        if (SCALING_DELTA < 0) {
            return large_storage1 >> -SCALING_DELTA;
        } else {
            return large_storage1;
        }
    }

    std::pair<lex::Position, lex::Position> get_position_form_variant(const VariantTypes &variant) {
        auto get_pos = [](const auto &v) -> auto {
            return v.position();
        };
        return std::visit(get_pos, variant);
    }

    std::ostream &operator<<(std::ostream &ostream, const VariantTypes &datatype) {
        auto print_datatype = [&](auto &datatype) {
            ostream << datatype;
        };
        std::visit(print_datatype, datatype);
        return ostream;
    }

    VariantTypes operator+(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) + std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) + std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) + std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) + std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator-(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) - std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) - std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) - std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) - std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator*(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) * std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) * std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) * std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) * std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator/(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) / std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) / std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) / std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) / std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator<(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) < std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) < std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) < std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) < std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator<=(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) <= std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) <= std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) <= std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) <= std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator>(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) > std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) > std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) > std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) > std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator>=(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) >= std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) >= std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) >= std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) >= std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator==(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) == std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) == std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) == std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) == std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator!=(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) != std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) != std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) != std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) != std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator&&(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) && std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) && std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) && std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) && std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator||(const VariantTypes &variable_one, const VariantTypes &variable_two) {
        switch (variable_one.index()) {
            case 0:
                return std::get<Boolean>(variable_one) || std::move(variable_two);
            case 1:
                return std::get<Integer>(variable_one) || std::move(variable_two);
            case 2:
                return std::get<Decimal>(variable_one) || std::move(variable_two);
            case 3:
                return std::get<String>(variable_one) || std::move(variable_two);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator+(const VariantTypes &variable) {
        switch (variable.index()) {
            case 0:
                return +std::get<Boolean>(variable);
            case 1:
                return +std::get<Integer>(variable);
            case 2:
                return +std::get<Decimal>(variable);
            case 3:
                return +std::get<String>(variable);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator-(const VariantTypes &variable) {
        switch (variable.index()) {
            case 0:
                return -std::get<Boolean>(variable);
            case 1:
                return -std::get<Integer>(variable);
            case 2:
                return -std::get<Decimal>(variable);
            case 3:
                return -std::get<String>(variable);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator!(const VariantTypes &variable) {
        switch (variable.index()) {
            case 0:
                return -std::get<Boolean>(variable);
            case 1:
                return -std::get<Integer>(variable);
            case 2:
                return -std::get<Decimal>(variable);
            case 3:
                return -std::get<String>(variable);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

} // dat