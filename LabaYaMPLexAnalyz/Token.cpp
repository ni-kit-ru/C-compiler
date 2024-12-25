#include <iostream>
#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <fstream>
#include <unordered_map>
#include "Token.h"

Token::Token(std::string lexeme, std::string type) {
	this->lexeme = lexeme;
	this->type = type;
}
Token::Token() {}