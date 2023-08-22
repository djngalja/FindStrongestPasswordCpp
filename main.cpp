#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Password
{
    int count_patterns;

    int ContainsDigits()
    {
        for (char c: password)
            if (isdigit(c)) return 1;
        return 0;
    }

    int ContainsUpperCase()
    {
        for (char c: password)
            if (isupper(c)) return 1;
        return 0;
    }

    int ContainsLowerCase()
    {
        for (char c: password)
            if (islower(c)) return 1;
        return 0;
    }

    int CountSpecialChars()
    {
        int counter = 0;
        for (char c: password)
            if (!isalnum(c)) counter++;
        return counter;
    }

    void FindCommonPatterns()
    {
        std::vector<std::string> patterns =
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
                        common_patterns += temp_string + ", ";
                        count_patterns++;
                        i += pattern.size()-1;
                    }
                }
                i++;
            }
        }
    }

    void FindRepeatingChars()
    {
        if (password.size() < 3) return;
        std::size_t i = 0;
        while (i < password.size()-3)
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
            if (temp_string.size()>3)
            {
                common_patterns += temp_string + ", ";
                count_patterns++;
            }
            i++;
        }
    }

public:
    int score;
    std::string password;
    int count_special_chars;
    int digits;
    int lower_case;
    int upper_case;
    std::string common_patterns;

    Password(std::string word)
    {
        password = word;
        digits = ContainsDigits();
        lower_case = ContainsLowerCase();
        upper_case = ContainsUpperCase();
        count_special_chars = CountSpecialChars();
        count_patterns = 0;
        FindCommonPatterns();
        FindRepeatingChars();
        if (common_patterns.size()!=0)
            common_patterns.erase(common_patterns.size()-2, common_patterns.size());
        score = digits + lower_case + upper_case + count_special_chars + password.size()/8 - count_patterns;
    }
};

void print_headers(const std::vector<std::string>& headers, const std::vector<std::string>& longest_words);
void print_border(const std::vector<std::string>& longest_words, char c='=');
template<typename T> std::string make_cell(T current_word, const std::string& longest_word, bool contains=false);
void print_comparison_table(std::vector<Password> passwords);
std::vector<std::string> make_longest_words_vector(const std::vector<Password>& passwords, const std::vector<std::string>& headers);

int main()
{
    std::string input;
    std::cout << "Enter passwords separated by white spaces:" << std::endl;
    std::getline(std::cin, input);

    std::vector<Password> passwords;
    std::string temp_string;
    for (char c: input)
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

    print_comparison_table(passwords);
    system("pause");
    return 0;
}

std::vector<std::string> make_longest_words_vector(const std::vector<Password>& passwords, const std::vector<std::string>& headers)
{
    std::vector<std::string> longest_words(headers);
    std::string longest_password(headers[1]);
    std::string longest_pattern(headers[7]);
    for (Password password: passwords)
    {
        if (longest_password.size() < password.password.size()) longest_password = password.password;
        if (longest_pattern.size() < password.common_patterns.size()) longest_pattern = password.common_patterns;
    }

    longest_words[1] = longest_password;
    longest_words[7] = longest_pattern;
    return longest_words;
}


void print_comparison_table(std::vector<Password> passwords)
{
    std::vector<std::string> headers = {"Score", "Password", "Length", "SP Chars", "Digits", "LCase", "UCase", "Patterns"};

    std::sort(passwords.begin(), passwords.end(), [](Password a, Password b){return a.score > b.score;});

    std::vector<std::string>  longest_words(make_longest_words_vector(passwords, headers));
    print_border(longest_words);
    print_headers(headers, longest_words);
    print_border(longest_words);

    for (std::size_t i=0; i<passwords.size(); i++)
    {
        int j = 0;
        std::cout << " | "
        << make_cell(passwords[i].score, longest_words[j++])
        << make_cell(passwords[i].password, longest_words[j++])
        << make_cell(passwords[i].password.size(), longest_words[j++])
        << make_cell(passwords[i].count_special_chars, longest_words[j++])
        << make_cell(passwords[i].digits,longest_words[j++], true)
        << make_cell(passwords[i].lower_case, longest_words[j++], true)
        << make_cell(passwords[i].upper_case, longest_words[j++], true)
        << make_cell(passwords[i].common_patterns, longest_words[j++])
        << std::endl;
        if (i!=passwords.size()-1)
            print_border(longest_words, '-');
    }
    print_border(longest_words);
}

void print_border(const std::vector<std::string>& longest_words, char c)
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

void print_headers(const std::vector<std::string>& headers, const std::vector<std::string>& longest_words)
{
        std::cout << " | ";
        for (std::size_t i=0; i<headers.size(); i++)
        {
            if (i==1 || i==7)
                std::cout << make_cell(headers[i], longest_words[i]);
            else
                std::cout << headers[i] << " | ";
        }
        std::cout << std::endl;
}

template<typename T>
std::string make_cell(T current_word, const std::string& longest_word, bool contains)
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
