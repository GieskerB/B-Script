#include "../Utility.hpp"
#include "../../Error/Error.hpp"

template<typename T>
static inline T variant_cast(const dat::VariantTypes &var) {
    return std::visit([](auto &&arg) -> T { return static_cast<T>(arg); }, var);
}

template<int N>
static inline lex::Position variant_position(const dat::VariantTypes &var) {
    return std::visit([](auto &&arg) -> lex::Position { return N == 1 ? arg.position().first : arg.position().second; },
                      var);
}

static inline size_t max_prio(const dat::VariantTypes &var1, const dat::VariantTypes &var2) {
    return std::max(var1.index(), var2.index());
}

static inline size_t min_prio(const dat::VariantTypes &var1, const dat::VariantTypes &var2) {
    return std::min(var1.index(), var2.index());
}


// With casing priority in witch dat::String has the highes priority and dat::Boolean the lowest,
// the application of the correct operator is almost every time inferred correctly. Only exception
// being dat::String * dat::Integer and vic versa.

dat::VariantTypes operator+(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) + variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            return std::get<dat::Integer>(left) + variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            return std::get<dat::Decimal>(left) + variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) + variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator+");
    }
}

dat::VariantTypes operator-(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) - variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            return std::get<dat::Integer>(left) - variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            return std::get<dat::Decimal>(left) - variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) * variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator-");
    }
}

dat::VariantTypes operator*(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) * variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            std::cerr << std::get<dat::Integer>(left) << " " << std::get<dat::Integer>(right) << "\n";
            return std::get<dat::Integer>(left) * variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            return std::get<dat::Decimal>(left) * variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            if (min_prio(right, left) == 1) {
                // Other operant is a dat::Integer
                if (left.index() == 1) {
                    /* === String * Integer === */
                    return std::get<dat::String>(left) * variant_cast<dat::Integer>(right);
                } else {
                    /* === Integer * String === */
                    return std::get<dat::Integer>(left) * variant_cast<dat::String>(right);
                }
            } else {
                return std::get<dat::String>(left) * variant_cast<dat::String>(right);
            }
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator*");
    }
}

dat::VariantTypes operator/(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) / variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Integer>(left) / variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Decimal>(left) / variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) / variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator/");
    }
}

dat::VariantTypes operator+(const dat::VariantTypes &variant) {
    auto left_type = variant.index();

    switch (left_type) {
        case 0: /* === Boolean === */ {
            return +std::get<dat::Boolean>(variant);
        }
        case 1: /* === Integer === */ {
            return +std::get<dat::Integer>(variant);
        }
        case 2: /* === Decimal === */ {
            return +std::get<dat::Decimal>(variant);
        }
        case 3: /* === String === */{
            return +std::get<dat::String>(variant);
        }
        default:
            throw std::runtime_error("Unexpected type in unary operator+");
    }
}

dat::VariantTypes operator-(const dat::VariantTypes &variant) {
    auto left_type = variant.index();

    switch (left_type) {
        case 0: /* === Boolean === */ {
            return -std::get<dat::Boolean>(variant);
        }
        case 1: /* === Integer === */ {
            return -std::get<dat::Integer>(variant);
        }
        case 2: /* === Decimal === */ {
            return -std::get<dat::Decimal>(variant);
        }
        case 3: /* === String === */{
            return -std::get<dat::String>(variant);
        }
        default:
            throw std::runtime_error("Unexpected type in unary operator-");
    }
}

dat::VariantTypes operator!(const dat::VariantTypes &variant) {
    auto left_type = variant.index();

    switch (left_type) {
        case 0: /* === Boolean === */ {
            return !std::get<dat::Boolean>(variant);
        }
        case 1: /* === Integer === */ {
            return !std::get<dat::Integer>(variant);
        }
        case 2: /* === Decimal === */ {
            return !std::get<dat::Decimal>(variant);
        }
        case 3: /* === String === */{
            return !std::get<dat::String>(variant);
        }
        default:
            throw std::runtime_error("Unexpected type in unary operator!");
    }
}

dat::Boolean operator<(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) < variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Integer>(left) < variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Decimal>(left) < variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) < variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator<");
    }
}

dat::Boolean operator>(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) > variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Integer>(left) > variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Decimal>(left) > variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) > variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator>");
    }
}

dat::Boolean operator<=(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) <= variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Integer>(left) <= variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Decimal>(left) <= variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) <= variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator<=");
    }
}

dat::Boolean operator>=(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) >= variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Integer>(left) >= variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Decimal>(left) >= variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) >= variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator>=");
    }
}

dat::Boolean operator==(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) == variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Integer>(left) == variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Decimal>(left) == variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) == variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator==");
    }
}

dat::Boolean operator!=(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) != variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Integer>(left) != variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            if (min_prio(right, left) == 0) {
                // One operant is a boolean
                //TODO RIGHT ERROR MESSAGE
                throw err::InvalidSyntaxError{variant_position<1>(right), variant_position<2>(left), "TODO"};
            }
            return std::get<dat::Decimal>(left) != variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) != variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator!=");
    }
}

dat::Boolean operator&&(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) && variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            return std::get<dat::Integer>(left) && variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            return std::get<dat::Decimal>(left) && variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) && variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator&&");
    }
}

dat::Boolean operator||(const dat::VariantTypes &right, const dat::VariantTypes &left) {
    switch (max_prio(right, left)) {
        case 0: /* === Boolean === */ {
            return std::get<dat::Boolean>(left) || variant_cast<dat::Boolean>(right);
        }
        case 1: /* === Integer === */ {
            return std::get<dat::Integer>(left) || variant_cast<dat::Integer>(right);
        }
        case 2: /* === Decimal === */ {
            return std::get<dat::Decimal>(left) || variant_cast<dat::Decimal>(right);
        }
        case 3: /* === String === */{
            return std::get<dat::String>(left) || variant_cast<dat::String>(right);
        }
        default:
            throw std::runtime_error("Unexpected type of right in operator||");
    }
}


