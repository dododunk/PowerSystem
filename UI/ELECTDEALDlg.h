#if !defined(AFX_ELECTDEAL_H__E70EE5D6_8E6F_4E72_A00C_92DCDF28233E__INCLUDED_)
#define AFX_ELECTDEAL_H__E70EE5D6_8E6F_4E72_A00C_92DCDF28233E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ELECTDEAL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CELECTDEAL dialog
#include "resource.h"
class CELECTDEALDlg : public CDialog
{
// Construction
public:
	CELECTDEALDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CELECTDEAL)
	enum { IDD = IDD_SENDORSTOP };
	int		m_radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CELECTDEAL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CELECTDEAL)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELECTDEAL_H__E70EE5D6_8E6F_4E72_A00C_92DCDF28233E__INCLUDED_)
