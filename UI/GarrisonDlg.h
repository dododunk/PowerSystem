#if !defined(AFX_GARRISON_H__1D6F9969_F658_4318_863C_98AC913CC717__INCLUDED_)
#define AFX_GARRISON_H__1D6F9969_F658_4318_863C_98AC913CC717__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Garrison.h : header file
#include "GarrisonRecordSet.h"



#include "IFRMView.h"

/////////////////////////////////////////////////////////////////////////////
// CGarrison dialog

class CGarrisonDlg : public CDialog
{
// Construction
public:
	CString m_FieldName;
	short m_symbol;
	short m_FieldPosition;
	CGarrisonDlg(CWnd* pParent = NULL);   // standard constructor
    CGarrisonDlg(CGarrisonRecordSet* pSet,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGarrison)
	enum { IDD = IDD_GARRISONINFO };
	CGarrisonRecordSet*	m_pSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGarrison)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGarrison)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearch();
	afx_msg void OnFirstrecord();
	afx_msg void OnPreviousrecord();
	afx_msg void OnNextrecord();
	afx_msg void OnLastrecord();
	afx_msg void OnAddrecord();
	afx_msg void OnDelrecord();
	afx_msg void OnSavedata();
	afx_msg void OnModify();
	afx_msg void OnSeachbrowse();
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

#endif // !defined(AFX_GARRISON_H__1D6F9969_F658_4318_863C_98AC913CC717__INCLUDED_)
