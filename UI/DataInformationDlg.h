#if !defined(AFX_DATAINFORMATION_H__32089DA2_23EA_4637_84C7_2546C3AF9D82__INCLUDED_)
#define AFX_DATAINFORMATION_H__32089DA2_23EA_4637_84C7_2546C3AF9D82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataInformation.h : header file
//
#include "Resource.h"
#include "DataInfoRecordSet.h"

/////////////////////////////////////////////////////////////////////////////
// CDataInformation dialog

class CDataInformationDlg : public CDialog
{
// Construction
public:
	CString m_FieldName;
	short m_symbol;
	short m_FieldPosition;

	CDataInformationDlg(CWnd* pParent = NULL);   // standard constructor
    CDataInformationDlg(CDataInfoRecordSet* pSet,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDataInformation)
	enum { IDD = IDD_DATAINFO };
	CDataInfoRecordSet*	m_pSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataInformation)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataInformation)
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

#endif // !defined(AFX_DATAINFORMATION_H__32089DA2_23EA_4637_84C7_2546C3AF9D82__INCLUDED_)
