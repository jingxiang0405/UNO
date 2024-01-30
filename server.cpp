#include "server.h"
#include "CLI.h"
#include "uno_server.h"
#include "util.h"
#include <iostream>
#include <string>
extern "C" {
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
}

// for server
struct ClientInfo {
  int socket_fd;
  std::string name;
};

Server::Server(int player_count, int port) {
  this->port = port;
  this->max_player_count = player_count;
}

Server::~Server() { close(server_fd); }

char *GetIPAddress() {
  struct ifaddrs *ifaddr, *ifa;
  int family, s;
  char *host = new char[NI_MAXHOST];

  if (getifaddrs(&ifaddr) == -1) {
    throw("At Server::GetIPAddress(): getifaddrs() failed");
  }

  for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == NULL) {
      continue;
    }

    family = ifa->ifa_addr->sa_family;

    if (family == AF_INET || family == AF_INET6) {
      s = getnameinfo(ifa->ifa_addr,
                      (family == AF_INET) ? sizeof(struct sockaddr_in)
                                          : sizeof(struct sockaddr_in6),
                      host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
      if (s != 0) {
        exit(EXIT_FAILURE);
      }

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
Server *Server::complete() {
  std::cout << "Complete" << std::endl;
  return this;
}
Server *Server::CreateSocket() {

  std::cout << "Creating socket..." << std::flush;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Socket creation error");
  }
  ioctl(server_fd, FIONBIO, 0);
  return this;
}

Server *Server::SetupAddress() {
  std::cout << "Setting address" << std::flush;
  ip = GetIPAddress();
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ip);
  address.sin_port = htons(port);
  return this;
}

Server *Server::BindAddress() {
  std::cout << "binding address" << std::flush;
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    throw "Socket binding error";
  }
  return this;
}

Server *Server::Listen() {
  std::cout << "listening...(max:" << max_player_count << ")" << std::flush;
  if (listen(server_fd, max_player_count) < 0) {
    throw "Socket listen error";
  }
  return this;
}

int Server::Accept() {
  int addrlen = sizeof(address);
  std::cout << "Waiting for new connection..." << std::endl;
  int socket =
      accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
  if (socket < 0) {
    throw "Socket connect error";
  }

  return socket;
}

char *Server::getIP() const { return ip; }

void Server::Loop() {

  printf("Initializing Server...\n");
  try {
    CreateSocket()
        ->complete()
        ->SetupAddress()
        ->complete()
        ->BindAddress()
        ->complete()
        ->Listen()
        ->complete();

  } catch (const char *e) {
    std::cerr << e << std::endl;
  }

  printf("Server is up on ip:%s\n", ip);

  // wait for clients connection
  std::vector<ClientInfo> client_vec(max_player_count);
  for (int i = 0; i < max_player_count; ++i) {
    ClientInfo p;
    char buf[20];
    memset(buf, 0, 20);
    int new_socket = Accept();
    p.socket_fd = new_socket;
    read(new_socket, buf, 20);
    p.name = std::string(buf);
    client_vec[i] = p;
    printf("Client Connected: \"%s\"\n", buf);
  }

  char *buffer = new char[1024];

  // send init message
  for (int i = 0; i < max_player_count; ++i) {
    ClientInfo &client = client_vec[i];
    // id
    std::string message = "i" + std::to_string(i);

    // every player's name
    for (int j = 0; j < max_player_count; ++j) {

      message += "," + client_vec[j].name;
    }

    // send init message
    write(client.socket_fd, message.c_str(), message.length());
    memset(buffer, 0, 1024);
    read(client.socket_fd, buffer, 1024);
  }

  uno_server_init(max_player_count);

  // in-game loop
  std::cout << "Game started." << std::endl;
  while (true) {
    for (int id = 0; id < client_vec.size(); ++id) {

      // (from uno_server.cpp) get message to client
      char *command = command_to_client(id);

      std::cout << "Command to client(id=" << id
                << ", socket=" << client_vec[id].socket_fd << "):\"" << command
                << "\"" << std::endl;

      // send message to client
      if (send(client_vec[id].socket_fd, command, strlen(command), 0) == -1) {
        throw "Write Error";
      }
    }

    // (from uno_server.cpp) get the target for server to read
    int id = get_current_id();
    if (id == -1) {

      break;
    } else {
      std::cout << "Current id=" << id << std::endl;
      memset(buffer, 0, 1024);

      // read
      if (recv(client_vec[id].socket_fd, buffer, 1024, 0) < 0) {
        throw "Read Error";
      }

      std::cout << "Message from client[id=" << id << "]:" << buffer
                << std::endl;

      // (from uno_server.cpp) deal with the message from client
      handle_client_message(buffer);
    }
  }

  // close connnection
  for (auto &player : client_vec) {
    close(player.socket_fd);
  }
}

void Server::Start() {
  try {
    Loop();
  } catch (const char *err) {
    std::cerr << err << std::endl;
  }
}
