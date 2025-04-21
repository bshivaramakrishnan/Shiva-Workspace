// Server.h
#pragma once
#include <winsock2.h>
#include <string>
#include <sstream>
using namespace std;

class Server {
    int serverPort;
    SOCKET serverSocket;
    sockaddr_in addr;

    void HandleClient(SOCKET clientSocket);
    void HandleConfigureBackup(SOCKET clientSocket, int userId, const std::string& filename);
    void HandleListBackups(SOCKET clientSocket, int userId);
    void HandleRestoreBackup(SOCKET clientSocket, int userId, const std::string& filename);
    void HandleDeleteBackup(SOCKET clientSocket, int userId, const std::string& filename);

public:
    Server(int port);
    ~Server();
    void start();
};