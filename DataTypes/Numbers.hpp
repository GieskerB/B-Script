//
// Created by bjarn on 06.06.2024.
//

#ifndef B_SHARP_NUMBERS_HPP
#define B_SHARP_NUMBERS_HPP

#include <string>
#include <cstdint>
#include <array>



typedef int64_t uint64 ;
typedef __uint128_t uint128;

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
        uint64 m_storage;

        void clap_to_size();

        Number(Size, bool);

    public:
        bool m_is_positive;

    };

    class Integer : public Number {

        bool c_IS_SIGNED;

//        const static Integer LITERALS[11];

//        explicit Integer(unsigned char);

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

        unsigned char c_SCALING_FACTOR;

        uint128 m_extended_storage;

        static std::array<std::string,2> slip(std::string&);

    public:

        Decimal(std::string, Size, unsigned char);

    };

}
#endif //B_SHARP_NUMBERS_HPP
