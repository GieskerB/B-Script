#ifndef B_SHARP_DATATYPES_HPP
#define B_SHARP_DATATYPES_HPP

#include "../Interpreter/Context.hpp"
#include "../Lexer/Position.hpp"

namespace itp {
    class Context;
}

namespace dat {

    enum DataTypeType {
        NUMBER,
        BOOLEAN,
        CHARACTER,
        STRING
    };

    class DataType {

    protected:

        lex::Position m_position_start, m_position_end;
        itp::Context *p_context;

        DataType(const lex::Position &, const lex::Position &, itp::Context *, const DataTypeType&);

    public:

        DataType() = delete;

        DataTypeType c_DATATYPE_TYPE;

        virtual void virtual_method();

        void set_position(const lex::Position &, const lex::Position &);
        void set_context(itp::Context &);

//        [[nodiscard]] std::pair<lex::Position, lex::Position> get_position() const;
//        [[nodiscard]] itp::Context get_context() const;

    };

    class Boolean : public DataType {

        bool m_storage;

    public:

        Boolean() = delete;
        Boolean(bool);

    };

    class Character : public DataType {

        char m_storage;

    public:

        Character() = delete;
        Character(char);

    };

    class String : public DataType {

        static const unsigned int MAX_LENGTH;


    };


} // dat

#endif //B_SHARP_DATATYPES_HPP
