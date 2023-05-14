#include "includes/Lexer.h"

Lexer::Lexer(const std::string &input)
	: m_input(input), current_pos(0) {}

Token Lexer::getNextToken()
{
	skipWhiteSpace();

	if (current_pos >= m_input.length())
	{
		return { TokenType::EOI, "" };
	}

	char current_char = m_input[current_pos++];

	switch (current_char)
	{
	case '+':
		return { TokenType::PLUS, "+" };
	case '-':
		if (!isdigit(m_input[current_pos - 2]) && m_input[current_pos - 2] != ')')
			return extractNumber(current_char);
		return { TokenType::MINUS, "-" };
	case '*':
		if (peek('*'))
		{
			return { TokenType::POWER, "**" };
		}
		return { TokenType::MULTIPLY, "*" };
	case '/':
		return { TokenType::DIVIDE, "/" };
	case '(':
		return { TokenType::LPAREN, "(" };
	case ')':
		return { TokenType::RPAREN, ")" };
	default:
		if (isdigit(current_char))
		{
			return extractNumber(current_char);
		}
		return { TokenType::INVALID, std::string(1, current_char) };
	}
}

void Lexer::skipWhiteSpace()
{
	while (current_pos < m_input.length() && isspace(m_input[current_pos]))
	{
		++current_pos;
	}
}

Token Lexer::extractNumber(char first_digit)
{
	std::string number;
	number += first_digit;
	//if (first_digit == '-')
		//current_pos++;

	while (current_pos < m_input.length() && isdigit(m_input[current_pos]))
	{
		number += m_input[current_pos++];
	}

	return { TokenType::NUMBER, number };
}


bool Lexer::peek(char expected)
{
	if (m_input[current_pos] == expected)
	{
		current_pos++;
		return true;
	}

	return false;
}

std::ostream& operator<< (std::ostream& os, Token token)
{
	switch (token.type)
	{
	case TokenType::NUMBER:
		os << "Number ";
		break;
	case TokenType::PLUS:
		os << "Plus ";
		break;
	case TokenType::MINUS:
		os << "Minus ";
		break;
	case TokenType::MULTIPLY:
		os << "Multiply ";
		break;
	case TokenType::DIVIDE:
		os << "Divide ";
		break;
	case TokenType::POWER:
		os << "Power";
		break;
	case TokenType::LPAREN:
		os << "LParen ";
		break;
	case TokenType::RPAREN:
		os << "RParen ";
		break;
	case TokenType::INVALID:
		os << "Invalid ";
		break;
	}
	os << token.lexeme;
	return os;
}