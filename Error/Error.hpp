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

        std::string m_name, m_message;
        lex::Position m_start_pos, m_end_pos;

        /*
         * def string_with_arrows(text, pos_start, pos_end):
    result = ''

    # Calculate indices
    idx_start = max(text.rfind('\n', 0, pos_start.idx), 0)
    idx_end = text.find('\n', idx_start + 1)
    if idx_end < 0: idx_end = len(text)

    # Generate each line
    line_count = pos_end.ln - pos_start.ln + 1
    for i in range(line_count):
        # Calculate line columns
        line = text[idx_start:idx_end]
        col_start = pos_start.col if i == 0 else 0
        col_end = pos_end.col if i == line_count - 1 else len(line) - 1

        # Append to result
        result += line + '\n'
        result += ' ' * col_start + '^' * (col_end - col_start)

        # Re-calculate indices
        idx_start = idx_end
        idx_end = text.find('\n', idx_start + 1)
        if idx_end < 0: idx_end = len(text)

    return result.replace('\t', '')
         */

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

} // err

#endif //B_SHARP_ERROR_HPP
