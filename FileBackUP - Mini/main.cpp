// main.cpp
#include "Client.h"
#include "Server.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void runAsServer(int port) {
    std::cout << "Starting in server mode...\n";
    Server server(port);
    server.start();
}

void runAsClient(const std::string& ip, int port) {
    std::cout << "Starting in client mode...\n";
    Client client(ip, port);
    client.ConnectToServer();
    client.Authenticate();
    client.ShowMenu();
}

int main() {
    int moduletype = 0;
    std::string serverIP = "127.0.0.1";
    int port = 54000;

    std::ifstream config("..\\config\\mode.txt");
    if (!config.is_open()) {
        std::cerr << "Error: Could not open config file!\n";
        return 1;
    }

    std::string line;
    while (std::getline(config, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));

            if (key == "moduletype") {
                moduletype = std::stoi(value);
            }
            else if (key == "servertoconnect") {
                serverIP = value;
            }
            else if (key == "port") {
                port = std::stoi(value);
            }
        }
    }

    config.close();

    if (moduletype == 1) {
        runAsServer(port);
    }
    else if (moduletype == 2) {
        runAsClient(serverIP, port);
    }
    else {
        std::cerr << "Invalid moduletype. Use 1 for server or 2 for client.\n";
        return 1;
    }

    return 0;
}