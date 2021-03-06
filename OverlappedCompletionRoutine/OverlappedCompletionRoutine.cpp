// OverlappedCompletionRoutine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>

SOCKET	s;
char	szXau[1024];
WSABUF	buffer;
OVERLAPPED	overlapped;
DWORD	dwByteReceived = 0;
DWORD	dwFlags = 0;


void CALLBACK CompletionRoutine(IN DWORD dwError, 
								IN DWORD cbTransferred, 
								IN LPWSAOVERLAPPED lpOverlapped, 
								IN DWORD dwFlags)
{
	if (dwError != 0||cbTransferred==0) // Xử lý lỗi
	{
		closesocket(s);
		return;
	};
	szXau[cbTransferred] = 0;
	printf("Server:%s",szXau);
	memset(&overlapped,0,sizeof(overlapped));
	dwFlags = 0;
	dwByteReceived = 0;
	WSARecv(s,&buffer,1,&dwByteReceived,&dwFlags,
		&overlapped,CompletionRoutine);

}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2,2);
	int			ret = WSAStartup(wVersion,&wsaData);

	SOCKADDR_IN	serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	ret = connect(s,(sockaddr*)&serverAddr,
		sizeof(serverAddr));
	if (ret == SOCKET_ERROR)
	{
		printf("Loi ket noi !!!");
		return 0;
	};
	memset(&overlapped,0,sizeof(overlapped));
	buffer.buf = szXau;
	buffer.len = 1024;
	ret = WSARecv(s,&buffer,1,&dwByteReceived,&dwFlags,
		&overlapped,
		CompletionRoutine
		);

	while (1) SleepEx(1000,FALSE);
	




	getch();
	return 0;
}

