// Parameter.cpp : implementation file
//

#include "stdafx.h"

#include "ParameterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameter dialog


CParameterDlg::CParameterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParameterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameter)
	m_parameter1 = FALSE;
	m_parameter2 = FALSE;
	m_parameter3 = FALSE;
	m_parameter4 = FALSE;
	m_parameter5 = FALSE;
	m_parameter6 = FALSE;
	m_parameter7 = FALSE;
	m_parameter8 = FALSE;
	//}}AFX_DATA_INIT
}


void CParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameter)
	DDX_Check(pDX, IDC_CHECK1, m_parameter1);
	DDX_Check(pDX, IDC_CHECK2, m_parameter2);
	DDX_Check(pDX, IDC_CHECK6, m_parameter3);
	DDX_Check(pDX, IDC_CHECK3, m_parameter4);
	DDX_Check(pDX, IDC_CHECK4, m_parameter5);
	DDX_Check(pDX, IDC_CHECK5, m_parameter6);
	DDX_Check(pDX, IDC_CHECK7, m_parameter7);
	DDX_Check(pDX, IDC_CHECK8, m_parameter8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameterDlg, CDialog)
	//{{AFX_MSG_MAP(CParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameter message handlers

BOOL CParameterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParameterDlg::OnOK() 
{
	UpdateData(TRUE);	
	CDialog::OnOK();
}
