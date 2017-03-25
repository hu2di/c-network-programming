// CSocketServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSocketServer.h"
#include <stdio.h>
#include <conio.h>
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
CSocket		server;
CSocket		* pClients[1024];

int			nClient = 0;

DWORD	WINAPI	ClientThread(LPVOID lParam)
{
	SOCKET i = (SOCKET)lParam;
	char	buffer[1024];
	int		len;
	CSocket socket;
	
	socket.Attach(i);
	

	while (1)
	{
		len = socket.Receive(buffer,1024);
		if (len >0)
		{
			buffer[len] = 0;
			printf("Client :%s",buffer);
		}
		else
		{
			socket.Close();
			//delete pClients[i];
			//pClients[i] = 0;
			printf("Client ngat ket noi !\n");
			break;
		}
	};
	return 0;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		AfxSocketInit();
		
		server.Create(8888);
		//server.Create(8888,SOCK_DGRAM,"0.0.0.0");
		server.Listen();
		int i;
		memset(pClients,0,sizeof(CSocket*)*1024);
		while (1)
		{
			for (i = 0;i<nClient;i++)
				if (pClients[i]==0) break;
			pClients[i] = new CSocket;
			server.Accept(*pClients[i]);
			CreateThread(0,0,ClientThread,
				(LPVOID)pClients[i]->m_hSocket,0,0);
			pClients[i]->Detach();
			delete pClients[i];
			pClients[i] = 0;
			if (i==nClient)
				nClient++;
		}
	
	}

	return nRetCode;
}
