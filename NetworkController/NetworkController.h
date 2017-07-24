// NetworkController.h : main header file for the NETWORKCONTROLLER application
//

#if !defined(AFX_NETWORKCONTROLLER_H__7AE6A154_83B2_4DF1_91E0_10C4F1FE0868__INCLUDED_)
#define AFX_NETWORKCONTROLLER_H__7AE6A154_83B2_4DF1_91E0_10C4F1FE0868__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetworkApp:
// See NetworkController.cpp for the implementation of this class
//

class CNetworkApp : public CWinApp
{
public:
	CNetworkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetworkApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNetworkApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORKCONTROLLER_H__7AE6A154_83B2_4DF1_91E0_10C4F1FE0868__INCLUDED_)
