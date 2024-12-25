#include <iostream>
#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <fstream>
#include <unordered_map>
//#include "Token.h"
#include "Lexem.cpp"
#include "HashTable.cpp"





int main() {
    std::ifstream fin("C:/Users/cc959/source/repos/in.txt");
    std::ofstream fout("C:/Users/cc959/source/repos/out.txt");
    Lexem lexem;
    Token m("shg", "ggf");
    std::string str = lexem.lexems(fin);
    TokenTable hash(1000);
    std::vector <std::string> TokenType = { "CONST", "SEP", "VAR", "KEYWORD", "OP" };
    //std::vector<int> finalState = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 20, 22, 25, 31, 34, 37, 40 };
    Lexem a;
    std::vector <std::string> array;
    while (str != "") {
        if (lexem.getState(str) == -1) {
            fout << str << " ERROR\n";
        }
        else if (lexem.getState(str) == 10 || lexem.getState(str) == 11) {
            hash.addToken(Token(str, "SEP"));
            array.push_back(str);
        }
        else if (lexem.getState(str) == 20 || lexem.getState(str) == 12) {
            hash.addToken(Token(str, "OP"));
            array.push_back(str);
        }
        else if (lexem.getState(str) == 31 || lexem.getState(str) == 14 || lexem.getState(str) == 22 ||
            lexem.getState(str) == 37 || lexem.getState(str) == 40 || lexem.getState(str) == 25 ||
            lexem.getState(str) == 34)
        {
            hash.addToken(Token(str, "KEYWORD"));
            array.push_back(str);
        }
        else if (lexem.getState(str) == 1) {
            hash.addToken(Token(str, "CONST"));
            array.push_back(str);
        }
        else /*if (lexem.getState(str) == 2 || lexem.getState(str) == 3 || lexem.getState(str) == 4 ||
            lexem.getState(str) == 5 || lexem.getState(str) == 6 || lexem.getState(str) == 7 ||
            lexem.getState(str) == 8 || lexem.getState(str) == 9)*/
        {
            hash.addToken(Token(str, "VAR"));
            array.push_back(str);
        }

        str = lexem.lexems(fin);
    }
    
}
