// CommLineDlg.h : header file
//

#if !defined(AFX_COMMLINEDLG_H__5C9EDFD2_1E85_4B7D_843A_BF2ADD59E81D__INCLUDED_)
#define AFX_COMMLINEDLG_H__5C9EDFD2_1E85_4B7D_843A_BF2ADD59E81D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCommLineDlg dialog

class CCommLineDlg : public CDialog
{
// Construction
public:
	CCommLineDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCommLineDlg)
	enum { IDD = IDD_COMMLINE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommLineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCommLineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMLINEDLG_H__5C9EDFD2_1E85_4B7D_843A_BF2ADD59E81D__INCLUDED_)
