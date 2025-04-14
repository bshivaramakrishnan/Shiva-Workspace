#include <iostream>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

void receiveMessages(SOCKET socket) {
    char buffer[512];
    while (true) {
        int bytes = recv(socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        cout << "\n[Server]: " << buffer << endl;
        cout << "[Client]: ";
        cout.flush();
    }
    cout << "\nServer disconnected.\n";
}

void sendMessages(SOCKET socket) {
    char buffer[512];
    while (true) {
        cout << "[Client]: ";
        cin.getline(buffer, sizeof(buffer));
        if (strcmp(buffer, "exit") == 0) break;
        send(socket, buffer, strlen(buffer), 0);
    }
    closesocket(socket);
}


int main() {
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7000);
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0) {
        cerr << "Invalid address or address not supported" << endl;
        WSACleanup();
        return -1;
    }

    const int maxAttempts = 5;
    int attempts = 0;
    bool connected = false;
    SOCKET sock = INVALID_SOCKET;

    while (attempts < maxAttempts && !connected) {
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == INVALID_SOCKET) {
            cout << "socket() failed with error: " << WSAGetLastError() << endl;
            WSACleanup();
            return -1;
        }

        if (connect(sock, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
            cout << "Client: connect() attempt " << (attempts + 1)
                << " failed with error " << WSAGetLastError() << endl;
            closesocket(sock);
            attempts++;
            if (attempts < maxAttempts) {
                cout << "Retrying connection in 2 seconds..." << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
        else {
            connected = true;
            cout << "Client: Connect() is OK!" << endl;
            cout << "Client: Can start sending and receiving data..." << endl;
        }
    }

    if (!connected) {
        cout << "Client: Failed to connect after " << maxAttempts << " attempts." << endl;
        WSACleanup();
        return 0;
    }

    thread receiver(receiveMessages, sock);
    thread sender(sendMessages, sock);

    sender.join();
    receiver.detach();

    WSACleanup();
    return 0;
}
