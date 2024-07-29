#include "Utility.hpp"

namespace dat {

    VariantTypes Utility::create_form_key(const std::string &value, short key) {
        short type = key & 0b1111;
        short size = (key >> 4) & 0b1111;
        short extra = (key >> 8) & 0b11111111;

        if (type == 1) {
            VariantTypes res = Integer{value, static_cast<Size>(size), extra != 0};
            return Integer{value, static_cast<Size>(size), extra != 0};
        } else if (type == 2) {
            return Decimal(value, static_cast<Size>(size), extra);
        } else {
            if (value.find('.') == std::string::npos) {
                return Integer(value);
            } else {
                return Decimal(value);
            }
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
            return v.get_position();
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