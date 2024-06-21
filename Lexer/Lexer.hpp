#ifndef B_SHARP_LEXER_HPP
#define B_SHARP_LEXER_HPP

#include <string>
#include <vector>
#include "Token.hpp"

namespace lex {

    struct Position {
        int index{0}, line{0}, column{0};
        std::string file_name;

        inline void advance(char current_char) ;
    };

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
