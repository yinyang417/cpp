#include <iostream>
#include <cstring>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() 
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[1024];

    // 创建套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 配置服务端地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定地址到套接字
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // 监听连接
    listen(serverSocket, 5);
    std::cout << "Server listening on port 8888..." << std::endl;

    while (true) 
    {
        // 接受客户端连接
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);

        // 接收登录信息
        char username[100], password[100];
        recv(clientSocket, username, sizeof(username), 0);
        recv(clientSocket, password, sizeof(password), 0);

        // 验证用户身份
        bool isValidUser = (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0);

        // 发送验证结果给客户端
        send(clientSocket, (char*)&isValidUser, sizeof(isValidUser), 0);

        if (!isValidUser) 
        {
            // 关闭连接并继续下一个循环等待新的客户端连接
            closesocket(clientSocket);
            continue;
        }

        std::cout << "User " << username << " logged in." << std::endl;

        // 接收客户端发送的文本
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);

        // 将文本转换为大写
        for (int i = 0; i < strlen(buffer); ++i) 
        {
            buffer[i] = toupper(buffer[i]);
        }

        // 将大写文本发送回客户端
        send(clientSocket, buffer, sizeof(buffer), 0);

        // 关闭连接
        closesocket(clientSocket);
        std::cout << "Connection closed with user " << username << std::endl;
    }

    // 关闭服务端套接字
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}