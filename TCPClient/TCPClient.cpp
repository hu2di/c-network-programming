// TCPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

int _tmain(int argc, _TCHAR* argv[])
{
	// B1: Khoi tao WinSock
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2,2);
	int			ret;
	ret = WSAStartup(wVersion,&wsaData);

	// B2: Tao socket
	SOCKET		client;
	client = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	// B3: Dien dia chi/ten mien
	SOCKADDR_IN	serverAddr;
	char		serverName[1024];
	printf("Nhap vao dia chi server:");
	scanf("%s",serverName);
	// Phan giai ten mien
	addrinfo	* pResult;
	ret = getaddrinfo(serverName,"8888",0,&pResult);
	if (ret != 0) // Loi
	{
		printf("Ten mien khong ton tai !!!");
		goto END;
	};
	// Copy ket qua vao serverAddr
	memcpy(&serverAddr,pResult->ai_addr,
		pResult->ai_addrlen);
	freeaddrinfo(pResult);
	// B4: Ket noi den server
	ret = connect(client,(sockaddr*)&serverAddr,
		sizeof(serverAddr));
	if (ret == SOCKET_ERROR)
	{
		printf("Loi ket noi:%d!!!",WSAGetLastError());
		goto END;
	};
	printf("Da ket noi den server !\n");
	// B6,B7: Gui nhan du lieu 
	char	szXau[1024];
	ret = recv(client,szXau,1024,0);
	if (ret>0)
	{
		szXau[ret] = 0; // Them ky tu NULL vao cuoi xau
		printf("Server:%s\n",szXau);
	};
	while(1)
	{
		printf("Nhap vao mot xau:");
		scanf("%s",szXau);
		send(client,szXau,strlen(szXau),0);
		if (strncmp(szXau,"bye",3)==0)
			break;
		ret = recv(client,szXau,1024,0);
		if (ret > 0)
		{
			szXau[ret] = 0;
			printf("Server:%s",szXau);
		}
	}
	printf("Xong !");
END:
	closesocket(client);
	WSACleanup();
	getch();
	return 0;
}

