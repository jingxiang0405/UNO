#ifndef SERVER_H
#define SERVER_H
#include <thread>
#include <ifaddrs.h>
#include <netinet/in.h>
class Server {
public:
    Server(int player_count, int port);
    char *getIP() const;
    std::thread Spawn();
private:
    Server* CreateSocket();
    Server* SetupAddress();
    Server* BindAddress();
    Server* Listen();
    Server* complete();
    int Accept();

    void Loop();

    char *ip;
    int port, max_player_count;
    int server_fd;
    sockaddr_in address;
};

#endif
