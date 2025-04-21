// Client.cpp
#include "Client.h"
#include <iostream>
#include <fstream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

Client::Client(const std::string& ip, int port) : serverIP(ip), serverPort(port) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSA Startup Failed";
        exit(1);
    };

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
}

void Client::ConnectToServer() {
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed\n";
        closesocket(clientSocket);
        WSACleanup();
        exit(1);
    }
    std::cout << "Connected to server.\n";
}

void Client::Authenticate() {
    char buffer[1024] = { 0 };

    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << buffer;

    string username;
    getline(std::cin, username);
    send(clientSocket, username.c_str(), username.size(), 0);

    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << buffer;
    string password;
    getline(std::cin, password);
    send(clientSocket, password.c_str(), password.size(), 0);

    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << buffer << std::endl;

    if (string(buffer).find("Failed") != string::npos) {
        closesocket(clientSocket);
        WSACleanup();
        exit(1);
    }
}

void Client::ShowMenu() {
    while (true) {
        cout << "\nFile Backup System\n";
        cout << "1. Configure Backup\n";
        cout << "2. List Backups\n";
        cout << "3. Restore Backup\n";
        cout << "4. Delete Backup\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: ConfigureBackup(); break;
        case 2: ListBackups(); break;
        case 3: RestoreBackup(); break;
        case 4: DeleteBackup(); break;
        case 5: exit(0);
        default: std::cout << "Invalid choice!\n";
        }
    }
}

void Client::ConfigureBackup() {
    cout << "Enter file path to backup: ";
    string filePath;
    getline(cin, filePath);

    std::ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    string filename = filePath.substr(filePath.find_last_of("\\/") + 1);
    string command = "1 " + filename;
    send(clientSocket, command.c_str(), static_cast<int>(command.size()), 0);

    char buffer[1024];
    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        int bytes = static_cast<int>(file.gcount());
        if (send(clientSocket, buffer, bytes, 0) == SOCKET_ERROR) {
            std::cerr << "Failed to send file data.\n";
            file.close();
            return;
        }
    }

    const char* eofMarker = "EOF";
    send(clientSocket, eofMarker, 3, 0);

    file.close();

    memset(buffer, 0, sizeof(buffer));
    int received = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (received > 0) {
        std::cout << string(buffer, received) << endl;
    }
}

void Client::ListBackups() {
    std::string command = "2";
    send(clientSocket, command.c_str(), command.size(), 0);

    char buffer[1024] = { 0 };
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Available backups:\n" << buffer << std::endl;
}

void Client::RestoreBackup() {
    ListBackups();
    std::cout << "Enter filename to restore: ";
    std::string filename;
    std::getline(std::cin, filename);

    std::string command = "3 " + filename;
    send(clientSocket, command.c_str(), command.size(), 0);

    std::cout << "Enter save path (with filename): ";
    std::string savePath;
    std::getline(std::cin, savePath);

    std::ofstream file(savePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error creating file: " << savePath << std::endl;
        return;
    }

    char buffer[1024];
    while (true) {
        int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << "bytes :" << bytes << "Data : " << buffer;
        if (bytes <= 0 || (bytes == 3 && strncmp(buffer, "EOF", 3) == 0)) break;
        file.write(buffer, bytes);
        memset(buffer, '\0', sizeof(buffer));
    }
    file.close();
    std::cout << "File restored successfully to: " << savePath << endl;
}

void Client::DeleteBackup() {
    ListBackups();
    std::cout << "Enter filename to delete: ";
    std::string filename;
    std::getline(std::cin, filename);

    std::string command = "4 " + filename;
    send(clientSocket, command.c_str(), command.size(), 0);

    char buffer[1024] = { 0 };
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Server: " << buffer << std::endl;
}

Client::~Client() {
    closesocket(clientSocket);
    WSACleanup();
}