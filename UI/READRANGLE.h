#if !defined(AFX_READRANGLE_H__7A4042B0_4230_4FF2_A5D2_D376D1E07BAF__INCLUDED_)
#define AFX_READRANGLE_H__7A4042B0_4230_4FF2_A5D2_D376D1E07BAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// READRANGLE.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CREADRANGLE dialog

class CREADRANGLEDlg : public CDialog
{
// Construction
public:
	CString m_GetSubRangeStr;
	CString m_ReadRangeStr;
	CString m_AppearStr;
	CString m_GetSubNameStr;
	BYTE m_days;
	CREADRANGLEDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CREADRANGLE)
	enum { IDD = IDD_READRANGLE };
	CSpinButtonCtrl	m_spin;
	int		m_radio1;
	BOOL	m_ISBT;
	int		m_radio3;
	int		m_radio4;
	BOOL	m_Isygdd;
	BOOL	m_Iswgdd;
	BOOL	m_IsSanCurrent;
	BOOL	m_IsSanVoltage;
	BOOL	m_Isjfdd;
	BOOL	m_Isfdd;
	BOOL	m_Ispdd;
	BOOL	m_Isgdd;
	BOOL	m_Isglls;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREADRANGLE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CREADRANGLE)
	afx_msg void OnRadio5();
	afx_msg void OnRadio41();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READRANGLE_H__7A4042B0_4230_4FF2_A5D2_D376D1E07BAF__INCLUDED_)
