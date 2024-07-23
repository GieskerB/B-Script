#ifndef B_SHARP_INTEGER_HPP
#define B_SHARP_INTEGER_HPP

#include <string>
#include "Number.hpp"
#include "Decimal.hpp"

namespace dat {

    class Decimal;

    class Integer : public Number {

        friend class Printer;
        friend class Decimal;

        bool c_IS_SIGNED;

        void fit_string(std::string &);

        Integer();

        explicit Integer(const Decimal &);

    public:

        Integer(const Integer &);

        explicit Integer(std::string, Size = INTEGER, bool = false);

        Integer& operator=(const Integer&);

        void print(std::ostream& os) const override;

        std::shared_ptr<DataType> operator+(const DataType&) override;
        std::shared_ptr<DataType> operator-(const DataType&) override;
        std::shared_ptr<DataType> operator*(const DataType&) override;
        std::shared_ptr<DataType> operator/(const DataType&) override;

    };
} // dat

#endif
