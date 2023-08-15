#include <iostream>
#include <string>

bool is_digit(char c);
bool is_upper_case(char c);
bool is_lower_case(char c);
bool is_letter_or_digit(char c);

class Password {
    std::string password;

    public:
        Password(std::string word){
            password = word;
        }

        int contains_digit() {
            for (size_t i=0; i<password.size(); i++) {
                if (is_digit(password[i])) return 1;
            }
            return 0;
       }

        int contains_upper_case() {
            for (size_t i=0; i<password.size(); i++) {
                if (is_upper_case(password[i])) return 1;
            }
            return 0;
        }

        int contains_lower_case() {
            for (size_t i=0; i<password.size(); i++) {
                if (is_lower_case(password[i])) return 1;
            }
            return 0;
        }

        int count_special_chars() {
            int counter = 0;
            for (size_t i=0; i<password.size(); i++) {
                if (!is_letter_or_digit(password[i])) counter++;
            }
            return counter;
        }

};

int main()
{
    std::string word = "password__123_";
    Password password(word);
    std::cout << "digits = " << password.contains_digit() << std::endl;
    std::cout << "lower case = " << password.contains_lower_case() << std::endl;
    std::cout << "upper case = " << password.contains_upper_case() << std::endl;
    std::cout << "special chars = " << password.count_special_chars() << std::endl;

    return 0;
}

bool is_digit(char c) {
    if(c>=48 && c<=57) return true;
    else return false;
}

bool is_upper_case(char c) {
    if (c>=65 && c<=90) return true;
    else return false;
}

bool is_lower_case(char c) {
    if (c>=97 && c<=122) return true;
    else return false;
}

bool is_letter_or_digit(char c) {
    if (is_digit(c) || is_upper_case(c) || is_lower_case(c)) return true;
    else return false;
}
