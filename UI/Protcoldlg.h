#if !defined(AFX_PROTCOLDLG_H__AFEB3581_4B29_411A_A922_5D7F82098B7E__INCLUDED_)
#define AFX_PROTCOLDLG_H__AFEB3581_4B29_411A_A922_5D7F82098B7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Protcoldlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CProtcoldlg dialog

class CProtcoldlg : public CDialog
{
// Construction
public:
	BYTE m_kinds;
	short m_protcol;
	CProtcoldlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProtcoldlg)
	enum { IDD = IDD_PROTCOL };
	CComboBox	m_moduleline;
	CComboBox	m_motherline;
	CComboBox	m_comboprotcol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtcoldlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProtcoldlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSsetmother();
	afx_msg void OnSetline();
	afx_msg void OnModifyprotcol();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTCOLDLG_H__AFEB3581_4B29_411A_A922_5D7F82098B7E__INCLUDED_)
