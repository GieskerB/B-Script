#include <stdexcept>
#include "Numbers.hpp"
#include "NumberPrinter.hpp"

namespace num {


    void Integer::fit_string(std::string &string) {
        const int MAX_INTEGER_SIZE = CONSTANTS.INFORMATION_LIMIT_PER_NUMBER_OF_BITS[c_SIZE * 8];
        if (string.size() > MAX_INTEGER_SIZE) {
            string = std::string("9", MAX_INTEGER_SIZE);
        }
    }

    Integer::Integer() : Number(Size::LONG, true, NumberType::INT), c_IS_SIGNED(false) {}

    Integer::Integer(const num::Decimal &other) : Number(other, NumberType::INT),
                                                  c_IS_SIGNED(false) {
        m_storage = other.m_storage >> other.c_SCALING_FACTOR;
    }

    Integer::Integer(std::string str_repr, Size size, bool is_signed) : Number(size,
                                                                               str_repr.empty() or str_repr[0] != '-',
                                                                               NumberType::INT),
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

    Integer &Integer::operator=(const num::Integer &other) {
        m_storage = other.m_storage;
        m_is_positive = other.m_is_positive;
        clap_to_size();
        return *this;
    }


} // num