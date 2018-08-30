//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_LINELOSS_H__773533D1_71D8_4E7A_9F16_94F5DDD45418__INCLUDED_)
#define AFX_LINELOSS_H__773533D1_71D8_4E7A_9F16_94F5DDD45418__INCLUDED_

#include "MutiTreeCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineLoss.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CLineLoss dialog
#include "resource.h"
class CLineLossDlg : public CDialog
{
// Construction
public:
	CString m_AppearCondtion;
	CLineLossDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLineLoss)
	enum { IDD = IDD_LINELOSS };
	CComboBox	m_listend;
	CComboBox	m_listbegin;
	int		m_radios;
	CString	m_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineLoss)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineLoss)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangedDatatree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTotal();
	afx_msg void OnRadio1();
	afx_msg void OnRadio10();
	afx_msg void OnRadio5();
	afx_msg void OnSelchangeBegintime();
	afx_msg void OnSelchangeEndtime();
	afx_msg void OnRadio41();
	afx_msg void OnRadio42();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_GetDataname;
	void    GetSubSupply(CString CompanyName, CString SubstationName, CString LineName,CString  SubNo,CString SubName,CString BeginTime,CString EndTime);
	void    SubSupply(CString m_Condtion);
	CString GetSubName(CString Sql);
	void    CheckNumbers();
	long    GetRecords(CString SqlStr);

	//CString FieldName    所求字段名
    //CString CompanyName  公司名
    double  GetCompanyElc(CString Order,CString CompanyName);
	
	//得到某变电站本身的总表值及下所有线总表的和
	//CString FieldName       所求字段名 TB_Garrison.GARRISON_WORKDEGREE
	//CString CompanyName     公司名
	//CString SubstationName  变电站名
	//short   kinds           种类 0－－－本身的表值 1－－下面所有线路的表和
    double GetSubStaitonElc(CString Order,CString CompanyName, CString SubstationName,short kinds);


	//得到某线路本身的总表值及下所有变台总表的和
	//CString FieldName       所求字段名 TB_Garrison.有功电度
	//CString CompanyName     公司名
	//CString SubstationName  变电站名
	//CString LineName        线路名称
	//short   kinds           种类 0－－－本身的表值 1－－下面所有变台的表和
	double GetLineElc(CString Order,CString CompanyName, CString SubstationName,CString LineName,short kinds);

	void EnableWindows(BOOL IsTrue);
	void InitializeCombo();
	CString      m_StrSql;
	CString     BeginTime;
	CString       EndTime;
	VARIANT           VAR;
	CString GetCompanyNames;
	CString GetCompanyName();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINELOSS_H__773533D1_71D8_4E7A_9F16_94F5DDD45418__INCLUDED_)
