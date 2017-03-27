//FileServerTH.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret;

	ret = WSAStartup(wVersion, &wsaData);
	SOCKET server, client;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrLen = sizeof(SOCKADDR_IN);

	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(server, (sockaddr*)&serverAddr, sizeof(serverAddr));
	ret = listen(server, 16);
	printf("Dang doi client...\n");
	client = accept(server, (sockaddr*)&clientAddr, &clientAddrLen);
	printf("Client da ket noi !\n");
	
	//Xu li...
	char answer[1024];
	int len = 0;
	while (1)
	{
		ret = recv(client, answer + len, 1, 0);
		if (ret <= 0) break;
		len = len + ret;
		if (answer[len - 1] == '\n')
		{
			answer[len - 1] = 0;
			break;
		}
	}
	char tenfile[1024];
	char response[1024];
	strcpy(tenfile,answer+3);
	tenfile[strlen(tenfile-1)] = NULL;
	FILE *fp = fopen(tenfile, "rb");
	if (fp == NULL)
	{
		strcpy(response,"FALSE File not found");
		send(client, response, strlen(response), 0);
		printf("Not found\n");
		goto END;
	}
	else
	{
		fseek(fp, 0, SEEK_END);
		int len = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		strcpy(response, "OK ");
		strcat(response, (char*)&len);
		//Gui kich thuoc file
		send(client, response, strlen(response), 0);

		//Gui file
		char szBuff[8192];
		while (!feof(fp))
		{
			len = fread(szBuff, 1, 8192, fp);
			if (len > 0)
				send(client, szBuff, len, 0);
		}
		printf("Xong!");
	}
	END:
	closesocket(client);
	WSACleanup();
	getch();
	return 0;
}

