#include "CLI.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <unordered_map>
const int COLUMN_LIMIT = 5;
std::unordered_map<char, std::string> color_map = {{'r', "\e[41;30m"},
                                                   {'g', "\e[42;30m"},
                                                   {'y', "\e[43;30m"},
                                                   {'b', "\e[44;30m"},
                                                   {'n', "\e[0m"}};
std::unordered_map<char, int> index_map = {

    {'0', 0},  {'1', 1},  {'2', 2},  {'3', 3},  {'4', 4},
    {'5', 5},  {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9},
    {'s', 10}, {'r', 11}, {'t', 12}, {'w', 13}, {'f', 14}};

std::vector<std::string> CLI::all_player_name;
int CLI::client_id;

void CLI::print_cards(std::string &cards, bool number) {
  int len = cards.length();
  int i = 0;
  int init_h = (number) ? -1 : 0;
  const int climit = COLUMN_LIMIT * 2;
  int limit = climit;
  for (int n = 0; n <= len / climit; ++n) {

    if (n == len / climit)
      limit = len;
    for (int h = init_h; h < CARD_HEIGHT; ++h) {

      for (int j = i; j < limit; j += 2) {
        if (h == -1) {
          std::cout << "         (" << (j / 2) + 1 << ")         ";
        } else {
          std::cout << color_map[cards[j + 1]]
                    << card_display_array[index_map[cards[j]]][h] << "\e[0m ";
        }
      }
      std::cout << std::endl;
    }
    i = limit;
    limit *= 2;
  }
}
void CLI::print_update(std::vector<std::string> &msg_arr) {
  system("clear");
  int curr_id = msg_arr[0].c_str()[0] - '0';
  std::cout << "==============================" << std::endl;
  std::cout << std::setw(14) << std::internal << CLI::all_player_name[curr_id]
            << "\'s turn" << std::endl;
  std::cout << "==============================" << std::endl;

  for (int i = 0; i < CLI::all_player_name.size(); ++i) {
    std::cout << CLI::all_player_name[i] << " : " << msg_arr[i + 3]
              << std::endl;
  }

  std::cout << "==============================" << std::endl
            << "Card on the table:" << std::endl;
  CLI::print_cards(msg_arr[1], false);

  std::cout << "==============================" << std::endl
            << "Your cards:" << std::endl;
  CLI::print_cards(msg_arr[2], true);
  std::cout << "==============================" << std::endl;
}

int CLI::play_card(int card_count) {
  int index;

  while (true) {
    std::cout << "Choose a card to play by index(0 to draw):" << std::flush;
    std::cin >> index;
    if (index <= card_count && index >= 0)
      return index - 1;
  }
}

char CLI::get_wild_color() {
  char c;
  while (true) {
    std::cout << "Which color do you want(r/b/g/y):" << std::flush;
    std::cin >> c;
    if (c == 'r' || c == 'b' || c == 'g' || c == 'y')
      return c;
  }
}
void CLI::print_end(int winner_id) {
  system("clear");
  std::cout << "==============================" << std::endl
            << CLI::all_player_name[winner_id] << " is the winner!" << std::endl
            << "==============================" << std::endl;
}

/* int main() { */
/*   std::vector<std::string> msg_arr = {"2", "tr", "9b8r7g", "3", "5", "3"}; */
/*   CLI::print_update(msg_arr); */
/* } */
