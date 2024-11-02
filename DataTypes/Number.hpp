#ifndef B_SHARP_NUMBER_HPP
#define B_SHARP_NUMBER_HPP

#include <array>
#include <limits>
#include "DataType.hpp"

typedef uint64_t uint64;
typedef __uint128_t uint128;

namespace itp {
    class Context;
}

namespace dat {

    struct LookUp {
        static constexpr std::array<uint8_t , 21> log_base_2_of_10_to_x{0, 4, 7, 10, 14, 17, 20, 24, 27, 30, 34, 37, 40, 44,
                                                                    47, 50, 54, 57, 60, 64};
        static constexpr std::array<uint8_t, 65> log_base_10_of_2_to_x{0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5,
                                                                    6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10,
                                                                    10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14,
                                                                    14, 15, 15, 15,
                                                                    16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19,
                                                                    19, 20};
        static constexpr std::array<std::pair<const char *, uint64>, 65> MAX_NUMBER_LIMIT{
                std::pair{"0", 0}, std::pair{"1", 1}, std::pair{"3", 3}, std::pair{"7", 7}, std::pair{"15", 15},
                std::pair{"31", 31}, std::pair{"63", 63}, std::pair{"127", 127}, std::pair{"255", 255},
                std::pair{"511", 511}, std::pair{"1023", 1023}, std::pair{"2047", 2047}, std::pair{"4095", 4095},
                std::pair{"8191", 8191}, std::pair{"16383", 16383}, std::pair{"32767", 32767},
                std::pair{"65535", 65535}, std::pair{"131071", 131071}, std::pair{"262143", 262143},
                std::pair{"524287", 524287}, std::pair{"1048575", 1048575}, std::pair{"2097151", 2097151},
                std::pair{"4194303", 4194303}, std::pair{"8388607", 8388607}, std::pair{"16777215", 16777215},
                std::pair{"33554431", 33554431}, std::pair{"67108863", 67108863}, std::pair{"134217727", 134217727},
                std::pair{"268435455", 268435455}, std::pair{"536870911", 536870911},
                std::pair{"1073741823", 1073741823}, std::pair{"2147483647", 2147483647},
                std::pair{"4294967295", 4294967295}, std::pair{"8589934591", 8589934591},
                std::pair{"17179869183", 17179869183}, std::pair{"34359738367", 34359738367},
                std::pair{"68719476735", 68719476735}, std::pair{"137438953471", 137438953471},
                std::pair{"274877906943", 274877906943}, std::pair{"549755813887", 549755813887},
                std::pair{"1099511627775", 1099511627775}, std::pair{"2199023255551", 2199023255551},
                std::pair{"4398046511103", 4398046511103}, std::pair{"8796093022207", 8796093022207},
                std::pair{"17592186044415", 17592186044415}, std::pair{"35184372088831", 35184372088831},
                std::pair{"70368744177663", 70368744177663}, std::pair{"140737488355327", 140737488355327},
                std::pair{"281474976710655", 281474976710655}, std::pair{"562949953421311", 562949953421311},
                std::pair{"1125899906842623", 1125899906842623}, std::pair{"2251799813685247", 2251799813685247},
                std::pair{"4503599627370495", 4503599627370495}, std::pair{"9007199254740991", 9007199254740991},
                std::pair{"18014398509481983", 18014398509481983}, std::pair{"36028797018963967", 36028797018963967},
                std::pair{"72057594037927935", 72057594037927935}, std::pair{"144115188075855871", 144115188075855871},
                std::pair{"288230376151711743", 288230376151711743},
                std::pair{"576460752303423487", 576460752303423487},
                std::pair{"1152921504606846975", 1152921504606846975},
                std::pair{"2305843009213693951", 2305843009213693951},
                std::pair{"4611686018427387903", 4611686018427387903},
                std::pair{"9223372036854775807", 9223372036854775807},
                std::pair{"18446744073709551615", std::numeric_limits<unsigned long long>::max()}
        };
    };

    enum Size : char {
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

        Number(Size, bool);

    public:

        Number() = delete;
//        Number(const Number &) = delete;
//        Number(const Number &&) noexcept;

        void invert();
        [[nodiscard]] bool is_zero() const;
    };

} // dat

#endif //B_SHARP_NUMBER_HPP
