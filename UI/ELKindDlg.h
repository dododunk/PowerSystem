//{{AFX_INCLUDES()
//#include "rdc.h"
//}}AFX_INCLUDES
#if !defined(AFX_ELKIND_H__471B0229_C026_4033_A477_FC8B1F3115BE__INCLUDED_)
#define AFX_ELKIND_H__471B0229_C026_4033_A477_FC8B1F3115BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ELKind.h : header file
//
#include "resource.h"
#include "PriceSet.h"

/////////////////////////////////////////////////////////////////////////////
// CELKind dialog

class CELKindDlg : public CDialog
{
// Construction
public:
	CString m_FieldName;
	short m_symbol;
	short m_FieldPosition;
	CELKindDlg(CWnd* pParent = NULL);   // standard constructor
	CELKindDlg(CPriceSet* pSet,CWnd* pParent = NULL);
 

// Dialog Data
	//{{AFX_DATA(CELKind)
	enum { IDD = IDD_PRICE };
	CPriceSet*	m_pSet;
	CButton	m_search;
	CButton	m_save;
	CButton	m_modify;
	CButton	m_last;
	CButton	m_cancel;
	CButton	m_previous;
	CButton	m_next;
	CButton	m_delete;
	CButton	m_add;
	CButton	m_first;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CELKind)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CELKind)
	afx_msg void OnAddrecord();
	virtual BOOL OnInitDialog();
	afx_msg void OnFirstrecord();
	afx_msg void OnPreviousrecord();
	afx_msg void OnNextrecord();
	afx_msg void OnLastrecord();
	afx_msg void OnModify();
	afx_msg void OnDelrecord();
	afx_msg void OnSeachbrowse();
	afx_msg void OnSavedata();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDBVariant varCurrentRecord;
	BOOL m_modified;
	BOOL m_adding;
	void SetReadOnly(BOOL ISReading);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELKIND_H__471B0229_C026_4033_A477_FC8B1F3115BE__INCLUDED_)
