#include "util.h"
#include <sstream>

extern "C" {
#include <string.h>
}
std::vector<std::string> Util::string_split(const std::string &str,
                                            char delimeter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delimeter)) {
    tokens.push_back(token);
  }

  return tokens;
}

void Util::delete_substring(char *str, const char *sub) {
  char *pos = strstr(str, sub);
  if (pos != NULL) {
    size_t len = strlen(sub);
    memmove(pos, pos + len, strlen(pos + len) + 1);
  }
}

/* #include <iostream> */
/* int main() { */
/*   auto s = Util::string_split("u0,sg,rr5r5bfn7b7ytb,7", ','); */
/*   std::cout << s[2]; */
/* } */
