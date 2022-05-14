#include <algorithm>
#include <random>
#include <string>
#include <vector>



class RandomStrings {
private:
  std::vector<char> letters_{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                             'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                             's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  std::mt19937 mt;
  const size_t max_index_ = (letters_.size());

public:
  explicit RandomStrings(int seed) {
    mt.seed(seed);
  }
  unsigned int randd() { return mt(); }
  char generate_char() { return letters_[randd() % max_index_]; }
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