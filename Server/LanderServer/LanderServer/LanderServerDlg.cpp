
// LanderServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LanderServer.h"
#include "LanderServerDlg.h"
#include "MainThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "LandGameServer.h"
// CLanderServerDlg dialog




CLanderServerDlg::CLanderServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLanderServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLanderServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLanderServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_WIZNEXT, &CLanderServerDlg::OnBnClickedWiznext)
	ON_BN_CLICKED(IDC_BUTTON2, &CLanderServerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CLanderServerDlg message handlers

BOOL CLanderServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLanderServerDlg::OnPaint()
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
HCURSOR CLanderServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLanderServerDlg::OnBnClickedWiznext()
{
	// TODO:  在此添加控件通知处理程序代码
	CLandGameServer * m_Server = CLandGameServer::getInstance();
	CMainThread::getInstance();
	m_Server->Initialize();
	
}


void CLanderServerDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CLandGameServer * m_server = CLandGameServer::getInstance();
	CMainThread::getInstance()->Terminate();
	m_server->Finalize();
}
