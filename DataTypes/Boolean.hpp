//
// Created by bjarn on 23.07.2024.
//

#ifndef B_SHARP_BOOLEAN_HPP
#define B_SHARP_BOOLEAN_HPP

#include "DataType.hpp"

namespace dat {

    class Boolean : public DataType {

        bool m_storage;

    public:

        Boolean() = delete;
        Boolean(bool);

        void print(std::ostream& os) const override;

        std::shared_ptr<DataType> operator+(const DataType&) override;
        std::shared_ptr<DataType> operator-(const DataType&) override;
        std::shared_ptr<DataType> operator*(const DataType&) override;
        std::shared_ptr<DataType> operator/(const DataType&) override;
    };

} // dat

#endif //B_SHARP_BOOLEAN_HPP
