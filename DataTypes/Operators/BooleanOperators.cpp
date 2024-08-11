#include <iostream>
#include "../Number.hpp"
#include "../../Error/Error.hpp"

#include "../Boolean.hpp"
#include "../Integer.hpp"
#include "../Decimal.hpp"
#include "../String.hpp"
#include "../Utility.hpp"

namespace dat {

    VariantTypes Boolean::operator+(const VariantTypes &right_variant) const {
        Boolean left = Boolean::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */ {
                // Boolean + Boolean -> Integer + Bool = Integer
                const auto &left_casted = Integer::cast(left);
                const auto &right = std::get<Boolean>(right_variant);
                return left_casted + std::move(right);
            }
            case 1: /* === Integer === */ {
                // Boolean + Integer -> Integer + Integer = Integer
                const auto &left_casted = Integer::cast(left);
                const auto &right = std::get<Integer>(right_variant);
                return left_casted + std::move(right);
            }
            case 2: /* === Decimal === */ {
                // Boolean + Decimal -> Decimal + Decimal = Decimal
                const auto &left_casted = Integer::cast(left);
                const auto &right = std::get<Decimal>(right_variant);
                return left_casted + std::move(right);
            }
            case 3: /* === String === */{
                // Boolean + String -> String + String = String
                const auto &left_casted = String::cast(left);
                const auto &right = std::get<String>(right_variant);
                return left_casted + std::move(right);
            }
            default:
                throw std::runtime_error("Unexpected type of right_variant in operator.cpp");
        }
    }

    VariantTypes Boolean::operator-(const VariantTypes &right_variant) const {
        Boolean left = Boolean::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Boolean - Boolean -> Integer - Boolean = Integer
                const auto &left_casted = Integer::cast(left);
                const auto &right = std::get<Boolean>(right_variant);
                return left_casted - std::move(right);
            }
            case 1: /* === Integer === */ {
                // Boolean - Integer -> Integer - Integer = Integer
                const auto &left_casted = Integer::cast(left);
                const auto &right = std::get<Integer>(right_variant);
                return left_casted - std::move(right);
            }
            case 2: /* === Decimal === */ {
                // Boolean - Decimal -> Decimal - Decimal = Decimal
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

    VariantTypes Boolean::operator*(const VariantTypes &right_variant) const {
        Boolean left = Boolean::copy(*this);
        switch (right_variant.index()) {
            case 0: /* === Boolean === */{
                // Boolean * Boolean -> Integer * Boolean = Integer
                const auto &left_casted = Integer::cast(left);
                const auto &right = std::get<Boolean>(right_variant);
                return left_casted * std::move(right);
            }
            case 1: /* === Integer === */ {
                // Boolean * Integer -> Integer * Integer = Integer
                const auto &left_casted = Integer::cast(left);
                const auto &right = std::get<Integer>(right_variant);
                return left_casted * std::move(right);
            }
            case 2: /* === Decimal === */ {
                // Boolean * Decimal -> Decimal * Decimal = Decimal
                const auto &left_casted = Integer::cast(left);
                const auto &right = std::get<Decimal>(right_variant);
                return left_casted * std::move(right);
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

    VariantTypes Boolean::operator+() const {
        // +Boolean -> +Integer = Integer
        return +Integer::cast(*this);
    }

    VariantTypes Boolean::operator-() const {
        // -Boolean -> -Integer = Integer
        return -Integer::cast(*this);
    }

    VariantTypes Boolean::operator!() const {
        // !Boolean = Boolean
        Boolean result = Boolean::copy(*this);
        if (m_storage == TriState::TRUE) {
            result.m_storage = TriState::FALSE;
        } else if (m_storage == TriState::FALSE) {
            result.m_storage = TriState::TRUE;
        }
        return result;
    }

    Boolean Boolean::operator<(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */ {
                const auto &other_boolean = std::get<Boolean>(other);
                if (m_storage == TriState::NEUTRAL or other_boolean.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage < other_boolean.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator>(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */ {
                const auto &other_boolean = std::get<Boolean>(other);
                if (m_storage == TriState::NEUTRAL or other_boolean.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage > other_boolean.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator<=(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */ {
                const auto &other_boolean = std::get<Boolean>(other);
                if (m_storage == TriState::NEUTRAL or other_boolean.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage <= other_boolean.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator>=(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */ {
                const auto &other_boolean = std::get<Boolean>(other);
                if (m_storage == TriState::NEUTRAL or other_boolean.m_storage == TriState::NEUTRAL) {
                    return Boolean(TriState::NEUTRAL);
                }
                if (m_storage >= other_boolean.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator==(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */ {
                const auto &other_boolean = std::get<Boolean>(other);
                if (m_storage == other_boolean.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator!=(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */ {
                const auto &other_boolean = std::get<Boolean>(other);
                if (m_storage != other_boolean.m_storage) {
                    return Boolean(TriState::TRUE);
                } else {
                    return Boolean(TriState::FALSE);
                }
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator&&(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */ {
                const auto &other_boolean = std::get<Boolean>(other);
                if (copy.m_storage == TriState::FALSE || other_boolean.m_storage == TriState::FALSE) {
                    return Boolean(TriState::FALSE);
                };
                if (copy.m_storage == TriState::TRUE && other_boolean.m_storage == TriState::TRUE) {
                    return Boolean(TriState::TRUE);
                }
                return Boolean(TriState::NEUTRAL); // One or both are NEUTRAL
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }

    Boolean Boolean::operator||(const VariantTypes &other) const {
        Boolean copy = Boolean::copy(*this);
        switch (other.index()) {
            case 0: /* === Boolean === */ {
                const auto &other_boolean = std::get<Boolean>(other);
                if (copy.m_storage == TriState::TRUE || other_boolean.m_storage == TriState::TRUE) {
                    return Boolean(TriState::TRUE);
                };
                if (copy.m_storage == TriState::FALSE && other_boolean.m_storage == TriState::FALSE) {
                    return Boolean(TriState::FALSE);
                }
                return Boolean(TriState::NEUTRAL); // One or both are NEUTRAL
            }
            case 1: /* === Integer === */
            case 2: /* === Decimal === */
            case 3: /* === String === */
                throw err::InvalidSyntaxError(m_position_start, get_position_form_variant(other)
                                                      .second,
                                              "Operators not implemented.");
            default:
                throw std::runtime_error("Unexpected type of other in operator.cpp");
        }
    }
}
