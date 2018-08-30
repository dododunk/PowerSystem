// CARD.cpp : implementation file
//

#include "stdafx.h"
#include "ttt.h"
#include "CARD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCARD dialog


CCARD::CCARD(CWnd* pParent /*=NULL*/)
	: CDialog(CCARD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCARD)
	m_cardvalue = 0;
	//}}AFX_DATA_INIT
}


void CCARD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCARD)
	DDX_Control(pDX, IDC_CARDCOMBO, m_cardcombox);
	DDX_CBIndex(pDX, IDC_CARDCOMBO, m_cardvalue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCARD, CDialog)
	//{{AFX_MSG_MAP(CCARD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCARD message handlers

BOOL CCARD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//PCI-9111DG
	m_cardcombox.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCARD::OnOK() 
{
	UpdateData(TRUE);	
	CDialog::OnOK();
}

void CCARD::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
