#if !defined(AFX_AMETTER_H__3EF8AB79_B642_4E01_9543_127EB23F5D2A__INCLUDED_)
#define AFX_AMETTER_H__3EF8AB79_B642_4E01_9543_127EB23F5D2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ametter.h : header file
//
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CAmetter dialog

class CAmetterRecordset;

class CAmetterDlg : public CDialog
{
// Construction
public:
	BOOL m_Enalbed;
	CString m_FieldName;
	short m_symbol;
	short m_FieldPosition;

	CAmetterDlg(CWnd* pParent = NULL);   // standard constructor
 	CAmetterDlg(CAmetterRecordset* pSet,CWnd* pParent = NULL);
  
// Dialog Data
	//{{AFX_DATA(CAmetter)
	enum { IDD = IDD_AMMETTER };
	CAmetterRecordset*	m_pSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAmetter)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAmetter)
	afx_msg void OnFirstrecord();
	afx_msg void OnPreviousrecord();
	afx_msg void OnNextrecord();
	afx_msg void OnLastrecord();
	afx_msg void OnAddrecord();
	afx_msg void OnSavedata();
	afx_msg void OnModify();
	afx_msg void OnDelrecord();
	afx_msg void OnSeachbrowse();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDBVariant varCurrentRecord;
	void SetReadOnly(BOOL ISReading);
	BOOL m_adding;
	BOOL m_modified;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMETTER_H__3EF8AB79_B642_4E01_9543_127EB23F5D2A__INCLUDED_)
