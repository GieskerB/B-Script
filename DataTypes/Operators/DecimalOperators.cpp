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
        Decimal left = Decimal::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Decimal + Boolean -> Decimal + Decimal = Decimal
                const VariantTypes right_casted = Decimal::cast(std::get<Boolean>(right_variant));
                return left + right_casted;
            }
            case 1: /* === Integer === */ {
                // Decimal + Integer -> Decimal + Decimal = Decimal
                const VariantTypes right_casted = Decimal::cast(std::get<Integer>(right_variant));
                return left + right_casted;
            }
            case 2: /* === Decimal === */ {
                // Decimal + Decimal = Decimal
                const auto &other_decimal = std::get<Decimal>(right_variant);
                const char SCALING_DELTA = static_cast<char>(left.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);

                auto shifted_storage = shift_to_equal_size(left.m_storage, other_decimal.m_storage, SCALING_DELTA);

                auto result_shifted = storage_addition(shifted_storage.first, shifted_storage.second,
                                                       left.m_is_positive,
                                                       other_decimal.m_is_positive);

                left.m_storage = unshift_form_equal_size(result_shifted.first, SCALING_DELTA);
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
        Decimal left = Decimal::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Decimal - Boolean -> Decimal - Decimal = Decimal
                const VariantTypes right_casted = Decimal::cast(right_variant);
                return left - right_casted;
            }
            case 1: /* === Integer === */ {
                // Decimal - Integer -> Decimal - Decimal = Decimal
                const VariantTypes right_casted = Decimal::cast(right_variant);
                return left - right_casted;
            }
            case 2: /* === Decimal === */ {
                // Decimal - Decimal -> Decimal + (-Decimal) = Decimal
                const auto &other_decimal = Decimal::copy(std::get<Decimal>(right_variant));
                // This cant be a String
                return std::get<Decimal>(left + (-other_decimal));
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Decimal Decimal::operator*(const VariantTypes &right_variant) const {
        Decimal left = Decimal::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Decimal * Boolean -> Decimal * Decimal = Decimal
                const VariantTypes right_casted = Decimal::cast(right_variant);
                return left * right_casted;
            }
            case 1: /* === Integer === */ {
                // Decimal * Integer -> Decimal * Decimal = Decimal
                const VariantTypes right_casted = Decimal::cast(right_variant);
                return left * right_casted;
            }
            case 2: /* === Decimal === */ {
                // Decimal * Decimal = Decimal
                const auto &other_decimal = std::get<Decimal>(right_variant);
                const char SCALING_DELTA = static_cast<char>(left.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);

                auto shifted_storage = shift_to_equal_size(left.m_storage, other_decimal.m_storage, SCALING_DELTA);

                left.m_is_positive ^= ~other_decimal.m_is_positive;

                shifted_storage.first *= shifted_storage.second;

                if (SCALING_DELTA > 0) {
                    shifted_storage.first >>= left.c_SCALING_FACTOR;
                } else {
                    shifted_storage.first >>= other_decimal.c_SCALING_FACTOR;
                }

                left.m_storage = unshift_form_equal_size(shifted_storage.first, SCALING_DELTA);
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
        Decimal left = Decimal::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Decimal / Boolean -> Decimal / Decimal = Decimal
                const VariantTypes right_casted = Decimal::cast(right_variant);
                return left * right_casted;
            }
            case 1: /* === Integer === */ {
                // Decimal / Integer -> Decimal / Decimal = Decimal
                const VariantTypes right_casted = Decimal::cast(right_variant);
                return left * right_casted;
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(right_variant);
                if (other_decimal.is_zero()) {
                    throw err::RuntimeError(other_decimal.m_position_start, other_decimal.m_position_end,
                                            "Division by 0 is not allowed!", *other_decimal.p_context);
                }

                const char SCALING_DELTA = static_cast<char>(left.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);

                auto shifted_storage = shift_to_equal_size(left.m_storage, other_decimal.m_storage, SCALING_DELTA);

                left.m_is_positive ^= ~other_decimal.m_is_positive;

                if (SCALING_DELTA > 0) {
                    shifted_storage.first <<= left.c_SCALING_FACTOR;
                } else {
                    shifted_storage.first <<= other_decimal.c_SCALING_FACTOR;
                }

                shifted_storage.first /= shifted_storage.second;

                left.m_storage = unshift_form_equal_size(shifted_storage.first, SCALING_DELTA);
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
        return Decimal::copy(*this);
    }

    Decimal Decimal::operator-() const {
        auto result = Decimal::copy(*this);
        result.m_is_positive = !result.m_is_positive;
        return result;
    }

    VariantTypes Decimal::operator!() const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    Boolean Decimal::operator<(const VariantTypes &right_variant) const {
        Decimal left = Decimal::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                // Decimal < Integer -> Decimal < Decimal = Boolean
                const auto &right = std::get<Integer>(right_variant);
                return left < right;
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(right_variant);
                const char SCALING_DELTA = static_cast<char>(left.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);
                auto shifted_storage = shift_to_equal_size(left.m_storage, other_decimal.m_storage, SCALING_DELTA);

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, left.m_is_positive,
                                               other_decimal.m_is_positive);
                return Boolean(std::get<0>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Decimal::operator>(const VariantTypes &other) const {
        Decimal copy = Decimal::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                const auto &copy_casted = Integer::cast(copy);
                return other > copy_casted;
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const char SCALING_DELTA = static_cast<char>(copy.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);
                auto shifted_storage = shift_to_equal_size(copy.m_storage, other_decimal.m_storage, SCALING_DELTA);

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, copy.m_is_positive,
                                               other_decimal.m_is_positive);
                return Boolean(std::get<2>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Decimal::operator<=(const VariantTypes &other) const {
        Decimal copy = Decimal::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                const auto &copy_casted = Integer::cast(copy);
                return other <= copy_casted;
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const char SCALING_DELTA = static_cast<char>(copy.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);
                auto shifted_storage = shift_to_equal_size(copy.m_storage, other_decimal.m_storage, SCALING_DELTA);

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, copy.m_is_positive,
                                               other_decimal.m_is_positive);
                return Boolean(std::get<0>(comp) or std::get<1>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Decimal::operator>=(const VariantTypes &other) const {
        Decimal copy = Decimal::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                const auto &copy_casted = Integer::cast(copy);
                return other >= (copy_casted);
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const char SCALING_DELTA = static_cast<char>(copy.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);
                auto shifted_storage = shift_to_equal_size(copy.m_storage, other_decimal.m_storage, SCALING_DELTA);

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, copy.m_is_positive,
                                               other_decimal.m_is_positive);
                return Boolean(std::get<1>(comp) or std::get<2>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Decimal::operator==(const VariantTypes &other) const {
        Decimal copy = Decimal::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                const auto &copy_casted = Integer::cast(copy);
                return other == (copy_casted);
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const char SCALING_DELTA = static_cast<char>(copy.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);
                auto shifted_storage = shift_to_equal_size(copy.m_storage, other_decimal.m_storage, SCALING_DELTA);

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, copy.m_is_positive,
                                               other_decimal.m_is_positive);
                return Boolean(std::get<1>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Decimal::operator!=(const VariantTypes &other) const {
        Decimal copy = Decimal::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                const auto &copy_casted = Integer::cast(copy);
                return other != (copy_casted);
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const char SCALING_DELTA = static_cast<char>(copy.c_SCALING_FACTOR - other_decimal.c_SCALING_FACTOR);
                auto shifted_storage = shift_to_equal_size(copy.m_storage, other_decimal.m_storage, SCALING_DELTA);

                auto comp = storage_comparison(shifted_storage.first, shifted_storage.second, copy.m_is_positive,
                                               other_decimal.m_is_positive);
                return Boolean(std::get<0>(comp) or std::get<2>(comp));
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Decimal::operator&&(const VariantTypes &other) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    Boolean Decimal::operator||(const VariantTypes &other) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

}
