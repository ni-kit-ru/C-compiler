#pragma once
#include <string>

struct Token {
	std::string lexeme = "";
	std::string type;
	Token(std::string lex, std::string type);
	Token();
};
