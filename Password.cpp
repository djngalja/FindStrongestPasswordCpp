#include "Password.h"

int Password::ContainsDigits()
{
    for (char c: password)
        if (isdigit(c)) return 1;
    return 0;
}

int Password::ContainsUpperCase()
{
    for (char c: password)
        if (isupper(c)) return 1;
    return 0;
}

int Password::ContainsLowerCase()
{
    for (char c: password)
        if (islower(c)) return 1;
    return 0;
}

int Password::CountSpecialChars()
{
    int counter = 0;
    for (char c: password)
        if (!isalnum(c)) counter++;
    return counter;
}

void Password::FindCommonPatterns()
{
    const std::vector<std::string> patterns =
    {
        "123123",
        "123321",
        "123qwe",
        "1q2w3e",
        "abc123",
        "admin",
        "dragon",
        "iloveyou",
        "lovely",
        "password",
        "qwerty",
        "welcome"
    };
    for (std::string pattern: patterns)
    {
        std::size_t i = 0;
        while (i < password.size())
        {
            std::string temp_string;
            if (tolower(password[i]) == pattern[0] && password.size() >= (i+pattern.size()))
            {
                for (std::size_t j=0; j<pattern.size(); j++)
                {
                    if (tolower(password[i+j]) == pattern[j]) temp_string += password[i+j];
                    else break;
                }
                if (temp_string.size() == pattern.size())
                {
                    set_patterns.insert(temp_string);
                    count_patterns++;
                    i += pattern.size()-1;
                }
            }
            i++;
        }
    }
}

void Password::FindRepeatingChars()
{
    std::size_t i = 0;
    while (i < password.size()-3) //looking for sequences longer than 3 chars
    {
        std::string temp_string;
        if (password[i] == password[i+1])
        {
            temp_string += password[i];
            while ((i < (password.size()-1)) && (password[i] == password[i+1]))
            {
                temp_string += password[i+1];
                i++;
            }
        }
        if (temp_string.size() > 3)
        {
            set_patterns.insert(temp_string);
            count_patterns++;
        }
        i++;
    }
}

void Password::FindAbcPatterns(bool backwards)
{
    int d = backwards? -1 : 1; //common difference
    std::size_t i = 0;
    while (i < password.size()-3)
    {
        std::string temp_string;
        if ((tolower(password[i]+d) == tolower(password[i+1])) && isalnum(password[i]))
        {
            temp_string += password[i];
            while ((i<password.size()-1) && (tolower(password[i]+d) == tolower(password[i+1])) && isalnum(password[i]))
            {
                temp_string += password[i+1];
                i++;
            }
        }
        if (temp_string.size() > 3)
        {
            set_patterns.insert(temp_string);
            count_patterns++;
        }
        i++;
    }
}


Password::Password(const std::string& word) : password(word), count_patterns(0)
{
    digits = ContainsDigits();
    lower_case = ContainsLowerCase();
    upper_case = ContainsUpperCase();
    count_special_chars = CountSpecialChars();
    if (password.size() > 3)
    {
        FindCommonPatterns();
        FindRepeatingChars();
        FindAbcPatterns();
        FindAbcPatterns(true);
    }
    for(std::string str: set_patterns) string_patterns += str + ", ";
    if (string_patterns.size()!=0)
        string_patterns.erase(string_patterns.size()-2, string_patterns.size());
    score = digits + lower_case + upper_case + count_special_chars + password.size()/8 - count_patterns;
}
