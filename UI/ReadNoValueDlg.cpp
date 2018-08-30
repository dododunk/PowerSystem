// ReadNoValueDlg.cpp : implementation file
//

#include "stdafx.h"

#include "ReadNoValueDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadNoValueDlg dialog


CReadNoValueDlg::CReadNoValueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadNoValueDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadNoValueDlg)
	m_radio        =     0;
	m_PhaseNoKnown = FALSE;
	//}}AFX_DATA_INIT
}


void CReadNoValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadNoValueDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Check(pDX, IDC_CHECK1, m_PhaseNoKnown);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReadNoValueDlg, CDialog)
	//{{AFX_MSG_MAP(CReadNoValueDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadNoValueDlg message handlers

void CReadNoValueDlg::OnOK() 
{
    UpdateData(TRUE);
	CDialog::OnOK();
}
