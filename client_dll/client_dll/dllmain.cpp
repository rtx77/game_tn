#include "pch.h"
#include <stdio.h>

#include <winsock2.h>

#pragma warning(disable : 4996)

DWORD WINAPI thread_client(void* data);

#define buf_size 1024
#define port 1234
#define ip "127.0.0.1"

char buf_1[buf_size] = { 0 };
char buf_2[buf_size] = { 0 };

extern "C" __declspec(dllexport) int __stdcall function(char* str1, char* str2);


void main_dll()
{
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);


    SOCKET s_1 = socket(AF_INET, SOCK_STREAM, 0);
    SOCKET s_2 = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);


    sa.sin_addr.S_un.S_addr = inet_addr(ip);
    connect(s_1, (const sockaddr*)&sa, sizeof(sa));
    connect(s_2, (const sockaddr*)&sa, sizeof(sa));
    HANDLE thread = NULL;
    thread = CreateThread(NULL, 0, thread_client, &s_2, 0, NULL);

    //Основной поток
    while (1) {
        //какое сообщение принимаем
        memset(buf_1, 0, sizeof(buf_1));
        recv(s_1, buf_1, sizeof(buf_1), 0);
    }

}

DWORD WINAPI thread_client(void* data) {
    SOCKET* p = (SOCKET*)data;
    //какое сообщение отправляем
    while (1) {
        send(*p, (const char*)buf_2, sizeof(buf_2), 0);
    }
}

extern "C" __declspec(dllexport) int __stdcall function(char* str1, char* str2) {
    strcpy(buf_1, str1);
    strcpy(buf_2, str2);
    main_dll();
    return 1;
}

