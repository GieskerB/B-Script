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

    Integer Integer::copy(const dat::Integer &other) {
        Integer result("0");
        result.c_IS_SIGNED = other.c_IS_SIGNED;
        result.c_SIZE = other.c_SIZE;
        result.m_storage = other.m_storage;
        result.m_is_positive = other.m_is_positive;
        result.m_position_start = other.m_position_start;
        result.m_position_end = other.m_position_end;
        result.p_context = other.p_context;
        return result;
    }

    Integer Integer::cast(const dat::Boolean &other) {
        switch (other.m_storage) {
            case Boolean::TRUE:
                return Integer("1");
            case Boolean::FALSE:
                return Integer("0");
            default:
                throw err::RuntimeError(other.m_position_start, other.m_position_end,
                                        "Can not cast the boolean Value of Neutral into a number.",*other.p_context);
        }
    }

    Integer Integer::cast(const dat::Decimal &other) {
        Integer result("0");
        result.c_IS_SIGNED = false;
        result.c_SIZE = other.c_SIZE;
        result.m_storage = other.m_storage >> other.c_SCALING_FACTOR;
        result.m_is_positive = other.m_is_positive;
        result.m_position_start = other.m_position_start;
        result.m_position_end = other.m_position_end;
        result.p_context = other.p_context;
        return result;
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