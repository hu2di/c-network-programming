// AsyncSelectServerDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CAsyncSelectServerDlg dialog
class CAsyncSelectServerDlg : public CDialog
{
// Construction
public:
	SOCKET	server,client;
	CAsyncSelectServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ASYNCSELECTSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


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
	afx_msg void OnBnClickedBtnstart();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	CString m_szStatus;
	CListBox m_lsHistory;
	CString m_szChatText;
	afx_msg void OnBnClickedBtnsend();
};
