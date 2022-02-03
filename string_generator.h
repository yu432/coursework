#include <algorithm>
#include <random>
#include <string>
#include <vector>

int pow(int a, size_t b) {
  if (b == 0) {
    return 1;
  } else if (b % 2 == 0) {
    auto x = pow(a, b / 2);
    return x * x;
  } else {
    auto x = pow(a, b / 2);
    return a * x * x;
  }
}

class RandomStrings {
private:
  std::vector<char> letters_{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                             'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                             's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  std::default_random_engine engine_;
  std::uniform_int_distribution<> distribution_;
  const size_t max_index_ = (letters_.size());

public:
  int Rand() { return distribution_(engine_); }
  char generate_char() { return letters_[Rand() % max_index_]; }
  std::string generate_string(size_t size_of_str) {
    std::string result;
    result.reserve(size_of_str);
    for (size_t i = 0; i < size_of_str; ++i) {
      result.push_back(generate_char());
    }
    return result;
  }

  std::vector<std::string> generate_set_strings(size_t size_of_set,
                                                size_t size_of_string) {
    std::vector<std::string> res;
    res.reserve(size_of_set);
    for (size_t i = 0; i < size_of_set; ++i) {
      res.push_back(generate_string(size_of_string));
    }
    return res;
  };

};