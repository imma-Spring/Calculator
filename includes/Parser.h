#pragma once
#include <vector>
#include "Token.h"
#include "BinaryOpNode.h"
#include "NumberNode.h"

class Parser
{
public:
	Parser(const std::vector<Token> &tokens) : m_tokens(tokens), current_token(0) {}

	std::unique_ptr<ASTNode> parseExpression();

private:
	std::unique_ptr<ASTNode> parseTerm();
	std::unique_ptr<ASTNode> parseFactor();
	std::unique_ptr<ASTNode> parsePrimary();

	std::vector<Token> m_tokens;
	size_t current_token;
};

