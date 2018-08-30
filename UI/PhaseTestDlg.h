//{{AFX_INCLUDES()
#include "sstabctl.h"
//}}AFX_INCLUDES
#if !defined(AFX_PHASETEST_H__B65C8003_8268_46C8_9117_2CB694ECAF18__INCLUDED_)
#define AFX_PHASETEST_H__B65C8003_8268_46C8_9117_2CB694ECAF18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PhaseTest.h : header file
//
#include "resource.h"
#include "MutiTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CPhaseTest dialog

class CPhaseTestDlg : public CDialog
{
// Construction
public:
	short m_kinds;
	CString  m_StrSql;
	CPhaseTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPhaseTest)
	enum { IDD = IDD_PHASETEST };
	int		m_times;
	BOOL	m_nook;
	int		m_radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhaseTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPhaseTest)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHASETEST_H__B65C8003_8268_46C8_9117_2CB694ECAF18__INCLUDED_)
