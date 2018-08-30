#if !defined(AFX_TIMECHECK_H__CD3BD817_CDC0_41C8_9D7F_8533D3CC7CEE__INCLUDED_)
#define AFX_TIMECHECK_H__CD3BD817_CDC0_41C8_9D7F_8533D3CC7CEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeCheck dialog
#include "resource.h"
class CTimeCheckDlg : public CDialog
{
// Construction
public:
	CTimeCheckDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeCheck)
	enum { IDD = IDD_TIMECHECK };
	COleDateTime	m_localtime;
	COleDateTime	m_othertime;
	CString	m_info;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeCheck)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeCheck)
	afx_msg void OnRefresh();
	afx_msg void OnSetlocal();
	afx_msg void OnOtherset();
	afx_msg void OnOtherrefresh();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMECHECK_H__CD3BD817_CDC0_41C8_9D7F_8533D3CC7CEE__INCLUDED_)
