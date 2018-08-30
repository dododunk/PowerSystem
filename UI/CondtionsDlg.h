#if !defined(AFX_CONDTIONS_H__407765F7_D225_44A9_8D9C_7803D23D7DB7__INCLUDED_)
#define AFX_CONDTIONS_H__407765F7_D225_44A9_8D9C_7803D23D7DB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Condtions.h : header file
#include "BtnST.h"	
#include "resource.h"
#include "MutiTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CCondtions dialog

class CCondtionsDlg : public CDialog
{
// Construction
public:
	BOOL m_PhaseNoKnown;
	BYTE m_NoReadingKinds;
	CString m_GetTimeStr;
	CCondtionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCondtions)
	enum { IDD = IDD_CONDTION };
	CSpinButtonCtrl	m_spin35;
	CSpinButtonCtrl	m_spin34;
	CSpinButtonCtrl	m_spin32;
	int		m_radio1;
	BOOL	m_Check1;
	BOOL	m_ReadLabel;
	int		m_radio2;
	int		m_radio3;
	int		m_readradiokinds;
	BYTE	m_shikedian;
	BYTE	m_readRangle;
	BYTE	m_readtimes;
	BOOL	m_QuickReading;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCondtions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCondtions)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	virtual void OnOK();
	afx_msg void OnHighset();
	afx_msg void OnCheck34();
	afx_msg void OnCheck37();
	afx_msg void OnCheck39();
	afx_msg void OnCheck38();
	afx_msg void OnCheck109();
	afx_msg void OnRadio4();
	afx_msg void OnRadio37();
	afx_msg void OnChangeEdit36();
	afx_msg void OnReadlabel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void IsSelect(int index);
	void initializeListInfo();
//	CButtonST m_OthersButton;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONDTIONS_H__407765F7_D225_44A9_8D9C_7803D23D7DB7__INCLUDED_)
