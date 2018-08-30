#if !defined(AFX_TRANSFORMER_H__82DED1E7_D8A0_44CE_81DA_A6A053658A82__INCLUDED_)
#define AFX_TRANSFORMER_H__82DED1E7_D8A0_44CE_81DA_A6A053658A82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Transformer.h : header file
////
#include "resource.h"
#include "TransformRecordset.h"

/////////////////////////////////////////////////////////////////////////////
// CTransformer dialog
class CTransFormRecordset;

class CTransformerDlg : public CDialog
{
// Construction
public:	
	BOOL m_Enalbed;
	short m_FieldPosition;//×Ö¶ÎÃû³ÆÎ»ÖÃ
	short        m_symbol;//·ûºÅ
	CString   m_FieldName;//Öµ 
	BOOL       m_IfAdding;
	CTransformerDlg(CWnd* pParent = NULL);   // standard constructor
   	CTransformerDlg(CTransformRecordset* pSet,CWnd* pParent = NULL);
  	// Dialog Data
	//{{AFX_DATA(CTransformer)
	enum { IDD = IDD_TRANSFORMER };
	CTransformRecordset*	m_pSet;
	CTime	m_times;
	int		m_radios;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformer)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransformer)
	virtual BOOL OnInitDialog();
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
	BOOL m_adding;
	void SetReadOnly(BOOL ISReading);
	BOOL m_modified;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMER_H__82DED1E7_D8A0_44CE_81DA_A6A053658A82__INCLUDED_)
