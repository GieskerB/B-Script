#include <sstream>
#include <vector>
#include <ranges>
#include <cmath>

#include "Number.hpp"
#include "Utility.hpp"

namespace dat {



    /*
     * To further make sure a number does not get too big when initialized, just compare it to the biggest number
     * possible with a given number of bits.
     */
    bool Number::check_overflow(const std::string &string, unsigned char bit_size) {
        const std::string COMPARE = CONSTANTS.MAX_NUMBER_LIMIT_STRING[bit_size];

        if (string.size() < COMPARE.size()) {
            return true;
        }
        for (int i = 0; i < COMPARE.size(); ++i) {
            if (string[i] > COMPARE[i]) {
                return false;
            } else if (string[i] < COMPARE[i]) {
                return true;
            }

        }
        // If lex_all equals it's okay and right_node on the limit.
        return true;
    }

    /*
     * A struct to store some global constants
     */
    template<unsigned char N>
    Constants<N>::Constants() : INFORMATION_LIMIT_PER_NUMBER_OF_BITS{0} {
        uint64 temp_value = 1ULL;
        for (unsigned char i = 0; i != N; ++i) {
            INFORMATION_LIMIT_PER_NUMBER_OF_BITS[i] = std::ceil(i / std::log2f(10.f));
            if (i == 0) {
                MAX_NUMBER_LIMIT[i] = 0;
            } else {
                MAX_NUMBER_LIMIT[i] = temp_value;
                temp_value <<= 1;
                temp_value |= 1;
            }
            MAX_NUMBER_LIMIT_STRING[i] = number_to_string(MAX_NUMBER_LIMIT[i], true);
        }
    }

    /*
     * to make sure a number does not get too big. Just "throw away" to larger bits.
     */
    void Number::clap_to_size() {
        switch (c_SIZE) {
            case BYTE:
                m_storage &= 0xFF;
                break;
            case SHORT:
                m_storage &= 0xFFFF;
                break;
            case INTEGER:
                m_storage &= 0xFFFFFFFF;
                break;
            case LONG:
                m_storage &= 0xFFFFFFFFFFFFFFFF;
                break;
        }

    }

    /*
     * Initialization of lex_all base values.
     */
    Number::Number(Size size, bool is_positive) : DataType(lex::Position::NULL_POSITION,
                                                           lex::Position::NULL_POSITION,
                                                           nullptr),
                                                  c_SIZE(size), m_storage(0),
                                                  m_is_positive(is_positive) {}

    Number::Number(const dat::Number &&other) noexcept: DataType(std::move(other)), c_SIZE(other.c_SIZE),
                                                        m_storage(other.m_storage),
                                                        m_is_positive(other.m_is_positive) {}


    void Number::invert() {
        m_is_positive = !m_is_positive;
    }

    bool Number::is_zero() const {
        return m_storage == 0;
    }

} // dat