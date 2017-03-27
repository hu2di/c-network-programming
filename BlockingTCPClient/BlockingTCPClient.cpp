// BlockingTCPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<winsock2.h>
#include<WS2tcpip.h>

SOCKET client;

DWORD WINAPI ReceiverThread(LPVOID lParameter)
{
	char szXau[1024];
	int len = 0;
	while (1)
	{
		len = recv(client, szXau, 1024, 0);
		if (len > 0)
		{
			szXau[len] = 0;
			printf("Server: %s\n", szXau);
		}
		else
			break;
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
		//B1: Khoi tao winsock
		WSADATA wsaData;
		WORD wVersion = MAKEWORD(2, 2);
		int ret;
		ret = WSAStartup(wVersion, &wsaData);

		//B2: Tao socket
		client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		//B3: Dien dia chi/ten mien
		SOCKADDR_IN serverAddr;
		char serverName[1024];
		printf("Nhap vao dia chi server:");
		scanf("%s", serverName);

		//Phan giai ten mien
		addrinfo *pResult;
		ret = getaddrinfo(serverName, "8888", 0, &pResult);
		if (ret != 0) //Loi
		{
			printf("Ten mien khong ton tai!!!");
			goto END;
		};
		memcpy(&serverAddr, pResult->ai_addr, pResult->ai_addrlen);
		freeaddrinfo(pResult);

		//B4: Ket noi den server
		ret = connect(client, (sockaddr*)&serverAddr, sizeof(serverAddr));
		if (ret == SOCKET_ERROR)
		{
			printf("Loi ket noi: %d!!!", WSAGetLastError());
			goto END;
		};
		printf("Da ket noi den server !\n");

		//B6,B7: Gui nhan du lieu
		//CreateThread(0, 0, ReceiverThread, 0, 0, 0);
		char Xau[1024];
		while (1) 
		{
			gets(Xau);
			send(client, Xau, strlen(Xau), 0);
			CreateThread(0, 0, ReceiverThread, 0, 0, 0);
		}
		
		//B8: Dong ket noi
	END:
	closesocket(client);
	WSACleanup();
	getch();
	return 0;
}

