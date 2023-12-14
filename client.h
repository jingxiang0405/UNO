#ifndef CLIENT_H
#define CLIENT_H
#include <netinet/in.h>
#include <string>
#include <thread>
class Client {

public:
    Client(int port = 8080);
    void SetServerIP(char* ip);
    std::thread Spawn();
private:
    void CreateSocket();
    void SetupServerAddress();
    void FormatIP();
    void Connect();

    void Loop();

    char *server_ip;
    int port;
    int socket_fd;
    sockaddr_in server_addr;
};
#endif
