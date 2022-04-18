#include <random>
#include <map>
#include <functional>

#include "conservative_count_min.h"
#include "count_min.h"
#include "hash.h"
#include "max_min.h"
#include "string_generator.h"
#include "ziph.h"

class Constants{
public:
  size_t SIZE_OF_TABLE = 300;
  size_t SIZE_OF_STREAM = 100000;
  std::vector<std::function<unsigned int(const char *, unsigned int)>> VECTOR_HASHES{MurmurHash_1,
                                                                                     MurmurHash_2,
                                                                                     MurmurHash_3};
  int TYPE = 3; // 1 for Uniform dist, 2 for Gaussian dist, 3 for Ziphian dist
};

int main() {
  Constants Constants;
  RandomStrings generator;
  for(int iter = 0; iter < 100; iter++) {
    auto x = generator.generate_set_strings(100, 5);

    auto CM = CountMin(
        Constants.VECTOR_HASHES,
        Constants.SIZE_OF_TABLE);

    auto ConservativeCM = ConservativeCountMin(
        Constants.VECTOR_HASHES,
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

      for (size_t i = 0; i < Constants.SIZE_OF_STREAM; i++) {
        int num = int(std::round(d(gen)));
        if (num >= 0 && num < Constants.SIZE_OF_TABLE) {
          CM.Update(x[num]);
          ConservativeCM.Update(x[num]);
        }
      }

    } else if (Constants.TYPE == 3) {
      int rand_int = random();
      std::default_random_engine generator_for_zipf(rand_int);
      zipfian_int_distribution<int>::param_type p(0, 99, 0.999);
      zipfian_int_distribution<int> distribution(p);
      for (size_t i = 0; i < Constants.SIZE_OF_STREAM; i++) {
        int num = distribution(generator_for_zipf);
        CM.Update(x[num]);
        ConservativeCM.Update(x[num]);
      }
    }

    //CM.Print();
    //ConservativeCM.Print();

    std::cout << "CM error:\n";
    CM.EvaluateError(x);
    std::cout << "Conservative CM error:\n";
    ConservativeCM.EvaluateError(x);
  }
}
