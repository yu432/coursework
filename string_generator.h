#include <random>
#include <vector>
#include <algorithm>
#include <string>

class RandomStrings {
private:
    std::vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    std::default_random_engine engine;
    std::uniform_int_distribution<> distribution;
    const size_t max_index = (letters.size());


  public:
    int Rand() {
      return distribution(engine);
    }
    char generate_char() {
      return letters[ Rand() % max_index ];
    }
    std::string generate_string(size_t size_of_str) {
      std::string result;
      result.reserve(size_of_str);
      for(size_t i = 0; i < size_of_str; ++i) {
        result.push_back(generate_char());
      }
      return result;
    }

    std::vector<std::string> generate_set_strings(size_t size_of_set, size_t size_of_string) {
        std::vector<std::string> res;
        res.reserve(size_of_set);
        for(size_t i = 0; i < size_of_set; ++i) {
          res.push_back(generate_string(size_of_string));
        }
        return res;
    };
};