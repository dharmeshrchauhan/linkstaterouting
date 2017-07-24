// NetworkDoc.cpp : implementation of the CNetworkDoc class
//

#include "stdafx.h"
#include "NetworkController.h"

#include "NetworkDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetworkDoc

IMPLEMENT_DYNCREATE(CNetworkDoc, CDocument)

BEGIN_MESSAGE_MAP(CNetworkDoc, CDocument)
	//{{AFX_MSG_MAP(CNetworkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetworkDoc construction/destruction

CNetworkDoc::CNetworkDoc()
{
	// TODO: add one-time construction code here

}

CNetworkDoc::~CNetworkDoc()
{
}

BOOL CNetworkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNetworkDoc serialization

void CNetworkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNetworkDoc diagnostics

#ifdef _DEBUG
void CNetworkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNetworkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNetworkDoc commands

void CNetworkDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_Network.CloseCommLines();
	CDocument::OnCloseDocument();
}

