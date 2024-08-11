#ifndef B_SHARP_NUMBER_HPP
#define B_SHARP_NUMBER_HPP

#include <array>
#include "DataType.hpp"

typedef uint64_t uint64;
typedef __uint128_t uint128;

namespace itp {
    class Context;
}

namespace dat {

    template<unsigned char N>
    struct Constants {
        unsigned char INFORMATION_LIMIT_PER_NUMBER_OF_BITS[N];
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
    static constexpr std::array<Size, 4> sizes = {Size::BYTE, Size::SHORT, Size::INTEGER, Size::LONG};

    class Number : public DataType {

        friend class Integer;
        friend class Decimal;

    protected:

        Size c_SIZE;
        uint64 m_storage;
        bool m_is_positive;

        void clap_to_size();

        static bool check_overflow(const std::string &, unsigned char);

        Number(Size, bool);

    public:

        Number() = delete;
        Number(const Number &) = delete;
        Number(const Number &&) noexcept;

        void invert();
        [[nodiscard]] bool is_zero() const;
    };

} // dat

#endif //B_SHARP_NUMBER_HPP
