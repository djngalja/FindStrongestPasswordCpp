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
        while (i < m_password.size())
        {
            std::string temp_string;
            if (tolower(m_password[i]) == pattern[0] && m_password.size() >= (i+pattern.size()))
            {
                for (std::size_t j=0; j<pattern.size(); j++)
                {
                    if (tolower(m_password[i+j]) == pattern[j]) temp_string += m_password[i+j];
                    else break;
                }
                if (temp_string.size() == pattern.size())
                {
                    m_pattern_set.insert(temp_string);
                    m_score--;
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
    while (i < m_password.size()-3) //looking for sequences longer than 3 chars
    {
        std::string temp_string;
        if (m_password[i] == m_password[i+1])
        {
            temp_string += m_password[i];
            while ((i < (m_password.size()-1)) && (m_password[i] == m_password[i+1]))
            {
                temp_string += m_password[i+1];
                i++;
            }
        }
        if (temp_string.size() > 3)
        {
            m_pattern_set.insert(temp_string);
            m_score--;
        }
        i++;
    }
}

void Password::FindAbcPatterns(bool backwards)
{
    int d = backwards? -1 : 1; //common difference
    std::size_t i = 0;
    while (i < m_password.size()-3)
    {
        std::string temp_string;
        if ((tolower(m_password[i]+d) == tolower(m_password[i+1])) && isalnum(m_password[i]))
        {
            temp_string += m_password[i];
            while ((i<m_password.size()-1) && (tolower(m_password[i]+d) == tolower(m_password[i+1])) && isalnum(m_password[i]))
            {
                temp_string += m_password[i+1];
                i++;
            }
        }
        if (temp_string.size() > 3)
        {
            m_pattern_set.insert(temp_string);
            m_score--;
        }
        i++;
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
        FindAbcPatterns();
        FindAbcPatterns(true);
    }
    for(std::string str: m_pattern_set) m_pattern_string += str + ", ";
    if (m_pattern_string.size()!=0)
        m_pattern_string.erase(m_pattern_string.size()-2, m_pattern_string.size());
    m_score += m_digits + m_lower_case + m_upper_case + m_count_special_chars + m_password.size()/8;
}

std::string Password::getPassword()
{
    return m_password;
}

int Password::getCountSpecialChars()
{
    return m_count_special_chars;
}

int Password::getDigits()
{
    return m_digits;
}

int Password::getLowerCase()
{
    return m_lower_case;
}

int Password::getUpperCase()
{
    return m_upper_case;
}

std::string Password::getPatternString()
{
    return m_pattern_string;
}

int Password::getScore()
{
    return m_score;
}
