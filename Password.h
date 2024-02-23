#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <vector>
#include <unordered_set>

class Password {
private:
  std::string m_password;
  int m_count_special_chars;
  int m_digits;
  int m_lower_case;
  int m_upper_case;
  std::size_t m_min_pattern_len;
  std::unordered_set<std::string> m_pattern_set;
  std::string m_pattern_string;
  int m_score;

  int ContainsDigits();
  int ContainsUpperCase();
  int ContainsLowerCase();
  int CountSpecialChars();
  void FindCommonPatterns();
  void FindRepeatingChars();
  void FindRepeatingPairs();
  void FindAbcPatterns(bool backwards = false);

public:
  Password(const std::string& password, std::size_t min_pattern_len = 4);
  friend class Table;
};

#endif // PASSWORD_H
