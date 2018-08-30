#if !defined(AFX_ANGLESET_H__D596C165_0A1F_4DF7_943F_5A915F2D42E1__INCLUDED_)
#define AFX_ANGLESET_H__D596C165_0A1F_4DF7_943F_5A915F2D42E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AngleSet.h : header file
//
#include "WBButton.h"
/////////////////////////////////////////////////////////////////////////////
// CAngleSet dialog

class CAngleSet : public CDialog
{
// Construction
public:
	CAngleSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAngleSet)
	enum { IDD = IDD_PARAMETERSET };
	CSpinButtonCtrl	m_SpinButton;
	CWBButton	m_readanglecd;
	CWBButton	m_readanglec;
	CWBButton	m_readangleb;
	CWBButton	m_readangle;
	CWBButton	m_dangleset;
	CWBButton	m_anglesetc;
	CWBButton	m_anglesetb;
	CWBButton	m_angleseta;
	int		m_Sangle;
	int		m_dangle;
	int		m_SangleB;
	int		m_SangleC;
	int		m_generatrixno;
	int		m_radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAngleSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAngleSet)
	afx_msg void OnAngleset();
	afx_msg void OnDangleset();
	afx_msg void OnReadangle();
	afx_msg void OnAnglesetb();
	afx_msg void OnAnglesetc();
	afx_msg void OnReadangleb();
	afx_msg void OnReadanglec();
	virtual BOOL OnInitDialog();
	afx_msg void OnReadanglecd();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetThreePhaseAngle(short generatrixno,short phase,int angles,BYTE kinds);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANGLESET_H__D596C165_0A1F_4DF7_943F_5A915F2D42E1__INCLUDED_)
