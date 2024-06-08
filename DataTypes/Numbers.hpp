//
// Created by bjarn on 06.06.2024.
//

#ifndef B_SHARP_NUMBERS_HPP
#define B_SHARP_NUMBERS_HPP

#include <string>

namespace num {

    enum Size {
        BYTE = 1,
        SHORT = 2,
        INTEGER = 4,
        LONG = 8
    };

    class Number {

        friend class NumberPrinter;


    protected:

        Size c_SIZE;
        unsigned long long m_storage;

        Number(Size, bool);

    public:
        bool m_is_positive;

    };

    class Integer : public Number {

        bool c_is_signed;

        const static Integer LITERALS[11];

        void clap_to_size();

        explicit Integer(unsigned char);

    public:

        Integer(Size, bool);

        Integer(std::string, Size, bool);

        friend Integer operator+( Integer , const Integer &);
        friend Integer operator+=( Integer &, const Integer &);

        friend Integer operator-( Integer , const Integer &);
        friend Integer operator-=( Integer &, const Integer &);

        friend Integer operator*( Integer , const Integer &);
        friend Integer operator*=( Integer &, const Integer &);

        friend Integer operator/( Integer , const Integer &);
        friend Integer operator/=( Integer &, const Integer &);
    };


    class Decimal : public Number {

        unsigned char m_SCALING_FACTOR;

    };

}
#endif //B_SHARP_NUMBERS_HPP
