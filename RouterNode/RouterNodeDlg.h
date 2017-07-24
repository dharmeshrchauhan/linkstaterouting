// RouterNodeDlg.h : header file
//

#if !defined(AFX_ROUTERNODEDLG_H__6E1C121D_5CEB_407A_9787_97050817BB40__INCLUDED_)
#define AFX_ROUTERNODEDLG_H__6E1C121D_5CEB_407A_9787_97050817BB40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRouterNodeDlg dialog

class CRouterNodeDlg : public CDialog
{
// Construction
public:
	bool m_DlgActive;
	CRouterNodeDlg(CWnd* pParent = NULL);	// standard constructor
	afx_msg void OnShow();
// Dialog Data
	//{{AFX_DATA(CRouterNodeDlg)
	enum { IDD = IDD_ROUTERNODE_DIALOG };
	CListBox	m_lb;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRouterNodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRouterNodeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUTERNODEDLG_H__6E1C121D_5CEB_407A_9787_97050817BB40__INCLUDED_)
