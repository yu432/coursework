#include <iostream>
#include "hash.h"
#include "string_generator.h"
int main() {
  std::string s = "hello,world";
  RandomStrings generator;
  for(auto &i : generator.generate_set_strings(1000, 50)) {
    std::cout << i << "\n";
  }
}
