#include "Server.h"
#include "DatabaseHandler.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <sstream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

Server::Server(int port) : serverPort(port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    DatabaseUtil::Initialize();
    DatabaseUtil::EstablishDBConnection(DatabaseUtil::SERVER_DB_FILE_NAME);
}

void Server::start() {
    if (bind(serverSocket, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << serverPort << "..." << std::endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::thread(&Server::HandleClient, this, clientSocket).detach();
    }
}

void Server::HandleClient(SOCKET clientSocket) {
    char buffer[1024] = { 0 };
    int userId = -1;
    int bytesReceived;

    try {
        // Authentication phase
        std::string prompt = "Authentication\nEnter Username:\n";
        if (send(clientSocket, prompt.c_str(), static_cast<int>(prompt.size()), 0) == SOCKET_ERROR) {
            throw std::runtime_error("Send username prompt failed");
        }

        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) throw std::runtime_error("Username receive failed");
        std::string username(buffer, bytesReceived);
        memset(buffer, 0, sizeof(buffer));

        prompt = "Enter Password:\n";
        if (send(clientSocket, prompt.c_str(), static_cast<int>(prompt.size()), 0) == SOCKET_ERROR) {
            throw std::runtime_error("Send password prompt failed");
        }

        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) throw std::runtime_error("Password receive failed");
        std::string password(buffer, bytesReceived);
        memset(buffer, 0, sizeof(buffer));

        if (!DatabaseUtil::authenticateUser(username, password)) {
            std::string response = "Authentication Failed\n";
            send(clientSocket, response.c_str(), static_cast<int>(response.size()), 0);
            closesocket(clientSocket);
            return;
        }

        std::string response = "Authentication Successful\n";
        if (send(clientSocket, response.c_str(), static_cast<int>(response.size()), 0) == SOCKET_ERROR) {
            throw std::runtime_error("Send auth success failed");
        }

        userId = DatabaseUtil::getUserId(username);

        // Command processing loop
        while (true) {
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0) break;

            std::string command(buffer, bytesReceived);
            if (command.empty()) continue;

            int operation = command[0] - '0';
            std::string filename = command.size() > 2 ? command.substr(2) : "";

            switch (operation) {
            case 1: HandleConfigureBackup(clientSocket, userId, filename); break;
            case 2: HandleListBackups(clientSocket, userId); break;
            case 3: HandleRestoreBackup(clientSocket, userId, filename); break;
            case 4: HandleDeleteBackup(clientSocket, userId, filename); break;
            default: {
                std::string err = "Invalid command\n";
                send(clientSocket, err.c_str(), static_cast<int>(err.size()), 0);
            }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Client handling error: " << e.what() << std::endl;
    }

    closesocket(clientSocket);
}

void Server::HandleConfigureBackup(SOCKET clientSocket, int userId, const std::string& filename) {
    const std::string uploadDir = "uploads";
    if (!CreateDirectoryA(uploadDir.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
        std::string err = "ERROR: Cannot create upload directory.";
        send(clientSocket, err.c_str(), static_cast<int>(err.size()), 0);
        return;
    }

    std::ofstream file(uploadDir + "\\" + filename, std::ios::binary);
    if (!file.is_open()) {
        std::string err = "ERROR: Cannot open file for writing.";
        send(clientSocket, err.c_str(), static_cast<int>(err.size()), 0);
        return;
    }

    char data[1024];
    while (true) {
        int bytes = recv(clientSocket, data, sizeof(data), 0);
        if (bytes <= 0 || (bytes == 3 && strncmp(data, "EOF", 3) == 0)) break;
        file.write(data, bytes);
    }
    file.close();

    std::string filepath = uploadDir + "\\" + filename;
    if (!DatabaseUtil::saveBackupMetadata(userId, filename, filepath)) {
        std::string err = "ERROR: Failed to save backup metadata.";
        send(clientSocket, err.c_str(), static_cast<int>(err.size()), 0);
        return;
    }

    std::string doneMsg = "File uploaded successfully.";
    send(clientSocket, doneMsg.c_str(), static_cast<int>(doneMsg.size()), 0);
    std::cout << "User " << userId << " uploaded: " << filename << std::endl;
}

void Server::HandleListBackups(SOCKET clientSocket, int userId) {
    auto backups = DatabaseUtil::listBackups(userId);
    std::string list;

    for (const auto& backup : backups) {
        list += backup + "\n";
    }

    if (list.empty()) {
        list = "No files available.\n";
    }

    send(clientSocket, list.c_str(), static_cast<int>(list.size()), 0);
}

void Server::HandleDeleteBackup(SOCKET clientSocket, int userId, const std::string& filename) {
    std::string path = "uploads\\" + filename;
    if (remove(path.c_str()) != 0 && errno != ENOENT) {
        std::string err = "ERROR: Cannot delete file.";
        send(clientSocket, err.c_str(), static_cast<int>(err.size()), 0);
        return;
    }

    if (!DatabaseUtil::deleteBackup(userId, filename)) {
        std::string err = "ERROR: Failed to delete backup record.";
        send(clientSocket, err.c_str(), static_cast<int>(err.size()), 0);
        return;
    }

    std::string msg = "File deleted successfully.";
    send(clientSocket, msg.c_str(), static_cast<int>(msg.size()), 0);
    std::cout << "User " << userId << " deleted: " << filename << std::endl;
}

void Server::HandleRestoreBackup(SOCKET clientSocket, int userId, const std::string& filename) {
    std::string filepath = DatabaseUtil::getBackupPath(userId, filename);
    if (filepath.empty()) {
        std::string err = "ERROR: File not found.";
        send(clientSocket, err.c_str(), static_cast<int>(err.size()), 0);
        return;
    }

    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::string err = "ERROR: Cannot open file for reading.";
        send(clientSocket, err.c_str(), static_cast<int>(err.size()), 0);
        return;
    }

    char data[1024];
    while (!file.eof()) {
        file.read(data, sizeof(data));
        int bytes = static_cast<int>(file.gcount());
        if (send(clientSocket, data, bytes, 0) == SOCKET_ERROR) {
            std::cerr << "Send file data failed" << std::endl;
            break;
        }
    }

    // Send EOF marker
    const char* eofMarker = "EOF";
    send(clientSocket, eofMarker, 3, 0);

    file.close();
    std::cout << "User " << userId << " restored: " << filename << std::endl;
}

Server::~Server() {
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
    WSACleanup();
    DatabaseUtil::CloseDBConnection();
}