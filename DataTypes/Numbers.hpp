//
// Created by bjarne on 06.06.2024.
//

#ifndef B_SHARP_NUMBERS_HPP
#define B_SHARP_NUMBERS_HPP

#include <string>
#include <cstdint>
#include <array>
#include <cmath>
#include <vector>
#include <ranges>


typedef uint64_t uint64 ;
typedef __uint128_t uint128;

namespace num {

    std::string number_to_string(uint64, bool);
    uint64 string_to_number(const std::string&,unsigned char);
    bool check_overflow(const std::string&, unsigned char);

    template<unsigned char N>
    struct Constants {
        unsigned char INFORMATION_LIMIT_PER_NUMER_OF_BTIS[N];
        uint64 MAX_NUMBER_LIMIT[N]{0};
        std::string MAX_NUMBER_LIMIT_STRING[N];
        Constants();
    };

    const Constants<65> CONSTANTS{};


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

        void clap_to_size();

        Number(Size, bool);

    };

    class Integer : public Number {

        friend class NumberPrinter;

        bool c_IS_SIGNED;

        bool check_string_size(const std::string &);

    public:

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

        static std::array<std::string,2> slip(const std::string&);

        void fit_string(std::array<std::string,2> &);

    public:

        Decimal(std::string, Size, unsigned char);

    };

}
#endif //B_SHARP_NUMBERS_HPP
