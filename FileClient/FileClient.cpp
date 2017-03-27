// FileClient.cpp : Defines the entry point for the console application.
/*
Nhập tên file cần gửi: abc.dat
[Tên file][Kích thước][Nội dung]
 256byte     4byte        xxxx
*/
#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret;
	ret = WSAStartup(wVersion, &wsaData);
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN serverAddr;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_family = AF_INET;
	ret = connect(client, (sockaddr*)&serverAddr, sizeof(serverAddr));
	//Xu li loi...
	FILE *fp = fopen("send.mp3", "rb");
	if (fp == NULL)
	{
		printf("Khong mo file");
		getch();
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char szFilename[256];
	strcpy(szFilename, "send.mp3");

	//Gui ten tap tin
	send(client, szFilename, 256, 0);

	//Gui kich thuoc file
	send(client, (char*)&len, 4, 0);

	//Gui file
	char szBuff[8192];
	while (!feof(fp))
	{
		len = fread(szBuff, 1, 8192, fp);
		if (len > 0)
			send(client, szBuff, len, 0);
	}
	printf("Xong!");
	closesocket(client);
	WSACleanup();
	getch();
	return 0;
}

