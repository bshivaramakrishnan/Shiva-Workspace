#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Link with Winsock library

int main() {
    // Step 1: Initialize Winsock
    WSADATA wsadata;
    int wsaerr;
    WORD version = MAKEWORD(2, 2);
    wsaerr = WSAStartup(version, &wsadata);
    if (wsaerr != 0) {
        std::cout << "WSAStartup failed with error: " << wsaerr << std::endl;
        return 1;
    }
    std::cout << "WSAStartup() is OK!\n";

    // Step 2: Create a socket
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "Socket creation failed! Error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    std::cout << "Socket() is OK!\n";

    // Step 3: Bind the socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(55555);

    if (bind(serverSocket, reinterpret_cast<SOCKADDR*>(&service), sizeof(service)) == SOCKET_ERROR) {
        std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "bind() is OK!\n";

    // Step 4: Listen for connections
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cout << "listen() failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "listen() is OK. Waiting for connections...\n";

    // Step 5: Accept a connection
    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "accept() failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "Client connected!\n";

    // Step 6: Receive data
    char recvbuf[512];
    int recvResult = recv(clientSocket, recvbuf, sizeof(recvbuf), 0);
    if (recvResult > 0) {
        recvbuf[recvResult] = '\0'; // Null-terminate
        std::cout << "Received: " << recvbuf << std::endl;

        // Step 7: Send a response
        const char* reply = "Hello from server!";
        send(clientSocket, reply, strlen(reply), 0);
    }
    else {
        std::cout << "recv() failed or connection closed.\n";
    }

    // Step 8: Cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    std::cout << "Server shutdown.\n";
    return 0;
}
