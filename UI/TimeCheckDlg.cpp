// TimeCheck.cpp : implementation file
//

#include "stdafx.h"

#include "TimeCheckDlg.h"


#include "IFRMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeCheck dialog


CTimeCheckDlg::CTimeCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeCheckDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeCheck)
	m_localtime = COleDateTime::GetCurrentTime();
	m_othertime = COleDateTime::GetCurrentTime();
	m_info = _T("");
	//}}AFX_DATA_INIT
}


void CTimeCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeCheck)
	DDX_Text(pDX, IDC_EDIT_LOCALTIME, m_localtime);
	DDX_Text(pDX, IDC_EDIT_OTHERTIME, m_othertime);
	DDX_Text(pDX, IDC_INFO, m_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeCheckDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeCheck)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	ON_BN_CLICKED(IDC_SETLOCAL, OnSetlocal)
	ON_BN_CLICKED(IDC_OTHERSET, OnOtherset)
	ON_BN_CLICKED(IDC_OTHERREFRESH, OnOtherrefresh)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeCheck message handlers

void CTimeCheckDlg::OnRefresh() 
{
   	CTime time = CTime::GetCurrentTime();
	m_localtime.SetDateTime(time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
    UpdateData(FALSE);
	SetTimer(2,1000,NULL);
 	
}

//设置本机的时间
void CTimeCheckDlg::OnSetlocal() 
{	
	CString      Str;
    UpdateData(TRUE);
	if(m_localtime.GetStatus() != COleDateTime::valid)
	{ 
		//MessageBox("你输入的时间有误，请重新输入！","警告:",MB_OK|MB_ICONWARNING);
		return;
	}
    else
	{	
		
	
		Str.Format("本机当前时间设置为[%4d-%02d-%02d %02d:%02d:%02d]吗?",m_localtime.GetYear(),m_localtime.GetMonth(),m_localtime.GetDay(),m_localtime.GetHour(),m_localtime.GetMinute(),m_localtime.GetSecond()); //转换时间格式
        if(MessageBox(Str," ",MB_YESNO|MB_ICONQUESTION) != IDYES)
		{
           return;
		}

		SYSTEMTIME systime;
		systime.wYear          = m_localtime.GetYear();      //年
		systime.wMonth         = m_localtime.GetMonth();     //月
		systime.wDayOfWeek     = 0;
		systime.wDay           = m_localtime.GetDay();       //日 
		systime.wHour          = m_localtime.GetHour();      //时
		systime.wMinute        = m_localtime.GetMinute();    //分
		systime.wSecond        = m_localtime.GetMinute();    //秒
		systime.wMilliseconds  = 500;                        //毫秒
	
		if(::SetLocalTime(&systime))
		{	
			m_info.Format("本机当前时间设置为: %4d-%02d-%02d %02d:%02d:%02d",m_localtime.GetYear(),m_localtime.GetMonth(),m_localtime.GetDay(),m_localtime.GetHour(),m_localtime.GetMinute(),m_localtime.GetSecond()); //转换时间格式
			UpdateData(FALSE);

		}

	}

}

//BEGINS;COMMAND:13:年-月-日-时-分-秒;ENDS
//设置外机的时间
void CTimeCheckDlg::OnOtherset() 
{   
	CString  TimeStr; 
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CTime time       = CTime::GetCurrentTime();

	TimeStr.Format("BEGINS;COMMAND:13:%d-%d-%d-%d-%d-%d;ENDS",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
    if(pview->SetRemoteTime(TimeStr))
	{
		Sleep(1000);
		m_info.Format("外机当前时间设置为: %4d-%02d-%02d %02d:%02d:%02d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); //转换时间格式
		UpdateData(FALSE);

	}
	else
	{
	    m_info = "以本机设置对方时间时,端口连接错误,请重试..."; //转换时间格式
		UpdateData(FALSE);
	}

}

//得到外机的时间
void CTimeCheckDlg::OnOtherrefresh() 
{   
	//定义变量
	CString      TimeStr; 
	CString        times;
	CString       str[6];
	int    colum     = 0;
	int    k         = 0;
	
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	TimeStr = "BEGINS;COMMAND:14;ENDS";
    if(pview->SetRemoteTime(TimeStr))
	{
        SetTimer(1,1000,NULL);
		m_info = "正在提取数据,请稍侯..."; //转换时间格式
		UpdateData(FALSE);
	}
	else
	{
	    m_info = "提取外机当前时间时,端口连接错误,请重试..."; //转换时间格式
		UpdateData(FALSE);
	}
	
}

void CTimeCheckDlg::OnTimer(UINT nIDEvent) 
{
	
	switch(nIDEvent)
	{
	case 1:
		{
			
			CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
			CTime time = CTime::GetCurrentTime();
			KillTimer(1);
			CTimeSpan ts = 1;
			time  = time - ts;
			
			//如果字符不为空
			if(!pview->m_TimeStrs.IsEmpty())
			{
				
				CString	times = pview->m_TimeStrs;
				
				CString       str[6];
				int k =  0,colum = 0;
				
				//去空格
				times.TrimLeft();
				times.TrimRight();
				
				//以-为分隔符
				while(times.Find('-') != -1)
				{				
					k   =  times.Find('-');
					if(k != -1)
					{
						str[colum] =  times.Left(k);
						times  = times.Right(times.GetLength() - k - 1);
						
						if(colum > 4)
						{
							break;
						}
						colum++;
					}
					
				}
				
				//秒
				str[5] = times;
				
				//设置时间
				m_othertime.SetDateTime(atoi(str[0]),atoi(str[1]),atoi(str[2]),atoi(str[3]),atoi(str[4]),atoi(str[5]));
				pview->m_TimeStrs = "";
				
				UpdateData(FALSE);
				pview->m_TimeStrs = "";
				
				m_info.Format("对方时间为:%s-%s-%s %s:%s:%s \r\n本机时间为:%d-%d-%d %d:%d:%d",str[0],str[1],str[2],str[3],str[4],str[5],time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); //转换时间格式
				UpdateData(FALSE);
			}
			else
			{
				m_info = "提取对方时间失败...";
				UpdateData(FALSE);
			}
			break;	
		}
	case 2:
		{
			CTime time = CTime::GetCurrentTime();
			m_localtime.SetDateTime(time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		//	m_info.Format("本机当前时间为: %4d-%02d-%02d %02d:%02d:%02d",m_localtime.GetYear(),m_localtime.GetMonth(),m_localtime.GetDay(),m_localtime.GetHour(),m_localtime.GetMinute(),m_localtime.GetSecond()); //转换时间格式
			UpdateData(FALSE);
			break;
		}

	}
	CDialog::OnTimer(nIDEvent);
}

void CTimeCheckDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	KillTimer(1);
	KillTimer(2);	

}

BOOL CTimeCheckDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/*
    m_setlocal.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//;;
	m_otherset.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//;
	m_refresh.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//;
	m_OtherRefresh.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//;
    */

	//设置窗口的图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_MIS);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
