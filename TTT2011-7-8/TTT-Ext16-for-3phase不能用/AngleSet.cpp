// AngleSet.cpp : implementation file
//

#include "stdafx.h"
#include "TTT.h"
#include "AngleSet.h"
#include "MainFrm.h"
#include "TTTDoc.h"
#include "TTTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAngleSet dialog//spin


CAngleSet::CAngleSet(CWnd* pParent /*=NULL*/)
	: CDialog(CAngleSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAngleSet)
	m_Sangle       = 30;
	m_dangle       = 30;
	m_SangleB      = 30;
	m_SangleC      = 30;
	m_generatrixno = 1;
	m_radio = 0;
	//}}AFX_DATA_INIT
}


void CAngleSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAngleSet)
	DDX_Control(pDX, IDC_SPIN, m_SpinButton);
	DDX_Control(pDX, IDC_READANGLECD, m_readanglecd);
	DDX_Control(pDX, IDC_READANGLEC, m_readanglec);
	DDX_Control(pDX, IDC_READANGLEB, m_readangleb);
	DDX_Control(pDX, IDC_READANGLE, m_readangle);
	DDX_Control(pDX, IDC_DANGLESET, m_dangleset);
	DDX_Control(pDX, IDC_ANGLESETC, m_anglesetc);
	DDX_Control(pDX, IDC_ANGLESETB, m_anglesetb);
	DDX_Control(pDX, IDC_ANGLESET, m_angleseta);
	DDX_Text(pDX, IDC_SANGLE, m_Sangle);
	DDX_Text(pDX, IDC_DANGLE, m_dangle);
	DDX_Text(pDX, IDC_SANGLEB, m_SangleB);
	DDX_Text(pDX, IDC_SANGLEC, m_SangleC);
	DDX_Text(pDX, IDC_GENERATRIXNO, m_generatrixno);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAngleSet, CDialog)
	//{{AFX_MSG_MAP(CAngleSet)
	ON_BN_CLICKED(IDC_ANGLESET, OnAngleset)
	ON_BN_CLICKED(IDC_DANGLESET, OnDangleset)
	ON_BN_CLICKED(IDC_READANGLE, OnReadangle)
	ON_BN_CLICKED(IDC_ANGLESETB, OnAnglesetb)
	ON_BN_CLICKED(IDC_ANGLESETC, OnAnglesetc)
	ON_BN_CLICKED(IDC_READANGLEB, OnReadangleb)
	ON_BN_CLICKED(IDC_READANGLEC, OnReadanglec)
	ON_BN_CLICKED(IDC_READANGLECD, OnReadanglecd)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAngleSet message handlers

void CAngleSet::OnAngleset() 
{
	UpdateData(TRUE);
	
	//short generatrixno 母线编号
	//short phase  相别 0 A相 1 B相 2 C相
    //int   angles 角度
	SetThreePhaseAngle(m_generatrixno,0, m_Sangle,m_radio);

}

