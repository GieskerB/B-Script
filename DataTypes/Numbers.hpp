#ifndef B_SHARP_NUMBERS_HPP
#define B_SHARP_NUMBERS_HPP

#include <string>
#include <cstdint>
#include <cmath>
#include <vector>
#include <ranges>


#include "DataTypes.hpp"
#include "../Lexer/Position.hpp"
#include "../Interpreter/Context.hpp"


typedef uint64_t uint64;
typedef __uint128_t uint128;

namespace itp {
    class Context;
}

namespace num {

    std::string number_to_string(uint64, bool);

    uint64 string_to_number(const std::string &, unsigned char);

    template<unsigned char N>
    struct Constants {
        unsigned char INFORMATION_LIMIT_PER_NUMBER_OF_BITS[N];
        uint64 MAX_NUMBER_LIMIT[N]{0};
        std::string MAX_NUMBER_LIMIT_STRING[N];

        Constants();
    };

    const Constants<65> CONSTANTS{};

    enum NumberType {
        INT,
        DEC
    };

    enum Size {
        BYTE = 1,
        SHORT = 2,
        INTEGER = 4,
        LONG = 8
    };

    static constexpr std::array<Size, 4> sizes = {Size::BYTE, Size::SHORT, Size::INTEGER, Size::LONG};

    class Number : public dat::DataType {

        friend class NumberPrinter;

    protected:

        Size c_SIZE;
        uint64 m_storage;
        bool m_is_positive;

        virtual void clap_to_size();

        static bool check_overflow(const std::string &, unsigned char);

        Number(Size, bool, const NumberType &);
        Number(const Number &, const NumberType &);

    public:

        NumberType c_NUMBER_TYPE;

        static std::shared_ptr<Number> create_form_key(const std::string &, short);

        void invert();
        [[nodiscard]] bool is_zero() const;
    };

    class Decimal;

    class Integer : public Number {

        friend class NumberPrinter;
        friend class Decimal;

        bool c_IS_SIGNED;

        void fit_string(std::string &);

        Integer();
        Integer(const Decimal &);

    public:

        Integer(const Integer &) = default;
        Integer(std::string, Size = INTEGER, bool = false);

        Integer &operator=(const Integer &);

        friend Integer operator+(const Integer &, const Integer &);
        friend Integer operator+=(Integer &, const Integer &);

        friend Integer operator-(const Integer &, const Integer &);
        friend Integer operator-=(Integer &, const Integer &);

        friend Integer operator*(const Integer &, const Integer &);
        friend Integer operator*=(Integer &, const Integer &);

        friend Integer operator/(const Integer &, const Integer &);
        friend Integer operator/=(Integer &, const Integer &);

        friend Decimal operator+(const Integer &, const Decimal &);
        friend Decimal operator+(Decimal, const Integer &);
        friend Integer operator+=(Integer &, const Decimal &);
        friend Decimal operator+=(Decimal &, const Integer &);

        friend Decimal operator-(const Integer &, const Decimal &);
        friend Decimal operator-(Decimal, const Integer &);
        friend Integer operator-=(Integer &, const Decimal &);
        friend Decimal operator-=(Decimal &, const Integer &);

        friend Decimal operator*(const Integer &, const Decimal &);
        friend Decimal operator*(Decimal, const Integer &);
        friend Integer operator*=(Integer &, const Decimal &);
        friend Decimal operator*=(Decimal &, const Integer &);

        friend Decimal operator/(const Integer &, const Decimal &);
        friend Decimal operator/(Decimal, const Integer &);
        friend Integer operator/=(Integer &, const Decimal &);
        friend Decimal operator/=(Decimal &, const Integer &);
    };


    class Decimal : public Number {

        friend class NumberPrinter;
        friend class Integer;

        unsigned char c_SCALING_FACTOR;

        static std::pair<std::string, std::string> slip(const std::string &);
        void fit_string(std::pair<std::string, std::string> &);

        Decimal();
        Decimal(const Integer &, unsigned scaling_factor);

    public:

        Decimal(const Decimal &) = default;
        Decimal(std::string, Size = INTEGER, unsigned char = 16);


        friend Decimal operator+(const Decimal &, const Decimal &);
        friend Decimal operator+=(Decimal &, const Decimal &);

        friend Decimal operator-(const Decimal &, const Decimal &);
        friend Decimal operator-=(Decimal &, const Decimal &);

        friend Decimal operator*(const Decimal &, const Decimal &);
        friend Decimal operator*=(Decimal &, const Decimal &);

        friend Decimal operator/(const Decimal &, const Decimal &);
        friend Decimal operator/=(Decimal &, const Decimal &);

        friend Decimal operator+(const Integer &, const Decimal &);
        friend Decimal operator+(Decimal, const Integer &);
        friend Integer operator+=(Integer &, const Decimal &);
        friend Decimal operator+=(Decimal &, const Integer &);

        friend Decimal operator-(const Integer &, const Decimal &);
        friend Decimal operator-(Decimal, const Integer &);
        friend Integer operator-=(Integer &, const Decimal &);
        friend Decimal operator-=(Decimal &, const Integer &);

        friend Decimal operator*(const Integer &, const Decimal &);
        friend Decimal operator*(Decimal, const Integer &);
        friend Integer operator*=(Integer &, const Decimal &);
        friend Decimal operator*=(Decimal &, const Integer &);

        friend Decimal operator/(const Integer &, const Decimal &);
        friend Decimal operator/(Decimal, const Integer &);
        friend Integer operator/=(Integer &, const Decimal &);
        friend Decimal operator/=(Decimal &, const Integer &);
    };

}
#endif //B_SHARP_NUMBERS_HPP
