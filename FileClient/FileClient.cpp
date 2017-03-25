// FileClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2,2);
	int			ret;
	ret = WSAStartup(wVersion,&wsaData);
	SOCKET		client;
	client = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	SOCKADDR_IN	serverAddr;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_family = AF_INET;
	ret = connect(client,(sockaddr*)&serverAddr,sizeof(serverAddr));
	// Xy ly loi...
	FILE * fp = fopen("abc.txt","rb");
	if (fp==NULL)
	{
		printf("Khong mo dc file");
		getch();
		return 0;
	};
	fseek(fp,0,SEEK_END);
	int		len = ftell(fp);
	fseek(fp,0,SEEK_SET);
	char szFilename[256];
	strcpy(szFilename,"abc.txt");
	// Gui ten tep tin
	send(client,szFilename,256,0);

	// Gui kich thuoc tep tin
	send(client,(char*)&len,4,0);

	char	szBuff[4096];
	while (!feof(fp))
	{
		ret = fread(szBuff,1,4096,fp);
		if (ret>0)
			send(client,szBuff,ret,0);
	}

	printf("Xong !");
	closesocket(client);
	WSACleanup();
	getch();
	return 0;
}

