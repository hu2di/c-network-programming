// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "CAsyncSocket.h"
#include "MySocket.h"


// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket member functions

void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	char	buffer[1024];
	int		len;
	len = Receive(buffer,1024);

	


	wchar_t	message[1024];
	MultiByteToWideChar(CP_ACP,0,buffer,
		len,message,1024);
	message[len] = 0;

	pWnd->MessageBox(message,L"Server",
		MB_ICONINFORMATION);


	CAsyncSocket::OnReceive(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	pWnd->MessageBox(L"Ket noi bi dong",L"Loi",
		MB_ICONERROR);

	CAsyncSocket::OnClose(nErrorCode);
}
