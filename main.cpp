#include <iostream>
#include "hash.h"
int main() {
  std::string s = "hello,world";
  std::cout << MurmurHash2(&s[0], s.length());
}
