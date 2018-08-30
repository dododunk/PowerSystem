#if !defined(AFX_TESTCOMM_H__2218CF1F_23FC_4F2A_94D3_7E797E645C00__INCLUDED_)
#define AFX_TESTCOMM_H__2218CF1F_23FC_4F2A_94D3_7E797E645C00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestComm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestComm dialog
#include "Resource.h"
class CTestCommDlg : public CDialog
{
// Construction
public:
	CTestCommDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestComm)
	enum { IDD = IDD_COMMSET };
	BOOL	m_test1;
	BOOL	m_test2;
	BOOL	m_test3;
	BOOL	m_test4;
	int		m_test5;
	int		m_testtimes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestComm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestComm)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCOMM_H__2218CF1F_23FC_4F2A_94D3_7E797E645C00__INCLUDED_)
