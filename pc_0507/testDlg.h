// testDlg.h : header file
//



#if !defined(AFX_TESTDLG_H__D9A5AE2F_CC77_4A91_BAF1_C62A427102D3__INCLUDED_)
#define AFX_TESTDLG_H__D9A5AE2F_CC77_4A91_BAF1_C62A427102D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
	CStatic	m_ctrl_lab_read_data;
	CStatic	m_ctrl_lab_zero_point_number;
	CStatic	m_static_protocol_data;
	CString	m_ctrl_lab_trig_times;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
void CTestDlg:: Fun_RW_Trig_Angle_Init( ) ;

void static  CALLBACK  CTestDlg:: Thread_RW_Trig_Angle( CTestDlg *pDlg ) ;

/////////////////////////
void static   CALLBACK CTestDlg:: Thread_Meter_Read( CTestDlg *pDlg ) ;


void CTestDlg:: Fun_PC_Zero_Cap_init( ) ;


void CTestDlg::Fun_Protocol_Show( unsigned char * buf , bool flag ) ;


void CTestDlg::Fun_Protocol_Show_Recv( unsigned char  * buf , bool flag ) ;




//int  CTestDlg:: Fun_AD_Device_Init( ) ;


protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnDecode();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnReadAngle();
	afx_msg void OnRbtnA();
	afx_msg void OnBtnSetAngle();
	afx_msg void OnBtnCongealSend();
	afx_msg void OnSelendokComboUserCmd();
	afx_msg void OnBtnAdTest();
	afx_msg void OnClose();
	afx_msg void OnBtnThreadTest();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnThreadTestStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__D9A5AE2F_CC77_4A91_BAF1_C62A427102D3__INCLUDED_)
