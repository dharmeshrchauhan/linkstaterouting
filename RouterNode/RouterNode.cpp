// RouterNode.cpp : Defines the class behaviors for the application.
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
// CRouterNodeApp

BEGIN_MESSAGE_MAP(CRouterNodeApp, CWinApp)
	//{{AFX_MSG_MAP(CRouterNodeApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_THREAD_MESSAGE(0x1010, thmsgHandler)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRouterNodeApp construction

CRouterNodeApp::CRouterNodeApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRouterNodeApp object

CRouterNodeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRouterNodeApp initialization

BOOL CRouterNodeApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

//	for(int i=0; i<__argc; i++)
//		AfxMessageBox(__argv[i], 0, 0);

	CRouterNodeDlg* pDlg;

	pDlg  = new CRouterNodeDlg;
	m_pMainWnd = pDlg;

	void thread(void* dummy);
	void thread1(void* pDlgbox);
	extern CNeighbourhood Nbr;
	Nbr.InitInstance(__argc,__argv);    //Initializes Nbr with 
	extern CInputOutput IO;
	IO.InitInstance(__argc,__argv);
	_beginthread(thread,0,NULL);
//	AfxMessageBox("After SendHello",0,0);


//	dlg.Create(IDD_ROUTERNODE_DIALOG);
//	while(!dlg.m_DlgActive);
	
//	dlg.OnShow();
	_beginthread(thread1,0,(void*)pDlg);

//	while(dlg.m_DlgActive);
	

//	while(dlg.m_DlgActive)
//	{
//		Nbr.m_evUpdate.Lock();
//		dlg.OnShow();
//	}
	
/*	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
*/
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return TRUE;
}

void thread1(void *pDlgbox)
{
	CRouterNodeDlg * pDlg = (CRouterNodeDlg*)pDlgbox;
	pDlg->OnShow();
	CWinThread * pth = AfxGetThread();
	extern CNeighbourhood Nbr;
	while(1)
	{
		Nbr.m_evUpdate.Lock();
//		pth->SetThreadPriority(THREAD_PRIORITY_HIGHEST);
		pDlg->OnShow();
//		pth->SetThreadPriority(THREAD_PRIORITY_NORMAL);
	}

}

void thread(void *dummy)
{
	extern CInputOutput IO;
	while(1)
	{
		IO.SendHello();
		Sleep(10000);
	}
}

void CRouterNodeApp::thmsgHandler(UINT n, LONG l)
{
	AfxMessageBox("Thread message received", 0,0);
}
