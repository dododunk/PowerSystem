#if !defined(AFX_PARAMETER_H__CFED28F6_9574_4B1A_8BE8_40792C05652A__INCLUDED_)
#define AFX_PARAMETER_H__CFED28F6_9574_4B1A_8BE8_40792C05652A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Parameter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParameter dialog
#include "Resource.h"
class CParameterDlg : public CDialog
{
// Construction
public:
	CParameterDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParameter)
	enum { IDD = IDD_PARAMETER };
	BOOL	m_parameter1;
	BOOL	m_parameter2;
	BOOL	m_parameter3;
	BOOL	m_parameter4;
	BOOL	m_parameter5;
	BOOL	m_parameter6;
	BOOL	m_parameter7;
	BOOL	m_parameter8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParameter)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETER_H__CFED28F6_9574_4B1A_8BE8_40792C05652A__INCLUDED_)
