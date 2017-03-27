// AsyncSelectServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AsyncSelectServer.h"
#include "AsyncSelectServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_SOCKET		WM_USER+1

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAsyncSelectServerDlg dialog




CAsyncSelectServerDlg::CAsyncSelectServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAsyncSelectServerDlg::IDD, pParent)
	, m_szStatus(_T("Server dang tat"))
	, m_szChatText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsyncSelectServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LBSTATUS, m_szStatus);
	DDX_Control(pDX, IDC_CHAT, m_lsHistory);
	DDX_Text(pDX, IDC_TEXT, m_szChatText);
}

BEGIN_MESSAGE_MAP(CAsyncSelectServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTNSTART, &CAsyncSelectServerDlg::OnBnClickedBtnstart)
	ON_BN_CLICKED(IDC_BTNSEND, &CAsyncSelectServerDlg::OnBnClickedBtnsend)
END_MESSAGE_MAP()


// CAsyncSelectServerDlg message handlers

BOOL CAsyncSelectServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	WSADATA		wsaData;
	WORD		wVersion = MAKEWORD(2,2);
	int			ret;
	ret = WSAStartup(wVersion,&wsaData);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAsyncSelectServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAsyncSelectServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAsyncSelectServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAsyncSelectServerDlg::OnBnClickedBtnstart()
{
	// TODO: Add your control notification handler code here
	server  =	socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	SOCKADDR_IN	serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(8888);
	int		ret;
	ret = bind(server,(sockaddr*)&serverAddr,
		sizeof(serverAddr));
	ret = listen(server,16);

	WSAAsyncSelect(server,this->m_hWnd,WM_SOCKET,
		FD_ACCEPT);

	m_szStatus = "Dang doi ket noi o cong 8888...";
	UpdateData(FALSE);

}

LRESULT CAsyncSelectServerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	char	szXau[1024];
	int		len;
	SOCKADDR_IN	clientAddr;
	int			clientAddrLen = sizeof(SOCKADDR_IN);
	switch (message)
	{
	case WM_SOCKET:
		if (WSAGETSELECTERROR(lParam))
		{
			MessageBox("Loi ket noi","Loi",
				MB_ICONERROR);
			closesocket(client);
			m_szStatus = "Dang doi ket noi o cong 8888...";
			UpdateData(FALSE);
			break;
		};
		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_ACCEPT:
			client = accept(server,
				(sockaddr*)&clientAddr,
				&clientAddrLen);
			MessageBox("Co ket noi moi !","Socket",
				MB_ICONINFORMATION);
			m_szStatus = "Client da ket noi !";
			UpdateData(FALSE);
			WSAAsyncSelect(client,this->m_hWnd,
				WM_SOCKET,FD_READ|FD_CLOSE);
			break;
		case FD_READ:
			len = recv(client,szXau,1024,0);
			if (len>0)
			{
				szXau[len] = 0;
				m_lsHistory.AddString(szXau);

			}
		}
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CAsyncSelectServerDlg::OnBnClickedBtnsend()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	send(client,m_szChatText,
		m_szChatText.GetLength(),0);
	m_lsHistory.AddString(m_szChatText);
	m_szChatText = "";
	UpdateData(FALSE);
}
