//
// Created by bjarn on 23.07.2024.
//

#ifndef B_SHARP_STRING_HPP
#define B_SHARP_STRING_HPP

#include "DataType.hpp"

namespace dat {

    class String : public DataType {

        static const unsigned int MAX_LENGTH;

    public:

        String() = delete;
        String(const std::string&): DataType(lex::Position::NULL_POSITION, lex::Position::NULL_POSITION, nullptr){};

        void print(std::ostream& os) const override;

        std::shared_ptr<DataType> operator+(const DataType&)const  override;
        std::shared_ptr<DataType> operator-(const DataType&) const override;
        std::shared_ptr<DataType> operator*(const DataType&) const override;
        std::shared_ptr<DataType> operator/(const DataType&) const override;
    };

} // dat

#endif //B_SHARP_STRING_HPP
