#include <iostream>
#include <stdio.h>

#include <winsock2.h>

#pragma warning(disable : 4996)

#define buf_size 1024
char buf_1[buf_size] = { 0 };
char buf_2[buf_size] = { 0 };

DWORD WINAPI thread_client(void* data);

int main()
{
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);


    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1234);

    bind(s, (const sockaddr*)&sa, sizeof(sa));
    listen(s, 100);

    SOCKET client_socket_1;
    SOCKET client_socket_2;
    SOCKADDR_IN client_addr;
    int client_addr_size = sizeof(client_addr);

    client_socket_1 = accept(s, (sockaddr*)&client_addr, &client_addr_size);
    client_socket_2 = accept(s, (sockaddr*)&client_addr, &client_addr_size);

    HANDLE thread = NULL;
    thread = CreateThread(NULL, 0, thread_client, &client_socket_2, 0, NULL);

    //Основной поток
    while (1) {
        send(client_socket_1, buf_1, sizeof(buf_1), 0);
    }
    return 0;
}

DWORD WINAPI thread_client(void* data) {
    SOCKET* p = (SOCKET*)data;
    while (1) {
        memset(buf_2, 0, sizeof(buf_2));
        recv(*p, buf_2, sizeof(buf_2), 0);
    }
}