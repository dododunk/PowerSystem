//{{AFX_INCLUDES()
#include "sstabctl.h"
//}}AFX_INCLUDES
#if !defined(AFX_MYDIALOGBAR_H__CD3A4607_CE3C_4C66_ADC7_9D96F352BF51__INCLUDED_)
#define AFX_MYDIALOGBAR_H__CD3A4607_CE3C_4C66_ADC7_9D96F352BF51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDialogBar.h : header file
//
#include "Resource.h"
#include "MutiTreeCtrl.h"
#include "InitDialogBar.h"
/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar dialog

class CMyDialogBar : public CInitDialogBar
{
// Construction
public:	
	void ShowTab(short kinds);
	void DeleteAllSelectTree();
	CMyDialogBar();   // standard constructor
	//得到选择条件
	CString      SelectCondition();
	CString m_ModuleFindContionStr;	
	CString    m_GetModuleCondtion;
	void       InitializeCombo();
    //初始化树控件
	void          Treeinitialize();

// Dialog Data
	//{{AFX_DATA(CMyDialogBar)
	enum { IDD = CG_IDD_MYDIALOGBAR };
	CComboBox	m_AppearList;
	CComboBox	m_list;
	CComboBox	m_SelectKind;
	CString	   m_FindCString;
	int		        m_radio2;
	CMultiTreeCtrl    m_datatree;
	CSSTabCtl	m_SSTabData;
	BOOL	m_synchronization;
	int		m_combkinds;
	BOOL	m_check1;
	BOOL	m_check2;
	BOOL	m_check9;
	BOOL	m_check5;
	BOOL	m_check6;
	BOOL	m_check7;
	BOOL	m_check8;
	BOOL	m_check11;
	BOOL	m_check10;
	BOOL	m_check12;
	BOOL	m_check3;
	BOOL	m_check4;
	int		m_radio1;
	int		m_radio4;
	BOOL	m_check13;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialogBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialogBar();
	//}}AFX_VIRTUAL

// Implementation
protected:
	//CBitmapButton    m_Search;
	// Generated message map functions
	//{{AFX_MSG(CMyDialogBar)
	afx_msg void OnSelchangedDatatree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickDatatree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupCombo();
	afx_msg void OnSetfocusFindstring();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickSstabdata(short PreviousTab);
	afx_msg void OnSynchronization();
	
	afx_msg void OnListselect();
	afx_msg void OnCloseupAppearcombo();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio38();
	afx_msg void OnRadio37();
	afx_msg void OnCloseupListcombo();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString  m_TimeRangeStr;
	CString  m_DSCondition;
	CString  m_AppearContion;
	CString m_GetSelectCondtionStr;
	void FindCondtionModule(CString str,long m_Records);
	BOOL m_IsRightDataAppear;
	void AddAllKindAmmeter(CString condtion,HTREEITEM Item,int n);

	CImageList      m_imageList;
	CImageList       m_imgState;
	
	HTREEITEM  hSelectedItem;
	//定位标志
	VARIANT              VAR;


    
	//查找到模块标志
	BOOL    m_bFinding;
	//显示数据
    void initializeFieldInfo(CString m_title,CString m_totalsql,int columns,VARIANT  position);//显示数据
	//按项查找 kinds  0-脉冲表范围 1－485表范围
	//按模块找
	void  FindImpluseOr485Module(HTREEITEM hSelectedItem,int image,BYTE kinds);
	//按模块找
	void  FindModule(HTREEITEM hSelectedItem,int image,int m_SmallModule,int m_BigModule);
	//按项查找 
	void FindItem(HTREEITEM hSelectedItem,int image);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOGBAR_H__CD3A4607_CE3C_4C66_ADC7_9D96F352BF51__INCLUDED_)
