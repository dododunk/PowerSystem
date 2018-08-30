#if !defined(AFX_TIMESELECT_H__DDA88F04_4D1B_4E2E_B53E_216735C68E03__INCLUDED_)
#define AFX_TIMESELECT_H__DDA88F04_4D1B_4E2E_B53E_216735C68E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeSelect dialog
#include "resource.h"
class CTimeSelectDlg : public CDialog
{
// Construction
public:
	CTimeSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeSelect)
	enum { IDD = IDD_TIMEDIALOG };
	CTime	m_Begin;
	CTime	m_End;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeSelect)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESELECT_H__DDA88F04_4D1B_4E2E_B53E_216735C68E03__INCLUDED_)
