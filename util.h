#ifndef UTIL_H
#define UTIL_H

extern "C" {
#include <time.h>
}
#include <algorithm>
#include <random>
#include <string>
#include <vector>
namespace Util {
std::vector<std::string> string_split(const std::string &str, char delimeter);

// header only
template <typename T> void shuffle_vector(std::vector<T> &vec) {
  std::shuffle(vec.begin(), vec.end(),
               std::default_random_engine(time(nullptr)));
}

void delete_substring(char *str, const char *sub);
}; // namespace Util

#endif
