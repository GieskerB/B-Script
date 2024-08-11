#include "Integer.hpp"
#include "Utility.hpp"
#include "../Error/Error.hpp"

namespace dat {
    void Integer::fit_string(std::string &string) {
        const int MAX_INTEGER_SIZE = CONSTANTS.INFORMATION_LIMIT_PER_NUMBER_OF_BITS[c_SIZE * 8];
        if (string.size() > MAX_INTEGER_SIZE) {
            string = std::string("9", MAX_INTEGER_SIZE);
        }
    }

    Integer::Integer(const Boolean &other) : Number(Size::BYTE, true), c_IS_SIGNED(false) {
        switch (other.m_storage) {
            case Boolean::TRUE:
                m_storage = 1;
                break;
            case Boolean::FALSE:
                m_storage = 0;
                break;
            case Boolean::NEUTRAL: {
                auto pos = other.get_position();
                throw err::RuntimeError(pos.first, pos.second, "Can not convert value 'neutral' into a number",
                                        other.get_context());
            }
        }
    }

    Integer::Integer(const Integer &other) : Number(other.c_SIZE, other.m_is_positive), c_IS_SIGNED(other.c_IS_SIGNED) {
        m_storage = other.m_storage;
    }

    Integer::Integer(const Decimal &other) : Number(other.c_SIZE, other.m_is_positive),
                                             c_IS_SIGNED(false) {
        m_storage = other.m_storage >> other.c_SCALING_FACTOR;
    }

    Integer::Integer(const String &other) : Number(Size::LONG, false), c_IS_SIGNED(false) {
        throw err::RuntimeError(other.get_position().first, other.get_position().second,
                                "Casting error form String to Integer.",
                                other.get_context());
    }

    Integer::Integer(const Integer &&other) noexcept: Number(std::move(other)), c_IS_SIGNED(other.c_IS_SIGNED) {}


    Integer::Integer(std::string str_repr, Size size, bool is_signed) : Number(size,
                                                                               str_repr.empty() or str_repr[0] != '-'),
                                                                        c_IS_SIGNED(is_signed) {
        if (str_repr.empty()) {
            return;
        }

        if (!m_is_positive and str_repr.size() == 1) {
            throw std::runtime_error("Invalid number format1: '" + str_repr + "'\n");
        }
        fit_string(str_repr);

        if (Number::check_overflow(str_repr, c_SIZE * 8)) {
            m_storage = string_to_number(str_repr, c_SIZE * 8);
        } else {
            m_storage = CONSTANTS.MAX_NUMBER_LIMIT[c_SIZE * 8];
        }

        clap_to_size();
    }

    Integer Integer::cast(const Boolean &other) {
        return Integer(other);
    }
    Integer Integer::copy(const dat::Integer & other) {
        return Integer(other);
    }
    Integer Integer::cast(const dat::Decimal & other) {
        return Integer(other);
    }
    Integer Integer::cast(const dat::String & other) {
        return Integer(other);
    }

    Integer Integer::cast(const VariantTypes &other) {
        switch (other.index()) {
            case 0 :
                return Integer::cast(std::get<Boolean>(other));
            case 1 :
                return Integer::copy(std::get<Integer>(other));
            case 2 :
                return Integer::cast(std::get<Decimal>(other));
            case 3 :
                return Integer::cast(std::get<String>(other));
            default:
                throw std::runtime_error("Error in Integer cast: Unexpected DataType");
        }
    }


    std::string Integer::to_string() const {
        return number_to_string(m_storage, m_is_positive);
    }

    /*
     * In case of Integers simply print the number with help of the number_to_string method!
     */
    void Integer::print(std::ostream &os) const {
        os << to_string();
    }


} // dat