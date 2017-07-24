// NetworkDoc.h : interface of the CNetworkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKDOC_H__EBDC67BF_D8CC_4FA1_930C_6E347F95F1D7__INCLUDED_)
#define AFX_NETWORKDOC_H__EBDC67BF_D8CC_4FA1_930C_6E347F95F1D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Node.h"

class CNetworkDoc : public CDocument
{

protected: // create from serialization only
	CNetworkDoc();
	DECLARE_DYNCREATE(CNetworkDoc)

// Attributes
public:
	CNetwork m_Network;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetworkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNetworkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNetworkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORKDOC_H__EBDC67BF_D8CC_4FA1_930C_6E347F95F1D7__INCLUDED_)
