// TIMEDLG.cpp : implementation file
//

#include "stdafx.h"
#include "ttt.h"
#include "TIMEDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTIMEDLG dialog


CTIMEDLG::CTIMEDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CTIMEDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTIMEDLG)
	m_seconds = 0;
	//}}AFX_DATA_INIT
}


void CTIMEDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTIMEDLG)
	DDX_Text(pDX, IDC_EDITTIME, m_seconds);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTIMEDLG, CDialog)
	//{{AFX_MSG_MAP(CTIMEDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTIMEDLG message handlers

void CTIMEDLG::OnOK() 
{
    UpdateData(TRUE);	
	CDialog::OnOK();
}

BOOL CTIMEDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    GetDlgItem(IDC_EDITTIME)->SetFocus();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
