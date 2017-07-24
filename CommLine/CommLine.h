// CommLine.h : main header file for the COMMLINE application
//

#if !defined(AFX_COMMLINE_H__CFFD979D_E896_4DE8_A772_759B4B425126__INCLUDED_)
#define AFX_COMMLINE_H__CFFD979D_E896_4DE8_A772_759B4B425126__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCommLineApp:
// See CommLine.cpp for the implementation of this class
//

class CCommLineApp : public CWinApp
{
public:
	CCommLineApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommLineApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCommLineApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMLINE_H__CFFD979D_E896_4DE8_A772_759B4B425126__INCLUDED_)
