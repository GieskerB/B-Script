
#ifndef B_SHARP_DATATYPE_HPP
#define B_SHARP_DATATYPE_HPP

#include <variant>
#include "../Interpreter/Context.hpp"
#include "../Lexer/Position.hpp"

namespace itp {
    class Context;
}

namespace dat {

    class Boolean;
    class Integer;
    class Decimal;
    class String;


    class DataType {

    protected:

        lex::Position m_position_start, m_position_end;
        itp::Context *p_context;

        DataType(const lex::Position &, const lex::Position &, itp::Context *);

    public:

        DataType() = delete;

        void set_position(const lex::Position &, const lex::Position &);
        void set_context(itp::Context &);

        template<typename A, typename B>
        friend auto operator+ (const std::shared_ptr<A>&, const std::shared_ptr<B>&);
        template<typename A, typename B>
        friend auto operator- (const std::shared_ptr<A>&, const std::shared_ptr<B>&);
        template<typename A, typename B>
        friend auto operator* (const std::shared_ptr<A>&, const std::shared_ptr<B>&);
        template<typename A, typename B>
        friend auto operator/ (const std::shared_ptr<A>&, const std::shared_ptr<B>&);

        virtual std::shared_ptr<DataType> operator+(const DataType&) = 0;
        virtual std::shared_ptr<DataType> operator-(const DataType&) = 0;
        virtual std::shared_ptr<DataType> operator*(const DataType&) = 0;
        virtual std::shared_ptr<DataType> operator/(const DataType&) = 0;

        virtual void print(std::ostream& os) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const DataType& dt) {
            dt.print(os);
            return os;
        }

    };

    template<typename A, typename B>
    auto operator+(const std::shared_ptr<A> &a, const std::shared_ptr<B> &b) {
        return std::shared_ptr<DataType>(*a + *b);
    }
    template<typename A, typename B>
    auto operator-(const std::shared_ptr<A> &a, const std::shared_ptr<B> &b) {
        return std::shared_ptr<DataType>(*a - *b);
    }
    template<typename A, typename B>
    auto operator*(const std::shared_ptr<A> &a, const std::shared_ptr<B> &b) {
        return std::shared_ptr<DataType>(*a * *b);
    }
    template<typename A, typename B>
    auto operator/(const std::shared_ptr<A> &a, const std::shared_ptr<B> &b) {
        return std::shared_ptr<DataType>(*a / *b);
    }


} // dat

#endif //B_SHARP_DATATYPE_HPP
