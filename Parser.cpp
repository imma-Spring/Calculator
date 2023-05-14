#include "includes/Parser.h"
#include <iostream>

std::unique_ptr<ASTNode> Parser::parsePrimary() {
    Token token = m_tokens[current_token++];

    if (token.type == TokenType::NUMBER) {
        try {
            double value = (token.lexeme[0] == '-' ? -1 * std::stod(token.lexeme.substr(1)) : std::stod(token.lexeme));
            return std::make_unique<NumberNode>(value);
        }
        catch (const std::exception& e) {
            std::cout << "Error: Invalid number format" << std::endl;
            return nullptr;
        }
    }
    else if (token.type == TokenType::LPAREN) {
        auto expression = parseExpression();
        if (expression == nullptr) {
            // Error occurred while parsing the nested expression
            return nullptr;
        }

        if (current_token < m_tokens.size() && m_tokens[current_token].type == TokenType::RPAREN) {
            ++current_token;
            return expression;
        }
        else {
            std::cout << "Error: Missing closing parenthesis" << std::endl;
            return nullptr;
        }
    }
    else {
        std::cout << "Error: Invalid factor" << std::endl;
        return nullptr;
    }
}

std::unique_ptr<ASTNode> Parser::parseTerm() {
    auto result = parsePrimary();

    while (current_token < m_tokens.size()) {
        Token token = m_tokens[current_token];
        if (token.type == TokenType::MULTIPLY || token.type == TokenType::DIVIDE || token.type == TokenType::POWER) {
            ++current_token;
            auto factor = parsePrimary();
            if (factor == nullptr) {
                // Error occurred while parsing the factor
                return nullptr;
            }
            result = std::make_unique<BinaryOpNode>(token.type, std::move(result), std::move(factor));
        }
        else {
            break;
        }
    }

    return result;
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto result = parseTerm();

    while (current_token < m_tokens.size()) {
        Token token = m_tokens[current_token];
        if (token.type == TokenType::PLUS || token.type == TokenType::MINUS) {
            ++current_token;
            auto term = parseTerm();
            if (term == nullptr) {
                // Error occurred while parsing the term
                return nullptr;
            }
            result = std::make_unique<BinaryOpNode>(token.type, std::move(result), std::move(term));
        }
        else {
            break;
        }
    }

    return result;
}

