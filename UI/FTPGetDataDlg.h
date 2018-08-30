#if !defined(AFX_FTPGETDATA_H__0156D92C_2177_4B0C_A48D_C5173A86850C__INCLUDED_)
#define AFX_FTPGETDATA_H__0156D92C_2177_4B0C_A48D_C5173A86850C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FTPGetData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFTPGetData dialog

class CFTPGetDataDlg : public CDialog
{
// Construction
public:
	CFTPGetDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFTPGetData)
	enum { IDD = IDD_FTP };
	int		m_port;
	CString	m_loginname;
	CString	m_password;
	BOOL	m_anomymous;
	int		m_everytimes;
	CString	m_description;
	CString	m_FileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPGetData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFTPGetData)
	afx_msg void OnAnonymous();
	virtual BOOL OnInitDialog();
	afx_msg void OnConnecttest();
	afx_msg void OnSet();
	afx_msg void OnDatarange();
	afx_msg void OnHandset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPGETDATA_H__0156D92C_2177_4B0C_A48D_C5173A86850C__INCLUDED_)
