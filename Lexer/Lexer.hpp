#ifndef B_SHARP_LEXER_HPP
#define B_SHARP_LEXER_HPP

#include <string>
#include <vector>
#include <iostream>

#include "Token.hpp"
#include "Position.hpp"

namespace lex {
    class Token;

    /**
     * The lexer turns a text into a sequenz of tokens for the parser to process.
     */
    class Lexer {

        std::string m_text;
        Position m_pos;
        char m_current_char;

        [[nodiscard]] bool is_digit() const;

        [[nodiscard]] Token make_number_token();

    public:

        explicit Lexer(const std::string&);

        void advance();

        std::vector<Token> make_token();

    };

} // lex

#endif //B_SHARP_LEXER_HPP
