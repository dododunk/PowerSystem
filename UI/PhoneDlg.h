#if !defined(AFX_PHONE_H__1DC570A4_9FC2_4019_9321_E4348C178A6D__INCLUDED_)
#define AFX_PHONE_H__1DC570A4_9FC2_4019_9321_E4348C178A6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Phone.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPhone dialog
#include "resource.h"
class CPhoneDlg : public CDialog
{
// Construction
public:
	CPhoneDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPhone)
	enum { IDD = IDD_TELDIALOG };
	CString	m_address;
	CString	m_phone;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhone)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPhone)
	afx_msg void OnAdd();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHONE_H__1DC570A4_9FC2_4019_9321_E4348C178A6D__INCLUDED_)
