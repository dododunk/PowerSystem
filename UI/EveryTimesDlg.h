#if !defined(AFX_EVERYTIMES_H__0C2FA6A7_7879_4C28_9772_7A0217FB7123__INCLUDED_)
#define AFX_EVERYTIMES_H__0C2FA6A7_7879_4C28_9772_7A0217FB7123__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EveryTimes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEveryTimes dialog
#include "resource.h"
class CEveryTimesDlg : public CDialog
{
// Construction
public:
	int m_times;
	int m_every;
	CEveryTimesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEveryTimes)
	enum { IDD = IDD_EVERYTIMES };
	CSpinButtonCtrl	m_SpinEvery;
	CSpinButtonCtrl	m_SpinTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEveryTimes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEveryTimes)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVERYTIMES_H__0C2FA6A7_7879_4C28_9772_7A0217FB7123__INCLUDED_)
