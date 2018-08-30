// BreadSetting.cpp : implementation file
//

#include "stdafx.h"

#include "BreadSettingDlg.h"
#include "SearchDlg.h"


#include "IFRMView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBreadSetting dialog


CBreadSettingDlg::CBreadSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBreadSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBreadSetting)
	m_iBroadTimes    = 10;
	m_iBroadTime     = COleDateTime::GetCurrentTime();
	m_minuter        = 10;
	//}}AFX_DATA_INIT
	m_times         = 0;
}


void CBreadSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBreadSetting)
	DDX_Text(pDX, IDC_EDIT_BROADTIMES, m_iBroadTimes);
	DDX_Text(pDX, IDC_EDIT_BROADTIME, m_iBroadTime);
	DDX_Text(pDX, IDC_MINUTER, m_minuter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBreadSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CBreadSetting)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CBreadSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBreadSetting message handlers
BOOL CBreadSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//窗口居中
	CenterWindow();

	//设置窗口的图标
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
	
	CWnd * pt = GetDlgItem(IDC_PAUSE);
	pt->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBreadSettingDlg::OnOK() 
{

  UpdateData(TRUE);
  
  m_times  =     0; 

  if(m_iBroadTime.GetStatus() != COleDateTime::valid)
  { 
	  return;
  }
   
  CTime    time1(m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond());
  CTime    time0     = CTime::GetCurrentTime();
  CTimeSpan ts       = time1 - time0;
  long broadTime     = ts.GetTotalSeconds();//倒计时
  
  if(broadTime > 131072 || broadTime < 0 )//时间限制
  { 
	  
	  MessageBox("所发驻留时间减去现在时间，范围应在[0,131072]秒之间，\r\n约0-36.4小时之间,请重输!","警告",MB_OK|MB_ICONWARNING);
	  return;
	  
  }
  else
  {
	  if(m_iBroadTimes > 1)
	  {

		  if(broadTime < m_minuter* 60* m_iBroadTimes)//时间限制
		  {
			  
			  MessageBox("现在到所发驻留时间两时间段内发送不完所设定的次数,请重输!","警告",MB_OK|MB_ICONWARNING);
			  return;
			  
		  }

	  }
	  
  }

   if(m_iBroadTimes > 30 || m_iBroadTimes < 1)
   {
	   MessageBox("输入的次数有错(1~30),请重新输入！","警告:",MB_OK|MB_ICONWARNING);
	   return;
   }
   
   if(m_minuter < 10 || m_minuter > 15)
   {
	   MessageBox("输入的时间间隔有错(10~15),请重新输入！","警告:",MB_OK|MB_ICONWARNING);
	   return;
   }
   	
   CButton * pt = (CButton *)GetDlgItem(IDCANCEL);
   pt->EnableWindow(FALSE);
   pt = (CButton *)GetDlgItem(IDOK);
   pt->EnableWindow(FALSE);
   pt = (CButton *)GetDlgItem(IDC_PAUSE);
   pt->EnableWindow(TRUE);

   KillTimer(10);

   //设置定时器
   SetTimer(10,m_minuter*60*1000,NULL);
   OnTimer(10);

}



void CBreadSettingDlg::OnCancel() 
{

	if(m_times < m_iBroadTimes && m_times > 0)
	{
		
		CString   str;
		str.Format("发送次数还没有完毕，共要发%d次，\r\n仅发%d次，退出？",m_iBroadTimes,m_times);
       	KillTimer(10);

		if(MessageBox(str," ",MB_YESNO|MB_ICONQUESTION) != IDYES)
		{
			//设置定时器
			SetTimer(10,m_minuter*60*1000,NULL);
			OnTimer(10);
			return;
		}

	}

	CDialog::OnCancel();
}


void CBreadSettingDlg::OnTimer(UINT nIDEvent) 
{

	if(nIDEvent == 10)
	{

		CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
		m_times ++;	
	
		//退出按钮无效
		CButton * pt = (CButton *)GetDlgItem(IDCANCEL);
        pt->EnableWindow(FALSE);
	
		CTime    m_timeBroadTime(m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond());
	
		pview->SendBreadorder(m_timeBroadTime,m_times); 
	
		//退出按钮有效
		pt = (CButton *)GetDlgItem(IDCANCEL);
        pt->EnableWindow(TRUE);

		if(pview->m_StartRead == FALSE)
		{	
			CString   str;
			pt = (CButton *)GetDlgItem(IDOK);
            pt->EnableWindow(TRUE);	
			pt = (CButton *)GetDlgItem(IDCANCEL);
            pt->EnableWindow(TRUE);	
			pt = (CButton *)GetDlgItem(IDC_PAUSE);
            pt->EnableWindow(FALSE);

			KillTimer(10);
			str.Format("发送驻留次数被中断，共计发送%d次！！",m_times);
			MessageBox(str," ",MB_OK);
			return;
		}
		
		if(m_times == m_iBroadTimes )
		{
			CString   str;
			pt = (CButton *)GetDlgItem(IDOK);
            pt->EnableWindow(TRUE);
			pt = (CButton *)GetDlgItem(IDCANCEL);
            pt->EnableWindow(TRUE);	
			pt = (CButton *)GetDlgItem(IDC_PAUSE);
            pt->EnableWindow(FALSE);
		
			KillTimer(10);

			str.Format("发送驻留次数完毕，共计发送%d次！！",m_iBroadTimes);
			MessageBox(str," ",MB_OK);
		}
	
	}
	
	CDialog::OnTimer(nIDEvent);
}





void CBreadSettingDlg::OnPause() 
{  
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
    pview->m_StartRead   = FALSE;
	
	KillTimer(10);
}


void CBreadSettingDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
