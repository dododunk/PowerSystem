#if !defined(AFX_ZHULIUTIMESELECT_H__6C4CE1AE_9B07_45D4_BD57_00E487A5A994__INCLUDED_)
#define AFX_ZHULIUTIMESELECT_H__6C4CE1AE_9B07_45D4_BD57_00E487A5A994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZHULIUTIMESELECT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZHULIUTIMESELECT dialog
#include "resource.h"
class CZHULIUTIMESELECTDlg : public CDialog
{
// Construction
public:
	CZHULIUTIMESELECTDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZHULIUTIMESELECT)
	enum { IDD = IDD_ZHULIUTIMESELECT };
	CSpinButtonCtrl	m_SpinScans;
	CSpinButtonCtrl	m_SpinScan;
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
	BOOL	m_autorun;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZHULIUTIMESELECT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZHULIUTIMESELECT)
	afx_msg void OnAllabandon();
	afx_msg void OnAllselect();
	virtual BOOL OnInitDialog();
	afx_msg void OnTotalset();
	afx_msg void OnFengset();
	afx_msg void OnCheck101();
	afx_msg void OnCheck102();
	afx_msg void OnCheck103();
	afx_msg void OnCheck104();
	afx_msg void OnCheck105();
	afx_msg void OnCheck106();
	afx_msg void OnCheck107();
	afx_msg void OnCheck108();
	afx_msg void OnCheck109();
	afx_msg void OnCheck110();
	afx_msg void OnCheck111();
	afx_msg void OnCheck112();
	afx_msg void OnCheck113();
	afx_msg void OnCheck114();
	afx_msg void OnCheck115();
	afx_msg void OnCheck116();
	afx_msg void OnCheck117();
	afx_msg void OnCheck118();
	afx_msg void OnCheck119();
	afx_msg void OnCheck120();
	afx_msg void OnCheck121();
	afx_msg void OnCheck122();
	afx_msg void OnCheck123();
	afx_msg void OnCheck124();
	afx_msg void OnCheck125();
	afx_msg void OnCheck126();
	afx_msg void OnCheck127();
	afx_msg void OnCheck128();
	afx_msg void OnCheck129();
	afx_msg void OnCheck130();
	afx_msg void OnCheck131();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//初始化参数
    void InitializeParameter();
	CString m_AppearStr;
	void AskOk();
	BOOL m_Result[31];
	BOOL m_CanSelect;
	void CheckStatus();//检查状态
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZHULIUTIMESELECT_H__6C4CE1AE_9B07_45D4_BD57_00E487A5A994__INCLUDED_)
