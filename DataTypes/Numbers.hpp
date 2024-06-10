//
// Created by bjarne on 06.06.2024.
//

#ifndef B_SHARP_NUMBERS_HPP
#define B_SHARP_NUMBERS_HPP

#include <string>
#include <cstdint>
#include <array>



typedef uint64_t uint64 ;
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
        bool m_is_positive;

        static uint64 string_to_number(const std::string&);

        void clap_to_size();

        Number(Size, bool);

    };

    class Integer : public Number {

        friend class NumberPrinter;

        bool c_IS_SIGNED;

    public:
//        Integer(Size, bool);

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

        friend class NumberPrinter;

        unsigned char c_SCALING_FACTOR;

        static std::array<std::string,2> slip(std::string&);

        static uint64 pow_base_10(int);

    public:

        Decimal(std::string, Size, unsigned char);

    };

}
#endif //B_SHARP_NUMBERS_HPP
