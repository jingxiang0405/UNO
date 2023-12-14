#ifndef SERVER_H
#define SERVER_H
#include <thread>
#include <ifaddrs.h>
#include <netinet/in.h>
class Server {
public:
    Server(int port = 8080);
    char *getIP() const;
    std::thread Spawn();
private:
    void CreateSocket();
    void SetupAddress();

    void BindAddress();
    void Listen();
    int Accept();

    void Loop();
    char *ip;
    int port, max_player_count;
    int server_fd;
    sockaddr_in address;
};

#endif
