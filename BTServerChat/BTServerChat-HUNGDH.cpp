// BTServerChat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

SOCKET clients[1024];
int clientCount = 0;

DWORD WINAPI SenderThread(LPVOID lParam)
{
	char szXau[1024];
	while (1)
	{
		gets(szXau);
		strcat(szXau, "\n");
		for (int i = 0; i < clientCount; i++)
			send(clients[i], szXau, strlen(szXau), 0);
	}
	return 0;
}

DWORD WINAPI ReceiverThread(LPVOID lParam)
{
	char szXau[1024];
	int len;
	int i = (int)lParam;
	while (1)
	{
		len = recv(clients[i], szXau, 1024, 0);
		if (len > 0)
		{
			szXau[len] = 0;
			printf("Client %d:%s\n", i, szXau);
		}
		else
		{
			printf("\nClient %d ngat ket noi!\n\n", i);
			closesocket(clients[i]);
			clients[i] = 0;
			break;
		}
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret;
	ret = WSAStartup(wVersion, &wsaData);

	SOCKET server;
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(server, (sockaddr*)&serverAddr, sizeof(serverAddr));

	ret = listen(server, 16);

	SOCKADDR_IN clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	printf("DANG DOI KET NOI TU CLIENT...\n");
	int i = 0;
	while (1)
	{
		for (i = 0; i < clientCount; i++)
		if (clients[i] == 0) break;

		clients[i] = accept(server, (sockaddr*)&clientAddr, &clientAddrLen);
		printf("Co ket noi tu %s:%d.Bat dau gui nhan du lieu !Vi tri %d\n",
			inet_ntoa(clientAddr.sin_addr),
			ntohs(clientAddr.sin_port), i);
		CreateThread(0, 0, ReceiverThread, (LPVOID)i, 0, 0);
		if (i == clientCount) clientCount++;
		if (clientCount == 1)
			CreateThread(0, 0, SenderThread, 0, 0, 0);
	}

	closesocket(server);
	WSACleanup();
	return 0;
}

