// OverlappedEvent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2,2);
	int			ret;
	ret = WSAStartup(wVersion,&wsaData);

	SOCKET		s;
	s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	SOCKADDR_IN	serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port   = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = connect(s,(sockaddr*)&serverAddr,
		sizeof(serverAddr));

	if (ret == SOCKET_ERROR)
		return 0;
	OVERLAPPED	overlapped;
	memset(&overlapped,0,sizeof(overlapped));
	WSAEVENT	event = WSACreateEvent();
	overlapped.hEvent = event;

	OVERLAPPED	overlappedSend;
	WSAEVENT	eventSend = WSACreateEvent();

	char	szXau[1024];
	WSABUF  buffer;
	buffer.buf = szXau;
	buffer.len = 1024;
	DWORD	dwByteTransfered = 0;
	DWORD	dwFlags = 0;

	WSABUF	bufferSend;
	bufferSend.buf = "Xin chao !";
	bufferSend.len = strlen(bufferSend.buf);
	DWORD	dwByteSent = 0;
	DWORD	dwFlagsSent = 0;
	while (1)
	{
		dwFlags = 0;
		memset(&overlapped,0,sizeof(overlapped));
		overlapped.hEvent = event;
		ret = WSARecv(s,&buffer,1,&dwByteTransfered,&dwFlags,
			&overlapped,NULL);
		if (ret == SOCKET_ERROR)
		{
			ret = WSAGetLastError();
			if (ret != WSA_IO_PENDING)
			{
				printf("Loi WSARecv !!!");
				break;
			}
		};


		memset(&overlappedSend,0,sizeof(overlappedSend));
		overlappedSend.hEvent = eventSend;
		ret = WSASend(s,&bufferSend,1,&dwByteSent,
			dwFlagsSent,&overlappedSend,0);

		ret = WSAWaitForMultipleEvents(1,&eventSend,TRUE,
			WSA_INFINITE,FALSE);
		if (ret == WSA_WAIT_FAILED)
			break;
		if (ret == WSA_WAIT_TIMEOUT)
			continue;
		ret = WSAGetOverlappedResult(s,&overlappedSend,
			&dwByteSent,FALSE,&dwFlagsSent);
		if (dwByteSent > 0)
			printf("Da gui %d byte !\n",dwByteSent);

		ret = WSAWaitForMultipleEvents(1,&event,TRUE,
			WSA_INFINITE,FALSE);
		if (ret == WSA_WAIT_FAILED)
			break;
		if (ret == WSA_WAIT_TIMEOUT)
			continue;
		WSAGetOverlappedResult(s,&overlapped,&dwByteTransfered,
			FALSE,&dwFlags);
		if (dwByteTransfered > 0)
		{
			szXau[dwByteTransfered] = 0;
			printf("Server:%s\n",szXau);
		};
		WSAResetEvent(event);

	}



	return 0;
}

