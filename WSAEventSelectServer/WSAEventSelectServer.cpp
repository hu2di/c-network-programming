// WSAEventSelectServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<WS2tcpip.h>
#include<WinSock2.h>



int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret;
	ret = WSAStartup(wVersion, &wsaData);

	SOCKET server;
	SOCKET clients[1024];
	memset(clients, 0, 1024 * sizeof(SOCKET));
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	clients[0] = server;
	int nClient = 1;

	WSAEVENT events[1024];
	memset(events, 0, 1024 * sizeof(WSAEVENT));
	events[0] = WSACreateEvent();//Doi tuong su kien cho server

	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	ret = bind(server, (sockaddr*)&serverAddr, sizeof(serverAddr));
	WSAEventSelect(server, events[0], FD_ACCEPT);
	ret = listen(server, 16);

	char szXau[1024];
	int i,index,len = 0;
	WSANETWORKEVENTS networkEvents;
	while (1)
	{
		ret = WSAWaitForMultipleEvents(nClient,events,FALSE,WSA_INFINITE,FALSE);
		if (ret == WSA_WAIT_FAILED)
		{
			printf("Loi WSAWaitForMultipleEvents !!!");
			break;
		}
		index = ret - WSA_WAIT_EVENT_0;
		for (i = index; i < nClient; i++)
		{
			ret = WSAWaitForMultipleEvents(1, &events[i], TRUE, 1, FALSE);
			if (ret == WSA_WAIT_FAILED || ret == WSA_WAIT_TIMEOUT) continue;
			WSAEnumNetworkEvents(clients[i], events[i], &networkEvents);
			WSAResetEvent(events[i]);
			if (networkEvents.lNetworkEvents & FD_ACCEPT)
			{
				//Su kien ACCEPT
				if (networkEvents.iErrorCode[FD_ACCEPT_BIT]!=0)
					printf("Accept that bai!");
				else
				{
					SOCKADDR_IN clientAddr;
					int clientAddrLen = sizeof(clientAddr);
					clients[nClient] = accept(server, (sockaddr*)&clientAddr, &clientAddrLen);
					events[nClient] = WSACreateEvent();
					WSAEventSelect(clients[nClient], events[nClient], FD_READ | FD_CLOSE);
					nClient++;
					printf("Client %d vua ket noi!\n", nClient);
					nClient++;
				}
			}
			if (networkEvents.lNetworkEvents&FD_READ)
			{
				if (networkEvents.iErrorCode[FD_READ_BIT] != 0)
				{
					printf("Loi FD_READ!\n");
					continue;
				}
				len = recv(clients[i], szXau, 1024, 0);
				if (len > 0)
				{
					szXau[len] = 0;
					printf("Client %d:%s", i, szXau);
				}
			}
			if (networkEvents.lNetworkEvents & FD_CLOSE)
			{
				if (networkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
					printf("Loi FD_CLOSE %d", networkEvents.iErrorCode[FD_CLOSE_BIT]);
				closesocket(clients[i]);
				WSACloseEvent(events[i]);
				clients[i] = 0;
				events[i] = 0;

				for (int j = i; j < nClient - 1; j++)
				{
					clients[j] = clients[j + 1];
					events[j] = events[j + 1];
				}
				nClient--;
			}
		}
	}
	_getch();
	return 0;
}

