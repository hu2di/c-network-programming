// TCPServer1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//B1 = Khoi tao
	WSADATA	wsaData;
	WORD	wVersion = MAKEWORD(2, 2);
	int		ret = 0;
	ret = WSAStartup(wVersion, &wsaData);

	//B2 - Tao socket
	SOCKET	s;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//B3 - Bind
	SOCKADDR_IN sAddr;
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(8888);
	sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(s, (sockaddr*)&sAddr, sizeof(sAddr));
	if (ret == SOCKET_ERROR)
	{
		printf("Loi bind: %d", WSAGetLastError());
		getch();
		return 0;
	}
	// B4 - Listen
	ret = listen(s, 16);
	if (ret == SOCKET_ERROR)
	{
		printf("Loi listen: %d", WSAGetLastError());
		getch();
		return 0;
	};
	printf("Dang doi ket noi...\n");
	// B5 - Accept
	SOCKET	c;
	SOCKADDR_IN	cAddr;
	int			cAddrLen = sizeof(cAddr);
	c = accept(s, (sockaddr*)&cAddr, &cAddrLen);
	printf("Co ket noi tu: %s:%d\n", inet_ntoa(cAddr.sin_addr),
		ntohs(cAddr.sin_port));

	// B6,B7 - Gui, nhan du lieu
	char	szXau[1024];
	int		len = 0;
	while (1)
	{
		/*
		gets(szXau);
		send(c,szXau,strlen(szXau),0);
		*/
		len = recv(c, szXau, 1024, 0);
		szXau[len] = 0; // Them ky tu NULL
		printf("Client:%s\n", szXau);
	};
	// B8 - closesocket
	closesocket(s);
	closesocket(c);
	// B9 - Giai phong  WinSock
	WSACleanup();
	_getch();

	return 0;
}

