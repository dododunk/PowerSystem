#if !defined(AFX_WUGONGDLG_H__F04D10C8_DEFE_4364_AC0D_992F4C831A0E__INCLUDED_)
#define AFX_WUGONGDLG_H__F04D10C8_DEFE_4364_AC0D_992F4C831A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WuGongDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWuGongDlg dialog
#include "resource.h"
class CWuGongDlg : public CDialog
{
// Construction
public:
	
//对应模块的上限下限
    void GetWuGongUpDown();
	CWuGongDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWuGongDlg)
	enum { IDD = IDD_WUGONGDLG };
	int		m_up;
	int		m_down;
	int		m_EveryTimeKinds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWuGongDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWuGongDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WUGONGDLG_H__F04D10C8_DEFE_4364_AC0D_992F4C831A0E__INCLUDED_)
