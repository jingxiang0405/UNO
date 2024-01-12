#include "client.h"
#include "server.h"
#include <functional>
#include <iostream>
#include <thread>

const int PORT = 8080;
int main (int argc, char *argv[]) {

    // username
    std::string name;
    switch (argc) {

    // wrong usage
    case 1:
        std::cout << "Please specify program type\n"
                  << "Usage:\n"
                  << "[Execution File] [0(Server), 1(Client), 2(Server&Client)]" << std::endl;
        return -1;

    case 2:
        int programType = atoi(argv[1]);

        // Server and Client
        if (programType == 2) {
            int player_count;
            std::cout << "Specify player count:" << std::flush;
            std::cin >> player_count;
            Server s(player_count, PORT);
            Client c(PORT);
            c.SetServerIP(s.getIP());
            s.Spawn().join();
            c.Spawn().join();
        }

        // Client only
        else if (programType == 1) {

            char *ip = new char[15];
            std::cout << "Server ip address:";
            std::cout.flush();
            std::cin >> ip;

            Client c(PORT);
            c.SetServerIP(ip);
            c.Spawn().join();
        }
        // Server only
        else if (programType == 0) {
            int player_count;
            std::cout << "Specify player count:" << std::flush;
            std::cin >> player_count;
            Server s(player_count, PORT);
            s.Spawn().join();
        }
    }
}
