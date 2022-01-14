#include "conservative_count_min.h"
#include "count_min.h"
#include "hash.h"
#include "max_min.h"
#include "string_generator.h"
#include <iostream>
int main() {
  RandomStrings generator;
  auto x = generator.generate_set_strings(15, 5);
  for (auto &i : x) {
    std::cout << i << " ";
    std::cout << MurmurHash2(&i[0], i.size()) << "\n";
  }
  auto CM = CountMin(
      std::vector<std::function<unsigned int(const char *, unsigned int)>>{
          MurmurHash2, YuraHash},
      10);

  auto ConservativeCM = ConservativeCountMin(
      std::vector<std::function<unsigned int(const char *, unsigned int)>>{
          MurmurHash2, YuraHash},
      10);

  auto MaxMinSketch = MaxMin(
      std::vector<std::function<unsigned int(const char *, unsigned int)>>{
          MurmurHash2, YuraHash},
      10);

  for (const auto &i : x) {
    CM.Update(i);
    ConservativeCM.Update(i);
    MaxMinSketch.Update(i);
  }

  CM.Print();

  ConservativeCM.Print();

  MaxMinSketch.Print();
}
