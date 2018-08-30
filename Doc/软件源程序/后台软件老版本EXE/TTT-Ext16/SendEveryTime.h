#if !defined(AFX_SENDEVERYTIME_H__0F9A62BE_79D6_458D_BE00_1CB788532F62__INCLUDED_)
#define AFX_SENDEVERYTIME_H__0F9A62BE_79D6_458D_BE00_1CB788532F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendEveryTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendEveryTime dialog

class CSendEveryTime : public CDialog
{
// Construction
public:
	CSendEveryTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendEveryTime)
	enum { IDD = IDD_TIMEEVERY };
	int		m_Seconds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendEveryTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendEveryTime)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDEVERYTIME_H__0F9A62BE_79D6_458D_BE00_1CB788532F62__INCLUDED_)
