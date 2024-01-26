#include "dealer.h"
#include "util.h"

extern "C" {
#include <stdio.h>
#include <string.h>
}
struct Player {
  int id;
  Player *prev;
  Player *next;
  Player(int i) : id(i) {}
};

const int INIT_CARD_COUNT = 7;
const int MAX_CARD_COUNT = 50;
UnoDealer dealer;
char **card_arr;
char *top_card;
int nPlayer;

Player *current_player;
bool order;

void uno_server_init(int player_count) {
  order = true;
  nPlayer = player_count;
  // sequence list
  current_player = new Player(0);
  Player *temp = current_player;

  for (int i = 1; i < player_count; ++i) {
    Player *p = new Player(i);
    p->prev = temp;
    temp->next = p;

    // connect the loop
    if (player_count == i + 1) {
      p->next = current_player;
      current_player->prev = p;
    }

    temp = p;
  }

  // card array
  card_arr = new char *[player_count];
  for (int i = 0; i < player_count; ++i) {
    card_arr[i] = new char[MAX_CARD_COUNT * 2 + 1];
    card_arr[i][MAX_CARD_COUNT * 2] = '\0';
    strcpy(card_arr[i], dealer.get_card(INIT_CARD_COUNT));
  }

  top_card = dealer.get_first_card();
}

int check_end() {
  for (int i = 0; i < nPlayer; ++i) {
    if (strlen(card_arr[i]) == 0)
      return i;
  }
  return 0;
}

Player *get_next_player() {

  return (order) ? current_player->next : current_player->prev;
}
char *command_to_client(int client_id) {
  char *str;
  int status = check_end();
  if (status == 0)

  {
    int len = 7 + strlen(card_arr[client_id]) + (3 * nPlayer);
    str = new char[len];
    char *buffer = new char[10];
    int index;
    // fixed position
    str[0] = 'u';
    str[1] = current_player->id + '0';
    str[2] = ',';
    strncpy(str + 3, top_card, 2);
    str[5] = ',';

    // dynamic position
    // client's card
    strncpy(str + 6, card_arr[client_id], strlen(card_arr[client_id]));
    index = 6 + strlen(card_arr[client_id]);
    str[index++] = ',';

    // every client's card count
    for (int i = 0; i < nPlayer; ++i) {
      int card_count = strlen(card_arr[i]) / 2;
      snprintf(buffer, sizeof(buffer), "%d", card_count);

      // not the last
      if (nPlayer != i + 1) {
        strcat(buffer, ",");
      }
      int len = strlen(buffer);
      strncpy(str + index, buffer, len);
      index += len;
    }
  } else {
    str = new char[2];
    str[0] = 'e';
    str[1] = status + '0';
  }
  return str;
}
// check if the card is valid
bool is_valid_play(char *card) {
  return (card[0] == 'w' || card[0] == 'f' || top_card[0] == card[0] ||
          top_card[1] == card[1]);
}
void draw(int id, int count) {
  char *newCards = dealer.get_card(count);
  strcat(card_arr[id], newCards);
  delete[] newCards;
}

void handle_client_message(char *card) {
  cout << "top=" << top_card << ", card=" << card << endl;
  char type = card[0];
  int turn = 1;

  // draw  card
  if (card[0] == 'd') {
    draw(current_player->id, 1);
  }
  // play card
  else if (is_valid_play(card)) {
    char color = card[1];
    switch (type) {
    case 'f': {
      draw(get_next_player()->id, 4);

      // skip next player
      ++turn;
      // for deletion of card_arr
      card[1] = 'n';
      break;
    }
    case 'w': {

      // for deletion of card_arr
      card[1] = 'n';
      break;
    }
    case 't': {
      draw(get_next_player()->id, 2);
      // skip next player
      ++turn;
      break;
    }
    case 's': {
      // skip next player
      ++turn;
      break;
    }
    case 'r': {
      order = !order;
      break;
    }
    }

    Util::delete_substring(card_arr[current_player->id], card);

    // recover string
    card[1] = color;

    // overlap the top card
    strncpy(top_card, card, 2);

  } else {
    --turn;
  }
  for (int i = 0; i < turn; ++i) {
    current_player = get_next_player();
  }
}

int get_current_id() { return current_player->id; }
