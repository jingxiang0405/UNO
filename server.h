#ifndef SERVER_H
#define SERVER_H
#include <ifaddrs.h>
#include <netinet/in.h>
class Server {
public:
  Server(int player_count, int port);
  ~Server();
  char *getIP() const;
  void Start();

private:
  // for connection
  Server *CreateSocket();
  Server *SetupAddress();
  Server *BindAddress();
  Server *Listen();
  Server *complete();
  int Accept();

  // main loop
  void Loop();

  char *ip;
  int port, max_player_count;
  int server_fd;
  sockaddr_in address;
};

#endif
