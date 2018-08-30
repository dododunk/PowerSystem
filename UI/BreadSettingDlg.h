#if !defined(AFX_BREADSETTING_H__125C1B3F_3EEE_440F_8214_CBCFE3BF49FD__INCLUDED_)
#define AFX_BREADSETTING_H__125C1B3F_3EEE_440F_8214_CBCFE3BF49FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BreadSetting.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CBreadSetting dialog
#include "resource.h"
class CBreadSettingDlg : public CDialog
{
// Construction
public:
	CBreadSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBreadSetting)
	enum { IDD = IDD_BREADSETTING };
	int		m_iBroadTimes;
	COleDateTime	m_iBroadTime;
	int		m_minuter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBreadSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBreadSetting)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStop();
	afx_msg void OnPause();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_times;
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BREADSETTING_H__125C1B3F_3EEE_440F_8214_CBCFE3BF49FD__INCLUDED_)
