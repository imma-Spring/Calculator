#pragma once

#include "Token.h"

#include <iostream>

class Lexer
{
public:
	Lexer(const std::string& input);

	Token getNextToken();

private:
	void skipWhiteSpace();

	Token extractNumber(char first_digit);

	bool peek(char expected);

	std::string m_input;
	size_t current_pos;
};

std::ostream& operator<< (std::ostream &os, Token token);