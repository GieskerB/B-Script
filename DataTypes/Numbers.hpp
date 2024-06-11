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
//    constexpr std::string number_to_string(uint64, bool);
//    constexpr uint64 string_to_number(const std::string&,unsigned char);

    constexpr std::string number_to_string(uint64 number, bool is_positive) {
        std::vector<char> digits;

        if (number == 0) {
            digits.push_back('0');
        }
        while (number != 0) {
            unsigned char digit = number % 10;
            number /= 10;
            digits.push_back(static_cast<char>(digit + '0'));
        }
        if (!is_positive) {
            digits.push_back(static_cast<char>('-'));
        }

        // TODO: Use string stream here!
        std::string result{};
        for (char &digit: std::ranges::reverse_view(digits)) {
            result.push_back( digit);
        }
        return result;
    }

    constexpr uint64 string_to_number(const std::string & str_repr,unsigned char bit_length) {
        const char start = str_repr[0] == '-' ? 1 : 0;
//        std::string number_base_10 = str_repr.substr(start,CONSTANTS.MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH[bit_length]);

        if(str_repr.empty() or str_repr == "0") {
            return 0;
        }

        uint64 result{0},base{1};

        for (int i = static_cast<int>(str_repr.size() - 1); i >= start; --i) {
            char digit = str_repr[i];
            if (digit < '0' or digit > '9') {
                throw std::runtime_error("Invalid number format2: '" + str_repr + "'\n");
            }
            digit -= '0';
            if(result + digit * base < result) {
                break;
            }
            result += digit * base;
            base *= 10;
        }
        return result;
    }

    template<unsigned char N>
    struct Constants {
        unsigned char MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH[N];
        uint64 MAX_NUMBER_LIMIT[N];
        std::string MAX_NUMBER_LIMIT_STRING[N];

        Constants() : MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH() {
            uint64 temp_value = 1ULL;
            for (unsigned char i = 0; i != N; ++i) {
                MAX_BASE_10_LENGTH_FOR_BASE_2_LENGTH[i] = std::ceil(i / std::log2f(10.f));
                if(i == 0) {
                    MAX_NUMBER_LIMIT[i] = 0;
                } else {
                    MAX_NUMBER_LIMIT[i] = temp_value;
                    temp_value <<=1;
                    temp_value|= 1;
                }
                MAX_NUMBER_LIMIT_STRING[i] = std::move( number_to_string(MAX_NUMBER_LIMIT[i],true));
            }
        }
    };

    const Constants<64> CONSTANTS{};


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
