// CSocketClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSocketClient.h"
#include <afxsock.h>
#include <stdio.h>
#include <conio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

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
		CSocket	sClient;
		sClient.Create();
		char * request = "GET / HTTP/1.0\r\nHost:www.google.com\r\n\r\n";
		sClient.Connect(L"www.google.com.vn",80);
		sClient.Send(request,strlen(request));
		char    response[65536];
		int		len = 0;
		len = sClient.Receive(response,65536);
		if (len > 0)
		{
			response[len] = 0;
			printf("%s",response);
			getch();
		}
	}

	return nRetCode;
}
