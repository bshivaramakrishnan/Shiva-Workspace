#include <iostream>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

map<int, int> login;
map<int, string> file;

void saveUserToFile(const string& filename, int id, int pass) {
    ofstream outfile(filename, ios::app);
    string chatFilename = "chat_" + to_string(id) + ".txt";
    outfile << id << " " << pass << " " << chatFilename << "\n";
    login[id] = pass;
    file[id] = chatFilename;
}

void loadUsersFromFile(const string& filename) {
    ifstream infile(filename);
    int id, pass;
    string filenameStr;
    while (infile >> id >> pass >> filenameStr) {
        login[id] = pass;
        file[id] = filenameStr;
    }
}

bool authenticate(int id, int password) {
    auto it = login.find(id);
    return (it != login.end() && it->second == password);
}

void receiveMessages(SOCKET socket, ofstream& filein) {
    char buffer[512];
    while (true) {
        int bytes = recv(socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        cout << "\n[Client]: " << buffer << endl;
        cout << "[Server]: ";
        cout.flush();
        filein << "\n[Client]: " << buffer << endl;
    }
    cout << "\nClient disconnected.\n";
}

void sendMessages(SOCKET socket, ofstream& filein) {
    char buffer[512];
    while (true) {
        cout << "[Server]: ";
        cin.getline(buffer, sizeof(buffer));
        if (strcmp(buffer, "exit") == 0) break;
        send(socket, buffer, strlen(buffer), 0);
        filein << "\n[Server]: " << buffer << endl;
    }
    closesocket(socket);
}

int main() {
    loadUsersFromFile("users.txt");

    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        cout << "WSAStartup failed\n";
        return 1;
    }

    SOCKET serverSocket = INVALID_SOCKET;
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7000);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    const int maxAttempts = 5;
    int attempts = 0;

    while (attempts < maxAttempts) {
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            cout << "socket() failed: " << WSAGetLastError() << endl;
            WSACleanup();
            return 1;
        }

        int enable = 1;
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&enable), sizeof(enable));

        if (bind(serverSocket, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
            cout << "bind() failed (attempt " << (attempts + 1) << "): " << WSAGetLastError() << endl;
            closesocket(serverSocket);
            attempts++;
            this_thread::sleep_for(chrono::seconds(2));
            continue;
        }
        else {
            cout << "bind() is OK!\n";
            break;
        }
    }

    listen(serverSocket, 1);
    cout << "Waiting for connection...\n";

    SOCKET acceptSocket = INVALID_SOCKET;
    acceptSocket = accept(serverSocket, nullptr, nullptr);
    if (acceptSocket == INVALID_SOCKET) {
        cout << "accept() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    cout << "accept() is OK!\n";

    char choice[10] = {};
    send(acceptSocket, "Register User (Y) / Login User (L): ", 40, 0);
    recv(acceptSocket, choice, sizeof(choice) - 1, 0);

    int id = 0, password = 0;
    char buffer[100] = {};

    if (strcmp(choice, "Y") == 0) {
        // Get ID
        send(acceptSocket, "Enter ID: ", 20, 0);
        recv(acceptSocket, buffer, sizeof(buffer) - 1, 0);
        id = atoi(buffer);
        memset(buffer, 0, sizeof(buffer));

        // Get Password
        send(acceptSocket, "Enter Password: ", 20, 0);
        recv(acceptSocket, buffer, sizeof(buffer) - 1, 0);
        password = atoi(buffer);
        memset(buffer, 0, sizeof(buffer));

        // Save user
        saveUserToFile("users.txt", id, password);
        send(acceptSocket, "Registration Successful\n", 30, 0);
    }

    // Login Process
    send(acceptSocket, "User ID: ", 20, 0);
    recv(acceptSocket, buffer, sizeof(buffer) - 1, 0);
    id = atoi(buffer);
    memset(buffer, 0, sizeof(buffer));

    send(acceptSocket, "Password: ", 20, 0);
    recv(acceptSocket, buffer, sizeof(buffer) - 1, 0);
    password = atoi(buffer);
    memset(buffer, 0, sizeof(buffer));

    if (!authenticate(id, password)) {
        send(acceptSocket, "INVALID CREDENTIALS", 25, 0);
    }
    else {
        ofstream chatFile(file[id], ios::app);
        thread receiver(receiveMessages, acceptSocket, ref(chatFile));
        thread sender(sendMessages, acceptSocket, ref(chatFile));

        sender.join();
        receiver.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
