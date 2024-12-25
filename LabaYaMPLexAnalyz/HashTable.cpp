#include <iostream>
#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <fstream>
#include "Token.h"
#include <string>

class TokenTable {
private:
    Token* table;
    int* status;
    int size;
    int capacity;


    int hash(const std::string& lexeme) {
        int hashValue = 0;
        for (char c : lexeme) {
            hashValue += static_cast<int>(c);
        }
        return hashValue % capacity;
    }


    int findFreeIndex(const std::string& lexeme) {
        int idx = hash(lexeme);
        while (status[idx] == 1 && table[idx].lexeme != lexeme) {
            idx = (idx + 1) % capacity;
        }
        return idx;
    }

public:

    TokenTable(int initialCapacity) : size(0), capacity(initialCapacity) {
        table = new Token[capacity];
        status = new int[capacity];
        for (int i = 0; i < capacity; ++i) {
            status[i] = 0;  // Все ячейки пустые
        }
    }

    //TokenTable();


    ~TokenTable() {
        delete[] table;
        delete[] status;
    }


    void addToken(const Token& t) {
        if (size >= capacity) {
            std::cerr << "Table is full!\n";
            return;
        }

        int idx = findFreeIndex(t.lexeme);
        table[idx] = t;
        status[idx] = 1;
        ++size;
    }


    int getId(Token& t, int capacity) {
        int idx = hash(t.lexeme);
        int startIdx = idx;
        while (status[idx] != 0) {
            if (status[idx] == 1 && table[idx].lexeme == t.lexeme && table[idx].type == t.type) {
                return idx;
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx) break;
        }
        return -1;
    }


    void printTable(std::ostream& fout) {
        fout << "Token | Lexeme | Type\n";
        fout << "----------------------\n";
        for (int i = 0; i < capacity; ++i) {
            if (status[i] == 1) {
                fout << i << " | " << table[i].lexeme << " | " << table[i].type << '\n';
            }
        }
    }
};
