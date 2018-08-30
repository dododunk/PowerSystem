#if !defined(AFX_CHANGEFILEDLG_H__18D7398C_5590_4ED9_8F07_1A1B93E2A7BB__INCLUDED_)
#define AFX_CHANGEFILEDLG_H__18D7398C_5590_4ED9_8F07_1A1B93E2A7BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeFileDlg dialog

class CChangeFileDlg : public CDialog
{
// Construction
public:
	CChangeFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeFileDlg)
	enum { IDD = IDD_CHANGEDIALOG };
	int		m_xishu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeFileDlg)
	afx_msg void OnClose();
	afx_msg void OnSourcefile();
	afx_msg void OnDestfile();
	afx_msg void OnChange();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_Destfile;
	CString m_Sourefile;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEFILEDLG_H__18D7398C_5590_4ED9_8F07_1A1B93E2A7BB__INCLUDED_)
