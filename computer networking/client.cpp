#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
    {
        std::cout << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) 
    {
        std::cout << "Failed to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8888);

    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (serverAddress.sin_addr.s_addr == INADDR_NONE) 
    {
        std::cout << "Invalid address/Address not supported." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) 
    {
        std::cout << "Connection failed." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::string username, password;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    std::string login = username + " " + password;
    if (send(clientSocket, login.c_str(), login.length(), 0) < 0) {
        std::cout << "Failed to send login information." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    char serverResponse[1024];
    memset(serverResponse, 0, sizeof(serverResponse));
    if (recv(clientSocket, serverResponse, sizeof(serverResponse), 0) < 0) {
        std::cout << "Failed to receive server response." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server response: " << serverResponse << std::endl;

    std::string text;
    std::cout << "Enter text to send: ";
    std::cin.ignore(); 
    std::getline(std::cin, text);

    if (send(clientSocket, text.c_str(), text.length(), 0) < 0) {
        std::cout << "Failed to send text." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    char serverText[1024];
    memset(serverText, 0, sizeof(serverText));
    if (recv(clientSocket, serverText, sizeof(serverText), 0) < 0) {
        std::cout << "Failed to receive server response." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server response: " << serverText << std::endl;

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}