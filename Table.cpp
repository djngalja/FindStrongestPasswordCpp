#include "Table.h"

void Table::SplitStringIntoPasswords(const std::string& str)
{
    std::string temp_string;
    for (char c: str)
    {
        if (!isspace(c))
            temp_string.push_back(c);
        else
        {
            if (!temp_string.empty())
            {
                Password temp_obj(temp_string);
                m_passwords.push_back(temp_obj);
                temp_string.clear();
            }
        }
    }
    if (!temp_string.empty())
    {
        Password temp_obj(temp_string);
        m_passwords.push_back(temp_obj);
    }
}

void Table::MakeLongestWordVector()
{
    m_longest_words = m_headers;
    std::string longest_password(m_headers[1]);
    std::string longest_pattern(m_headers[7]);
    for (Password password: m_passwords)
    {
        if (longest_password.size() < password.m_password.size())
            longest_password = password.m_password;
        if (longest_pattern.size() < password.m_pattern_string.size())
            longest_pattern = password.m_pattern_string;
    }
    m_longest_words[1] = longest_password;
    m_longest_words[7] = longest_pattern;
}

template<typename T>
std::string Table::MakeCell(T current_word, const std::string& longest_word, bool contains)
{
    std::ostringstream oss;
    oss << current_word;
    std::string cell = oss.str();
    if (contains)
    {
        if (cell=="1") cell = "+";
        else cell = " ";
    }
    cell.resize(longest_word.size(), ' ');
    cell += " | ";
    return cell;
}

void Table::PrintHeaders()
{
    std::cout << " | ";
    for (std::size_t i=0; i<m_headers.size(); i++)
    {
        if (i==1 || i==7)
            std::cout << MakeCell(m_headers[i], m_longest_words[i]);
        else
            std::cout << m_headers[i] << " | ";
    }
    std::cout << std::endl;
}

void Table::PrintBorder(char c)
{
    std::cout << " ";
    for (std::string word: m_longest_words)
    {
        std::string border("+");
        border.resize(word.size()+3, c);
        std::cout << border;
    }
    std::cout << "+" << std::endl;
}

Table::Table(const std::string& str)
{
    SplitStringIntoPasswords(str);
    MakeLongestWordVector();
}

void Table::PrintTable()
{
    std::sort(m_passwords.begin(), m_passwords.end(), [](Password a, Password b){return a.m_score > b.m_score;});
    PrintBorder();
    PrintHeaders();
    PrintBorder();
    for (std::size_t i=0; i<m_passwords.size(); i++)
    {
        std::cout << " | "
        << MakeCell(m_passwords[i].m_score, m_longest_words[0])
        << MakeCell(m_passwords[i].m_password, m_longest_words[1])
        << MakeCell(m_passwords[i].m_password.size(), m_longest_words[2])
        << MakeCell(m_passwords[i].m_count_special_chars, m_longest_words[3])
        << MakeCell(m_passwords[i].m_digits, m_longest_words[4], true)
        << MakeCell(m_passwords[i].m_lower_case, m_longest_words[5], true)
        << MakeCell(m_passwords[i].m_upper_case, m_longest_words[6], true)
        << MakeCell(m_passwords[i].m_pattern_string, m_longest_words[7])
        << std::endl;
        if (i != m_passwords.size()-1)
            PrintBorder('-');
    }
    PrintBorder();
}
