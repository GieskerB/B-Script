#include "../Utility.hpp"

    template<typename T>
    static inline T variant_cast(const dat::VariantTypes &var) {
        return std::visit([](auto &&arg) -> T { return static_cast<T>(arg); }, var);
    }

    dat::VariantTypes operator+(const dat::VariantTypes &right, const dat::VariantTypes &left) {
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
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
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
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
                return std::get<dat::String>(left) - variant_cast<dat::String>(right);
            }
            default:
                throw std::runtime_error("Unexpected type of right in operator-");
        }
    }

    dat::VariantTypes operator*(const dat::VariantTypes &right, const dat::VariantTypes &left) {
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
            case 0: /* === Boolean === */ {
                return std::get<dat::Boolean>(left) * variant_cast<dat::Boolean>(right);
            }
            case 1: /* === Integer === */ {
                std::cerr <<std::get<dat::Integer>(left)<<" " << std::get<dat::Integer>(right)<< "\n";
                return std::get<dat::Integer>(left) * variant_cast<dat::Integer>(right);
            }
            case 2: /* === Decimal === */ {
                return std::get<dat::Decimal>(left) * variant_cast<dat::Decimal>(right);
            }
            case 3: /* === String === */{
                return std::get<dat::String>(left) * variant_cast<dat::String>(right);
            }
            default:
                throw std::runtime_error("Unexpected type of right in operator*");
        }
    }

    dat::VariantTypes operator/(const dat::VariantTypes &right, const dat::VariantTypes &left) {
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
            case 0: /* === Boolean === */ {
                return std::get<dat::Boolean>(left) / variant_cast<dat::Boolean>(right);
            }
            case 1: /* === Integer === */ {
                return std::get<dat::Integer>(left) / variant_cast<dat::Integer>(right);
            }
            case 2: /* === Decimal === */ {
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
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
            case 0: /* === Boolean === */ {
                return std::get<dat::Boolean>(left) < variant_cast<dat::Boolean>(right);
            }
            case 1: /* === Integer === */ {
                return std::get<dat::Integer>(left) < variant_cast<dat::Integer>(right);
            }
            case 2: /* === Decimal === */ {
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
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
            case 0: /* === Boolean === */ {
                return std::get<dat::Boolean>(left) > variant_cast<dat::Boolean>(right);
            }
            case 1: /* === Integer === */ {
                return std::get<dat::Integer>(left) > variant_cast<dat::Integer>(right);
            }
            case 2: /* === Decimal === */ {
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
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
            case 0: /* === Boolean === */ {
                return std::get<dat::Boolean>(left) <= variant_cast<dat::Boolean>(right);
            }
            case 1: /* === Integer === */ {
                return std::get<dat::Integer>(left) <= variant_cast<dat::Integer>(right);
            }
            case 2: /* === Decimal === */ {
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
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
            case 0: /* === Boolean === */ {
                return std::get<dat::Boolean>(left) >= variant_cast<dat::Boolean>(right);
            }
            case 1: /* === Integer === */ {
                return std::get<dat::Integer>(left) >= variant_cast<dat::Integer>(right);
            }
            case 2: /* === Decimal === */ {
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
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
            case 0: /* === Boolean === */ {
                return std::get<dat::Boolean>(left) == variant_cast<dat::Boolean>(right);
            }
            case 1: /* === Integer === */ {
                return std::get<dat::Integer>(left) == variant_cast<dat::Integer>(right);
            }
            case 2: /* === Decimal === */ {
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
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
            case 0: /* === Boolean === */ {
                return std::get<dat::Boolean>(left) != variant_cast<dat::Boolean>(right);
            }
            case 1: /* === Integer === */ {
                return std::get<dat::Integer>(left) != variant_cast<dat::Integer>(right);
            }
            case 2: /* === Decimal === */ {
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
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
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
        auto left_type = left.index();
        auto right_type = right.index();

        switch (left_type) {
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


