// FileReceiver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<winSock2.h>
#include<WS2tcpip.h>

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
	char filename[1024];
	int len;
	len = recv(client, filename, 256, MSG_WAITALL);
	int filesize;
	len = recv(client, (char*)&filesize, 4, MSG_WAITALL);
	printf("Bat dau nhan file: %s, kich thuoc %d byte\n", filename, filesize);
	FILE *fp = fopen(filename, "wb");
	char buffer[8192];
	int bytesreceived = 0;
	while (bytesreceived < filesize)
	{
		len = recv(client, buffer, 8192, 0);
		if (len>0)
		{
			bytesreceived = bytesreceived + len;
			fwrite(buffer, 1, len, fp);
			printf(".");
		}
	};
	fclose(fp);
	printf("Xong!\n");
	closesocket(client);
	closesocket(server);
	WSACleanup();
	system("pause");
	return 0;
}

