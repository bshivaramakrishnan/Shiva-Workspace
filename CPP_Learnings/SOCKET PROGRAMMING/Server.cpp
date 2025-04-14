#include <iostream>
#include <thread>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

void receiveMessages(SOCKET clientSocket) {
    char buffer[512];
    while (true) {
        int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        std::cout << "\nClient: " << buffer << std::endl;
    }
    std::cout << "Client disconnected.\n";
}

void sendMessages(SOCKET clientSocket) {
    char buffer[512];
    while (true) {
        std::cin.getline(buffer, sizeof(buffer));
        if (strcmp(buffer, "exit") == 0) break;
        send(clientSocket, buffer, strlen(buffer), 0);
    }
    closesocket(clientSocket);
}

int main() {
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (sockaddr*)&addr, sizeof(addr));
    listen(serverSocket, 1);
    std::cout << "Waiting for connection...\n";

    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    std::cout << "Client connected!\n";

    std::thread receiver(receiveMessages, clientSocket);
    std::thread sender(sendMessages, clientSocket);

    sender.join();
    receiver.detach(); 

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
