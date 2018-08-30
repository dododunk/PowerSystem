#if !defined(AFX_TIMEDLG_H__71557F30_D868_4B41_9ABD_08BCA0A06D0E__INCLUDED_)
#define AFX_TIMEDLG_H__71557F30_D868_4B41_9ABD_08BCA0A06D0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TIMEDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTIMEDLG dialog

class CTIMEDlg : public CDialog
{
// Construction
public:
	CTIMEDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTIMEDLG)
	enum { IDD = IDD_DIALOGTIME };
	int		m_seconds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTIMEDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTIMEDLG)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEDLG_H__71557F30_D868_4B41_9ABD_08BCA0A06D0E__INCLUDED_)
