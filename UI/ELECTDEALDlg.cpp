// ELECTDEAL.cpp : implementation file
//

#include "stdafx.h"

#include "ELECTDEALDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CELECTDEAL dialog


CELECTDEALDlg::CELECTDEALDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CELECTDEALDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CELECTDEAL)
	m_radio = 0;
	//}}AFX_DATA_INIT
}


void CELECTDEALDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CELECTDEAL)
	DDX_Radio(pDX, IDC_RADIO3, m_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CELECTDEALDlg, CDialog)
	//{{AFX_MSG_MAP(CELECTDEAL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CELECTDEAL message handlers

void CELECTDEALDlg::OnOK() 
{
    UpdateData(TRUE);
	
	//设置窗口的图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_RESCYCLE);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
	
	CDialog::OnOK();
}

BOOL CELECTDEALDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
