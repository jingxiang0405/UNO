#include "dealer.h"
#include "util.h"

extern "C" {
#include <stdio.h>
#include <string.h>
}

// 玩家的結構，prev為上一個玩家，next為下一個玩家
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

// 當前牌桌上的牌
char *top_card;

// 玩家個數
int number_of_player;

// 當前玩家個數
Player *current_player;

// 代表玩家的順序是順時針或逆時針（不用管true是順還逆）
bool order;

// 代表遊戲是否已經結束
bool isEnd;

bool is_valid_play(char *card) {
  return (card[0] == 'w' || card[0] == 'f' || top_card[0] == card[0] ||
          top_card[1] == card[1]);
}

void uno_server_init(int player_count) {
  order = true;
  isEnd = false;
  number_of_player = player_count;

  current_player = new Player(0);
  Player *temp = current_player;

  for (int i = 1; i < player_count; ++i) {
    Player *p = new Player(i);
    p->prev = temp;
    temp->next = p;

    if (player_count == i + 1) {
      p->next = current_player;
      current_player->prev = p;
    }

    temp = p;
  }

  card_arr = new char *[player_count];
  for (int i = 0; i < player_count; ++i) {
    card_arr[i] = new char[MAX_CARD_COUNT * 2 + 1];
    card_arr[i][MAX_CARD_COUNT * 2] = '\0';
    strcpy(card_arr[i], dealer.get_card(INIT_CARD_COUNT));
  }

  top_card = dealer.get_uno_first_card();
}

// =============================
// 以下函數你「一定」會用到！
// =============================

// 根據給玩家（id）抽牌（count）張
void draw(int id, int count) {
  char *newCards = dealer.get_card(count);
  strcat(card_arr[id], newCards);
  delete[] newCards;
}
// 獲取下一輪的玩家的Player結構
Player *get_next_player() {
  return (order) ? current_player->next : current_player->prev;
}

int check_end() {
  for (int i = 0; i < number_of_player; ++i) {
    if (strlen(card_arr[i]) == 0)
      return i;
  }
  return -1;
}
// =============================
//
// =============================

char *command_to_client(int client_id) {
  char *str;
  int status = check_end();
  if (status == -1)

  {
    int len = 7 + strlen(card_arr[client_id]) + (3 * number_of_player);
    str = new char[len];
    char *buffer = new char[10];
    int index;

    // 此處要回傳回合更新字串，格式如下：
    // u[輪到某玩家的ID],[當前桌上的牌],    ->
    // 只需要做這行，下一行的內容已經在115行後完成
    // [客戶端擁有的牌],[ID=0的玩家手牌數量],[ID=1的玩家手牌數量],......
    //
    // 請完成command字串處理的前六個字
    // 結果為"u[當前玩家id],[當前UNO牌],"
    // 舉例：當前是玩家A(id=0)，並且當前的UNO牌是藍色迴轉牌，則前六個字元為"u0,rb,"
    // ID的範圍為0~9，不必擔心進位問題

    // TODO
    // -------------
    // =   區塊5   =
    // -------------
    str[0] = 'u';
    str[1] = current_player->id + '0';
    str[2] = ',';
    strncpy(str + 3, top_card, 2);
    str[5] = ',';
    // -------------
    // =   區塊5   =
    // -------------

    // 剩餘的command
    strncpy(str + 6, card_arr[client_id], strlen(card_arr[client_id]));
    index = 6 + strlen(card_arr[client_id]);
    str[index++] = ',';

    for (int i = 0; i < number_of_player; ++i) {
      int card_count = strlen(card_arr[i]) / 2;
      snprintf(buffer, sizeof(buffer), "%d", card_count);

      if (number_of_player != i + 1) {
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

void handle_client_message(char *card) {
  char type = card[0];

  // 在區塊6中，你需要決定玩家的抽牌與順序。
  // (你會用到的變數，另外還有全域變數！)
  // 控制玩家順序，代表該由誰出牌（0：不變，1：下個玩家，2：下下個玩家......）
  int turn = 1;

  // 玩家抽牌
  if (card[0] == 'd') {
    // TODO
    // -------------
    // =  區塊6-1  =
    // -------------
    draw(current_player->id, 1);
    // -------------
    // =  區塊6-1  =
    // -------------
  }
  // 玩家出牌
  else if (is_valid_play(card)) {
    char color = card[1];
    switch (type) {
    case 'f': {
      // TODO
      // -------------
      // =  區塊6-2  =
      // -------------
      draw(get_next_player()->id, 4);
      ++turn;
      // -------------
      // =  區塊6-2  =
      // -------------

      card[1] = 'n';
      break;
    }
    case 'w': {
      // TODO
      // -------------
      // =  區塊6-3  =
      // -------------
      // 空
      // -------------
      // =  區塊6-3  =
      // -------------
      card[1] = 'n';
      break;
    }
    case 't': {
      // TODO
      // -------------
      // =  區塊6-4  =
      // -------------
      draw(get_next_player()->id, 2);
      ++turn;
      // -------------
      // =  區塊6-4  =
      // -------------

      break;
    }
    case 's': {
      // TODO
      // -------------
      // =  區塊6-5  =
      // -------------
      ++turn;
      // -------------
      // =  區塊6-5  =
      // -------------

      break;
    }
    case 'r': {
      // TODO
      // -------------
      // =  區塊6-6  =
      // -------------
      order = !order;
      // -------------
      // =  區塊6-6  =
      // -------------
    }
    }

    // delete card played
    Util::delete_substring(card_arr[current_player->id], card);

    card[1] = color;

    // 覆蓋表面的牌
    strncpy(top_card, card, 2);

  } else {
    --turn;
  }
  for (int i = 0; i < turn; ++i) {
    current_player = get_next_player();
  }
}

int get_current_id() {
  // 回傳當前玩家的id
  // TODO
  // -------------
  // =   區塊7   =
  // -------------
  return (isEnd) ? -1 : current_player->id;
  // -------------
  // =   區塊7   =
  // -------------
}
