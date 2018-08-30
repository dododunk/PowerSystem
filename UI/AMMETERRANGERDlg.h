#if !defined(AFX_AMMETERRANGER_H__A6883F44_6115_44BF_B6D0_B10B74E3177B__INCLUDED_)
#define AFX_AMMETERRANGER_H__A6883F44_6115_44BF_B6D0_B10B74E3177B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AMMETERRANGER.h : header file
//
#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CAMMETERRANGER dialog

class CAMMETERRANGERDlg : public CDialog
{
// Construction
public:	
	CString m_title;
	CAMMETERRANGERDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAMMETERRANGER)
	enum { IDD = IDD_TIMESELECT };
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
	BOOL	m_check11;
	BOOL	m_check12;
	BOOL	m_check13;
	BOOL	m_check14;
	BOOL	m_check15;
	BOOL	m_check16;
	BOOL	m_check17;
	BOOL	m_check18;
	BOOL	m_check19;
	BOOL	m_check20;
	BOOL	m_check21;
	BOOL	m_check22;
	BOOL	m_check23;
	BOOL	m_check24;
	BOOL	m_check25;
	BOOL	m_check26;
	BOOL	m_check27;
	BOOL	m_check28;
	BOOL	m_check29;
	BOOL	m_check30;
	BOOL	m_check31;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAMMETERRANGER)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAMMETERRANGER)
	afx_msg void OnAllselect();
	afx_msg void OnAllabandon();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMMETERRANGER_H__A6883F44_6115_44BF_B6D0_B10B74E3177B__INCLUDED_)
