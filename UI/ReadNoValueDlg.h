#if !defined(AFX_READNOVALUEDLG_H__CF8F5B68_5D19_4792_A8DC_CC2D44652474__INCLUDED_)
#define AFX_READNOVALUEDLG_H__CF8F5B68_5D19_4792_A8DC_CC2D44652474__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReadNoValueDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReadNoValueDlg dialog
#include "resource.h"
class CReadNoValueDlg : public CDialog
{
// Construction
public:
	CReadNoValueDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReadNoValueDlg)
	enum { IDD = IDD_READNOVALUE };
	int		m_radio;
	BOOL	m_PhaseNoKnown;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadNoValueDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReadNoValueDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READNOVALUEDLG_H__CF8F5B68_5D19_4792_A8DC_CC2D44652474__INCLUDED_)
