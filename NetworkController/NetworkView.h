// NetworkView.h : interface of the CNetworkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKVIEW_H__9D13B7B0_F861_48A2_B5EF_171670526DF6__INCLUDED_)
#define AFX_NETWORKVIEW_H__9D13B7B0_F861_48A2_B5EF_171670526DF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum BSELECTED{NewNode, NewLine, RemNode, RemLine, NodeUp, NodeDown,
	           LineUp,  LineDown, HostUp, HostDown, RemHost,
               None};

class CNetworkView : public CFormView
{
	int h1C[2],hC1[2],h2C[2],hC2[2];

protected: // create from serialization only
	CNetworkView();
	DECLARE_DYNCREATE(CNetworkView)

public:
	//{{AFX_DATA(CNetworkView)
	enum { IDD = IDD_NETWORKCONTROLLER_FORM };
	int	m_SelButton;
	//}}AFX_DATA

// Attributes
public:
	CNetworkDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetworkView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnDraw(CDC *pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNetworkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNetworkView)
	afx_msg void OnTest();
	afx_msg void OnNewnode();
	afx_msg void OnNewline();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRun();
	afx_msg void OnRemoveline();
	afx_msg void OnRemovenode();
	afx_msg void OnNodeup();
	afx_msg void OnNodedown();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NetworkView.cpp
inline CNetworkDoc* CNetworkView::GetDocument()
   { return (CNetworkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORKVIEW_H__9D13B7B0_F861_48A2_B5EF_171670526DF6__INCLUDED_)
