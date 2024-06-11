//
// Created by bjarn on 08.06.2024.
//

#include <stdexcept>
#include <iostream>
#include "Numbers.hpp"

namespace num {

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

    Number::Number(Size size, bool is_positive) : c_SIZE(size), m_storage(0), m_is_positive(is_positive) {}

}