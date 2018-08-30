//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_SHOWDATA_H__DB6E2AF2_1D13_4894_A3F6_C5C897F48489__INCLUDED_)
#define AFX_SHOWDATA_H__DB6E2AF2_1D13_4894_A3F6_C5C897F48489__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowData.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CShowData dialog

class CShowDataDlg : public CDialog
{
// Construction
public:
	CString m_TimeRangeStr;
	short m_TableKinds;
	short m_Kinds;
	CString m_TimeRange;
	CString m_Condtion;
	BOOL m_Select[13];
	CShowDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowData)
	enum { IDD = IDD_DATASHOW };
	int		m_radio3;
	CRdc	m_remotedatactrl;
	CMsDgridCtrl	m_dbgrid;
	int		m_radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowData)
	afx_msg void OnDelete();
	virtual BOOL OnInitDialog();
	afx_msg void OnSavedata();
	afx_msg void OnHeadClickDbgrids(short ColIndex);
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio5();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CStringArray   m_NameArray;
	//数据库表转成EXCEL文件
    
	short  whichsel;
	void   Findnoreadmodule(short kinds);
	//CString   m_SelectStr  用户数据选择范围 
	//CString   m_DateRange  数据时间范围
	void DataSort(CString m_SelectStr,CString m_DateRange);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWDATA_H__DB6E2AF2_1D13_4894_A3F6_C5C897F48489__INCLUDED_)
