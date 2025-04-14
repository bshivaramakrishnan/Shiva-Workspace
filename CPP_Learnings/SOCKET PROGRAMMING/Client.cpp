#include <iostream>
#include <thread>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

void receiveMessages(SOCKET socket) {
    char buffer[512];
    while (true) {
        int bytes = recv(socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        std::cout << "\nServer: " << buffer << std::endl;
    }
    std::cout << "Server disconnected.\n";
}

void sendMessages(SOCKET socket) {
    char buffer[512];
    while (true) {
        std::cin.getline(buffer, sizeof(buffer));
        if (strcmp(buffer, "exit") == 0) break;
        send(socket, buffer, strlen(buffer), 0);
    }
    closesocket(socket);
}

int main() {
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (sockaddr*)&addr, sizeof(addr));
    std::cout << "Connected to server!\n";

    std::thread receiver(receiveMessages, sock);
    std::thread sender(sendMessages, sock);

    sender.join();
    receiver.detach();

    WSACleanup();
    return 0;
}
