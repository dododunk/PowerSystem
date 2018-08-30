#if !defined(AFX_MYDIALOGDATABAR_H__865BF186_0ED2_41B8_A89B_46934740ACB0__INCLUDED_)
#define AFX_MYDIALOGDATABAR_H__865BF186_0ED2_41B8_A89B_46934740ACB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDialogDataBar.h : header file
//
#include "resource.h"
#include "InitDialogBar.h"

/////////////////////////////////////////////////////////////////////////////
// CMyDialogDataBar dialog

class CMyDialogDataBar : public CInitDialogBar
{
// Construction
public:
	CMyDialogDataBar();   // standard constructor
	void      ChangeSize();
	VARIANT  m_MaxPosition;
	//下翻数据记录
    void ScrollRecord(VARIANT  position);
	//显示数据
    void initializeFieldInfo(CString m_title,CString m_totalsql,int columns,VARIANT  position);
   	// Dialog Data
	//{{AFX_DATA(CMyDialogDataBar)
	enum { IDD = CG_IDD_MYDIALOGDATA };
	CMsDgridCtrl	m_dbgrid;
	CRdc	m_remotedatactrl;
	CComboBox	m_list;
	int		m_radio1;
	BOOL	m_check1;
	BOOL	m_check2;
	BOOL	m_check3;
	BOOL	m_check4;
	BOOL	m_check5;
	BOOL	m_check6;
	BOOL	m_check7;
	BOOL	m_check8;
	int		m_radio4;
	BOOL	m_check9;
	BOOL	m_check10;
	BOOL	m_check11;
	BOOL	m_check12;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialogDataBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialogBar();

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDialogDataBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOGDATABAR_H__865BF186_0ED2_41B8_A89B_46934740ACB0__INCLUDED_)
