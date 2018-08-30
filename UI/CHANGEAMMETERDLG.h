#if !defined(AFX_CHANGEAMMETERDLG_H__256F11A3_3A26_4ECF_B9DE_DB3B6FD308B4__INCLUDED_)
#define AFX_CHANGEAMMETERDLG_H__256F11A3_3A26_4ECF_B9DE_DB3B6FD308B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHANGEAMMETERDLG.h : header file
//
#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// CCHANGEAMMETERDLG dialog
class CCHANGEAMMETERSet;
class CCHANGEAMMETERDlg : public CDialog
{
// Construction
public:	
	CString m_filtercondtion;
	CString m_FieldName;
	short m_symbol;
	short m_FieldPosition;
	CCHANGEAMMETERDlg(CWnd* pParent = NULL);   // standard constructor
	CCHANGEAMMETERDlg(CCHANGEAMMETERSet* pSet,CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CCHANGEAMMETERDLG)
	enum { IDD = IDD_CHANGEAMMETER };
	CCHANGEAMMETERSet*        	  m_pSet;
	CTime                  	 m_times;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHANGEAMMETERDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCHANGEAMMETERDLG)
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
    BOOL 	m_adding   ;
	BOOL    m_modified ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEAMMETERDLG_H__256F11A3_3A26_4ECF_B9DE_DB3B6FD308B4__INCLUDED_)
