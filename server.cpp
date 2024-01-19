#include "server.h"
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <iostream>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

char *GetIPAddress () {
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char *host = new char[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1) { throw("At Server::GetIPAddress(): getifaddrs() failed"); }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) { continue; }

        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET || family == AF_INET6) {
            s = getnameinfo(ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST, NULL, 0,
                            NI_NUMERICHOST);
            if (s != 0) { exit(EXIT_FAILURE); }

            if (family == AF_INET) {
                if (strcmp(host, "127.0.0.1") != 0) { // Exclude loopback address

                    return host;
                }
            }
        }
    }

    freeifaddrs(ifaddr);
    throw "Server Address not found";
}

Server::Server(int player_count, int port) {
    this->port = port;
    this->max_player_count = player_count;
    try{
        ip = GetIPAddress();
    }catch(const char* e){
        std::cerr << e << std::endl;
    }
}

Server* Server::complete(){
    std::cout << "Complete" << std::endl;
    return this;
}
Server* Server::CreateSocket() {

    std::cout << "Creating socket..." << std::flush;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { perror("Socket creation error"); }
    return this;
}

Server* Server::SetupAddress() {
    std::cout << "Setting address" << std::flush;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    return this;
}

Server* Server::BindAddress() {
    std::cout << "binding address" << std::endl;
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) { throw "Socket binding error"; }
    return this;
}

Server* Server::Listen() {
    std::cout << "listening...(max:" << max_player_count << std::endl;
    if (listen(server_fd, max_player_count) < 0) { throw "Socket listen error"; }
    return this;
}

int Server::Accept() {
    int addrlen = sizeof(address);
    std::cout << "Waiting for new connection..." << std::endl;
    int socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (socket < 0) { throw "Socket connect error"; }

    return socket;
}


char* Server::getIP() const{
    return ip;
}
void Server::Loop() {

    printf("Initializing Server...\n");
    try{
     CreateSocket()->complete()
         ->SetupAddress()->complete()
         ->BindAddress()->complete()
         ->Listen()->complete();


    }catch(const char* e){
        std::cerr << e << std::endl;
    }
       int addrlen = sizeof(address);

    char *ip_address = GetIPAddress();

    printf("Server is up on ip:%s\n", ip);
    
    // wait for clients connection
    int client_sockets[max_player_count];
    std::string client_names[max_player_count];
    for(int i = 0; i < max_player_count; ++i){
        char buf[20];
        memset(buf, 0, 20);
        int new_socket = Accept();
        client_sockets[i] = new_socket;
        read(new_socket, buf, 20);
        client_names[i] = std::string(buf);
        printf("Client Connected: \"%s\"\n", buf);
    }

    // send init message
    for(int i = 0; i < max_player_count; ++i){
       
        // id
        std::string message = "i" + std::to_string(i+1);
        
        // other players' name
        for(int j = 0; j < max_player_count; ++j){
            if(i==j)continue;

            message += "," + client_names[j];
        }

        // send init message
        write(client_sockets[i], message.c_str(), message.length());

    }

    // in-game loop
    char buffer[1024];
    while(true){
        for(int i = 0; i < max_player_count; ++i){
            read(client_sockets[i], buffer, 1024);
        }
    }
}

std::thread Server::Spawn() {
    return std::thread ([this] { Loop(); });
}
