#include "Integer.hpp"
#include "Utility.hpp"
#include "../Error/Error.hpp"

namespace dat {

    Integer::Integer(const Boolean &other) : Number(Size::BYTE, true), c_IS_SIGNED(false) {
        switch (other.m_storage) {
            case Boolean::TriState::TRUE:
                m_storage = 1;
                break;
            case Boolean::TriState::FALSE:
                m_storage = 0;
                break;
            case Boolean::TriState::NEUTRAL: {
                auto pos = other.position();
                throw err::RuntimeError(pos.first, pos.second, "Can not convert m_value 'neutral' into a number",
                                        other.context());
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
        throw err::RuntimeError(other.position().first, other.position().second,
                                "Casting error form String to Integer.",
                                other.context());
    }


    Integer::Integer(std::string str_repr, Size size, bool is_signed) : Number(size,
                                                                               str_repr.empty() or str_repr[0] != '-'),
                                                                        c_IS_SIGNED(is_signed) {
        if (str_repr.empty()) {
            return;
        }

        if (!m_is_positive and str_repr.size() == 1) {
            throw std::runtime_error("Invalid number format1: '" + str_repr + "'\n");
        }
        str_repr = str_repr.substr(0, str_repr.find('.') );
        m_storage = string_to_number(str_repr);
        uint64 bitmap = c_SIZE == Size::LONG ? -1 : ((1ULL << (c_SIZE * 8)) - 1);
        m_storage &= bitmap;
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