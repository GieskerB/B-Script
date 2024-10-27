#include <iostream>
#include "../Number.hpp"
#include "../../Error/Error.hpp"

#include "../Boolean.hpp"
#include "../Integer.hpp"
#include "../Decimal.hpp"
#include "../String.hpp"
#include "../Utility.hpp"

namespace dat {

    VariantTypes Decimal::operator+(const VariantTypes &right_variant) const {

        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Decimal + Boolean -> Decimal + Decimal = Decimal
                const Decimal right(std::get<Boolean>(right_variant));
                return *this + right;
            }
            case 1: /* === Integer === */ {
                // Decimal + Integer -> Decimal + Decimal = Decimal
                const Decimal right(std::get<Integer>(right_variant));
                return *this + right;
            }
            case 2: /* === Decimal === */ {
                // Decimal + Decimal = Decimal
                Decimal left(*this);
                const auto &right = std::get<Decimal>(right_variant);
                const char scale = static_cast<char>(left.c_SCALING_FACTOR - right.c_SCALING_FACTOR);

                auto shifted_storage = shift_to_equal_size(left.m_storage, right.m_storage, scale);

                auto result_shifted = storage_addition(shifted_storage.first, shifted_storage.second,
                                                       left.m_is_positive, right.m_is_positive);

                left.m_storage = unshift_form_equal_size(result_shifted.first, scale);
                left.m_is_positive = result_shifted.second;
                left.clap_to_size();
                return left;
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Decimal Decimal::operator-(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Decimal - Boolean -> Decimal - Decimal = Decimal
                const auto &right = Decimal(std::get<Boolean>(right_variant));
                return *this - right;
            }
            case 1: /* === Integer === */ {
                // Decimal - Integer -> Decimal - Decimal = Decimal
                const auto &right = Decimal(std::get<Integer>(right_variant));
                return *this - right;
            }
            case 2: /* === Decimal === */ {
                // Decimal - Decimal -> Decimal + (-Decimal) = Decimal
                const auto &other_decimal = Decimal(std::get<Decimal>(right_variant));
                return std::get<Decimal>(*this + (-other_decimal)); // This cant be a String
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Decimal Decimal::operator*(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Decimal * Boolean -> Decimal * Decimal = Decimal
                const auto &right = Decimal(std::get<Boolean>(right_variant));
                return *this * right;
            }
            case 1: /* === Integer === */ {
                // Decimal * Integer -> Decimal * Decimal = Decimal
                const auto &right = Decimal(std::get<Integer>(right_variant));
                return *this * right;
            }
            case 2: /* === Decimal === */ {
                // Decimal * Decimal = Decimal
                Decimal left(*this);
                const auto &other_decimal = std::get<Decimal>(right_variant);
                const char scale = static_cast<char>(left.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);

                auto shifted_storage = shift_to_equal_size(left.m_storage, other_decimal.m_storage, scale);

                left.m_is_positive ^= ~other_decimal.m_is_positive;

                shifted_storage.first *= shifted_storage.second;

                if (scale > 0) {
                    shifted_storage.first >>= left.c_SCALING_FACTOR;
                } else {
                    shifted_storage.first >>= other_decimal.c_SCALING_FACTOR;
                }

                left.m_storage = unshift_form_equal_size(shifted_storage.first, scale);
                left.clap_to_size();
                return left;
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant).second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Decimal Decimal::operator/(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Decimal / Boolean -> Decimal / Decimal = Decimal
                const auto &right = Decimal(std::get<Boolean>(right_variant));
                return *this * right;
            }
            case 1: /* === Integer === */ {
                // Decimal / Integer -> Decimal / Decimal = Decimal
                const auto &right = Decimal(std::get<Integer>(right_variant));
                return *this * right;
            }
            case 2: /* === Decimal === */ {
                Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);
                if (right.is_zero()) {
                    throw err::RuntimeError(right.m_position_start, right.m_position_end,
                                            "Division by 0 is not allowed!", *right.p_context);
                }

                const char scale = static_cast<char>(left.c_SCALING_FACTOR - right.c_SCALING_FACTOR);
                auto shifted_storage = shift_to_equal_size(left.m_storage, right.m_storage, scale);

                left.m_is_positive ^= ~right.m_is_positive;

                if (scale > 0) {
                    shifted_storage.first <<= left.c_SCALING_FACTOR;
                } else {
                    shifted_storage.first <<= right.c_SCALING_FACTOR;
                }

                shifted_storage.first /= shifted_storage.second;

                left.m_storage = unshift_form_equal_size(shifted_storage.first, scale);
                left.clap_to_size();
                return left;
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }


    Decimal Decimal::operator+() const {
        return *this;
    }

    Decimal Decimal::operator-() const {
        auto result = Decimal(*this);
        result.m_is_positive = !result.m_is_positive;
        return result;
    }

    VariantTypes Decimal::operator!() const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    Boolean Decimal::operator<(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                // Decimal < Integer -> Decimal < Decimal = Boolean
                const Decimal right(std::get<Integer>(right_variant));
                return *this < right;
            }
            case 2: /* === Decimal === */ {
                // Decimal < Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                auto shifted_storage = shift_to_equal_size(m_storage, right.m_storage,
                                                           static_cast<char>(c_SCALING_FACTOR -
                                                                             right.c_SCALING_FACTOR));

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, m_is_positive,
                                               right.m_is_positive);
                return Boolean(std::get<0>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Decimal::operator>(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                // Decimal < Integer -> Decimal < Decimal = Boolean
                const Decimal right(std::get<Integer>(right_variant));
                return *this > right;
            }
            case 2: /* === Decimal === */ {
                // Decimal < Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                auto shifted_storage = shift_to_equal_size(m_storage, right.m_storage,
                                                           static_cast<char>(c_SCALING_FACTOR -
                                                                             right.c_SCALING_FACTOR));

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, m_is_positive,
                                               right.m_is_positive);
                return Boolean(std::get<2>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Decimal::operator<=(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                // Decimal < Integer -> Decimal < Decimal = Boolean
                const Decimal right(std::get<Integer>(right_variant));
                return *this <= right;
            }
            case 2: /* === Decimal === */ {
                // Decimal < Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                auto shifted_storage = shift_to_equal_size(m_storage, right.m_storage,
                                                           static_cast<char>(c_SCALING_FACTOR -
                                                                             right.c_SCALING_FACTOR));

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, m_is_positive,
                                               right.m_is_positive);
                return Boolean(std::get<0>(comp) or std::get<1>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Decimal::operator>=(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                // Decimal < Integer -> Decimal < Decimal = Boolean
                const Decimal right(std::get<Integer>(right_variant));
                return *this >= right;
            }
            case 2: /* === Decimal === */ {
                // Decimal < Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                auto shifted_storage = shift_to_equal_size(m_storage, right.m_storage,
                                                           static_cast<char>(c_SCALING_FACTOR -
                                                                             right.c_SCALING_FACTOR));

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, m_is_positive,
                                               right.m_is_positive);
                return Boolean(std::get<1>(comp) or std::get<2>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Decimal::operator==(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                // Decimal < Integer -> Decimal < Decimal = Boolean
                const Decimal right(std::get<Integer>(right_variant));
                return *this == right;
            }
            case 2: /* === Decimal === */ {
                // Decimal < Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                auto shifted_storage = shift_to_equal_size(m_storage, right.m_storage,
                                                           static_cast<char>(c_SCALING_FACTOR -
                                                                             right.c_SCALING_FACTOR));

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, m_is_positive,
                                               right.m_is_positive);
                return Boolean(std::get<1>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Decimal::operator!=(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                // Decimal < Integer -> Decimal < Decimal = Boolean
                const Decimal right(std::get<Integer>(right_variant));
                return *this != right;
            }
            case 2: /* === Decimal === */ {
                // Decimal < Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                auto shifted_storage = shift_to_equal_size(m_storage, right.m_storage,
                                                           static_cast<char>(c_SCALING_FACTOR -
                                                                             right.c_SCALING_FACTOR));

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, m_is_positive,
                                               right.m_is_positive);
                return Boolean(std::get<0>(comp) or std::get<2>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Decimal::operator&&(const VariantTypes &) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    Boolean Decimal::operator||(const VariantTypes &) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

}
