// TimeSelect.cpp : implementation file
//

#include "stdafx.h"

#include "TimeSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeSelect dialog


CTimeSelectDlg::CTimeSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeSelect)
	m_Begin = CTime::GetCurrentTime();
	m_End   = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CTimeSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeSelect)
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKERBEGIN, m_Begin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKEREND, m_End);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeSelect message handlers

void CTimeSelectDlg::OnOK() 
{
	UpdateData(TRUE);
    CTimeSpan ts = m_End - m_Begin;
	
	if(ts.GetTotalSeconds() < 0)
	{
        MessageBox("结束时间应大于或等于起始时间！","警告",MB_OK|MB_ICONWARNING);
		return;
	}

	CDialog::OnOK();
}

BOOL CTimeSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//设置窗口的图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_RESCYCLE);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
