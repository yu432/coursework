#include "conservative_count_min.h"
#include "count_min.h"
#include "hash.h"
#include "max_min.h"
#include "pretty_print.h"
#include "string_generator.h"
#include "ziph.h"
#include <random>
#include <map>
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
  int counter = 0;
  /*  //  uniform distribution
  for (size_t i = 0; i < 100000; i++) {

    auto num = (generator.Rand()) % 100;
    CM.Update(x[num]);
    ConservativeCM.Update(x[num]);

  }
  */

  /*
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::normal_distribution<> d{50, 12};
  std::map<int, int>test_dist;
  for(size_t i = 0; i < 100000; i++) {
    int num = int(std::round(d(gen)));
    //std::cout << num << " " << i << "\n";
    if (num >= 0 && num < 100) {
      CM.Update(x[num]);
      ConservativeCM.Update(x[num]);
      ++test_dist[num];
    }

  }
  for(auto i : test_dist) {
    std::cout << i.first << " " << i.second << "\n";
  }
  */
  std::default_random_engine generator_for_zipf(2);
  zipfian_int_distribution<int>::param_type p(0, 99, 0.999);
  zipfian_int_distribution<int> distribution(p);
  std::map<int, int>test_dist;
  for(size_t i = 0; i < 100000; i++) {
    int num = distribution(generator_for_zipf);
    CM.Update(x[num]);
    ++test_dist[num];
    ConservativeCM.Update(x[num]);
    //std::cout << num << " " << ++counter << "\n";
  }
  for(auto i : test_dist) {
    std::cout << i.first << " " << i.second << "\n";
  }

  CM.Print();
  ConservativeCM.Print();

  std::cout <<"CM error:\n";
  CM.EvaluateError(x);
  std::cout <<"Conservative CM error:\n";
  ConservativeCM.EvaluateError(x);

}

//без строк сделать
//