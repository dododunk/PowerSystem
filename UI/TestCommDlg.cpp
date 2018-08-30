// TestComm.cpp : implementation file
//

#include "stdafx.h"
//
#include "TestCommDlg.h"
#include "Resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestComm dialog


CTestCommDlg::CTestCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCommDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestComm)
	m_test1     =  TRUE;
	m_test2     = FALSE;
	m_test3     = FALSE;
	m_test4     = FALSE;
	m_test5     =    20;
	m_testtimes = 20000;
	//}}AFX_DATA_INIT
}


void CTestCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestComm)
	DDX_Check(pDX, IDC_CHECK1, m_test1);
	DDX_Check(pDX, IDC_CHECK2, m_test2);
	DDX_Check(pDX, IDC_CHECK3, m_test3);
	DDX_Check(pDX, IDC_CHECK4, m_test4);
	DDX_Text(pDX, IDC_TIMEEVERY, m_test5);
	DDX_Text(pDX, IDC_TESTTIMES, m_testtimes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestCommDlg, CDialog)
	//{{AFX_MSG_MAP(CTestComm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestComm message handlers

void CTestCommDlg::OnOK() 
{
    UpdateData(TRUE);	

	if(!(m_test1 || m_test2 || m_test3 || m_test4))
	{
        MessageBox("先选择测试母线！"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	if(m_testtimes < 1)
	{
        MessageBox("测试次数应大于0！"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	CDialog::OnOK();
}
