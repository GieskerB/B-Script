#include <iostream>
#include "../Number.hpp"
#include "../../Error/Error.hpp"

#include "../Boolean.hpp"
#include "../Integer.hpp"
#include "../Decimal.hpp"
#include "../String.hpp"
#include "../Utility.hpp"

namespace dat {

    VariantTypes Integer::operator+(const VariantTypes &right_variant) const {
        Integer left = Integer::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Integer + Boolean -> Integer + Integer = Integer
                const auto &right_casted = Integer::cast(std::get<Boolean>(right_variant));
                return left + std::move(right_casted);
            }
            case 1: /* === Integer === */ {
                // Integer + Integer = Integer
                const auto &other_integer = (std::get<Integer>(right_variant));
                auto result = storage_addition(left.m_storage, other_integer.m_storage, left.m_is_positive,
                                               other_integer.m_is_positive);
                left.m_storage = result.first;
                left.m_is_positive = result.second;
                left.clap_to_size();
                return left;
            }
            case 2: /* === Decimal === */ {
                // Integer + Decimal -> Decimal + Decimal = Decimal
                const auto &left_casted = Decimal::cast(left);
                const auto &right = std::get<Decimal>(right_variant);
                return left_casted + std::move(right);
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");

        }
    }

    VariantTypes Integer::operator-(const VariantTypes &right_variant) const {
        Integer left = Integer::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Integer - Boolean -> Integer - Integer = Integer
                const auto &right_casted = Integer::cast(std::get<Boolean>(right_variant));
                return left - std::move(right_casted);
            }
            case 1: /* === Integer === */ {
                // Integer - Integer -> Integer + (-Integer) = Integer
                const auto &other_integer = Integer::copy(std::get<Integer>(right_variant));
                const auto &other_integer_inverted = std::get<Integer>(-other_integer);
                return left + std::move(other_integer_inverted);
            }
            case 2: /* === Decimal === */ {
                // Integer - Decimal -> Integer + (-Decimal) = Decimal
                const auto &other_decimal = Decimal::copy(std::get<Decimal>(right_variant));
                const auto &other_decimal_inverted = std::get<Decimal>(-other_decimal);
                return left + std::move(other_decimal_inverted);
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    VariantTypes Integer::operator*(const VariantTypes &right_variant) const {
        Integer left = Integer::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Integer - Boolean -> Integer - Integer = Integer
                const auto &right_casted = Integer::cast(std::get<Boolean>(right_variant));
                return left * std::move(right_casted);
            }
            case 1: /* === Integer === */ {
                // Integer * Integer = Integer
                const auto &other_integer = std::get<Integer>(right_variant);
                // neg times neg = pos
                left.m_is_positive ^= ~other_integer.m_is_positive;
                left.m_storage *= other_integer.m_storage;
                left.clap_to_size();
                return left;
            }
            case 2: /* === Decimal === */ {
                // TODO
                const auto &other_decimal = std::get<Decimal>(right_variant);
                const auto &casted_decimal = Decimal::cast(*this);
                return casted_decimal * std::move(other_decimal);
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    VariantTypes Integer::operator/(const VariantTypes &right_variant) const {
        Integer left = Integer::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Integer * Boolean -> Integer * Integer = Integer
                const auto &right_casted = Integer::cast(std::get<Boolean>(right_variant));
                return left * std::move(right_casted);
            }
            case 1: /* === Integer === */ {
                // Integer * Integer = Integer
                const auto &other_integer = std::get<Integer>(right_variant);
                if (other_integer.is_zero()) {
                    throw err::RuntimeError(other_integer.m_position_start, other_integer.m_position_end,
                                            "Division by 0 is not allowed!", *other_integer.p_context);
                }
                // neg times neg = pos
                left.m_is_positive ^= ~other_integer.m_is_positive;

                left.m_storage /= other_integer.m_storage;

                left.clap_to_size();
                return left;
            }
            case 2: /* === Decimal === */ {
                // TODO
                const auto &other_decimal = std::get<Decimal>(right_variant);
                const auto &casted_decimal = Decimal::cast(*this);
                return casted_decimal / std::move(other_decimal);
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }


    VariantTypes Integer::operator+() const {
        return Integer::copy(*this);
    }

    VariantTypes Integer::operator-() const {
        Integer result = Integer::copy(*this);
        result.invert();
        return result;
    }

    VariantTypes Integer::operator!() const {
        throw err::InvalidSyntaxError(m_position_start, m_position_end, "Operator not implemented.");
    }

    Boolean Integer::operator<(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operator not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                auto comp = storage_comparison(m_storage, other_integer.m_storage, m_is_positive,
                                               other_integer.m_is_positive);
                return Boolean(std::get<0>(comp));
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const auto &other_casted = Integer::cast(other_decimal);

                return copy < std::move(other_casted);
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Integer::operator>(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                auto comp = storage_comparison(m_storage, other_integer.m_storage, m_is_positive,
                                               other_integer.m_is_positive);
                return Boolean(std::get<2>(comp));
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const auto &other_casted = Integer::cast(other_decimal);

                return copy > std::move(other_casted);
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Integer::operator<=(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                auto comp = storage_comparison(m_storage, other_integer.m_storage, m_is_positive,
                                               other_integer.m_is_positive);
                return Boolean(std::get<0>(comp) or std::get<1>(comp));
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const auto &other_casted = Integer::cast(other_decimal);

                return copy <= std::move(other_casted);
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Integer::operator>=(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                auto comp = storage_comparison(m_storage, other_integer.m_storage, m_is_positive,
                                               other_integer.m_is_positive);
                return Boolean(std::get<1>(comp) or std::get<2>(comp));
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const auto &other_casted = Integer::cast(other_decimal);

                return copy >= std::move(other_casted);
            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Integer::operator==(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                auto comp = storage_comparison(m_storage, other_integer.m_storage, m_is_positive,
                                               other_integer.m_is_positive);
                return Boolean(std::get<1>(comp));
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const auto &other_casted = Integer::cast(other_decimal);

                if (other_decimal.has_decimal_places()) {
                    return Boolean(false);
                } else {
                    return copy == std::move(other_casted);
                }

            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Integer::operator!=(const VariantTypes &other) const {
        Integer copy = Integer::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                        .second, "Operators not implemented.");
            case 1: /* === Integer === */ {
                const auto &other_integer = std::get<Integer>(other);
                auto comp = storage_comparison(m_storage, other_integer.m_storage, m_is_positive,
                                               other_integer.m_is_positive);
                return Boolean(std::get<0>(comp) or std::get<2>(comp));
            }
            case 2: /* === Decimal === */ {
                const auto &other_decimal = std::get<Decimal>(other);
                const auto &other_casted = Integer::cast(other_decimal);

                if (other_decimal.has_decimal_places()) {
                    return Boolean(true);
                } else {
                    return copy != std::move(other_casted);
                }

            }
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Integer::operator&&(const VariantTypes &other) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    Boolean Integer::operator||(const VariantTypes &other) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

}

