// HelloSocket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<WinSock2.h>


int _tmain(int argc, _TCHAR* argv[])
{
	//Khoi tao
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret = 0;
	ret = WSAStartup(wVersion, &wsaData);
	if (ret == SOCKET_ERROR)
		printf("Khoi tao that bai!\n");
	else
		printf("Khoi tao thanh cong!\n");
	//Giai phong winsoc
	ret = WSACleanup();
	if (ret == 0)
		printf("Giai phong thanh cong!\n");
	else
		printf("Giai phong that bai! Ma loi: %d\n", WSAGetLastError());
	_getch();
	return 0;
}

