// ChatClientDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CChatClientDlg dialog
class CChatClientDlg : public CDialog
{
// Construction
public:
	CChatClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHATCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	SOCKET	client;
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
	CString m_szChat;
	afx_msg void OnBnClickedConnect();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedSend();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeAdd();
	afx_msg void OnEnChangeNick();
	afx_msg void OnEnChangePort();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnEnChangeHistory();
	afx_msg void OnEnChangeChat();
	CString m_szAddress;
	CString m_szPort;
	CString m_szNickname;
	CString m_szHistory;
	CString m_lstHistory;
	CListBox m_History;
};
