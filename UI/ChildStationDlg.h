#if !defined(AFX_CHILDSTATION_H__3603EBFE_72E2_4C3D_ABCC_7AF4817F8A39__INCLUDED_)
#define AFX_CHILDSTATION_H__3603EBFE_72E2_4C3D_ABCC_7AF4817F8A39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildStation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildStation dialog
#include "resource.h"
class CChildStationDlg : public CDialog
{
// Construction
public:
	CChildStationDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChildStation)
	enum { IDD = IDD_CHILDSTATION };
	CListBox	m_ListBox;
	CString	m_AddStation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildStation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChildStation)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetAllStationInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDSTATION_H__3603EBFE_72E2_4C3D_ABCC_7AF4817F8A39__INCLUDED_)
