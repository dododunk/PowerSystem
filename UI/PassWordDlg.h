#if !defined(AFX_PASSWORD_H__F3F1AD39_CB1E_4747_84D7_09BC2F63587B__INCLUDED_)
#define AFX_PASSWORD_H__F3F1AD39_CB1E_4747_84D7_09BC2F63587B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassWord.h : header file
//
#include "resource.h"
#include "XPButton.h"
#include "HoverEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CPassWord dialog

class CPassWordDlg : public CDialog
{
// Construction
public:
	BOOL  m_SingleBB;
	CPassWordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassWord)
	enum { IDD = IDD_PASSWORD };
	CHoverEdit	m_passok;
	CXPButton	m_stopping;
	CXPButton	m_Cancel;
	CHoverEdit	m_OldPassButton;
	CHoverEdit	m_NewPassButton;
	CXPButton	m_modify;
	CXPButton	m_comein;
	CString	m_newpassword;
	CString	m_oldpassword;
	CString	m_newpassok;
	int		m_userkind;
	int		m_softkind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassWord)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassWord)
	afx_msg void OnComein();
	virtual BOOL OnInitDialog();
	afx_msg void OnModify();
	afx_msg void OnPaint();
	afx_msg void OnStopping();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSelchangeUsecombo();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL ModifyPassword(CString str);
	CStringArray m_RegeditPath;
	CString GetPassword();
	int m_times;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORD_H__F3F1AD39_CB1E_4747_84D7_09BC2F63587B__INCLUDED_)
