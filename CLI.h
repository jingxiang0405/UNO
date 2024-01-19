#ifndef UI_H
#define UI_H
#include <vector>
#include "client.h"
#include "card.h"

namespace CLI{
void print_hand_cards(std::vector<Card> cards);
void print_update();
void print_end();

};
#endif

