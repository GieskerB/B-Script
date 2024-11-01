#include "Parser.hpp"
#include "../../Error/Error.hpp"
#include "Expression.hpp"

Parser::Parser(const std::string &source_code) : m_tok_index(-1) {
    lex::Lexer lexer{source_code};
    this->m_tokens = lexer.lex_all();
    advance();
}

lex::Token Parser::advance() {
    ++m_tok_index;
    if (m_tok_index < m_tokens.size()) {
        p_curr_tok = &m_tokens[m_tok_index];
    }
    return *p_curr_tok;
}

std::shared_ptr<Statement> Parser::parse_statement() {
    return parse_expression();
}

std::shared_ptr<Expression> Parser::parse_expression() {
    auto left = parse_comparison_expression();
    while (p_curr_tok->c_type == lex::TokenType::LOGIC_AND || p_curr_tok->c_type == lex::TokenType::LOGIC_OR) {
        lex::Token& op_token = *p_curr_tok;
        advance();
        auto right = parse_comparison_expression();
        left = std::make_shared<BinaryExpression>(left, op_token, right);
    }
    advance();
    return left;
}

std::shared_ptr<Expression> Parser::parse_assignment_expression() {
    return nullptr;
}

std::shared_ptr<Expression> Parser::parse_comparison_expression() {
    if (p_curr_tok->c_type == lex::TokenType::LOGIC_NOT) {
        lex::Token& operator_token = *p_curr_tok;
        advance();
        auto right = parse_comparison_expression();
        return std::make_shared<UnaryExpression>(operator_token, right);
    } else {
        auto left = parse_arithmetic_expression();
        while (p_curr_tok->c_type == lex::TokenType::DOUBLE_EQUALS ||
               p_curr_tok->c_type == lex::TokenType::NOT_EQUALS ||
               p_curr_tok->c_type == lex::TokenType::LESS_THEN ||
               p_curr_tok->c_type == lex::TokenType::LESS_THEN_OR_EQUALS ||
               p_curr_tok->c_type == lex::TokenType::GREATER_THEN ||
               p_curr_tok->c_type == lex::TokenType::GREATER_THEN_OR_EQUALS) {
            lex::Token& op_token = *p_curr_tok;
            advance();
            auto right = parse_arithmetic_expression();
            left = std::make_shared<BinaryExpression>(left, op_token, right);
        }
        advance();
        return left;
    }
}

std::shared_ptr<Expression> Parser::parse_arithmetic_expression() {
    auto left = parse_term();
    while (p_curr_tok->c_type == lex::TokenType::PLUS || p_curr_tok->c_type == lex::TokenType::MINUS) {
        lex::Token& op_token = *p_curr_tok;
        advance();
        auto right = parse_term();
        left = std::make_shared<BinaryExpression>(left, op_token, right);
    }
    advance();
    return left;
}

std::shared_ptr<Expression> Parser::parse_term() {
    auto left = parse_factor();
    while (p_curr_tok->c_type == lex::TokenType::MULTIPLY || p_curr_tok->c_type == lex::TokenType::DIVIDE) {
        lex::Token& op_token = *p_curr_tok;
        advance();
        auto right = parse_factor();
        left = std::make_shared<BinaryExpression>(left, op_token, right);
    }
    advance();
    return left;
}

std::shared_ptr<Expression> Parser::parse_factor() {
    if (p_curr_tok->c_type == lex::TokenType::PLUS or p_curr_tok->c_type == lex::TokenType::MINUS) {
        lex::Token& op_token = *p_curr_tok;
        advance();
        auto right = parse_expression();
        return std::make_shared<UnaryExpression>(op_token, right);
    } else if (p_curr_tok->c_type == lex::TokenType::VALUE) {
        lex::Token& temp_token = *p_curr_tok;
        advance();
        return std::make_shared<Literal>(temp_token.c_value);
    } else if (p_curr_tok->c_type == lex::TokenType::IDENTIFIER) {
        lex::Token& temp_token = *p_curr_tok;
        advance();
        return std::make_shared<Identifier>(temp_token);
    } else if (p_curr_tok->c_type == lex::TokenType::LEFT_ROUND_PARENTHESES) {
        advance();
        auto expr = parse_expression();
        if (p_curr_tok->c_type == lex::TokenType::RIGHT_ROUND_PARENTHESES) {
            advance();
            return expr;
        } else {
            throw err::InvalidSyntaxError(p_curr_tok->c_start_pos, p_curr_tok->c_end_pos,
                                          "Expected ')' here.");
        }
    }
    throw err::InvalidSyntaxError(p_curr_tok->c_start_pos, p_curr_tok->c_end_pos,
                                  "Primary Expression expected here.");
}

Program Parser::parse_all() {
    Program program{};

    while (m_tok_index < m_tokens.size()) {
        program.add_statement(parse_statement());
    }
    return program;
}
