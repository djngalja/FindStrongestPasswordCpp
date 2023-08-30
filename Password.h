#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <vector>
#include <set>

class Password
{
    std::string m_password;
    int m_count_special_chars;
    int m_digits;
    int m_lower_case;
    int m_upper_case;
    std::set<std::string> m_pattern_set;
    std::string m_pattern_string;
    int m_score;

    int ContainsDigits();
    int ContainsUpperCase();
    int ContainsLowerCase();
    int CountSpecialChars();
    void FindCommonPatterns();
    void FindRepeatingChars();
    void FindAbcPatterns(bool backwards = false);

public:
    Password(const std::string& word);

    std::string getPassword();
    int getCountSpecialChars();
    int getDigits();
    int getLowerCase();
    int getUpperCase();
    std::string getPatternString();
    int getScore();
};

#endif // PASSWORD_H
