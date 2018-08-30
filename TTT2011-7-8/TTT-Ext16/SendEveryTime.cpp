// SendEveryTime.cpp : implementation file
//

#include "stdafx.h"
#include "ttt.h"
#include "SendEveryTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendEveryTime dialog


CSendEveryTime::CSendEveryTime(CWnd* pParent /*=NULL*/)
	: CDialog(CSendEveryTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendEveryTime)
	m_Seconds = 15;
	//}}AFX_DATA_INIT
}


void CSendEveryTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendEveryTime)
	DDX_Text(pDX, IDC_SECONDS, m_Seconds);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendEveryTime, CDialog)
	//{{AFX_MSG_MAP(CSendEveryTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendEveryTime message handlers

void CSendEveryTime::OnOK() 
{
    UpdateData(TRUE);
	
	if(m_Seconds < 15 || m_Seconds > 300)
	{
        MessageBox("时间超界,范围应为[15-300]！"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	CDialog::OnOK();
}

BOOL CSendEveryTime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_SECONDS)->SetFocus();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
