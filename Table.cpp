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
            Password temp_obj(temp_string);
            passwords.push_back(temp_obj);
            temp_string.clear();
        }
    }
    Password temp_obj(temp_string);
    passwords.push_back(temp_obj);
}

void Table::MakeLongestWordVector()
{
    longest_words = headers;
    std::string longest_password(headers[1]);
    std::string longest_pattern(headers[7]);
    for (Password password: passwords)
    {
        if (longest_password.size() < password.password.size())
            longest_password = password.password;
        if (longest_pattern.size() < password.common_patterns.size())
            longest_pattern = password.common_patterns;
    }
    longest_words[1] = longest_password;
    longest_words[7] = longest_pattern;
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
    for (std::size_t i=0; i<headers.size(); i++)
    {
        if (i==1 || i==7)
            std::cout << MakeCell(headers[i], longest_words[i]);
        else
            std::cout << headers[i] << " | ";
    }
    std::cout << std::endl;
}

void Table::PrintBorder(char c)
{
    std::cout << " ";
    for (std::string word: longest_words)
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
    std::sort(passwords.begin(), passwords.end(), [](Password a, Password b){return a.score > b.score;});
    PrintBorder();
    PrintHeaders();
    PrintBorder();
    for (std::size_t i=0; i<passwords.size(); i++)
    {
        std::cout << " | "
        << MakeCell(passwords[i].score, longest_words[0])
        << MakeCell(passwords[i].password, longest_words[1])
        << MakeCell(passwords[i].password.size(), longest_words[2])
        << MakeCell(passwords[i].count_special_chars, longest_words[3])
        << MakeCell(passwords[i].digits,longest_words[4], true)
        << MakeCell(passwords[i].lower_case, longest_words[5], true)
        << MakeCell(passwords[i].upper_case, longest_words[6], true)
        << MakeCell(passwords[i].common_patterns, longest_words[7])
        << std::endl;
        if (i != passwords.size()-1)
            PrintBorder('-');
    }
    PrintBorder();
}
