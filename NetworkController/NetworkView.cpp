// NetworkView.cpp : implementation of the CNetworkView class
//

#include "stdafx.h"
#include "NetworkController.h"

#include "NetworkDoc.h"
#include "NetworkView.h"
#include "Node.h"
#include "Packet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetworkView

IMPLEMENT_DYNCREATE(CNetworkView, CFormView)

BEGIN_MESSAGE_MAP(CNetworkView, CFormView)
	//{{AFX_MSG_MAP(CNetworkView)
	ON_BN_CLICKED(ID_NEWNODE, OnNewnode)
	ON_BN_CLICKED(ID_NEWLINE, OnNewline)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(ID_RUN, OnRun)
	ON_BN_CLICKED(ID_REMOVELINE, OnRemoveline)
	ON_BN_CLICKED(ID_REMOVENODE, OnRemovenode)
	ON_BN_CLICKED(ID_NODEUP, OnNodeup)
	ON_BN_CLICKED(ID_NODEDOWN, OnNodedown)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetworkView construction/destruction
CNetworkView::CNetworkView()
	: CFormView(CNetworkView::IDD)
{
	//{{AFX_DATA_INIT(CNetworkView)
	m_SelButton = None;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CNetworkView::~CNetworkView()
{
}

void CNetworkView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetworkView)
	DDX_Radio(pDX, ID_NEWNODE, m_SelButton);
	//}}AFX_DATA_MAP
}

BOOL CNetworkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CNetworkView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CNetworkView diagnostics

#ifdef _DEBUG
void CNetworkView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNetworkView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNetworkDoc* CNetworkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNetworkDoc)));
	return (CNetworkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNetworkView message handlers

void CNetworkView::OnTest() 
{

}

void CNetworkView::OnNewnode() 
{
	// TODO: Add your control notification handler code here
	m_SelButton = NewNode;
}

void CNetworkView::OnNewline() 
{
	// TODO: Add your control notification handler code here
	m_SelButton = NewLine;
}

void CNetworkView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CFormView::OnRButtonUp(nFlags, point);
}

void CNetworkView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CNetworkDoc* pDoc = GetDocument();
	
	static CClientDC dc(this);
	
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	static bool nDelLineContinue;
	static bool nNewLineContinue;

	switch(m_SelButton)
	{
	case NewNode : 
		pDoc->m_Network.AddNewNode(point);
		pDoc->UpdateAllViews(NULL);
		
		nDelLineContinue = false;
		nNewLineContinue = false;
		break;

	case RemNode:
		{
			int		   nIndex;
			if( (nIndex = pDoc->m_Network.NodeClicked(point))
				== -1)
			{
				nDelLineContinue = false;
				nNewLineContinue = false;
				break;
			}
			pDoc->m_Network.RemoveNode(nIndex);
			pDoc->UpdateAllViews(NULL);
		}

		nDelLineContinue = false;
		nNewLineContinue = false;
		break;

	case NodeDown:
		{
			int		   nIndex;
			if( (nIndex = pDoc->m_Network.NodeClicked(point))
				== -1)
			{
				nDelLineContinue = false;
				nNewLineContinue = false;
				break;
			}
			pDoc->m_Network.NodeDown(nIndex);
			pDoc->UpdateAllViews(NULL);
		}
		nDelLineContinue = false;
		nNewLineContinue = false;
		break;
	
	case NodeUp:
		{
			int		   nIndex;
			if( (nIndex = pDoc->m_Network.NodeClicked(point))
				== -1)
				break;
			pDoc->m_Network.NodeUp(nIndex);
			pDoc->UpdateAllViews(NULL);
		}
		nDelLineContinue = false;
		nNewLineContinue = false;
		break;
		
	case NewLine :
		{
			static int nPrevIndex;
			int		   nCurIndex;
			
			if( (nCurIndex = pDoc->m_Network.NodeClicked(point))
				== -1)
				break;
			if(nNewLineContinue)
			{
				//dc.LineTo(point);
				pDoc->m_Network.AddNewCommLine(nPrevIndex, nCurIndex);
				pDoc->UpdateAllViews(NULL);
				
				if(nFlags & MK_CONTROL)
					nPrevIndex = nCurIndex;
				else
					nNewLineContinue = false;
			}
			else
			{
				nNewLineContinue = true;
				nPrevIndex = nCurIndex;
			}
		}

		nDelLineContinue = false;
		break;

	case RemLine:
		{
			static int nPrevIndex;
			int		   nCurIndex;
			
			if( (nCurIndex = pDoc->m_Network.NodeClicked(point))
				== -1)
				break;
			if(nDelLineContinue)
			{
				pDoc->m_Network.RemoveLine(nPrevIndex, nCurIndex);
				pDoc->UpdateAllViews(NULL);

				if(nFlags & MK_CONTROL)
					nPrevIndex = nCurIndex;
				else
					nDelLineContinue = false;
			}
			else
			{
				nDelLineContinue = true;
				nPrevIndex = nCurIndex;
			}
		}
		
		nNewLineContinue = false;
		break;

	}

	CFormView::OnLButtonDown(nFlags, point);
}

