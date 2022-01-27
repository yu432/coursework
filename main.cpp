#include "conservative_count_min.h"
#include "count_min.h"
#include "hash.h"
#include "max_min.h"
#include "pretty_print.h"
#include "string_generator.h"
int main() {
  RandomStrings generator;
  auto x = generator.generate_set_strings(100, 5);
  for (auto &i : x) {
    std::cout << i << " ";
    std::cout << MurmurHash2(&i[0], i.size()) << " " << FNVHash(&i[0], i.size())
              << " " << JenkinsHash(&i[0], i.size()) << "\n";
  }
  std::cout << "\n";

  auto CM = CountMin(
      std::vector<std::function<unsigned int(const char *, unsigned int)>>{
          MurmurHash2, FNVHash, JenkinsHash},
      100);

  auto ConservativeCM = ConservativeCountMin(
      std::vector<std::function<unsigned int(const char *, unsigned int)>>{
          MurmurHash2, FNVHash, JenkinsHash},
      100);

  for (size_t i = 0; i < 100000; i++) {
    auto num = (generator.Rand()) % 100;
    CM.Update(x[num]);
    ConservativeCM.Update(x[num]);
  }

  CM.Print();
  ConservativeCM.Print();

  std::cout <<"CM error: " << CM.EvaluateError(x) << "\n";
  std::cout <<"Conservative CM error: " << ConservativeCM.EvaluateError(x) << "\n";
  // 26^5 = 11881376 = 12 * 10^6
}
