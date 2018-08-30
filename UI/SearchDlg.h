//{{AFX_INCLUDES()
//#include "rdc.h"
//#include "msdgridctrl.h"
//}}AFX_INCLUDES
#if !defined(AFX_SEARCH_H__4DC5C1B2_3CD8_4A63_BC74_9CD5DC0B3CA1__INCLUDED_)
#define AFX_SEARCH_H__4DC5C1B2_3CD8_4A63_BC74_9CD5DC0B3CA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchDlg.h : header file
//
#include "resource.h"
#include "ExpandingDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CSearch dialog

class CSearchDlg : public CExpandingDlg
{
// Construction
public:
	BOOL m_showbuttons;
	BOOL m_modified;
	CString m_GetSqlStr;
	void SetDataBaseName(CString name);
	CSearchDlg(CWnd* pParent = NULL);   // standard constructor
	void initializeFieldInfo(CString DataName);
// Dialog Data
	//{{AFX_DATA(CSearch)
	enum { IDD = IDD_SEARCH };
	CButton	m_ok;
  	CButton	m_send;
	CButton	m_search;
	CButton	m_clear;
	CButton	m_addto;
	CButton	m_writetotxt;
	CButton	m_writetoexcel;
	CButton	m_replace;
	CButton	m_getfrom;
	CButton	m_delete;
	CButton	m_cancel;
	CComboBox	m_operate;
	CComboBox	m_CombDataInfo;
	CRdc	m_remotedatactrl;
	CMsDgridCtrl	m_dbgrid;
	int		m_radio;
	CString	m_dividsql;
	CString	m_totalsql;
	int		m_FieldPositionm;
	int		m_symbol;
	CString	m_FieldName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearch)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSearch();
	afx_msg void OnSend();
	afx_msg void OnAddto();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnClear();
	afx_msg void OnDelete();
	afx_msg void OnReplace();
	
	
	afx_msg void OnGetfrom();
	afx_msg void OnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString EnglishToChineseStr();
	CString m_dataname;//数据表名

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCH_H__4DC5C1B2_3CD8_4A63_BC74_9CD5DC0B3CA1__INCLUDED_)
