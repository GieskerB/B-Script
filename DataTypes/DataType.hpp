#ifndef B_SHARP_DATATYPE_HPP
#define B_SHARP_DATATYPE_HPP

#include <memory>
#include "../Lexer/Position.hpp"

namespace itp {
    class Context;
}

namespace dat {

    class DataType {

    protected:

        lex::Position m_position_start, m_position_end;
        itp::Context *p_context;

        DataType(const lex::Position &, const lex::Position &, itp::Context *);

    public:

        DataType() = delete;

        void set_position(const lex::Position &, const lex::Position &);
        void set_context(itp::Context &);

        [[nodiscard]] std::pair<lex::Position, lex::Position> position() const;
        [[nodiscard]] const itp::Context& context() const;

        virtual void print(std::ostream& os) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const DataType& dt) {
            dt.print(os);
            return os;
        }

    };

} // dat

#endif //B_SHARP_DATATYPE_HPP
