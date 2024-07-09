#ifndef B_SHARP_LEXER_HPP
#define B_SHARP_LEXER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <array>

#include "Token.hpp"
#include "../DataTypes/Numbers.hpp"
#include "Position.hpp"

namespace lex {
    class Token;

    struct Constants {
        std::vector<std::string> c_KEYWORDS;
        constexpr void generate_number_keywords(){
            for (auto& size : num::sizes) {
                const char byte_to_bits{static_cast<char>(size * 8)};
                const std::string size_string = std::to_string(byte_to_bits);
                c_KEYWORDS.push_back("int" + size_string);
                c_KEYWORDS.push_back("uint" + size_string);
                std::string dec_base = "dec" + size_string + ':';
                for (int scale_factor{0}; scale_factor <= byte_to_bits; ++scale_factor) {
                    c_KEYWORDS.push_back(dec_base + std::to_string(scale_factor));
                }
            }
        }

        constexpr Constants() {
            generate_number_keywords();
        }
    };

    const Constants CONSTANTS{};

    /**
     * The lexer turns a text into a sequenz of tokens for the parser to process.
     */
    class Lexer {

        std::string m_text;
        Position m_pos;
        char m_current_char;

        [[nodiscard]] bool is_digit() const;
        [[nodiscard]] bool is_letter() const;

        [[nodiscard]] Token make_number_token();
        [[nodiscard]] Token make_word_token();

    public:

        explicit Lexer(const std::string&);

        void advance();

        std::vector<Token> make_token();

    };

} // lex

#endif //B_SHARP_LEXER_HPP
