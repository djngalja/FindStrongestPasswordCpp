#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <vector>

class Password
{
    int count_patterns;

    int ContainsDigits();
    int ContainsUpperCase();
    int ContainsLowerCase();
    int CountSpecialChars();
    void FindCommonPatterns();
    void FindRepeatingChars();
    void FindAbcPatterns(bool backwards = false);

public:
    int score;
    std::string password;
    int count_special_chars;
    int digits;
    int lower_case;
    int upper_case;
    std::string common_patterns;

    Password(const std::string& word);
};

#endif // PASSWORD_H