void CAngleSet::OnDangleset() 
{
	UpdateData(TRUE);

    CString     str ;  
	CTTTView* pview = (CTTTView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	/*
	if(m_dangle < 5 || m_dangle > 80)
	{
		MessageBox("带通角设置错误,应设置在5－80度之间!","警告：",MB_OK|MB_ICONWARNING);
	}
	else
	*/
	{
		str.Format("你想把带通角设置成%d度?",m_dangle);
		if(MessageBox(str,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			pview->m_iBandPassPoints = int (m_dangle * 1.0/180.0 * 512);
			MessageBox("带通角设置完毕!"," ",MB_OK|MB_ICONASTERISK);
		}		
	}
}

void CAngleSet::OnReadangle() 
{
	UpdateData(TRUE);

    CTTTView* pview = (CTTTView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
    //short phase  相别 0 A相 1 B相 2 C相
    pview->ReadThreePhaseAngle(m_generatrixno,0,m_radio);

	
}

//short generatrixno 母线编号
//short phase  相别 0 A相 1 B相 2 C相
//int   angles 角度
//BYTE  kinds  种类 0--信号强度 1－延迟角度
void CAngleSet::SetThreePhaseAngle(short generatrixno,short phase,int angles,BYTE kinds)
{

    CString str;

	CTTTView* pview = (CTTTView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	/*
	if(angles < 5 || angles > 80)
	{
		
		switch(phase)
		{
		case 0:
			{  

				str = "A相信号强度设置错误,应设置在5－80之间!";
				break;

			}
		case 1:
			{

				str = "B相信号强度设置错误,应设置在5－80之间!";
				break;

			}
		case 2:
			{

				str = "C相信号强度设置错误,应设置在5－80之间!";
				break;

			}

		}

		MessageBox(str,"警告：",MB_OK|MB_ICONWARNING);
		return;
	}
	else*/
	

	{
	
		switch(phase)
		{
		case 0:
			{  
			    
				switch(kinds)
				{
				case 0:
					{
                    	str.Format("你想把A相信号强度设置成%d?",angles);
						break;
					}
				case 1:
					{
						str.Format("你想把A相延迟角度设置成%d?",angles);
						break;
					}
				case 2:
					{
						str.Format("你想把A相发射电流设置成%d?",angles);
						break;
					}
				}
			
				break;

			}
		case 1:
			{
			
				switch(kinds)
				{
				case 0:
					{
                    	str.Format("你想把B相信号强度设置成%d?",angles);
						break;
					}
				case 1:
					{
						str.Format("你想把B相延迟角度设置成%d?",angles);
						break;
					}
				case 2:
					{
						str.Format("你想把B相发射电流设置成%d?",angles);
						break;
					}
				}
				
				break;

			}
		case 2:
			{
				
				switch(kinds)
				{
				case 0:
					{
                    	str.Format("你想把C相信号强度设置成%d?",angles);
						break;
					}
				case 1:
					{
						str.Format("你想把C相延迟角度设置成%d?",angles);
						break;
					}
				case 2:
					{
						str.Format("你想把C相发射电流设置成%d?",angles);
						break;
					}
				}

				break;

			}

		}

	
		if(MessageBox(str,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			//short generatrixno 母线编号
			//short phase        相别 0 A相 1 B相 2 C相
            //int   angles       角度
            pview->SetPhaseAngle(generatrixno,phase,angles,kinds);
		}

	}	

}

void CAngleSet::OnAnglesetb() 
{
	UpdateData(TRUE);
    
	//short generatrixno 母线编号
	//short phase  相别 0 A相 1 B相 2 C相
    //int   angles 角度
	SetThreePhaseAngle(m_generatrixno,1, m_SangleB,m_radio);	
}

void CAngleSet::OnAnglesetc() 
{
    UpdateData(TRUE);
    
	//short generatrixno 母线编号
	//short phase  相别 0 A相 1 B相 2 C相
    //int   angles 角度
	SetThreePhaseAngle(m_generatrixno,2, m_SangleC,m_radio);	
}



void CAngleSet::OnReadangleb() 
{

   UpdateData(TRUE);
   CTTTView* pview = (CTTTView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
   //short phase  相别 0 A相 1 B相 2 C相
   pview->ReadThreePhaseAngle(m_generatrixno,1,m_radio);
	
}

void CAngleSet::OnReadanglec() 
{

   UpdateData(TRUE);
 
   //short phase  相别 0 A相 1 B相 2 C相
   CTTTView* pview = (CTTTView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
   //short phase  相别 0 A相 1 B相 2 C相
   pview->ReadThreePhaseAngle(m_generatrixno,2,m_radio);	

}

BOOL CAngleSet::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//设置按钮风格
	/**/
	m_readanglecd.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//
	m_readanglec.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_readangleb.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_readangle.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_dangleset.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_anglesetc.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_anglesetb.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_angleseta.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
    
//	m_first.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;

	//设置窗口的图标
//	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ANGLE);
//	ASSERT(hIcon);
//	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
	m_SpinButton.SetRange( 1, 4);
	m_SpinButton.SetPos(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAngleSet::OnReadanglecd() 
{

   UpdateData(TRUE);
   //读带通角大小
   CTTTView* pview = (CTTTView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
   CString str ;
   str.Format("当前带通角设置为%d度!",int(pview->m_iBandPassPoints*180.00/512 + 0.5));
   MessageBox(str," ",MB_OK|MB_ICONASTERISK);
  
}

void CAngleSet::OnRadio1() 
{
	UpdateData(TRUE);
    m_radio  = 0;	
	CWnd* pt =  GetDlgItem(IDC_STATIC1);
	pt->SetWindowText("请输入A相信号强度");	
	pt =  GetDlgItem(IDC_STATIC2);
	pt->SetWindowText("请输入B相信号强度");
	pt =  GetDlgItem(IDC_STATIC3);
	pt->SetWindowText("请输入C相信号强度");
	CEdit * pp = (CEdit *)GetDlgItem(IDC_SANGLE);
	pp->SetWindowText("30");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEB);
	pp->SetWindowText("30");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEC);
	pp->SetWindowText("30");

	pp = (CEdit *)GetDlgItem(IDC_ANGLESET);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETB);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETC);
	pp->EnableWindow(TRUE);

	UpdateData(TRUE);
    UpdateData(FALSE);
}

void CAngleSet::OnRadio2() 
{
	UpdateData(TRUE);
    m_radio  = 1;	
	CWnd* pt =  GetDlgItem(IDC_STATIC1);
	pt->SetWindowText("请输入A相延迟角度");	
	pt =  GetDlgItem(IDC_STATIC2);
	pt->SetWindowText("请输入B相延迟角度");
	pt =  GetDlgItem(IDC_STATIC3);
	pt->SetWindowText("请输入C相延迟角度");
	CEdit * pp = (CEdit *)GetDlgItem(IDC_SANGLE);
	pp->SetWindowText("0");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEB);
	pp->SetWindowText("0");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEC);
	pp->SetWindowText("0");
	pp = (CEdit *)GetDlgItem(IDC_ANGLESET);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETB);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETC);
	pp->EnableWindow(TRUE);

	UpdateData(TRUE);
    UpdateData(FALSE);	
}

void CAngleSet::OnRadio4() 
{
    m_radio  = 2;	
	CWnd* pt =  GetDlgItem(IDC_STATIC1);
	pt->SetWindowText("请输入A相发射电流");	
	pt =  GetDlgItem(IDC_STATIC2);
	pt->SetWindowText("请输入B相发射电流");
	pt =  GetDlgItem(IDC_STATIC3);
	pt->SetWindowText("请输入C相发射电流");
	CEdit * pp = (CEdit *)GetDlgItem(IDC_SANGLE);
	pp->SetWindowText("300");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEB);
	pp->SetWindowText("300");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEC);
	pp->SetWindowText("300");
	pp = (CEdit *)GetDlgItem(IDC_ANGLESET);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETB);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETC);
	pp->EnableWindow(TRUE);

	UpdateData(TRUE);
    UpdateData(FALSE);		
}

void CAngleSet::OnRadio5() 
{
   	CWnd* pp = (CEdit *)GetDlgItem(IDC_ANGLESET);
	pp->EnableWindow(FALSE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETB);
	pp->EnableWindow(FALSE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETC);
	pp->EnableWindow(FALSE);
	
}
