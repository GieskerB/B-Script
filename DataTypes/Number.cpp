#include <sstream>
#include <vector>
#include <ranges>

#include "Number.hpp"
#include "Utility.hpp"

namespace dat {

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

    Number::Number(Size size, bool is_positive) : DataType(lex::Position::NULL_POSITION,
                                                           lex::Position::NULL_POSITION,
                                                           nullptr),
                                                  c_SIZE(size), m_storage(0),
                                                  m_is_positive(is_positive) {}


    void Number::invert() {
        m_is_positive = !m_is_positive;
    }

    bool Number::is_zero() const {
        return m_storage == 0;
    }

} // dat