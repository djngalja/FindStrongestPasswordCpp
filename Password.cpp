#include "Password.h"

int Password::ContainsDigits()
{
    for (char c: m_password)
        if (isdigit(c)) return 1;
    return 0;
}

int Password::ContainsUpperCase()
{
    for (char c: m_password)
        if (isupper(c)) return 1;
    return 0;
}

int Password::ContainsLowerCase()
{
    for (char c: m_password)
        if (islower(c)) return 1;
    return 0;
}

int Password::CountSpecialChars()
{
    int counter = 0;
    for (char c: m_password)
        if (!isalnum(c)) counter++;
    return counter;
}

void Password::FindCommonPatterns()
{
    const std::vector<std::string> patterns = //find such patterns as 'qwErtY', 'ADMIN', etc.
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
        if (pattern.size() > m_password.size()) continue;
        for (std::size_t i=0; i<m_password.size(); i++)
        {
            std::string temp_string;
            if (tolower(m_password[i]) == pattern[0])
            {
                for (std::size_t j=0; j<pattern.size(); j++)
                {
                    if (tolower(m_password[i+j]) == pattern[j])
                        temp_string.push_back(m_password[i+j]);
                    else break;
                }
                if (temp_string.size() == pattern.size())
                {
                    m_pattern_set.insert(temp_string);
                    m_score--;
                    i += pattern.size()-1;
                }
            }
        }
    }
}

void Password::FindRepeatingChars() //find such patterns as '1111', 'PPPPP', '____', etc.
{
    for (std::size_t i=0; i<m_password.size()-3; i++) //for patterns longer than 3 chars
    {
        std::string temp_string;
        if (m_password[i]==m_password[i+1])
        {
            temp_string.push_back(m_password[i]);
            while (m_password[i]==m_password[i+1] && i<m_password.size()-1)
            {
                temp_string.push_back(m_password[i+1]);
                i++;
            }
        }
        if (temp_string.size()>3)
        {
            m_pattern_set.insert(temp_string);
            m_score--;
        }
    }
}

void Password::FindRepeatingPairs() //find such patterns as '121212', 'cdcdcd', 'HAHAHAHA', etc.
{
    if (m_password.size()<6) return; //for patterns not shorter than 6 chars
    for (std::size_t i=0; i<=m_password.size()-6; i++)
    {
        std::string temp_string;
        if (
            tolower(m_password[i]) == tolower(m_password[i+2])
            && tolower(m_password[i+1]) == tolower(m_password[i+3])
            && tolower(m_password[i]) != tolower(m_password[i+1])
            )
        {
            temp_string.push_back(m_password[i]);
            temp_string.push_back(m_password[i+1]);
            while (
                   tolower(m_password[i]) == tolower(m_password[i+2])
                   && tolower(m_password[i+1]) == tolower(m_password[i+3])
                   && i <= m_password.size()-3
                   )
            {
                temp_string.push_back(m_password[i+2]);
                temp_string.push_back(m_password[i+3]);
                i += 2;
            }
        }
        if (temp_string.size()>=6)
        {
            m_pattern_set.insert(temp_string);
            m_score--;
        }
    }
}

void Password::FindAbcPatterns(bool backwards) //find such patterns as 'abcd', '23456' or 'dcba', '65432' if backwards is 'true'
{
    int d = backwards? -1 : 1; //common difference
    for (std::size_t i=0; i<m_password.size()-3; i++) //for patterns longer than 3 chars
    {
        std::string temp_string;
        if ((tolower(m_password[i]+d) == tolower(m_password[i+1])) && isalnum(m_password[i]))
        {
            temp_string.push_back(m_password[i]);
            while ((tolower(m_password[i]+d) == tolower(m_password[i+1])) && i<m_password.size()-1)
            {
                temp_string.push_back(m_password[i+1]);
                i++;
            }
        }
        if (temp_string.size() > 3)
        {
            m_pattern_set.insert(temp_string);
            m_score--;
        }
    }
}

Password::Password(const std::string& password) : m_password(password), m_score(0)
{
    m_digits = ContainsDigits();
    m_lower_case = ContainsLowerCase();
    m_upper_case = ContainsUpperCase();
    m_count_special_chars = CountSpecialChars();
    if (m_password.size() > 3)
    {
        FindCommonPatterns();
        FindRepeatingChars();
        FindRepeatingPairs();
        FindAbcPatterns();
        FindAbcPatterns(true);
    }
    for(std::string str: m_pattern_set) m_pattern_string += str + ", ";
    if (m_pattern_string.size()!=0)
        m_pattern_string.erase(m_pattern_string.size()-2, m_pattern_string.size());
    m_score += m_digits + m_lower_case + m_upper_case + m_count_special_chars + m_password.size()/8;
}
