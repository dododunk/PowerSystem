#if !defined(AFX_WUGONGSPACE_H__70EDC1C2_01C6_4FB7_B4B1_12F7E108A089__INCLUDED_)
#define AFX_WUGONGSPACE_H__70EDC1C2_01C6_4FB7_B4B1_12F7E108A089__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WuGongSpace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWuGongSpace dialog
#include "resource.h"
class CWuGongSpaceDlg : public CDialog
{
// Construction
public:
	//对应模块的电容器容量
    int GetWuGongSpace(long m_doule);
	CString m_Module;
	CWuGongSpaceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWuGongSpace)
	enum { IDD = IDD_WUGONGSPACE };
	int		m_wgspace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWuGongSpace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWuGongSpace)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeWgspace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WUGONGSPACE_H__70EDC1C2_01C6_4FB7_B4B1_12F7E108A089__INCLUDED_)
