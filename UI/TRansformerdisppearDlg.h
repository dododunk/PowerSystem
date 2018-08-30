#if !defined(AFX_TRANSFORMERDISPPEAR_H__2559A664_E70B_42BA_A15F_C210CF9D2FB4__INCLUDED_)
#define AFX_TRANSFORMERDISPPEAR_H__2559A664_E70B_42BA_A15F_C210CF9D2FB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TRansformerdisppear.h : header file
//
#include "resource.h"
#include "MutiTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CTRansformerdisppear dialog

class CTRansformerdisppearDlg : public CDialog
{
// Construction
public:
	CString m_GetSubRangeStr;
	CString  m_GetSubNameStr;
	//得到选择变台名称
    CString GetSelectSubName();
	CTRansformerdisppearDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTRansformerdisppear)
	enum { IDD = IDD_TRANSFORMERDISP };
	CMultiTreeCtrl	m_datatree;
	BOOL	m_IsDaYongFu;
	BOOL	m_IsBT;
	BOOL	m_IsJuMin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTRansformerdisppear)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTRansformerdisppear)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	//得到选择条件
    CString SelectCondition();
	//初始化树控件
	void Initialize();
	void AddAllKindAmmeter(CString condtion,HTREEITEM Item,int n);	
	CImageList      m_imageList;
	CImageList       m_imgState;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMERDISPPEAR_H__2559A664_E70B_42BA_A15F_C210CF9D2FB4__INCLUDED_)
