// Client.h
#pragma once
#include <string>
#include <WS2tcpip.h>
using namespace std;

class Client {
    std::string serverIP;
    int serverPort;
    SOCKET clientSocket;
    sockaddr_in serverAddr;

public:
    Client(const std::string& ip, int port);
    ~Client();
    void ConnectToServer();
    void Authenticate();
    void ShowMenu();
    void ConfigureBackup();
    void ListBackups();
    void RestoreBackup();
    void DeleteBackup();
};