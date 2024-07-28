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

    std::ostream &operator<<(std::ostream & ostream, const VariantTypes & datatype) {
        auto print_datatype = [&](auto& datatype) {
            ostream << datatype;
        };
        std::visit(print_datatype,datatype);
        return ostream;
    }

    VariantTypes operator+(const VariantTypes & variable_one, const VariantTypes & variable_two) {
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

    VariantTypes operator-(const VariantTypes & variable_one, const VariantTypes & variable_two) {
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

    VariantTypes operator*(const VariantTypes & variable_one, const VariantTypes & variable_two) {
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

    VariantTypes operator/(const VariantTypes & variable_one, const VariantTypes & variable_two) {
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


} // dat