void CNetworkView::OnDraw(CDC* pDC) 
{
// TODO: Add your specialized code here and/or call the base class
	CNetworkDoc* pDoc = GetDocument();
	CFormView::OnDraw(pDC);

	pDC->SetBkMode(TRANSPARENT);
//	pDC->SelectStockObject(ROP2_BLACK);
	pDoc->m_Network.Draw(pDC);

}

void CNetworkView::OnRun() 
{
	// TODO: Add your control notification handler code here
	CNetworkDoc *pDoc = GetDocument();
	pDoc->m_Network.Run();
}

void CNetworkView::OnRemoveline() 
{
	// TODO: Add your control notification handler code here
	m_SelButton = RemLine;
}

void CNetworkView::OnRemovenode() 
{
	// TODO: Add your control notification handler code here
	m_SelButton = RemNode;
}

void CNetworkView::OnNodeup() 
{
	// TODO: Add your control notification handler code here
	m_SelButton = NodeUp;
}

void CNetworkView::OnNodedown() 
{
	// TODO: Add your control notification handler code here
	m_SelButton = NodeDown;
}

void CNetworkView::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
	int pid1,pid2;

	pid1 = _pipe ( h1C, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid1 != -1);
	pid2 = _pipe ( hC1, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid2 != -1);
	pid1 = _pipe ( h2C, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid1 != -1);
	pid2 = _pipe ( hC2, 10*sizeof(CPacket), _O_BINARY);
	ASSERT(pid2 != -1);

	char** args = new char*[11];
	char temp[30];

	for(unsigned i=0; i<10; i++)
		args[i] = new char[30];

	strcpy(args[0],"C:\\c.exe");

	strcpy(args[1],"0");

	strcpy(args[2],"0");

	strcpy(args[3], itoa(999999, temp, 10));

	strcpy(args[4], itoa(999999, temp, 10));

	strcpy(args[5], itoa(999999,temp, 10));

	strcpy(args[6], itoa(h1C[0], temp, 10));

	strcpy(args[7], itoa(hC1[1],temp, 10));

	strcpy(args[8], itoa(h2C[0], temp, 10));

	strcpy(args[9], itoa(hC2[1],temp, 10));
	
    
	args[10] = NULL;

	int handle = _spawnv(_P_NOWAIT, args[0], args);

	ASSERT(handle != -1);

	for(int i=0; i<11 ; i++)
	{
		delete[] args[i];
	}



}

void CNetworkView::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CPacket p,p1;
	p.m_Type;
	p.m_Source = 999;
	p.m_Dest = 1025;

	write(h1C[1], &p,  sizeof(p));
	read(hC2[0], &p1, sizeof(p1));

	char temp[100];
	AfxMessageBox(itoa(p1.m_Source,temp,10));
	AfxMessageBox(itoa(p1.m_Dest,temp,10));
	
}

void CNetworkView::OnButton3() 
{
	// TODO: Add your control notification handler code here

	DWORD d = GetTickCount();

	char temp[50];
	//MessageBox(itoa(d,temp,10));

	Sleep(1000);

	MessageBox(itoa(GetTickCount() - d, temp, 10));


	
}
