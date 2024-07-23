//
// Created by bjarn on 23.07.2024.
//

#ifndef B_SHARP_STRING_HPP
#define B_SHARP_STRING_HPP

#include "DataType.hpp"

namespace dat {

    class String : public DataType {

        static const unsigned int MAX_LENGTH;

        void print(std::ostream& os) const override;

        std::shared_ptr<DataType> operator+(const DataType&) override;
        std::shared_ptr<DataType> operator-(const DataType&) override;
        std::shared_ptr<DataType> operator*(const DataType&) override;
        std::shared_ptr<DataType> operator/(const DataType&) override;
    };

} // dat

#endif //B_SHARP_STRING_HPP
