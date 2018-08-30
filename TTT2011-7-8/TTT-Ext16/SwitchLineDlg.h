#if !defined(AFX_SWITCHLINEDLG_H__CA8D8B46_70B0_49EA_AB20_2835B14AA1A8__INCLUDED_)
#define AFX_SWITCHLINEDLG_H__CA8D8B46_70B0_49EA_AB20_2835B14AA1A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SwitchLineDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSwitchLineDlg dialog

class CSwitchLineDlg : public CDialog
{
// Construction
public:
	CSwitchLineDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSwitchLineDlg)
	enum { IDD = IDD_DIALOG_SWITCHLINE };
	CSpinButtonCtrl	m_SpinButton;
	int		m_iSwitchLine;
	int		m_generatrixno;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchLineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSwitchLineDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHLINEDLG_H__CA8D8B46_70B0_49EA_AB20_2835B14AA1A8__INCLUDED_)
