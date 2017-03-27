// TCPServerTH.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//Khoi tao Winsock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret = 0;
	ret = WSAStartup(wVersion, &wsaData);

	//Tao socket TCPServer
	SOCKET server;
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//Bind
	SOCKADDR_IN serverAddr;
	int P;
	printf("Nhap cong: ");
	scanf("%d", &P);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(P);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(server, (sockaddr*)&serverAddr,
		sizeof(serverAddr));
	if (ret == SOCKET_ERROR)
		printf("Loi bind: %d", WSAGetLastError());
	else
		printf("Dang doi ket noi o cong %d...\n", ntohs(serverAddr.sin_port));
	
	//Listen
	ret = listen(server, 16);
	
	// B5: Chap nhan ket noi
	SOCKET	client;
	SOCKADDR_IN	clientAddr;
	int			clientAddrLen = sizeof(clientAddr);
	client = accept(server, (sockaddr*)&clientAddr,
		&clientAddrLen);

	printf("Co ket noi moi tu: %s:%d !\n",
		inet_ntoa(clientAddr.sin_addr),
		ntohs(clientAddr.sin_port));
	// B6: Gui du lieu
	char * chao = "Hello Network Programming";
	ret = send(client, chao, strlen(chao), 0);
	printf("Da gui %d byte.Dang doi du lieu...\n",
		ret);
	// B7: Nhan du lieu
	char   buf[1024];
	ret = recv(client, buf, 1024, 0);
	if (ret>0)
	{
		buf[ret] = 0;  // Them ky tu NULL vao cuoi xau
		printf("Da nhan %d byte. Noi dung:%s", ret,
			buf);
	}

	// B8: Dong socket
	closesocket(server);
	closesocket(client);
	// B9: Giai phong WinSock
	WSACleanup();
	getch();
	return 0;
}

