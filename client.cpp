#include "client.h"
#include "CLI.h"
#include "util.h"
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

Client::Client(int port) { this->port = port; }

void Client::SetServerIP(char *ip) { this->server_ip = ip; }
void Client::CreateSocket() {
    // Create socket
    std::cout << "Create client socket" << std::endl;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { throw "Socket creation error"; }
}

void Client::SetupServerAddress() {
    memset(&server_addr, '0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
}

void Client::Connect() {

    std::cout << "Connecting to server..." << std::endl;
    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { throw "Connection failed"; }
}
void Client::FormatIP() {

    std::cout << "Formating IP:" << server_ip << std::endl;
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) { throw "Invalid address/ Address not supported"; }
}

void Client::SendNameToServer() {
    std::cout << "Enter your name:" << std::flush;
    std::cin >> name;
    send(socket_fd, name.c_str(), name.length(), 0);
}

void Client::Loop() {

    // connection procedure
    try {
        CreateSocket();
        SetupServerAddress();
        FormatIP();
        Connect();
        SendNameToServer();
    } catch (const char *e) { std::cerr << e << std::endl; }

    // string buffer for I/O with server
    char buf[1024];


    bool running = true;
   
    // I&O loop
    while (running) {

        // read message from server
        memset(buf, 0, 1024);
        read(socket_fd, buf, 1024);

        // check action
        char action = buf[0];

        // string for further manipulations
        std::string str;
        str.assign(buf + 1);
        std::vector<std::string> ss = string_split(str, ',');
        // init
        if (buf[0] == 'i') {
            this->id = std::stoi(ss[0]);
            for (int i = 0; i < 3; ++i) {
                this->foes_name[i] = ss[i + 1];
            }
            continue;
        }

        // end action
        else if (buf[0] == 'e') {

            break;
        }
        // update action 
        else if (buf[0] == 'u') {}

        // TODO get command
        char *message = "hello from client";

        // send messages to server
        send(socket_fd, message, strlen(message), 0);
    }
 
    close(socket_fd);
}

// creating a thread for execution
std::thread Client::Spawn() {
    return std::thread([this] { Loop(); });
}
