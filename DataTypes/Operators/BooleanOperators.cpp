#include <iostream>
#include "../Number.hpp"
#include "../../Error/Error.hpp"

namespace dat {

    VariantTypes Boolean::operator+(const VariantTypes &right_variant) const {
        Boolean left_boolean = Boolean(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Boolean + Boolean -> Integer + Bool = Integer
                const Integer left(left_boolean);
                const auto &right = std::get<Boolean>(right_variant);
                return left + right;
            }
            case 1: /* === Integer === */ {
                // Boolean + Integer -> Integer + Integer = Integer
                const Integer left(left_boolean);
                const auto &right = std::get<Integer>(right_variant);
                return left + right;
            }
            case 2: /* === Decimal === */ {
                // Boolean + Decimal -> Decimal + Decimal = Decimal
                const Decimal left(left_boolean);
                const auto &right = std::get<Decimal>(right_variant);
                return left + right;
            }
            case 3: /* === String === */{
                // Boolean + String -> String + String = String
                const String left(left_boolean);
                const auto &right = std::get<String>(right_variant);
                return left + right;
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    VariantTypes Boolean::operator-(const VariantTypes &right_variant) const {
        Boolean left_boolean = Boolean(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Boolean - Boolean -> Integer - Boolean = Integer
                const Integer left(left_boolean);
                const auto &right = std::get<Boolean>(right_variant);
                return left - right;
            }
            case 1: /* === Integer === */ {
                // Boolean - Integer -> Integer - Integer = Integer
                const Integer left(left_boolean);
                const auto &right = std::get<Integer>(right_variant);
                return left - right;
            }
            case 2: /* === Decimal === */ {
                // Boolean - Decimal -> Decimal - Decimal = Decimal
                const Decimal left(left_boolean);
                const auto &right = std::get<Decimal>(right_variant);
                return left - right;
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                        .second, "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    VariantTypes Boolean::operator*(const VariantTypes &right_variant) const {
        Boolean left_boolean = Boolean(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Boolean * Boolean -> Integer * Boolean = Integer
                const Integer left(left_boolean);
                const auto &right = std::get<Boolean>(right_variant);
                return left * right;
            }
            case 1: /* === Integer === */ {
                // Boolean * Integer -> Integer * Integer = Integer
                const Integer left(left_boolean);
                const auto &right = std::get<Integer>(right_variant);
                return left * right;
            }
            case 2: /* === Decimal === */ {
                // Boolean * Decimal -> Decimal * Decimal = Decimal
                const Decimal left(left_boolean);
                const auto &right = std::get<Decimal>(right_variant);
                return left * right;
            }
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    VariantTypes Boolean::operator/(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant).second,
                                              "Operator not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Integer Boolean::operator+() const {
        // +Boolean -> +Integer = Integer
        return +Integer(*this);
    }

    Integer Boolean::operator-() const {
        // -Boolean -> -Integer = Integer
        return -Integer(*this);
    }

    Boolean Boolean::operator!() const {
        // !Boolean = Boolean
        Boolean result(*this);
        if (m_storage == TriState::TRUE) {
            result.m_storage = TriState::FALSE;
        } else if (m_storage == TriState::FALSE) {
            result.m_storage = TriState::TRUE;
        }
        return result;
    }

    Boolean Boolean::operator<(const VariantTypes &right_variant) const {
        Boolean left(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                const auto &right = std::get<Boolean>(right_variant);
                if (m_storage == TriState::NEUTRAL or right.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage < right.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Boolean::operator>(const VariantTypes &right_variant) const {
        Boolean left(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                const auto &right = std::get<Boolean>(right_variant);
                if (m_storage == TriState::NEUTRAL or right.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage > right.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator<=(const VariantTypes &right_variant) const {
        Boolean left(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                const auto &right = std::get<Boolean>(right_variant);
                if (m_storage == TriState::NEUTRAL or right.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage <= right.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator>=(const VariantTypes &right_variant) const {
        Boolean left(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                const auto &right = std::get<Boolean>(right_variant);
                if (m_storage == TriState::NEUTRAL or right.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage >= right.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator==(const VariantTypes &right_variant) const {
        Boolean left(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                const auto &right = std::get<Boolean>(right_variant);
                if (m_storage == TriState::NEUTRAL or right.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage == right.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator!=(const VariantTypes &right_variant) const {
        Boolean left(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                const auto &right = std::get<Boolean>(right_variant);
                if (m_storage == TriState::NEUTRAL or right.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage == right.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator&&(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                const auto &right = std::get<Boolean>(right_variant);
                if (m_storage == TriState::FALSE || right.m_storage == TriState::FALSE) {
                    return Boolean(TriState::FALSE);
                }
                if (m_storage == TriState::TRUE && right.m_storage == TriState::TRUE) {
                    return Boolean(TriState::TRUE);
                }
                return Boolean(TriState::NEUTRAL); // One or both are NEUTRAL
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    Boolean Boolean::operator||(const VariantTypes &right_variant) const {
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                const auto &right = std::get<Boolean>(right_variant);
                if (m_storage == TriState::TRUE || right.m_storage == TriState::TRUE) {
                    return Boolean(TriState::TRUE);
                }
                if (m_storage == TriState::FALSE && right.m_storage == TriState::FALSE) {
                    return Boolean(TriState::FALSE);
                }
                return Boolean(TriState::NEUTRAL); // One or both are NEUTRAL
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(right_variant)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }
}
