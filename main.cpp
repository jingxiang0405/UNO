#include "client.h"
#include "server.h"
#include <iostream>
#include <thread>
#include <functional>
int main (int argc, char *argv[]) {

    // no parameter
    switch (argc) {
    case 1:
        std::cout << "Please specify program type\n"
                  << "Usage:\n"
                  << "[Execution File] [0(Server), 1(Client), 2(Server&Client)]" << std::endl;
        return -1;

    case 2:
        int programType = atoi(argv[1]);
    
        if (programType == 2) {
            Server s;
            Client c;
            
            s.Spawn().join();
            c.Spawn().join();
        } else if (programType == 1) {
            Client c;
            char* ip = new char[15];
            std::cout << "Server ip address:";
            std::cout.flush();
            std::cin >> ip;
            c.SetServerIP(ip);
            c.Spawn().join();

        } else if (programType == 0) {
            Server s;
            s.Spawn().join();
        }
    }
}
