#include "conservative_count_min.h"
#include "count_min.h"
#include "hash.h"
#include "max_min.h"
#include "pretty_print.h"
#include "string_generator.h"
int main() {
  RandomStrings generator;
  auto all_strings = generator.gen_all_alphabet_str_with_const_sz(5);
  auto x = generator.generate_set_strings(10, 5);
  for (auto &i : x) {
    std::cout << i << " ";
    std::cout << MurmurHash2(&i[0], i.size()) << " "
              << YuraHash(&i[0], i.size()) << "\n";
  }
  std::cout << "\n";

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

  int res_cm = 0;
  int res_conservative = 0;
  int res_max_min = 0;

  for (auto &i : all_strings) {
    if (CM.Count(i) == CM.TrueCount(i)) {
      ++res_cm;
    }
    if (ConservativeCM.Count(i) == ConservativeCM.TrueCount(i)) {
      ++res_conservative;
    }
    if (MaxMinSketch.Count(i) == MaxMinSketch.TrueCount(i)) {
      ++res_max_min;
    }
  }
  std::cout << "\n";
  std::cout << res_cm << " " << res_conservative << " " << res_max_min;
}
