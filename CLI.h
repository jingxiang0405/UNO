#ifndef UI_H
#define UI_H
#include "card.h"
#include "client.h"
#include <string>
#include <vector>
namespace CLI {
extern std::vector<std::string> all_player_name;
extern int client_id;
void print_cards(std::string &cards, bool number);
void print_update(std::vector<std::string> &msg_arr);
int play_card(int card_count);
char get_wild_color();
void print_end(int winner_id);
}; // namespace CLI
#endif
