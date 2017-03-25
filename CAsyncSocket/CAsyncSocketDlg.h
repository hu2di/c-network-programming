// CAsyncSocketDlg.h : header file
//

#pragma once


// CCAsyncSocketDlg dialog
class CCAsyncSocketDlg : public CDialog
{
// Construction
public:
	CCAsyncSocketDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CASYNCSOCKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	CMySocket socket;

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
	afx_msg void OnBnClickedKetnoi();
};
