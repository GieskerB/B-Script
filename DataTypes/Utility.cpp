#include <iostream>
#include <vector>
#include <sstream>
#include <ranges>
#include <algorithm>

#include "Utility.hpp"
#include "../Lexer/Keywords.hpp"

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

    std::string number_to_string(uint64 number, bool is_positivee) {
        std::vector<char> digits;

        if (number == 0) {
            digits.push_back('0');
        }
        while (number != 0) {
            unsigned char digit = number % 10;
            number /= 10;
            digits.push_back(static_cast<char>(digit + '0'));
        }
        if (!is_positivee) {
            digits.push_back(static_cast<char>('-'));
        }

        std::stringstream result;
        for (char &digit: std::ranges::reverse_view(digits)) {
            result << digit;
        }
        return result.str();
    }

    uint64 string_to_number(const std::string &str_repr) {
        if (str_repr.empty()) return 0;

        const int start = str_repr[0] == '-' ? 1 : 0;
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

    VariantTypes create_datatype_form_string(const lex::Token &tok) {
        const uint16_t param = tok.c_parameter;
        const std::string &value_str = tok.c_value;

        // Handel Strings and Boolean very easily
        if (param & lex::Keywords::BITMAP_STR or value_str[0] == '"') {
            return String(value_str);
        } else if (param & lex::Keywords::BITMAP_BOOL or value_str == Boolean::TRUE or value_str == Boolean::FALSE or
                   value_str == Boolean::NEUTRAL) {
            return Boolean(value_str);
        }

        // Now the complex part: Numbers
        const size_t decimal_pos = value_str.find('.');
        const bool has_decimal_point = decimal_pos != std::string::npos;
        if (param == 0) {
            // No data type specified.
            if (!has_decimal_point) {
                return Integer(value_str);
            }
            // Estimate bits needed for integer part.
            uint8_t decimal_point_pos = decimal_pos > 20 ? 20 : static_cast<uint8_t> (decimal_pos);
            uint8_t required_bits_int_part = LookUp::log_base_2_of_10_to_x[decimal_point_pos];
            return Decimal(value_str, Size::LONG, 64 - required_bits_int_part);
        } else {
            auto size = static_cast<dat::Size>(param >> 4 & 0b1111);
            if(param & lex::Keywords::BITMAP_INT) {
                return Integer(value_str, size, !(param & lex::Keywords::BITMAP_UNSIGNED));
            } else {
                uint8_t scale_fac = param >> 16;
                return Decimal(value_str,size,scale_fac);
            }
        }
    }

    std::pair<uint128, bool>
    storage_addition(uint128 storage1, const uint128& storage2, bool is_positive1, const bool is_positive2) {
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
    storage_addition(uint64 storage1, const uint64 storage2, bool is_positive1, const bool is_positive2) {
        return static_cast<std::pair<uint64, bool>> (storage_addition(static_cast<uint128>(storage1),
                                                                      static_cast<uint128>(storage2),
                                                                      is_positive1, is_positive2));
    }

    std::tuple<bool, bool, bool>
    storage_comparison(const uint128 storage1, const uint128& storage2, const bool is_positive1, const bool is_positive2) {
        bool is_smaller = (!is_positive1 and is_positive2) or (is_positive1 == is_positive2 and storage1 < storage2);
        bool is_equals = storage1 == storage2 and is_positive1 == is_positive2;
        bool is_bigger = (is_positive1 and !is_positive2) or (is_positive1 == is_positive2 and storage1 > storage2);
        return std::tuple{is_smaller, is_equals, is_bigger};
    }

    std::tuple<bool, bool, bool>
    storage_comparison(const uint64 storage1, const uint64 storage2, const bool is_positive1, const bool is_positive2) {
        return storage_comparison(static_cast<uint128>(storage1), static_cast<uint128>(storage2), is_positive1,
                                  is_positive2);
    }

    std::pair<uint128, uint128>
    shift_to_equal_size(const uint64 storage1, const uint64 storage2, const int8_t SCALING_DELTA) {
        if (SCALING_DELTA > 0) {
            return std::pair{storage1, (static_cast<uint128> (storage2)) << SCALING_DELTA};
        } else if (SCALING_DELTA < 0) {
            return std::pair{(static_cast<uint128> (storage1)) << -SCALING_DELTA, storage2};
        } else {
            return std::pair{storage1, storage2};
        }
    }

    uint64 unshift_form_equal_size(const uint128 large_storage1, const int8_t SCALING_DELTA) {
        if (SCALING_DELTA < 0) {
            return large_storage1 >> - SCALING_DELTA;
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

    VariantTypes operator+(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) + right;
            case 1:
                return std::get<Integer>(left) + right;
            case 2:
                return std::get<Decimal>(left) + right;
            case 3:
                return std::get<String>(left) + right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator-(const VariantTypes &left, const VariantTypes &right) {
//        return std::visit([&right](auto&& leftValue) {
//            return leftValue - right;
//        }, left);
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) - right;
            case 1:
                return std::get<Integer>(left) - right;
            case 2:
                return std::get<Decimal>(left) - right;
            case 3:
                return std::get<String>(left) - right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator*(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) * right;
            case 1:
                return std::get<Integer>(left) * right;
            case 2:
                return std::get<Decimal>(left) * right;
            case 3:
                return std::get<String>(left) * right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator/(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) / right;
            case 1:
                return std::get<Integer>(left) / right;
            case 2:
                return std::get<Decimal>(left) / right;
            case 3:
                return std::get<String>(left) / right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator<(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) < right;
            case 1:
                return std::get<Integer>(left) < right;
            case 2:
                return std::get<Decimal>(left) < right;
            case 3:
                return std::get<String>(left) < right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator<=(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) <= right;
            case 1:
                return std::get<Integer>(left) <= right;
            case 2:
                return std::get<Decimal>(left) <= right;
            case 3:
                return std::get<String>(left) <= right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator>(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) > right;
            case 1:
                return std::get<Integer>(left) > right;
            case 2:
                return std::get<Decimal>(left) > right;
            case 3:
                return std::get<String>(left) > right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator>=(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) >= right;
            case 1:
                return std::get<Integer>(left) >= right;
            case 2:
                return std::get<Decimal>(left) >= right;
            case 3:
                return std::get<String>(left) >= right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator==(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) == right;
            case 1:
                return std::get<Integer>(left) == right;
            case 2:
                return std::get<Decimal>(left) == right;
            case 3:
                return std::get<String>(left) == right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator!=(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) != right;
            case 1:
                return std::get<Integer>(left) != right;
            case 2:
                return std::get<Decimal>(left) != right;
            case 3:
                return std::get<String>(left) != right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator&&(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) && right;
            case 1:
                return std::get<Integer>(left) && right;
            case 2:
                return std::get<Decimal>(left) && right;
            case 3:
                return std::get<String>(left) && right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    Boolean operator||(const VariantTypes &left, const VariantTypes &right) {
        switch (left.index()) {
            case 0:
                return std::get<Boolean>(left) || right;
            case 1:
                return std::get<Integer>(left) || right;
            case 2:
                return std::get<Decimal>(left) || right;
            case 3:
                return std::get<String>(left) || right;
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator+(const VariantTypes &var) {
        switch (var.index()) {
            case 0:
                return +std::get<Boolean>(var);
            case 1:
                return +std::get<Integer>(var);
            case 2:
                return +std::get<Decimal>(var);
            case 3:
                return +std::get<String>(var);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator-(const VariantTypes &var) {
        switch (var.index()) {
            case 0:
                return -std::get<Boolean>(var);
            case 1:
                return -std::get<Integer>(var);
            case 2:
                return -std::get<Decimal>(var);
            case 3:
                return -std::get<String>(var);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

    VariantTypes operator!(const VariantTypes &var) {
        switch (var.index()) {
            case 0:
                return -std::get<Boolean>(var);
            case 1:
                return -std::get<Integer>(var);
            case 2:
                return -std::get<Decimal>(var);
            case 3:
                return -std::get<String>(var);
        }
        throw std::runtime_error("std::variant error in Utility operator");
    }

} // dat