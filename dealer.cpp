#include "dealer.h"
#include "util.h"
#include <iostream>
#include <vector>

extern "C" {
#include <string.h>
}
void UnoDealer::init() {

  deck.clear();
  std::vector<char> types = {'0', '1', '2', '3', '4', '5', '6',
                             '7', '8', '9', 's', 'r', 't'};

  std::vector<char> colors = {'r', 'g', 'b', 'y'};
  for (auto &t : types) {
    for (auto &c : colors) {
      std::string s(2, t);
      s[1] = c;
      deck.push_back(s);
      deck.push_back(s);
    }
  }
  for (int i = 0; i < 4; ++i) {
    deck.push_back("wn");
    deck.push_back("fn");
  }

  // shuffle
  Util::shuffle_vector(deck);
}
UnoDealer::UnoDealer() { init(); }

char *UnoDealer::get_card() {
  std::string s = deck.back();
  deck.pop_back();
  char *result = new char[3];
  strncpy(result, s.c_str(), s.length());
  return result;
}

char *UnoDealer::get_card(int quantity) {
  std::string s;
  for (int i = 0; i < quantity; ++i) {
    s += deck.back();
    deck.pop_back();
  }
  char *result = new char[s.length() + 1];
  strncpy(result, s.c_str(), s.length());
  return result;
}

char *UnoDealer::get_first_card() {
  std::string s;
  while (true) {
    s = deck.back();
    deck.pop_back();

    if (s[1] != 'n')
      break;

    deck.insert(deck.begin(), s);
  }
  char *result = new char[3];
  strncpy(result, s.c_str(), s.length());
  return result;
}
