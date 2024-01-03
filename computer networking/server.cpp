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

    // �����׽���
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // ���÷���˵�ַ
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // �󶨵�ַ���׽���
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // ��������
    listen(serverSocket, 5);
    std::cout << "Server listening on port 8888..." << std::endl;

    while (true) 
    {
        // ���ܿͻ�������
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);

        // ���յ�¼��Ϣ
        char username[100], password[100];
        recv(clientSocket, username, sizeof(username), 0);
        recv(clientSocket, password, sizeof(password), 0);

        // ��֤�û����
        bool isValidUser = (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0);

        // ������֤������ͻ���
        send(clientSocket, (char*)&isValidUser, sizeof(isValidUser), 0);

        if (!isValidUser) 
        {
            // �ر����Ӳ�������һ��ѭ���ȴ��µĿͻ�������
            closesocket(clientSocket);
            continue;
        }

        std::cout << "User " << username << " logged in." << std::endl;

        // ���տͻ��˷��͵��ı�
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);

        // ���ı�ת��Ϊ��д
        for (int i = 0; i < strlen(buffer); ++i) 
        {
            buffer[i] = toupper(buffer[i]);
        }

        // ����д�ı����ͻؿͻ���
        send(clientSocket, buffer, sizeof(buffer), 0);

        // �ر�����
        closesocket(clientSocket);
        std::cout << "Connection closed with user " << username << std::endl;
    }

    // �رշ�����׽���
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}