#include <random>
#include <map>
#include <functional>
#include <fstream>

#include "conservative_count_min.h"
#include "count_min.h"
#include "hash.h"
#include "max_min.h"
#include "string_generator.h"
#include "ziph.h"

unsigned int seed_for_hash_1 = 1;
unsigned int seed_for_hash_2 = 12;
unsigned int seed_for_hash_3 = 37;

unsigned int start_num_1 = 131;
unsigned int start_num_2 = 131;
unsigned int start_num_3 = 131;

class Constants{
public:
  size_t SIZE_OF_TABLE = 300;
  size_t SIZE_OF_STREAM = 50000;
  std::vector<std::function<unsigned int(const char *, unsigned int)>> VECTOR_HASHES{MurmurHash_1,
                                                                                     MurmurHash_2,
                                                                                     MurmurHash_3};
  int TYPE = 3; // 1 for Uniform dist, 2 for Gaussian dist, 3 for Ziphian dist
  size_t COUNT_DIFFERENT_ELEMS_IN_SET = 10000;
  size_t SIZE_OF_STRING = 5;
};

int main(int argc, char** argv) {
  Constants Constants;
  RandomStrings generator(std::stoi(argv[1]));
  for(int iter = 0; iter < std::stoi(argv[2]); iter++) {
    seed_for_hash_1 = generator.randd();
    seed_for_hash_2 = seed_for_hash_1;
    seed_for_hash_3 = seed_for_hash_1;

    start_num_1 = generator.randd();
    start_num_2 = generator.randd();
    start_num_3 = generator.randd();

    auto x = generator.generate_set_strings(Constants.COUNT_DIFFERENT_ELEMS_IN_SET,
                                            Constants.SIZE_OF_STRING);

    auto CM = CountMin(
        Constants.VECTOR_HASHES,
        Constants.SIZE_OF_TABLE);

    auto ConservativeCM = ConservativeCountMin(
        Constants.VECTOR_HASHES,
        Constants.SIZE_OF_TABLE);

    if (Constants.TYPE == 1) {
      for (size_t i = 0; i < Constants.SIZE_OF_STREAM; i++) {

        auto num = (generator.randd()) % Constants.SIZE_OF_TABLE;
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
      int gen = generator.randd();
      std::default_random_engine generator_for_zipf(gen);
      zipfian_int_distribution<int>::param_type p(0, Constants.COUNT_DIFFERENT_ELEMS_IN_SET - 1, 0.99);
      zipfian_int_distribution<int> distribution(p);
      std::map<int, int> for_dist;
      for (size_t i = 0; i < Constants.SIZE_OF_STREAM; i++) {
        int num = distribution(generator_for_zipf);
        if (num >= 0 && num < Constants.SIZE_OF_TABLE) {
          ++for_dist[num];
          CM.Update(x[num]);
          ConservativeCM.Update(x[num]);
        }
      }
      std::ofstream myfile;
      myfile.open("dist.txt");
      int counter = 0;
      for(auto i : for_dist) {
        myfile << x[counter] << " " << i.first << " " << i.second << "\n";
        ++counter;
      }
      myfile.close();
    }

    //CM.Print();
    //ConservativeCM.Print();

    std::cout << "CM error:\n";
    CM.EvaluateError(x);
    std::cout << "Conservative CM error:\n";
    ConservativeCM.EvaluateError(x);
  }
}
