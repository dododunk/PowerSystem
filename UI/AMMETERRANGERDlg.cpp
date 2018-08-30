// AMMETERRANGER.cpp : implementation file
//

#include "stdafx.h"

#include "AMMETERRANGERDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAMMETERRANGER dialog


CAMMETERRANGERDlg::CAMMETERRANGERDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAMMETERRANGERDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAMMETERRANGER)
	m_check1 = FALSE;
	m_check2 = FALSE;
	m_check3 = FALSE;
	m_check4 = FALSE;
	m_check5 = FALSE;
	m_check6 = FALSE;
	m_check7 = FALSE;
	m_check8 = FALSE;
	m_check9 = FALSE;
	m_check10 = FALSE;
	m_check11 = FALSE;
	m_check12 = FALSE;
	m_check13 = FALSE;
	m_check14 = FALSE;
	m_check15 = FALSE;
	m_check16 = FALSE;
	m_check17 = FALSE;
	m_check18 = FALSE;
	m_check19 = FALSE;
	m_check20 = FALSE;
	m_check21 = FALSE;
	m_check22 = FALSE;
	m_check23 = FALSE;
	m_check24 = FALSE;
	m_check25 = FALSE;
	m_check26 = FALSE;
	m_check27 = FALSE;
	m_check28 = FALSE;
	m_check29 = FALSE;
	m_check30 = FALSE;
	m_check31 = FALSE;
	//}}AFX_DATA_INIT
}


void CAMMETERRANGERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAMMETERRANGER)
	DDX_Check(pDX, IDC_CHECK101, m_check1);
	DDX_Check(pDX, IDC_CHECK102, m_check2);
	DDX_Check(pDX, IDC_CHECK103, m_check3);
	DDX_Check(pDX, IDC_CHECK104, m_check4);
	DDX_Check(pDX, IDC_CHECK105, m_check5);
	DDX_Check(pDX, IDC_CHECK106, m_check6);
	DDX_Check(pDX, IDC_CHECK107, m_check7);
	DDX_Check(pDX, IDC_CHECK108, m_check8);
	DDX_Check(pDX, IDC_CHECK109, m_check9);
	DDX_Check(pDX, IDC_CHECK110, m_check10);
	DDX_Check(pDX, IDC_CHECK111, m_check11);
	DDX_Check(pDX, IDC_CHECK112, m_check12);
	DDX_Check(pDX, IDC_CHECK113, m_check13);
	DDX_Check(pDX, IDC_CHECK114, m_check14);
	DDX_Check(pDX, IDC_CHECK115, m_check15);
	DDX_Check(pDX, IDC_CHECK116, m_check16);
	DDX_Check(pDX, IDC_CHECK117, m_check17);
	DDX_Check(pDX, IDC_CHECK118, m_check18);
	DDX_Check(pDX, IDC_CHECK119, m_check19);
	DDX_Check(pDX, IDC_CHECK120, m_check20);
	DDX_Check(pDX, IDC_CHECK121, m_check21);
	DDX_Check(pDX, IDC_CHECK122, m_check22);
	DDX_Check(pDX, IDC_CHECK123, m_check23);
	DDX_Check(pDX, IDC_CHECK124, m_check24);
	DDX_Check(pDX, IDC_CHECK125, m_check25);
	DDX_Check(pDX, IDC_CHECK126, m_check26);
	DDX_Check(pDX, IDC_CHECK127, m_check27);
	DDX_Check(pDX, IDC_CHECK128, m_check28);
	DDX_Check(pDX, IDC_CHECK129, m_check29);
	DDX_Check(pDX, IDC_CHECK130, m_check30);
	DDX_Check(pDX, IDC_CHECK131, m_check31);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAMMETERRANGERDlg, CDialog)
	//{{AFX_MSG_MAP(CAMMETERRANGER)
	ON_BN_CLICKED(ID_ALLSELECT, OnAllselect)
	ON_BN_CLICKED(ID_ALLABANDON, OnAllabandon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAMMETERRANGER message handlers

void CAMMETERRANGERDlg::OnAllselect() 
{
	m_check1 = TRUE;
	m_check2 = TRUE;
	m_check3 = TRUE;
	m_check4 = TRUE;
	m_check5 = TRUE;
	m_check6 = TRUE;
	m_check7 = TRUE;
	m_check8 = TRUE;
	m_check9 = TRUE;
	m_check10 = TRUE;
	m_check11 = TRUE;
	m_check12 = TRUE;
	m_check13 = TRUE;
	m_check14 = TRUE;
	m_check15 = TRUE;
	m_check16 = TRUE;
	m_check17 = TRUE;
	m_check18 = TRUE;
	m_check19 = TRUE;
	m_check20 = TRUE;
	m_check21 = TRUE;
	m_check22 = TRUE;
	m_check23 = TRUE;
	m_check24 = TRUE;
	m_check25 = TRUE;
	m_check26 = TRUE;
	m_check27 = TRUE;
	m_check28 = TRUE;
	m_check29 = TRUE;
	m_check30 = TRUE;
	m_check31 = TRUE;
	UpdateData(FALSE);
	
}

void CAMMETERRANGERDlg::OnAllabandon() 
{
	m_check1 = FALSE;
	m_check2 = FALSE;
	m_check3 = FALSE;
	m_check4 = FALSE;
	m_check5 = FALSE;
	m_check6 = FALSE;
	m_check7 = FALSE;
	m_check8 = FALSE;
	m_check9 = FALSE;
	m_check10 = FALSE;
	m_check11 = FALSE;
	m_check12 = FALSE;
	m_check13 = FALSE;
	m_check14 = FALSE;
	m_check15 = FALSE;
	m_check16 = FALSE;
	m_check17 = FALSE;
	m_check18 = FALSE;
	m_check19 = FALSE;
	m_check20 = FALSE;
	m_check21 = FALSE;
	m_check22 = FALSE;
	m_check23 = FALSE;
	m_check24 = FALSE;
	m_check25 = FALSE;
	m_check26 = FALSE;
	m_check27 = FALSE;
	m_check28 = FALSE;
	m_check29 = FALSE;
	m_check30 = FALSE;
	m_check31 = FALSE;
	UpdateData(FALSE);
}

void CAMMETERRANGERDlg::OnOK() 
{
	UpdateData(TRUE);
	
	if(!(m_check1 || m_check2 || m_check3 || m_check4 || m_check5 || m_check6 || m_check7 || m_check8 || m_check9 || m_check10 || m_check11 || m_check12 || m_check13 || m_check14 || m_check15 || m_check16 || m_check17 || m_check18 || m_check19 || m_check20 || m_check21 || m_check22 || m_check23 || m_check24 || m_check25 || m_check26 || m_check27 || m_check28 || m_check29 || m_check30 || m_check31))
	{
		MessageBox("读哪几天的数据呀？请选择读表日期！","",MB_OK|MB_ICONWARNING);
		return;
	}

	CDialog::OnOK();
}

BOOL CAMMETERRANGERDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//设置窗口的图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_RESCYCLE);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	SetWindowText(m_title);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
