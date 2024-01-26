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
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    throw "Socket creation error";
  }
}

void Client::SetupServerAddress() {
  memset(&server_addr, '0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(server_ip);
}

void Client::Connect() {

  std::cout << "Connecting to server..." << std::endl;
  if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    throw "Connection failed";
  }
}
void Client::FormatIP() {

  std::cout << "Formating IP:" << server_ip << std::endl;
  if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
    throw "Invalid address/ Address not supported";
  }
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
  } catch (const char *e) {
    std::cerr << e << std::endl;
  }

  // string buffer for I/O with server
  char *buf = new char[1024];

  bool running = true;

  // I&O loop
  while (running) {

    // read message from server
    memset(buf, 0, 1024);
    recv(socket_fd, buf, 1024, 0);
    std::cout << "Message from server:" << buf << std::endl;
    // string for further manipulations
    std::string str(buf);
    str = str.substr(1);
    std::cout << "str:" << str << std::endl;
    std::vector<std::string> ss = Util::string_split(str, ',');

    // init
    if (buf[0] == 'i') {
      std::cout << "Init" << std::endl;
      std::cout << "Your id is " << ss[0] << std::endl;
      this->id = ss[0].c_str()[0] - '0';
      CLI::client_id = this->id;
      for (int i = 1; i < ss.size(); ++i) {
        CLI::all_player_name.push_back(ss[i]);
      }
      std::cout << ss.size() << std::endl;
      write(socket_fd, "ready", 5);
      continue;
    }

    // end action
    else if (buf[0] == 'e') {
      CLI::print_end(ss[0].c_str()[0] - '0');
      running = false;
      break;
    }
    // update action
    else if (buf[0] == 'u') {

      CLI::print_update(ss);
      // your turn
      if (this->id == ss[0].c_str()[0] - '0') {

        int index = CLI::play_card(ss[2].length() / 2);

        std::string command;
        if (index == -1) {
          command = "d";
        } else {
          command = ss[2].substr(index * 2, 2);
        }
        // wild card
        if (command[0] == 'w' || command[0] == 'f') {
          char color = CLI::get_wild_color();
          command[1] = color;
        }
        std::cout << "[Test] command=" << command << std::endl;
        // send messages to server
        send(socket_fd, command.c_str(), command.length(), 0);
      }
    }
  }

  close(socket_fd);
}

// creating a thread for execution
std::thread Client::Spawn() {
  return std::thread([this] { Loop(); });
}
