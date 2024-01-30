#ifndef CLIENT_H
#define CLIENT_H
#include <netinet/in.h>
#include <string>
#include <vector>
class Client {

public:
  Client(int port = 8080);
  void SetServerIP(char *ip);
  void Start();

private:
  void CreateSocket();
  void SetupServerAddress();
  void FormatIP();
  void Connect();
  void Loop();

  void Print();
  void SendNameToServer();
  // for displaying
  std::string name;
  char *server_ip = nullptr;

  // identity in the game
  int id;

  int port;
  int socket_fd;
  sockaddr_in server_addr;
};
#endif
