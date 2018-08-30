#if !defined(AFX_SELECTTABLE_H__A659E80B_77B1_414F_9F7D_CF5A191B82FC__INCLUDED_)
#define AFX_SELECTTABLE_H__A659E80B_77B1_414F_9F7D_CF5A191B82FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectTable.h : header file
//
#include "resource.h"
#include "MutiTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CSelectTable dialog

class CSelectTableDlg : public CDialog
{
// Construction
public:
	short m_selects;
	CString m_StrSql;
	CString Sqlstr;
	CString StrTable;
	CSelectTableDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectTable)
	enum { IDD = IDD_SELECTDATA };
	int		          m_radio1;
	int		          m_radio2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectTable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectTable)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio2();
	virtual void OnOK();
	afx_msg void OnPassout();
	afx_msg void OnClear();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTTABLE_H__A659E80B_77B1_414F_9F7D_CF5A191B82FC__INCLUDED_)
