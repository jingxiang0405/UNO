#ifndef UNO_SERVER_H
#define UNO_SERVER_H

// 初始化
void uno_server_init(int player_count);

// 針對傳入的客戶端ID(client_id), 回傳對該客戶端的訊息(char*)
// 註：id範圍為0 ~ 玩家數量（player_count）（不包含）
//
// 訊息格式如下
//

//
// 遊戲結束(end):
// e[贏家ID]
//
//
char *command_to_client(int client_id);

//
// 註：
// 你需要判斷出牌是否符合規則，若不符合規則，則不需要做任何資料更新
// (舉例：若桌上的牌是綠色0，客戶端傳來紅色3，此行為不符合規則）
//
void handle_client_message(char *card);

// 請回傳目前行動的玩家ID
// 若遊戲結束，請回傳-1
int get_current_id();

// 註：
// 程式實際在執行時會先呼叫command_to_client()，針對每個ID，傳給客戶端訊息
// 接著透過get_current_id()讀取客戶端的訊息
// 再來呼叫handle_client_message()以更新伺服器的狀態。
// 如此循環往復，直到結束的回合。
//
//  舉例：若A(id=0)出了「紅色加兩張」的牌，且符合規定
//  你需要給A的下一位玩家B(id=1)抽兩張牌，並暫停行動一回合，
//  因此command_to_client回傳的會以"u3tr"開頭(後續省略)
//
// 註: 結束的回合需要在
// 1. command_to_client() 回傳e開頭的end事件
// 2. get_current_id() 回傳-1代表迴圈結束，否則一定會出bug。

#endif
