#include <iostream>
#include "hash.h"
#include "string_generator.h"
#include "count_min.h"
#include "conservative_count_min.h"
int main() {
  std::string s = "hello,world";
  RandomStrings generator;
  auto x = generator.generate_set_strings(15, 5);
  for(auto &i : x) {
    std::cout << i << " ";
    std::cout << MurmurHash2(&i[0], i.size()) << "\n";
  }
  auto CM = CountMin(std::vector<std::function<unsigned int(const char*, unsigned int)>>{
    MurmurHash2, YuraHash}, 10);
  for(const auto& i : x) {
    CM.Update(i);
  }
  CM.Print();


}
