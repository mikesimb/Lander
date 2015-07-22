
// LanderServerDlg.h : header file
//

#pragma once


// CLanderServerDlg dialog
class CLanderServerDlg : public CDialog
{
// Construction
public:
	CLanderServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LANDERSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedWiznext();
	afx_msg void OnBnClickedButton2();
};
