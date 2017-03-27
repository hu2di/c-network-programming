// DNS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<stdio.h>
#include<conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//Khoi tao winsock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret;
	ret = WSAStartup(wVersion, &wsaData);

	//Dien dia chi IP
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.0.1");
	addr.sin_port = htons(80);
	
	//Phan giai ten mien
	addrinfo *pList,*pHead;
	SOCKADDR_IN result;
	
	char tenmien[1024];
	printf("Nhap vao mot ten mien: ");
	scanf("%s", tenmien);
	
	ret = getaddrinfo(tenmien, "http", 0, &pList);
	if (ret == 0) //Thanh cong
	{
		pHead = pList;
		while (pList != 0)
		{
			memcpy(&result, pList->ai_addr, pList->ai_addrlen);
			printf("Dia chi IP:%s Port la:%d\n", 
				inet_ntoa(result.sin_addr), 
				ntohs(result.sin_port));
			pList = pList->ai_next;
		}
		freeaddrinfo(pHead);
	}
	else
		printf("Loi:%d", ret);
	_getch();
	WSACleanup();
	return 0;
}

