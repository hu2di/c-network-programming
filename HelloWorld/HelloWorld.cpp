// HelloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2,2);
	int			ret = 0;
	SOCKET s1,s2;

	ret = WSAStartup(wVersion,&wsaData);
	if (ret==SOCKET_ERROR)
		printf("Khoi tao that bai !\n");
	else
		printf("Khoi tao thanh cong !\n");
		
	// Tao socket TCP
	s1 = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	// Tao socket UDP
	s2 = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	ret = WSACleanup();
	if (ret==SOCKET_ERROR)
		printf("Giai phong that bai. Ma loi:%d !\n",
							WSAGetLastError());
	else
		printf("Giai phong thanh cong !\n");

	getch();
	return 0;
}

