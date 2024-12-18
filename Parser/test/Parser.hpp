#ifndef B_SHARP_PARSERNEW_HPP
#define B_SHARP_PARSERNEW_HPP

#include <string>
#include <memory>
#include <optional>
#include "../../Lexer/Token.hpp"
#include "Program.hpp"
#include "Expression.hpp"

class Parser {

private:
    std::vector<lex::Token> m_tokens;
    lex::Token* p_curr_tok{};
    uint64_t m_tok_index;

    lex::Token advance();

    std::shared_ptr<Statement> parse_statement();
    std::shared_ptr<Expression> parse_expression();

    std::shared_ptr<Expression> parse_assignment_expression();

    std::shared_ptr<Expression> parse_comparison_expression();
    std::shared_ptr<Expression> parse_arithmetic_expression();
    std::shared_ptr<Expression> parse_term();
    std::shared_ptr<Expression> parse_factor();

public:
    Parser() = delete;
     explicit Parser(const std::string&);

    Program parse_all();

};


#endif //B_SHARP_PARSER_HPP
