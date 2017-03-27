
// AsyncSeclectServerDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CAsyncSeclectServerDlg dialog
class CAsyncSeclectServerDlg : public CDialogEx
{
// Construction
public:
	SOCKET server, client;
	CAsyncSeclectServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ASYNCSECLECTSERVER_DIALOG };

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
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	CString m_szStatus;
	CListBox m_lsHistory;
	CString m_szChatText;
	afx_msg void OnBnClickedBtnsend();
};
