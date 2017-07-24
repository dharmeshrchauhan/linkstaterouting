// RouterNode.h : main header file for the ROUTERNODE application
//

#if !defined(AFX_ROUTERNODE_H__35982405_DD43_4D14_88DD_ABCF44F3179C__INCLUDED_)
#define AFX_ROUTERNODE_H__35982405_DD43_4D14_88DD_ABCF44F3179C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRouterNodeApp:
// See RouterNode.cpp for the implementation of this class
//

class CRouterNodeApp : public CWinApp
{
public:
	CRouterNodeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRouterNodeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRouterNodeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	afx_msg void thmsgHandler(UINT n, LONG l);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUTERNODE_H__35982405_DD43_4D14_88DD_ABCF44F3179C__INCLUDED_)
