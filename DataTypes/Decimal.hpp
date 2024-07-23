//
// Created by bjarn on 23.07.2024.
//

#ifndef B_SHARP_DECIMAL_HPP
#define B_SHARP_DECIMAL_HPP

#include <string>

#include "Number.hpp"
#include "Integer.hpp"


namespace dat {

    class Integer;

    class Decimal : public Number {

        friend class Printer;
        friend class Integer;

        unsigned char c_SCALING_FACTOR;

        static std::pair<std::string, std::string> slip(const std::string &);

        void fit_string(std::pair<std::string, std::string> &);

        Decimal();

        Decimal(const Integer &, unsigned scaling_factor);

    public:

        Decimal(const Decimal &) = default;

        Decimal(std::string, Size = INTEGER, unsigned char = 16);

        void print(std::ostream& os) const override;

        std::shared_ptr<DataType> operator+(const DataType&) override;
        std::shared_ptr<DataType> operator-(const DataType&) override;
        std::shared_ptr<DataType> operator*(const DataType&) override;
        std::shared_ptr<DataType> operator/(const DataType&) override;
    };
} // dat

#endif //B_SHARP_DECIMAL_HPP
