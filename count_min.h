#include<vector>
#include<unordered_set>
#include "pretty_print.h"
class CountMin {
private:
  std::vector<std::vector<int>>table_;
  std::vector<std::function<unsigned int(const char*, unsigned int)>>hashes_;
  size_t rows_;
  size_t columns_;

  //for check
  std::unordered_multiset<std::string> storage_;

public:
  CountMin(const std::vector<std::function<unsigned int(const char*, unsigned int)>>& hashes, size_t columns) {
    hashes_ = hashes;
    table_.resize(hashes.size(), std::vector<int>(columns));
    rows_ = hashes.size();
    columns_ = columns;
  }
  void Update(const std::string& s) {
    storage_.insert(s);
    for(size_t i = 0; i < rows_; i++) {
      table_[i][(hashes_[i].operator()(&s[0], s.size())) % columns_] += 1;
    }
  }
  void Update(const std::string& s, int num) {
    for(size_t i = 0; i < num; i++) {
      storage_.insert(s);
    }
    for(size_t i = 0; i < rows_; i++) {
      table_[i][(hashes_[i].operator()(&s[0], s.size())) % columns_] += num;
    }
  }

  bool Contains(const std::string& s) {
    for(size_t i = 0; i < rows_; i++) {
      if (table_[i][(hashes_[i].operator()(&s[0], s.size())) % columns_] < 1) {
        return false;
      }
    }
    return true;
  }

  bool TrueContains(const std::string& s) {
    return storage_.contains(s);
  }
  void Print() {
    for(const auto& i : table_) {
      for(const auto& j : i) {
        std::cout << j << " ";
      }
      std::cout << "\n";
    }
  }
};