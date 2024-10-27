#ifndef B_SHARP_LEXER_HPP
#define B_SHARP_LEXER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <array>

#include "Token.hpp"
#include "../DataTypes/Boolean.hpp"
#include "../DataTypes/Number.hpp"
#include "Position.hpp"

namespace lex {
    class Token;

    enum TokenType : unsigned short;

    struct Constants {
        std::vector<std::string> VARIABLE_KEYWORDS;
        std::vector<std::string> CONSTANTS_KEYWORDS;
        std::vector<std::string> BUILD_IN_KEYWORDS;

        void generate_variable_type_keywords() {
            VARIABLE_KEYWORDS.emplace_back("int");
            VARIABLE_KEYWORDS.emplace_back("dec");
            VARIABLE_KEYWORDS.emplace_back("bool");
            VARIABLE_KEYWORDS.emplace_back("str");
            for (auto &size: dat::sizes) {
                const char byte_to_bits{static_cast<char>(size * 8)};
                const std::string size_string = std::to_string(byte_to_bits);
                VARIABLE_KEYWORDS.push_back("int" + size_string);
                VARIABLE_KEYWORDS.push_back("uint" + size_string);
                std::string dec_base = "dec" + size_string;
                VARIABLE_KEYWORDS.push_back(dec_base);
                dec_base.push_back(':');
                for (int scale_factor{0}; scale_factor <= byte_to_bits; ++scale_factor) {
                    VARIABLE_KEYWORDS.push_back(dec_base + std::to_string(scale_factor));
                }
            }
        }



        void generate_constants_keywords() {
            CONSTANTS_KEYWORDS.emplace_back(dat::Boolean::TRUE);
            CONSTANTS_KEYWORDS.emplace_back(dat::Boolean::FALSE);
            CONSTANTS_KEYWORDS.emplace_back(dat::Boolean::NEUTRAL);
        }

        void generate_build_in_keywords() {
            BUILD_IN_KEYWORDS.emplace_back("if");
        }

        Constants() {
            generate_variable_type_keywords();
            generate_constants_keywords();
            generate_build_in_keywords();
        }
    };

    const Constants CONSTANTS{};

    /**
     * The lexer turns a text into a sequence of tokens for the parser to process.
     */
    class Lexer {
        std::string m_text;
        short m_var_type_param;
        Position m_pos;
        char m_current_char;

        [[nodiscard]] bool is_digit() const;
        [[nodiscard]] bool is_letter() const;
        [[nodiscard]] bool can_lex() const;

        [[nodiscard]] Token make_number_token();
        [[nodiscard]] Token make_word_token();
        [[nodiscard]] Token make_string_token();

        Token make_two_char_token(char, char, TokenType, TokenType);

    public:
        Lexer() = delete;
        explicit Lexer(const std::string &);
        void advance();
        std::vector<Token> lex_all();

    };

} // lex

#endif //B_SHARP_LEXER_HPP
