#include "conservative_count_min.h"
#include "count_min.h"
#include "hash.h"
#include "max_min.h"
#include "pretty_print.h"
#include "string_generator.h"
#include "ziph.h"
#include <random>
#include <map>
class Constants{
public:
  size_t SIZE_OF_TABLE = 300;
  size_t COUNT_HASH_FUNC = 3;
  size_t SIZE_OF_STREAM = 100000;
  int TYPE = 3; // 1 for Uniform dist, 2 for Gaussian dist, 3 for Ziphian dist
};

int main() {
  Constants Constants;
  RandomStrings generator;
  auto x = generator.generate_set_strings(100, 5);
  /*
  for (auto &i : x) {
    std::cout << i << " ";
    std::cout << MurmurHash2(&i[0], i.size()) << " " << FNVHash(&i[0], i.size())
              << " " << JenkinsHash(&i[0], i.size()) << "\n";
  }
  std::cout << "\n";
  */
  auto CM = CountMin(
      std::vector<std::function<unsigned int(const char *, unsigned int)>>{
          MurmurHash2, FNVHash, JenkinsHash},
      Constants.SIZE_OF_TABLE);

  auto ConservativeCM = ConservativeCountMin(
      std::vector<std::function<unsigned int(const char *, unsigned int)>>{
          MurmurHash2, FNVHash, JenkinsHash},
      Constants.SIZE_OF_TABLE);

  if (Constants.TYPE == 1) {
    for (size_t i = 0; i < Constants.SIZE_OF_STREAM; i++) {

      auto num = (generator.Rand()) % Constants.SIZE_OF_TABLE;
      CM.Update(x[num]);
      ConservativeCM.Update(x[num]);
    }
  } else if (Constants.TYPE == 2) {

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{(Constants.SIZE_OF_TABLE / 2.0), 35};

    for(size_t i = 0; i < Constants.SIZE_OF_STREAM; i++) {
      int num = int(std::round(d(gen)));
      if (num >= 0 && num < Constants.SIZE_OF_TABLE) {
        CM.Update(x[num]);
        ConservativeCM.Update(x[num]);
      }
    }
  } else if (Constants.TYPE == 3) {

    std::default_random_engine generator_for_zipf(2);
    zipfian_int_distribution<int>::param_type p(0, 99, 0.999);
    zipfian_int_distribution<int> distribution(p);
    //std::map<int, int> test_dist;
    for (size_t i = 0; i < Constants.SIZE_OF_STREAM; i++) {
      int num = distribution(generator_for_zipf);
      CM.Update(x[num]);
      //++test_dist[num];
      ConservativeCM.Update(x[num]);

    }
    //for (auto i : test_dist) {
    //  std::cout << i.first << " " << i.second << "\n";
    //}
  }

  CM.Print();
  ConservativeCM.Print();

  std::cout <<"CM error:\n";
  CM.EvaluateError(x);
  std::cout <<"Conservative CM error:\n";
  ConservativeCM.EvaluateError(x);

}
