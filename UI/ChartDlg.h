//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES
#if !defined(AFX_OWEMONEY_H__70515CBB_C09C_4CB2_A9C3_F18E4D2ABC4B__INCLUDED_)
#define AFX_OWEMONEY_H__70515CBB_C09C_4CB2_A9C3_F18E4D2ABC4B__INCLUDED_
#include "MakeArray.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OWEMONEY.h : header file
//
#include "ExpandingDialog.h"

#include "MutiTreeCtrl.h"

#include "VcPlot.h"
#include "VcAxis.h"
#include "VcValueScale.h"
#include "VcSeriesCollection.h"
#include "VcSeries.h"
#include "VcPen.h"
#include "VcCategoryScale.h"
#include "VcColor.h"
#include "VcDataGrid.h"
#include "VcBackdrop.h"
#include "VcFill.h"
#include "VcBrush.h"
#include "VcDataPoints.h"
#include "VcDataPoint.h"
#include "VcDataPointLabel.h"
#include "VcAxisTitle.h"
#include "vcmarker.h"
#include "vcstatline.h"
#include "vcview3d.h"
#include "DIBSectionLite.h"

/////////////////////////////////////////////////////////////////////////////
// COWEMONEY dialog
#include "resource.h"
class CChartDlg : public CDialog//CExpandingDialog
{
// Construction
public:
	CString m_RangeStr;
    void GetAllUSERInfo(CString StrSql);//得到所选择的用户信息
	CChartDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COWEMONEY)
	enum { IDD = IDD_CHARTDIALOG };
	CComboBox	m_UserCombox;
	CComboBox	m_listend;
	CComboBox	m_listbegin;
	CMSChart	m_Chart;
	CMsDgridCtrl	m_dbgrids;
	CRdc	m_remotedatactrls;
	int		m_radio1;
	CString	m_title;
	BOOL	m_showlegend;
	BOOL	m_check1;
	BOOL	m_check3;
	BOOL	m_check4;
	CString	m_xtitle;
	CString	m_ytitle;
	BOOL	m_showlabel;
	BOOL	m_showstasline;
	BOOL	m_showvalue;
	BOOL	m_showxlabel;
	int		m_datakinds;
	CString	m_multile;
	BOOL	m_Ismultiple;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COWEMONEY)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COWEMONEY)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnSavebmp();
	afx_msg void OnPrintbmp();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio8();
	afx_msg void OnShowlegend();
	afx_msg void OnSettitle();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnSetxtitle();
	afx_msg void OnSetytitle();
	afx_msg void OnShowlabel();
	afx_msg void OnShowstasline();
	afx_msg void OnSelchangeBegintime();
	afx_msg void OnSelchangeEndtime();
	afx_msg void OnShowvalue();
	afx_msg void OnCheck34();
	afx_msg void OnCheck39();
	afx_msg void OnCheck37();
	afx_msg void OnCheck38();
	afx_msg void OnCheck40();
	afx_msg void OnCheck41();
	afx_msg void OnCheck42();
	afx_msg void OnCheck43();
	afx_msg void OnShowxlabel();
	afx_msg void OnSelchangeUsercombo();
	afx_msg void OnCheck45();
	afx_msg void OnRadio4();
	afx_msg void OnRadio6();
	afx_msg void OnCheck3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void MsChartAppear();
	BOOL SELECT[12];
	void SetChartDataValue(float** data,int Rows,int Cols);
	void ShowChart(CString SqlStr, CString BeginTimes, CString EndTimes,short m_kinds);
	void InitializeCombo(short m_kinds);
	CString GetSubName(CString Sql);
	void initialize(short m_kinds);
	CImageList m_imageList;
	CImageList m_imgState;
	void WndToBmpFile(CDC* pDC,CString BmpFile);
	HANDLE DDBToDIB(CBitmap &bitmap, DWORD dwCompression,CPalette *pPal);
	//得到某一表的所有记录数
    
	VARIANT               VAR;
	CStringArray   m_StrArray;
	CString BeginTime,EndTime;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWEMONEY_H__70515CBB_C09C_4CB2_A9C3_F18E4D2ABC4B__INCLUDED_)
