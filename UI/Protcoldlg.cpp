// Protcoldlg.cpp : implementation file
//

#include "stdafx.h"

#include "Protcoldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtcoldlg dialog


CProtcoldlg::CProtcoldlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProtcoldlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProtcoldlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProtcoldlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtcoldlg)
	DDX_Control(pDX, IDC_MODULELINE, m_moduleline);
	DDX_Control(pDX, IDC_MOTHERLINE, m_motherline);
	DDX_Control(pDX, IDC_COMBOPROTCOL, m_comboprotcol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtcoldlg, CDialog)
	//{{AFX_MSG_MAP(CProtcoldlg)
	ON_BN_CLICKED(ID_SSETMOTHER, OnSsetmother)
	ON_BN_CLICKED(ID_SETLINE, OnSetline)
	ON_BN_CLICKED(ID_MODIFYPROTCOL, OnModifyprotcol)
	ON_BN_CLICKED(ID_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtcoldlg message handlers

BOOL CProtcoldlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    m_comboprotcol.SetCurSel(4);
	m_motherline.SetCurSel(0);		  
	m_moduleline.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CProtcoldlg::OnSsetmother() 
{
	UpdateData(TRUE);
    CString      str;
	m_motherline.GetLBText(m_motherline.GetCurSel(),str);
	m_protcol = atoi(str);

	//模块母线
    m_kinds   =         1;
	CDialog::OnOK();	
}

void CProtcoldlg::OnSetline() 
{
	UpdateData(TRUE);
    CString      str;
	m_moduleline.GetLBText(m_moduleline.GetCurSel(),str);
	m_protcol = atoi(str);

	//模块出线
    m_kinds   =         2;
	CDialog::OnOK();	
}

void CProtcoldlg::OnModifyprotcol() 
{	
    UpdateData(TRUE);
    CString      str;
	m_comboprotcol.GetLBText(m_comboprotcol.GetCurSel(),str);
	m_protcol = atoi(str);
	
	//抄表协议
    m_kinds   =         0;

	CDialog::OnOK();	
}

void CProtcoldlg::OnCancel() 
{
	CDialog::OnCancel();	
}
