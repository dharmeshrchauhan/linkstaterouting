// RouterNodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RouterNode.h"
#include "RouterNodeDlg.h"
#include "InputOutput.h"
#include "Neighbourhood.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRouterNodeDlg dialog

CRouterNodeDlg::CRouterNodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRouterNodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRouterNodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	Create(IDD_ROUTERNODE_DIALOG, NULL);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DlgActive = false;
}

void CRouterNodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRouterNodeDlg)
	DDX_Control(pDX, ID_LIST, m_lb);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRouterNodeDlg, CDialog)
	//{{AFX_MSG_MAP(CRouterNodeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_NEIGHBOUR, OnShow)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRouterNodeDlg message handlers

BOOL CRouterNodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_DlgActive = true;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRouterNodeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRouterNodeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}





void CRouterNodeDlg::OnShow() 
{
	// TODO: Add your control notification handler code here
	CString str;
	extern CNeighbourhood Nbr;
	
	m_lb.ResetContent();
	str.Format("%d",Nbr.m_Self);
	SetWindowText(str);
//	MessageBox("self");
//	m_lb.UpdateData(FALSE);
	for(int i=0; i<Nbr.nSize; i++)
	{
		str.Format("%d   %d",i,Nbr.Retrieve(i));
		m_lb.AddString(str);
	//	MessageBox(str);
	//	m_lb.UpdateData(FALSE);

	}

	for(int i=0; i<__argc; i++)
		m_lb.AddString(__argv[i]);
//	m_lb.UpdateData(FALSE);
}

void CRouterNodeDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_DlgActive = false;
	CDialog::PostNcDestroy();
	::PostQuitMessage(0);
}

void CRouterNodeDlg::OnQuit() 
{
	// TODO: Add your control notification handler code here
// AfxMessageBox("Window Destroyed",0,0);
	DestroyWindow();
//	::PostQuitMessage(0);
}
