#include "Parser.hpp"
#include "../../Error/Error.hpp"
#include "Expression.hpp"

Parser::Parser(const std::string &source_code) : /*m_tokens(lex::Lexer{source_code}.lex_all()),*/ m_token_index(0) {
    lex::Lexer lexer{source_code};
    this->m_tokens = lexer.lex_all();
}

lex::Token Parser::advance() {
    ++m_token_index;
    if (m_token_index < m_tokens.size()) {
        m_current_token = m_tokens[m_token_index];
    }
    return m_current_token;
}

std::shared_ptr<Statement> Parser::parse_statement() {
    return parse_expression();
}

std::shared_ptr<Expression> Parser::parse_expression() {
    auto left = parse_comparison_expression();
    while (m_current_token.c_type == lex::TokenType::LOGIC_AND || m_current_token.c_type == lex::TokenType::LOGIC_OR) {
        lex::Token op_token = m_current_token;
        advance();
        auto right = parse_comparison_expression();
        left = std::make_shared<BinaryExpression>(left, op_token, right);
    }
    return left;
}

std::shared_ptr<Expression> Parser::parse_assignment_expression() {
    return nullptr;
}

std::shared_ptr<Expression> Parser::parse_comparison_expression() {
    if (m_current_token.c_type == lex::TokenType::LOGIC_NOT) {
        lex::Token operator_token = m_current_token;
        advance();
        auto right = parse_comparison_expression();
        return std::make_shared<UnaryExpression>(operator_token, right);
    } else {
        auto left = parse_arithmetic_expression();
        while (m_current_token.c_type == lex::TokenType::DOUBLE_EQUALS ||
               m_current_token.c_type == lex::TokenType::NOT_EQUALS ||
               m_current_token.c_type == lex::TokenType::LESS_THEN ||
               m_current_token.c_type == lex::TokenType::LESS_THEN_OR_EQUALS ||
               m_current_token.c_type == lex::TokenType::GREATER_THEN ||
               m_current_token.c_type == lex::TokenType::GREATER_THEN_OR_EQUALS) {
            lex::Token op_token = m_current_token;
            advance();
            auto right = parse_arithmetic_expression();
            left = std::make_shared<BinaryExpression>(left, op_token, right);
        }
        return left;
    }
}

std::shared_ptr<Expression> Parser::parse_arithmetic_expression() {
    auto left = parse_term();
    while (m_current_token.c_type == lex::TokenType::PLUS || m_current_token.c_type == lex::TokenType::MINUS) {
        lex::Token op_token = m_current_token;
        advance();
        auto right = parse_term();
        left = std::make_shared<BinaryExpression>(left, op_token, right);
    }
    return left;
}

std::shared_ptr<Expression> Parser::parse_term() {
    auto left = parse_factor();
    while (m_current_token.c_type == lex::TokenType::MULTIPLY || m_current_token.c_type == lex::TokenType::DIVIDE) {
        lex::Token op_token = m_current_token;
        advance();
        auto right = parse_factor();
        left = std::make_shared<BinaryExpression>(left, op_token, right);
    }
    return left;
}

std::shared_ptr<Expression> Parser::parse_factor() {
    if (m_current_token.c_type == lex::TokenType::PLUS or m_current_token.c_type == lex::TokenType::MINUS) {
        lex::Token operator_token = m_current_token;
        advance();
        auto right = parse_expression();
        return std::make_shared<UnaryExpression>(operator_token, right);
    } else if (m_current_token.c_type == lex::TokenType::VALUE) {
        lex::Token temp_token = m_current_token;
        advance();
        return std::make_shared<Literal>(temp_token.c_value);
    } else if (m_current_token.c_type == lex::TokenType::IDENTIFIER) {
        lex::Token temp_token = m_current_token;
        advance();
        return std::make_shared<Identifier>(temp_token);
    } else if (m_current_token.c_type == lex::TokenType::LEFT_ROUND_PARENTHESES) {
        advance();
        auto expr = parse_expression();
        if (m_current_token.c_type == lex::TokenType::RIGHT_ROUND_PARENTHESES) {
            advance();
            return expr;
        } else {
            throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                          "Expected ')' here.");
        }
    }
    throw err::InvalidSyntaxError(m_current_token.c_start_pos, m_current_token.c_end_pos,
                                  "Primary Expression expected here.");
}

Program Parser::parse_all() {
    Program program{};

    while (m_token_index < m_tokens.size()) {
        program.add_statement(parse_statement());
    }
    return program;
}
