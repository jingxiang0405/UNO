// #include <stdio.h>
#include "client.h"
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
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
    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cout << strerror(errno);
        // throw "Connection failed";
    }
}
void Client::FormatIP() {

    std::cout << "Formating IP:" << server_ip << std::endl;
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) { throw "Invalid address/ Address not supported"; }
}
void Client::Loop() {
    // may need const
    char *message = "Hello, Server!";
    CreateSocket();
    SetupServerAddress();
    FormatIP();
    Connect();
    //
    send(socket_fd, message, strlen(message), 0);
    std::cout << "Message sent to server: " << message << std::endl;

    close(socket_fd);
}

std::thread Client::Spawn() {
    return std::thread([this] { Loop(); });
}
