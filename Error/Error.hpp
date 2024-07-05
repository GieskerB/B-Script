//
// Created by bjarn on 18.06.2024.
//

#ifndef B_SHARP_ERROR_HPP
#define B_SHARP_ERROR_HPP

#include <string>

#include "../Lexer/Lexer.hpp"
#include "../Lexer/Position.hpp"
#include "../Interpreter/Context.hpp"


class Context;
namespace err {

    class Error : std::exception {

        lex::Position m_end_pos;

    protected:

        Error(std::string, lex::Position , lex::Position , std::string);

        // Important information about the error: name, message and location.
        std::string m_name;
        // Important information about the error: name, message and location.
        std::string m_message;
        lex::Position m_start_pos;

        void underline_with_arrows() const;

    public:

        Error() = delete;

        virtual void print();

    };

    class IllegalCharError : public Error {
    public:
        IllegalCharError() = delete;
        explicit IllegalCharError(const lex::Position &, std::string);

    };

    class InvalidSyntaxError : public Error {
    public:
        InvalidSyntaxError() = delete;
        explicit InvalidSyntaxError(const lex::Position &, const lex::Position &, std::string);

    };

    class RuntimeError: public Error {
         itp::Context* p_context;

        void generate_trace_back();

    public:
        RuntimeError() = delete;
        explicit RuntimeError(const lex::Position& , const lex::Position&, std::string, const itp::Context&);

        void print();
    };

} // err

#endif //B_SHARP_ERROR_HPP
