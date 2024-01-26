#ifndef DEALER_H
#define DEALER_H

#include <string>
#include <vector>
class UnoDealer {
public:
  UnoDealer();
  char *get_card();
  char *get_card(int quantity);
  char *get_first_card();
  inline int size() { return deck.size(); }
  /* private: */
  std::vector<std::string> deck;
  void init();
};

#endif
