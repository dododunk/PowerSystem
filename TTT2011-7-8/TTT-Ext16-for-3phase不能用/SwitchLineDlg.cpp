// SwitchLineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TTT.h"
#include "SwitchLineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchLineDlg dialog


CSwitchLineDlg::CSwitchLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSwitchLineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSwitchLineDlg)
	m_iSwitchLine = -1;
	m_generatrixno = 0;
	//}}AFX_DATA_INIT
	m_iSwitchLine = 0;
}


void CSwitchLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSwitchLineDlg)
	DDX_Control(pDX, IDC_SPIN, m_SpinButton);
	DDX_CBIndex(pDX, IDC_COMBO_SWITCHLINE, m_iSwitchLine);
	DDX_Text(pDX, IDC_GENERATRIXNO, m_generatrixno);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSwitchLineDlg, CDialog)
	//{{AFX_MSG_MAP(CSwitchLineDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchLineDlg message handlers

BOOL CSwitchLineDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SpinButton.SetRange(1,4);
	m_SpinButton.SetPos(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSwitchLineDlg::OnOK() 
{
    UpdateData(TRUE);	
	CDialog::OnOK();
	
	//pt->m_WhichKind-------TRUE 变电站版本  FALSE 电局版
    //Apppt = (CIFRMApp*)AfxGetApp();
}
