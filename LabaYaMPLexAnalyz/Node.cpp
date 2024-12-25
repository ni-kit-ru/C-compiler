#pragma once
#include <string>
#include <vector>

class Node {
private:
	std::string lexem;
	std::vector<Node> children;
	std::string prefix;

public:
	Node(std::string lex) {
		lexem = lex;
	}

	Node() = default;

	void addNode(std::string lexeme) {
		Node newNode(lexeme);
		children.push_back(newNode);
		return;
	}

	Node& getNode(int iter) {
		return children[iter];
	}

	void changeLexem(std::string lexeme) {
		lexem = lexeme;
		return;
	}
	std::string& getPrefix() {
		return prefix;
	}
	void calculatePrefix() {
		prefix = lexem;
		for (auto child : children) {
			prefix += " " + getPrefix();

		}
	}
};