#if !defined(AFX_FENGBEISET_H__B7CCE542_2D66_46AD_A5B7_F8ECE0826A0D__INCLUDED_)
#define AFX_FENGBEISET_H__B7CCE542_2D66_46AD_A5B7_F8ECE0826A0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FENGBEISET.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFENGBEISET dialog

class CFENGBEISETDlg : public CDialog
{
// Construction
public:
	CString m_AppearStr[31];
	BOOL    m_Result[31];
	CFENGBEISETDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFENGBEISET)
	enum { IDD = IDD_FENGBEISET };
	CString	m_AppearStrs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFENGBEISET)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFENGBEISET)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton14();
	afx_msg void OnButton19();
	afx_msg void OnButton24();
	afx_msg void OnButton29();
	afx_msg void OnButton34();
	afx_msg void OnButton39();
	afx_msg void OnButton10();
	afx_msg void OnButton15();
	afx_msg void OnButton20();
	afx_msg void OnButton25();
	afx_msg void OnButton30();
	afx_msg void OnButton35();
	afx_msg void OnButton40();
	afx_msg void OnButton11();
	afx_msg void OnButton16();
	afx_msg void OnButton21();
	afx_msg void OnButton26();
	afx_msg void OnButton31();
	afx_msg void OnButton36();
	afx_msg void OnButton41();
	afx_msg void OnButton12();
	afx_msg void OnButton17();
	afx_msg void OnButton22();
	afx_msg void OnButton27();
	afx_msg void OnButton32();
	afx_msg void OnButton37();
	afx_msg void OnButton42();
	afx_msg void OnButton13();
	afx_msg void OnButton18();
	afx_msg void OnButton23();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Refresh();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FENGBEISET_H__B7CCE542_2D66_46AD_A5B7_F8ECE0826A0D__INCLUDED_)
