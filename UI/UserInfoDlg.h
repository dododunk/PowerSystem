#if !defined(AFX_USERINFO_H__89435EB0_6245_48AF_B625_C559CED3D4AB__INCLUDED_)
#define AFX_USERINFO_H__89435EB0_6245_48AF_B625_C559CED3D4AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserInfo.h : header file
//
#include "Resource.h"
#include "UseInfoRecordSet.h"
#include "BTNST.H"
#include "XPButton.h"

#include "PictureEx.h"	
/////////////////////////////////////////////////////////////////////////////
// CUserInfo dialog

class CUserInfoDlg : public CDialog
{
// Construction
public:
	CString m_FieldName;
	CString m_filtercondtion;
	short m_symbol;
	short m_FieldPosition;
	BOOL m_IfAdding;
	CUserInfoDlg(CWnd* pParent = NULL);   // standard constructor
	CUserInfoDlg(CUseInfoRecordSet* pSet,CWnd* pParent = NULL);
  
// Dialog Data
	//{{AFX_DATA(CUserInfo)
	enum { IDD = IDD_USERINFO };
	CComboBox	m_baklinecombox;
	CComboBox	m_bakmotherline;
	CComboBox	m_ammeter;
	CComboBox	m_linecombox;
	CComboBox	m_motherline;
	CButton	m_cancel;
	CButton	m_searchbrowse;
	CButton	m_savedata;
	CButton	m_previousrecord;
	CButton	m_nextrecord;
	CButton	m_modify;
	CButton	m_lastrecord;
	CButton	m_delrecord;
	CButton	m_addrecord;
	CButton	m_first;
	CPictureEx	m_Picture;
	CEdit	m_moduleno;
	CUseInfoRecordSet*	m_pSet;
	CTime	m_times;
	int		m_radios;
	int		m_ammeterradio;
	int		m_supplykinds;
	int		m_runnings;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInfo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserInfo)
	afx_msg void OnFirstrecord();
	afx_msg void OnPreviousrecord();
	afx_msg void OnNextrecord();
	afx_msg void OnLastrecord();
	afx_msg void OnAddrecord();
	afx_msg void OnDelrecord();
	afx_msg void OnSeachbrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnSavedata();
	afx_msg void OnModify();
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDatacheck();
	afx_msg void OnChangeCompany();
	afx_msg void OnChangePowerstation();
	afx_msg void OnChangeLine();
	afx_msg void OnChangeTransformerno();
	afx_msg void OnChangeModuleno();
	afx_msg void OnRadio14();
	afx_msg void OnRadio16();
	afx_msg void OnRadio15();
	afx_msg void OnChaammeter();
	afx_msg void OnBtsearch();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//初始化电表列表列表
    void  InitializeAmmeterCombo();
	void ShowCombox(BOOL m_IfShow);
	long m_OldModule;
	CDBVariant varCurrentRecord;
	CString   str[10];
	void SetReadOnly(BOOL ISReading);
	BOOL    m_adding;
	BOOL    m_modified;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERINFO_H__89435EB0_6245_48AF_B625_C559CED3D4AB__INCLUDED_)
