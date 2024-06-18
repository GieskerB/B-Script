#ifndef B_SHARP_LEXER_HPP
#define B_SHARP_LEXER_HPP

#include <string>
#include <vector>
#include "Token.hpp"

namespace lex {

    class Lexer {

        std::string m_text;
        int m_pos;
        char m_current_char;

        [[nodiscard]] bool is_digit() const;

        [[nodiscard]] Token make_number_token();

    public:

        explicit Lexer(std::string);

        void advance();

        std::vector<Token> make_token();

    };

} // lex

#endif //B_SHARP_LEXER_HPP
