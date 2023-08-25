#ifndef TABLE_H
#define TABLE_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include "Password.h"

class Table
{
    const std::vector<std::string> headers =
    {
        "Score",
        "Password",
        "Length",
        "SP Chars",
        "Digits",
        "LCase",
        "UCase",
        "Patterns"
    };
    std::vector<std::string> longest_words;
    std::vector<Password> passwords;

    void SplitStringIntoPasswords(const std::string& str);
    void MakeLongestWordVector();
    template<typename T> std::string MakeCell(T current_word, const std::string& longest_word, bool contains=false);
    void PrintHeaders();
    void PrintBorder(char c = '=');

public:
    Table(std::string& str);
    void PrintTable();
};

#endif // TABLE_H
