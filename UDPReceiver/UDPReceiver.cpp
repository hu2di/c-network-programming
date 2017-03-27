// UDPReceiver.cpp : Defines the entry point for the console application.
//

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

	SOCKET receiver;
	receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN receiverAddr, senderAddr;
	int senderAddrLen = sizeof(senderAddr);
	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(8888);
	receiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(receiver, (sockaddr*)&receiverAddr, sizeof(receiverAddr));
	if (ret == SOCKET_ERROR)
	{
		printf("Loi bind %d!!!", WSAGetLastError());
		goto END;
	}

	char szBuffer[1024];
	SOCKADDR_IN senders[1024];
	int i,senderCount = 0;

	while (1)
	{
		ret = recvfrom(receiver, szBuffer, 1024, 0, (sockaddr*)&senderAddr, &senderAddrLen);
		if (ret > 0)
		{
			//
			for (i = 0; i<senderCount; i++)
			if (senders[i].sin_addr.s_addr ==
				senderAddr.sin_addr.s_addr) break;
			if (i == senderCount)
			{
				memcpy(&senders[i], &senderAddr,
					sizeof(senderAddr));
				senderCount++;
			}
			//
			szBuffer[ret] = 0;
			printf("[%s:%d]:%s\n", inet_ntoa(senderAddr.sin_addr), ntohs(senderAddr.sin_port), szBuffer);
			for (i = 0; i< senderCount; i++)
				sendto(receiver, szBuffer, ret, 0,
				(sockaddr*)&senders[i], sizeof(senderAddr));
		}
	};
END:
	closesocket(receiver);
	WSACleanup();
	_getch();
	return 0;
}

