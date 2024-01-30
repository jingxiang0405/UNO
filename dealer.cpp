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
  char *result = new char[2];
  strncpy(result, s.c_str(), s.length());
  return result;
}

char *UnoDealer::get_card(int quantity) {
  std::string s;
  for (int i = 0; i < quantity; ++i) {
    // 取出牌庫最後一張，並且對s使用字串concat
    // TODO
    // -------------
    // =   區塊3   =
    // -------------
    s += deck.back();
    deck.pop_back();
    // -------------
    // =   區塊3   =
    // -------------
  }
  char *result = new char[s.length() + 1];
  strncpy(result, s.c_str(), s.length());
  return result;
}

char *UnoDealer::get_uno_first_card() {
  std::string s;
  while (true) {
    // 取出牌庫最後一張，並且複製到s上
    // TODO
    // -------------
    // =   區塊4   =
    // -------------
    s = deck.back();
    deck.pop_back();
    // -------------
    // =   區塊4   =
    // -------------

    // 排除轉色牌
    if (s[1] != 'n')
      break;
    deck.insert(deck.begin(), s);
  }
  char *result = new char[2];
  strncpy(result, s.c_str(), s.length());
  return result;
}

void UnoDealer::test() {
  std::string s3;
  int count = 4;
  for (int i = deck.size() - 1; count > 0; --count, --i) {
    s3 += deck[i];
  }

  char *card3 = get_card(4);

  std::cout << "[Segment 3]" << std::endl
            << "Result should be:" << s3 << std::endl
            << "Given  string is:" << card3 << std::endl;

  char *card4 = get_uno_first_card();

  std::string s4;
  for (auto it = deck.end(); it != deck.begin() - 1; --it) {
    if ((*it)[1] != 'n') {
      s4 = *it;
      break;
    }
  }
  std::cout << "[Segment 4]" << std::endl
            << "Result should be:" << s4 << std::endl
            << "Given  string is:" << card4 << std::endl;
}

// 助教測試用

/*
int main() {
  UnoDealer dealer;
  dealer.test();
}

*/
