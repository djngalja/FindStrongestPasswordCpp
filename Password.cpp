#include "Password.h"

int Password::ContainsDigits() {
  for (char c: m_password)
    if (isdigit(c)) return 1;
  return 0;
}

int Password::ContainsUpperCase() {
  for (char c: m_password)
    if (isupper(c)) return 1;
  return 0;
}

int Password::ContainsLowerCase() {
  for (char c: m_password)
    if (islower(c)) return 1;
  return 0;
}

int Password::CountSpecialChars() {
  int counter = 0;
  for (char c: m_password)
    if (!isalnum(c)) counter++;
  return counter;
}

//find such patterns as 'qwErtY', 'ADMIN', etc.
void Password::FindCommonPatterns() {
  //add common (lower case) passwords to this vector
  const std::vector<std::string> patterns = {
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
  std::string shortest_pattern = patterns[0];
  for (std::string pattern: patterns)
    if (pattern.size() < shortest_pattern.size())
      shortest_pattern = pattern;
  //make sure the password is long enough
  if (m_password.size() < shortest_pattern.size()) return;
  for (std::string pattern: patterns) {
    if (pattern.size() > m_password.size()) continue;
    for (std::size_t i=0; i<m_password.size(); i++) {
      std::string temp_string;
      if (tolower(m_password[i]) == pattern[0]) {
        for (std::size_t j=0; j<pattern.size(); j++) {
          if (tolower(m_password[i+j]) == pattern[j])
            temp_string.push_back(m_password[i+j]);
          else break;
        }
        if (temp_string.size() == pattern.size()) {
          m_pattern_set.insert(temp_string);
          i += pattern.size()-1;
        }
      }
    }
  }
}

//find such patterns as '1111', 'PPPPP', 'Aaaa', '____', etc.
void Password::FindRepeatingChars() {
  if (m_password.size() < 2) return;
  for (std::size_t i=0; i<=m_password.size()-m_min_pattern_len; i++) {
    std::string temp_string;
    if (tolower(m_password[i]) == tolower(m_password[i+1])) {
      temp_string.push_back(m_password[i]);
      while (
        i < m_password.size()-1
        && tolower(m_password[i]) == tolower(m_password[i+1])
      ) {
        temp_string.push_back(m_password[i+1]);
        i++;
      }
    }
    if (temp_string.size() >= m_min_pattern_len)
      m_pattern_set.insert(temp_string);
  }
}

//find such patterns as '1212', 'cdcdcd', 'HAHahaha', etc.
void Password::FindRepeatingPairs() {
  if (m_password.size() < 4) return;
  for (std::size_t i=0; i<=m_password.size()-m_min_pattern_len; i++) {
    std::string temp_string;
    if (
      tolower(m_password[i]) == tolower(m_password[i+2])
      && tolower(m_password[i+1]) == tolower(m_password[i+3])
      && tolower(m_password[i]) != tolower(m_password[i+1])
    ) {
      temp_string.push_back(m_password[i]);
      temp_string.push_back(m_password[i+1]);
      while (
        i <= m_password.size()-3
        && tolower(m_password[i]) == tolower(m_password[i+2])
        && tolower(m_password[i+1]) == tolower(m_password[i+3])
      ) {
        temp_string.push_back(m_password[i+2]);
        temp_string.push_back(m_password[i+3]);
        i += 2;
      }
        }
        if (temp_string.size() >= m_min_pattern_len) {
          m_pattern_set.insert(temp_string);
          i++;
        }
  }
}

//find such patterns as 'aBcD', '23456' or 'dcba', '65432' if backwards is 'true'
void Password::FindAbcPatterns(bool backwards) {
  if (m_password.size() < 2) return;
  int d = backwards? -1 : 1; //common difference
  for (std::size_t i=0; i<=m_password.size()-m_min_pattern_len; i++) {
    std::string temp_string;
    if (
      tolower(m_password[i]+d) == tolower(m_password[i+1])
      && isalnum(m_password[i])
    ) {
      temp_string.push_back(m_password[i]);
      while (
        tolower(m_password[i]+d) == tolower(m_password[i+1])
        && i < m_password.size()-1
      ) {
        temp_string.push_back(m_password[i+1]);
        i++;
      }
   }
   if (temp_string.size() >= m_min_pattern_len)
     m_pattern_set.insert(temp_string);
  }
}

Password::Password(const std::string& password, std::size_t min_pattern_len):
  m_password(password), m_min_pattern_len(min_pattern_len) {
  m_digits = ContainsDigits();
  m_lower_case = ContainsLowerCase();
  m_upper_case = ContainsUpperCase();
  m_count_special_chars = CountSpecialChars();
  if (m_password.size() >= m_min_pattern_len && m_min_pattern_len >= 2) {
    FindCommonPatterns();
    FindRepeatingChars();
    FindRepeatingPairs();
    FindAbcPatterns();
    FindAbcPatterns(true);
  }
  for(std::string str: m_pattern_set) m_pattern_string += str + ", ";
  if (m_pattern_string.size()!=0)
    m_pattern_string.erase(m_pattern_string.size()-2, m_pattern_string.size());
   m_score = m_digits + m_lower_case + m_upper_case
     + m_count_special_chars + m_password.size()/8 - m_pattern_set.size();
}
