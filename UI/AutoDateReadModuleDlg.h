//{{AFX_INCLUDES()
#include "sstabctl.h"
//}}AFX_INCLUDES
#if !defined(AFX_AUTODATEREADMODULE_H__3FF169CC_ACBE_4A21_8FE6_A887FA85C696__INCLUDED_)
#define AFX_AUTODATEREADMODULE_H__3FF169CC_ACBE_4A21_8FE6_A887FA85C696__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoDateReadModule.h : header file
//
#include "resource.h"
#include "PictureEx.h"
#include "Label.h"
/////////////////////////////////////////////////////////////////////////////
// CAutoDateReadModule dialog

class CAutoDateReadModuleDlg : public CDialog
{
// Construction
public:
	CString m_String[3];
	CAutoDateReadModuleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAutoDateReadModule)
	enum { IDD = IDD_DATE_SELECT };
	CSpinButtonCtrl	m_SpinScans;
	CSpinButtonCtrl	m_SpinScan;
	CSpinButtonCtrl	m_spin;
	CString	m_str;
	int		m_radio;
	int		m_radio1;
	int		m_radio2;
	BOOL	m_check1;
	BOOL	m_check2;
	BOOL	m_check3;
	BOOL	m_check4;
	BOOL	m_check5;
	BOOL	m_check6;
	BOOL	m_check7;
	BOOL	m_check8;
	BOOL	m_check9;
	BOOL	m_check10;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoDateReadModule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAutoDateReadModule)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSet();
	afx_msg void OnCancelset();
	virtual void OnCancel();
	afx_msg void OnAllset();
	afx_msg void OnAllclear();
	afx_msg void OnOk1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//初始化参数
    void InitializeParameter();
	void ShowButton(short kinds);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTODATEREADMODULE_H__3FF169CC_ACBE_4A21_8FE6_A887FA85C696__INCLUDED_)
