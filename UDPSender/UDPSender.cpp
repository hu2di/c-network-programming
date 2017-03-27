// UDPSender.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

int _tmain(int argc, _TCHAR* argv[])
{
	// khoi tao winsock 
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret;
	ret = WSAStartup(wVersion, &wsaData);

	// khoi tao Socket TCP Server 
	SOCKET sender;
	sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKADDR_IN receiverAddr;
	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(8888);
	receiverAddr.sin_addr.s_addr = inet_addr("192.168.43.49");
	
	char szXau[1024];
	while (1)
	{
		printf("Nhap vao mot xau:");
		gets(szXau);
		strcat(szXau, "\n");
		sendto(sender, szXau, strlen(szXau), 0, (sockaddr*)&receiverAddr, sizeof(receiverAddr));
		if (strncmp(szXau, "bye", 3) == 0) break;
	}
	printf("Xong!");
	closesocket(sender);
	WSACleanup();
	getch();
	return 0;
}

