//
// Created by bjarn on 18.06.2024.
//

#ifndef B_SHARP_ERROR_HPP
#define B_SHARP_ERROR_HPP

#include <string>

#include "../Lexer/Lexer.hpp"
#include "../Lexer/Position.hpp"


namespace err {

    class Error : std::exception {

        // Important information about the error: name, message and location.
        std::string m_name, m_message;
        lex::Position m_start_pos, m_end_pos;

        void underline_with_arrows() const;

    protected:

        Error(std::string, lex::Position , lex::Position , std::string);

    public:

        Error() = delete;

        void print();

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
    public:
        RuntimeError() = delete;
        explicit RuntimeError(const lex::Position& , const lex::Position&, std::string );
    };

} // err

#endif //B_SHARP_ERROR_HPP
