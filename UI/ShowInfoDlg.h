#if !defined(AFX_SHOWINFO_H__314D0EB2_0B97_4DC3_8DA0_196420995039__INCLUDED_)
#define AFX_SHOWINFO_H__314D0EB2_0B97_4DC3_8DA0_196420995039__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowInfo dialog
#include "resource.h"
class CShowInfoDlg : public CDialog
{
// Construction
public:
	CShowInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowInfo)
	enum { IDD = IDD_INFODIALOG };
	CString	m_info;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowInfo)
	afx_msg void OnSavefile();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CheckUseData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWINFO_H__314D0EB2_0B97_4DC3_8DA0_196420995039__INCLUDED_)
