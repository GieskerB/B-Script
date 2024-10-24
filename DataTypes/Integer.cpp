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

//    Integer::Integer(const Integer &&other) noexcept: Number(std::move(other)), c_IS_SIGNED(other.c_IS_SIGNED) {}


    Integer::Integer(std::string str_repr, Size size, bool is_signed) : Number(size,
                                                                               str_repr.empty() or str_repr[0] != '-'),
                                                                        c_IS_SIGNED(is_signed) {
        if (str_repr.empty()) {
            return;
        }

        if (!m_is_positive and str_repr.size() == 1) {
            throw std::runtime_error("Invalid number format1: '" + str_repr + "'\n");
        }

        m_storage = string_to_number(str_repr);
        uint64 bitmap = ((1ULL << (c_SIZE * 8)) - 1);
        m_storage &= bitmap;
    }

    Integer Integer::cast(const Boolean &other) {
        return Integer(other);
    }

    Integer Integer::copy(const dat::Integer &other) {
        return {other};
    }

    Integer Integer::cast(const dat::Decimal &other) {
        return Integer(other);
    }

    Integer Integer::cast(const dat::String &other) {
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