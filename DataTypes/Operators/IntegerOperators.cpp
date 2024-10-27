#include <iostream>
#include "../Number.hpp"
#include "../../Error/Error.hpp"

namespace dat {

    VariantTypes Integer::operator+(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Integer + Boolean -> Integer + Integer = Integer
                const Integer right(std::get<Boolean>(right_variant));
                return *this + right;
            }
            case 1: /* === Integer === */ {
                // Integer + Integer = Integer
                Integer left = Integer(*this);
                const auto &right = std::get<Integer>(right_variant);
                auto result = storage_addition(left.m_storage, right.m_storage, left.m_is_positive,
                                               right.m_is_positive);
                left.m_storage = result.first;
                left.m_is_positive = result.second;
                left.clap_to_size();
                return left;
            }
            case 2: /* === Decimal === */ {
                // Integer + Decimal -> Decimal + Decimal = Decimal
                const Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);
                return left + right;
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");

        }
    }

    VariantTypes Integer::operator-(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Integer - Boolean -> Integer - Integer = Integer
                const Integer right(std::get<Boolean>(right_variant));
                return *this - right;
            }
            case 1: /* === Integer === */ {
                // Integer - Integer -> Integer + (-Integer) = Integer
                const auto &right_casted= Integer(std::get<Integer>(right_variant));
                return *this + -right_casted;
            }
            case 2: /* === Decimal === */ {
                // Integer - Decimal -> Decimal - Decimal = Decimal
                const Decimal left_casted (*this);
                const auto &right = std::get<Decimal>(right_variant);
                return left_casted - right;
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    VariantTypes Integer::operator*(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Integer - Boolean -> Integer - Integer = Integer
                const Integer right ( std::get<Boolean>(right_variant));
                return *this * right;
            }
            case 1: /* === Integer === */ {
                // Integer * Integer = Integer
                Integer left(*this);
                const auto &other_integer = std::get<Integer>(right_variant);
                // neg times neg = pos
                left.m_is_positive ^= ~other_integer.m_is_positive;
                left.m_storage *= other_integer.m_storage;
                left.clap_to_size();
                return left;
            }
            case 2: /* === Decimal === */ {
                // Integer * Decimal -> Decimal * Decimal = Decimal
                const Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);
                return left * right;
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    VariantTypes Integer::operator/(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Integer * Boolean -> Integer * Integer = Integer
                const Integer right ( std::get<Boolean>(right_variant));
                return *this * right;
            }
            case 1: /* === Integer === */ {
                // Integer * Integer = Integer
                Integer left(*this);
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
                const Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);
                return left * right;
            }

            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }


    Integer Integer::operator+() const {
        return *this;
    }

    Integer Integer::operator-() const {
        Integer result = Integer(*this);
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
                const Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);

                return left < right;
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
                const Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);

                return left > right;
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
                const Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);

                return left <= right;
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
                const Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);

                return left >= right;
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
                const Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);

                return left == right;
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
                const Decimal left (*this);
                const auto &right = std::get<Decimal>(right_variant);

                return left != right;
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

