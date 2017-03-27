// ChatServerDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CChatServerDlg dialog
class CChatServerDlg : public CDialog
{
// Construction
public:
	CChatServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHATSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	SOCKET	server;
	SOCKET	clients[1024];
	int		nClient;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	CListBox m_lstHistory;
	CString m_szChat;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedStop();
	CString m_szStatus;
};
