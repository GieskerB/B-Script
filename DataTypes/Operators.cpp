#include "Numbers.hpp"

namespace num {

    Integer operator+(Integer int1, const Integer &int2) {
        return int1 += int2;
    }

    Integer operator+=(Integer &int1, const Integer &int2) {
        if (int1.m_is_positive and int2.m_is_positive) {
            int1.m_storage += int2.m_storage;
        } else if (int1.m_is_positive and !int2.m_is_positive) {
            if (int1.m_storage < int2.m_storage) {
                // Idea is: 2 - 5 = - (5 - 2)
                int1.m_is_positive = false;
                int1.m_storage = int2.m_storage - int1.m_storage;
            } else {
                int1.m_storage -= int2.m_storage;
            }
        } else if (!int1.m_is_positive and int2.m_is_positive) {
            if (int1.m_storage < int2.m_storage) {
                // Idea is: - 2 + 5 = 5 - 2
                int1.m_is_positive = true;
                int1.m_storage = int2.m_storage - int1.m_storage;
            } else {
                // Idea is: - 5 + 2 = - (5 - 2)
                int1.m_storage -= int2.m_storage;
            }
        } else { //!int1.m_is_positive and !int2.m_is_positive
            // Idea is: - 5 - 2 = - (5 + 2)
            int1.m_storage += int2.m_storage;
        }
        int1.clap_to_size();
        return int1;
    }

    Integer operator-(Integer int1, const Integer &int2) {
        return int1 -= int2;
    }

    Integer operator-=(Integer& int1, const Integer &int2) {
        Integer temp = int2;
        temp.m_is_positive  = ! temp.m_is_positive;
        return int1 += temp;
    }

    Integer operator*(Integer int1, const Integer &int2) {
        return int1 *= int2;
    }

    Integer operator*=(Integer &int1, const Integer &int2) {
        // neg times neg = pos
        int1.m_is_positive ^= ~int2.m_is_positive;

        int1.m_storage *= int2.m_storage;

        int1.clap_to_size();
        return int1;
    }

    Integer operator/(Integer int1, const Integer &int2) {
        return int1 /= int2;
    }

    Integer operator/=(Integer &int1, const Integer &int2) {
        // neg times neg = pos
        int1.m_is_positive ^= ~int2.m_is_positive;

        int1.m_storage /= int2.m_storage;

        int1.clap_to_size();
        return int1;
    }


}