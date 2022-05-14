#include <iostream>
#include <unordered_map>
#include <vector>
class CountMin {
private:
  std::vector<int> table_;
  std::vector<std::function<unsigned int(const char *, unsigned int)>> hashes_;

  // for check
  std::unordered_map<std::string, int> storage_;

public:
  CountMin(
      const std::vector<std::function<unsigned int(const char *, unsigned int)>>
          &hashes, size_t size_of_table) {
    hashes_ = hashes;
    table_.resize(size_of_table);
  }
  void Update(const std::string &s) {
    ++storage_[s];
    for (auto &hash : hashes_) {
      table_[(hash.operator()(&s[0], s.size())) % table_.size()] += 1;
    }
  }
  void Update(const std::string &s, int num) {
    storage_[s] += num;
    for (auto &hash : hashes_) {
      table_[(hash.operator()(&s[0], s.size())) % table_.size()] += num;
    }
  }
  int Count(const std::string &s) {
    auto minimal =
        table_[(hashes_[0].operator()(&s[0], s.size())) % table_.size()];
    for (auto &hash : hashes_) {
      if (table_[(hash.operator()(&s[0], s.size())) % table_.size()] <
          minimal) {
        minimal =
            table_[(hash.operator()(&s[0], s.size())) % table_.size()];
      }
    }
    return minimal;
  }
  size_t TrueCount(const std::string &s) { return storage_[s]; }

  bool Contains(const std::string &s) {
    for (auto &hash : hashes_) {
      if (table_[(hash.operator()(&s[0], s.size())) % table_.size()] < 1) {
        return false;
      }
    }
    return true;
  }

  bool TrueContains(const std::string &s) { return storage_[s]; }
  void Print() {
    for (const auto &i : table_) {
      std::cout << i << " ";
    }
    std::cout << "\n";
  }

  void EvaluateError(const std::vector<std::string>& strings) {
    for(auto &string : strings) {
      /*
      if (TrueCount(string) == 0) {
        std::cout << "0 ";
        continue;
      }
       */
      std::cout << double((Count(string) - TrueCount(string))) << " ";
    }
    std::cout << "\n";
  }
};