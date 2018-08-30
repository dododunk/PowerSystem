#if !defined(AFX_REPLACEDATA_H__7DE31B96_4C61_4DFD_89F0_3307D9DE25B8__INCLUDED_)
#define AFX_REPLACEDATA_H__7DE31B96_4C61_4DFD_89F0_3307D9DE25B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplaceData.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CReplaceData dialog
#include "resource.h"
class CReplaceDataDlg : public CDialog
{
// Construction
public:
	CString m_dataname;
	CReplaceDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReplaceData)
	enum { IDD = IDD_REPLDIALOG };
	CComboBox	m_combofield;
	CString	m_value;
	int		m_index;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReplaceData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReplaceData)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void initializeFieldInfo(CString DataName);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLACEDATA_H__7DE31B96_4C61_4DFD_89F0_3307D9DE25B8__INCLUDED_)
