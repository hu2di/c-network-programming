// FileClient.cpp : Defines the entry point for the console application.
/*
[Ten file][kich thuoc][file][chat][file]...[chat][file]
256        4       xxxx

192.168.43.49:8888
struct PACKET
{
DWORD Type      0-chat,1-Data
DWORD Length	sizeof(Data)
BYTE Data[]		Actual data
}
*/
#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

struct PACKET
{
	DWORD Type;
	DWORD Length;
	BYTE Data[8192];
};

SOCKET client;
DWORD WINAPI ChatThread(LPVOID lParam)
{
	PACKET pk;
	char szXau[1024];
	while (1)
	{
		gets(szXau);
		memset(&pk, 0, sizeof(pk));
		pk.Type = 0;
		pk.Length = strlen(szXau);
		memcpy(pk.Data, szXau, pk.Length);
		send(client,(char*)&pk,8+pk.Length,0);
		if (strncmp(szXau, "bye", 3) == 0) break;
	};
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret;
	ret = WSAStartup(wVersion, &wsaData);
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
	
	CreateThread(0, 0, ChatThread, 0, 0, 0);
	
	//Gui file
	char szBuff[8192];
	PACKET pk;
	while (!feof(fp))
	{
		memset(&pk, 0, sizeof(PACKET));
		ret = fread(szBuff, 1, 8192, fp);
		if (ret > 0)
		{
			pk.Type = 1;
			pk.Length = ret;
			memcpy(pk.Data, szBuff, pk.Length);
			send(client, (char*)&pk, 8 + pk.Length, 0);
		}
	}
	printf("Xong!");
	closesocket(client);
	WSACleanup();
	getch();
	return 0;
}

