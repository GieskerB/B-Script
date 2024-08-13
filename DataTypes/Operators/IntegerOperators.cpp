#include <iostream>
#include "../Number.hpp"
#include "../../Error/Error.hpp"

namespace dat {

    VariantTypes Integer::operator+(const VariantTypes &right_variant) const {
        Integer left = Integer::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Integer + Boolean -> Integer + Integer = Integer
                const VariantTypes &right_casted = Integer::cast(std::get<Boolean>(right_variant));
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
                const VariantTypes &right_casted = Integer::cast(std::get<Boolean>(right_variant));
                return left - std::move(right_casted);
            }
            case 1: /* === Integer === */ {
                // Integer - Integer -> Integer + (-Integer) = Integer
                const auto &right_casted= Integer::copy(std::get<Integer>(right_variant));
                return left + (-right_casted);
            }
            case 2: /* === Decimal === */ {
                // Integer - Decimal -> Decimal - Decimal = Decimal
                const auto &left_casted = Decimal::cast(left);
                const auto &right = std::get<Decimal>(right_variant);
                return left_casted - std::move(right);
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
                const VariantTypes &right_casted = Integer::cast(std::get<Boolean>(right_variant));
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
                // Integer * Decimal -> Decimal * Decimal = Decimal
                const auto &left_casted = Decimal::cast(left);
                const auto &right = std::get<Decimal>(right_variant);
                return left_casted * std::move(right);
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
                const VariantTypes &right_casted = Integer::cast(std::get<Boolean>(right_variant));
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
                // Integer / Decimal -> Decimal / Decimal = Decimal
                const auto &left_casted = Decimal::cast(left);
                const auto &right = std::get<Decimal>(right_variant);
                return left_casted / std::move(right);
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

    Boolean Integer::operator<(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            case 1: /* === Integer === */ {
                // Integer < Integer = Boolean
                const auto &right = std::get<Integer>(right_variant);
                const auto &comparison = storage_comparison(m_storage, right.m_storage, m_is_positive,
                                                     right.m_is_positive);
                return Boolean(std::get<0>(comparison));
            }
            case 2: /* === Decimal === */ {
                // Integer < Decimal -> Decimal < Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                const auto &left = Decimal::cast(right_variant);

                return left < std::move(right);
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Integer::operator>(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            case 1: /* === Integer === */ {
                // Integer > Integer = Boolean
                const auto &right = std::get<Integer>(right_variant);
                const auto &comparison = storage_comparison(m_storage, right.m_storage, m_is_positive,
                                                            right.m_is_positive);
                return Boolean(std::get<2>(comparison));
            }
            case 2: /* === Decimal === */ {
                // Integer > Decimal -> Decimal > Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                const auto &left = Decimal::cast(right_variant);

                return left > std::move(right);
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Integer::operator<=(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            case 1: /* === Integer === */ {
                // Integer <= Integer = Boolean
                const auto &right = std::get<Integer>(right_variant);
                const auto &comparison = storage_comparison(m_storage, right.m_storage, m_is_positive,
                                                            right.m_is_positive);
                return Boolean(std::get<0>(comparison) or std::get<1>(comparison));
            }
            case 2: /* === Decimal === */ {
                // Integer <= Decimal -> Decimal <= Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                const auto &left = Decimal::cast(right_variant);

                return left <= std::move(right);
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Integer::operator>=(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            case 1: /* === Integer === */ {
                // Integer >= Integer = Boolean
                const auto &right = std::get<Integer>(right_variant);
                const auto &comparison = storage_comparison(m_storage, right.m_storage, m_is_positive,
                                                            right.m_is_positive);
                return Boolean(std::get<1>(comparison) or std::get<2>(comparison));
            }
            case 2: /* === Decimal === */ {
                // Integer >= Decimal -> Decimal >= Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                const auto &left = Decimal::cast(right_variant);

                return left >= std::move(right);
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Integer::operator==(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            case 1: /* === Integer === */ {
                // Integer == Integer = Boolean
                const auto &right = std::get<Integer>(right_variant);
                const auto &comparison = storage_comparison(m_storage, right.m_storage, m_is_positive,
                                                            right.m_is_positive);
                return Boolean(std::get<1>(comparison));
            }
            case 2: /* === Decimal === */ {
                // Integer == Decimal -> Decimal == Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                const auto &left = Decimal::cast(right_variant);

                return left == std::move(right);
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Integer::operator!=(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            case 1: /* === Integer === */ {
                // Integer != Integer = Boolean
                const auto &right = std::get<Integer>(right_variant);
                const auto &comparison = storage_comparison(m_storage, right.m_storage, m_is_positive,
                                                            right.m_is_positive);
                return Boolean(std::get<0>(comparison) or std::get<2>(comparison));
            }
            case 2: /* === Decimal === */ {
                // Integer != Decimal -> Decimal != Decimal = Boolean
                const auto &right = std::get<Decimal>(right_variant);
                const auto &left = Decimal::cast(right_variant);

                return left != std::move(right);
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Integer::operator&&(const VariantTypes &) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

    Boolean Integer::operator||(const VariantTypes &) const {
        throw std::runtime_error("Unexpected type of other in operator.cpp");
    }

}

