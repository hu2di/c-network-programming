// SelectTCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
SOCKET	clients[1023];
int		clientCount = 0;
int		bStop = 0;
DWORD	WINAPI	SenderThread(LPVOID lParam)
{
	char	szXau[1024];
	while (1)
	{
		gets(szXau);
		strcat(szXau,"\n");
		for (int i=0;i<clientCount;i++)
			if (clients[i]!=0)
				send(clients[i],szXau,strlen(szXau),0);
		if (strncmp("quit",szXau,4)==0)
		{
			bStop = 1;
			break;
		}
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//B1: Khoi tao WinSock
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2,2);
	int			ret;
	ret = WSAStartup(wVersion,&wsaData);
	// B2: Tao socket server
	SOCKET	server;
	server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	// B3: Bind
	SOCKADDR_IN	serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(8888);
	ret = bind(server,(sockaddr*)&serverAddr,sizeof(serverAddr));
		// Kiem tra loi...
	// B4: Listen
	ret = listen(server,16);
	
	SOCKADDR_IN	clientAddr;
	int		clientAddrLen = sizeof(clientAddr);
	int		i;
	memset(clients,0,sizeof(SOCKET)*1023);
	// ~ for (int i=0;i<1023;i++) clients[i]=0
	fd_set	readfds;
	char	szXau[1024];
	int		len;
	timeval	timeout;
	while (bStop!=1)
	{
		// Xoa tap readfds
		FD_ZERO(&readfds);
		FD_SET(server,&readfds);	// Cho server vao tap tham do
		for (i=0;i<clientCount;i++)
			if (clients[i]!=0) FD_SET(clients[i],&readfds);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		ret = select(0,&readfds,0,0,&timeout);
		if (ret>0)
		{
			if (FD_ISSET(server,&readfds))	
			{
				for (i=0;i<clientCount;i++) 
					if (clients[i]==0) break;
				clients[i]=accept(server,(sockaddr*)&clientAddr,
									&clientAddrLen);
				printf("Co ket noi moi tu %s:%d, o vi tri %d!\n",
					inet_ntoa(clientAddr.sin_addr),
					ntohs(clientAddr.sin_port),i);
				if (i==clientCount) clientCount++;
				if (clientCount==1)
					CreateThread(0,0,SenderThread,0,0,0);
			};
			for (i=0;i<clientCount;i++)
				if (clients[i]!=0 && 
					FD_ISSET(clients[i],&readfds))
				{
					len = recv(clients[i],szXau,1024,0);
					if (len>0)
					{
						szXau[len] = 0;
						printf("Client %d:%s",i,szXau);
						for (int j=0;j<clientCount;j++)
							if (clients[j]!=0 && i!=j)
								send(clients[j],szXau,len,0);
					}
					else
					{
						printf("Client %d ngat ket noi!\n",i);
						closesocket(clients[i]);
						clients[i] = 0;

					}
				}

		}
		else
			if(ret==0)
			{
				//printf("Khong co su kien nao ca !\n");
			}
	}
	closesocket(server);
	WSACleanup();
	printf("Luong chinh ket thuc !");
	getch();
	return 0;
}

