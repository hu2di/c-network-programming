// FileClientTH.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<winSock2.h>
#include<WS2tcpip.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//B1: Khoi tao winsock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	int ret;
	ret = WSAStartup(wVersion, &wsaData);

	//B2: Tao socket
	SOCKET server;
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//B3: Dien dia chi/ten mien
	SOCKADDR_IN serverAddr;
	char serverName[1024],serverPort[10];
	printf("Nhap vao dia chi server:");
	scanf("%s", serverName);
	printf("\nNhap port:");
	scanf("%s", serverPort);

	//Phan giai ten mien
	addrinfo *pResult;
	ret = getaddrinfo(serverName, serverPort, 0, &pResult);
	if (ret != 0) //Loi
	{
		printf("Ten mien khong ton tai!!!");
		goto END;
	};
	memcpy(&serverAddr, pResult->ai_addr, pResult->ai_addrlen);
	freeaddrinfo(pResult);

	//B4: Ket noi den server
	ret = connect(server, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (ret == SOCKET_ERROR)
	{
		printf("Loi ket noi: %d!!!", WSAGetLastError());
		goto END;
	};
	printf("Da ket noi den server !\n");

	//Yeu cau tai file
	char filename[128],str[128];
	printf("Nhap ten file:");
	scanf("%s",filename);
	sprintf(str,"GET %s\n",filename);
	send(server, str, strlen(str), 0);
	char response[1024];
	int len = 0;
	while (1)
	{
		ret = recv(server, response + len, 1, 0);
		if (ret <= 0) break;
		len = len + ret;
		if (response[len - 1] == '\n')
		{
			response[len - 1] = 0;
			break;
		}
	}
	char kiemtra[10];
	strncpy(kiemtra,response,6);
	if (strcmp(kiemtra, "FALSE ") == 0) //Server tra ve false
	{
		char reason[1024];
		strcpy(reason,response+6);
		printf("%s", reason);
		goto END;
	}
	else //Server tra ve OK
	{
		char fsize[1024];
		strcpy(fsize,response + 3);
		int filesize = int(fsize);
		printf("Bat dau nhan file: %s, kich thuoc %d byte\n", filename, filesize);
		FILE *fp = fopen(filename, "wb");
		char buffer[8192];
		int bytesreceived = 0;
		while (bytesreceived < filesize)
		{
			len = recv(server, buffer, 8192, 0);
			if (len>0)
			{
				bytesreceived = bytesreceived + len;
				fwrite(buffer, 1, len, fp);
				printf(".");
			}
		};
		fclose(fp);
		printf("Xong!\n");
	}
	
	END:
	closesocket(server);
	WSACleanup();
	system("pause");
	return 0;
}
