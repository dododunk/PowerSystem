// testDlg.cpp : implementation file
//

#include "header.h"


#define     _DEBUG_MESSAGE_ZERO_TIMES_SHOW




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "PCI8664.h"


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define   _SHOW            false 

#define   _SHOW_CONTINUE   true 

 //stru_meter_read_protocol_Data  stru_meter_read_protocol ;

// stru_PC2MCU_Protocol     stru_pc2mcu_protocol ;





typedef unsigned long (CALLBACK *pfun_callback)(LPVOID pvUserParam) ;

void  Fun_PC_CLK_Init() ;

void  Fun_PC_Send_Data( unsigned char * buf , int len ) ;




void CTestDlg::Fun_Protocol_Show( unsigned char  * buf , bool flag )
{
    CString  str1 , str2 ;
	
	int  i ;
	
	CStatic * pstatic ;
	
	pstatic = ( CStatic * )GetDlgItem( IDC_LAB_PROTO_SEND ) ;
	
	pstatic->SetWindowText( "" ) ;
	
	if( flag == _SHOW )
	{
		str1 = str2 = "" ;
	}	   
	else if( flag == _SHOW_CONTINUE )
	{
		pstatic->GetWindowText( str1 ) ;
		
		str1 += "\n" ;
	}
	
	for( i = 0 ; i < 16 ; i ++ )
	{		
		str2.Format( "%x" , buf[ i ] ) ;
		
		str1 = str1 + "0x" + str2 + " " ;
	}
	
	pstatic->SetWindowText( str1 ) ;
}


void CTestDlg::Fun_Protocol_Show_Recv( unsigned char  * buf , bool flag )
{
    CString  str1 , str2 ;
	
	int  i ;
	
	CStatic * pstatic ;
	
	pstatic = ( CStatic * )GetDlgItem( IDC_LAB_PROTO_READBACK ) ;
	
	pstatic->SetWindowText( "" ) ;
	
	if( flag == _SHOW )
	{
		str1 = str2 = "" ;
	}	   
	else if( flag == _SHOW_CONTINUE )
	{
		pstatic->GetWindowText( str1 ) ;
		
		str1 += "\n" ;
	}
	
	for( i = 0 ; i < 16 ; i ++ )
	{		
		str2.Format( "%x" , buf[ i ] ) ;
		
		str1 = str1 + "0x" + str2 + " " ;
	}
	
	pstatic->SetWindowText( str1 ) ;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_ctrl_lab_trig_times = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_LAB_READ_DATA, m_ctrl_lab_read_data);
	DDX_Control(pDX, IDC_LAB_ZERO_POINT_NUMBER, m_ctrl_lab_zero_point_number);
	DDX_Control(pDX, IDC_LAB_PROTO_SEND, m_static_protocol_data);
	DDX_Text(pDX, IDC_LAB_TRIG_NUMBER, m_ctrl_lab_trig_times);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DECODE, OnBtnDecode)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_READ_ANGLE, OnBtnReadAngle)
	ON_BN_CLICKED(IDC_RBTN_A, OnRbtnA)
	ON_BN_CLICKED(IDC_BTN_SET_ANGLE, OnBtnSetAngle)
	ON_BN_CLICKED(IDC_BTN_CONGEAL_SEND, OnBtnCongealSend)
	ON_CBN_SELENDOK(IDC_COMBO_USER_CMD, OnSelendokComboUserCmd)
	ON_BN_CLICKED(IDC_BTN_AD_TEST, OnBtnAdTest)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_THREAD_TEST, OnBtnThreadTest)
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_THREAD_TEST_STOP, OnBtnThreadTestStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	g_ad_device_init = false ;
	
	Fun_AD_Device_Init_Test( ) ;

	Fun_PC_CLK_Init() ;  //init clk\trig pin initializaton states
	
	g_plab_zero_times = ( CStatic * )GetDlgItem( IDC_LAB_ZERO_POINT_NUMBER ) ;

	g_plab_zero_times->SetWindowText( "0" ) ;

	g_plab_trig_times = ( CStatic * )GetDlgItem( IDC_LAB_TRIG_NUMBER ) ;
	
	g_plab_trig_times->SetWindowText( "0" ) ;


	g_plab_read_data = ( CStatic * )GetDlgItem( IDC_LAB_READ_DATA ) ;
	
	g_plab_read_data->SetWindowText( "0" ) ;


	
	Fun_Thread_Trig_Timer_Raising_Init( ) ;  //ad开始第一个周波采集，定时器

	Fun_Thread_Trig_Timer_Falling_Init( ) ;//ad开始第2个周波采集，定时器

	Fun_PC_Trig_Pulse_Init(  _RAISING_EDGE ) ;

	Fun_Get_Sys_Frequence( ) ;

	Fun_Thread_AD_Read_Info_Init_0506( ) ;

	Fun_Thread_AD_Read_Init_0506( ) ;


	TimeProc_Operation_Init() ;

	////////////////////////////////////////

//	Fun_Fifo_Len_Init( 2 , 1 ) ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnBtnDecode() 
{
	// TODO: Add your control notification handler code here
  //////////////////init the wplc protocol
	
  CComboBox  * p_combo ;

  int index = 0 ;

  CString  str1 , str2 ;

//  int  i ;

  stru_Meter_Read     meter_read_proto ;

  stru_Meter_Congeal   meter_congeal_proto ;
//////////user cmd set 
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_USER_CMD ) ;

  index = p_combo->GetCurSel( ) ;

  switch( index )
  {
  case 0 :
	  {
         meter_read_proto.uc_user_cmd = 0x02 ;

		 break ;
	  }
  case 1 :
	  {
         meter_read_proto.uc_user_cmd = 0x06 ;

		 break ;
	  }
  case 2 :
	  {
         meter_read_proto.uc_user_cmd = 0xF2 ;

		 break ;
	  }
  default:
	  break;
  }
/////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_MODULE_ADDR ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.un_module_addr.ldata = atoi( str1 ) ;


/////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_SUB_ADDR ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.uc_sub_meter_addr = ( atoi( str1 ) ) ;

/////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_PHASE ) ;

  index = p_combo->GetCurSel( ) ;

  switch( index )
  {
  case 0 :
	  {
        meter_read_proto.uc_phase_number = _PHASE_A ;

		break ;
	  }
  case 1 :
	  {
        meter_read_proto.uc_phase_number = _PHASE_B ;

		break ;
	  }
  case 2 :
	  {
        meter_read_proto.uc_phase_number = _PHASE_C ;

		break ;
	  }
  case 3 :
	  {
        meter_read_proto.uc_phase_number = _PHASE_ALL ;

		break ;
	  }
  default:
	  break;
  }

  /////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_STATION_NUMBER ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.uc_station_number= atoi( str1 ) ;
//////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_CONGEAL_TIME ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_congeal_proto.un_congeal_time.idata = atoi( str1 ) ;
//////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_SECTION_NUMBER ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.uc_section  = atoi( str1 ) ;
  //////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_LINE_NUMBER ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.uc_line_number  = atoi( str1 ) ;



 // Fun_WPLC_Data_Set( meter_read_proto ) ;

  //CMD_Buf_Init( ) ;

    //生成电表查询指令



   Meter_Read_Single( & meter_read_proto ) ;

 

/*
	if( send_flag == _PHASE_A )
	{
		g_uc_cmd_buf[ 0 ] = 0x68 ;
		
		g_uc_cmd_buf[ 1 ] = 0x11 ;
		
		g_uc_cmd_buf[ 2 ] = 0x22 ;
		
		g_uc_cmd_buf[ 3 ] = 0x00 ;
		
		g_uc_cmd_buf[ 4 ] = 0x00 ;
		
		g_uc_cmd_buf[ 5 ] = 0x0F ;
		
		g_uc_cmd_buf[ 6 ] = 0xFF ;
		
		g_uc_cmd_buf[ 7 ] = 0xF4 ;
		
		g_uc_cmd_buf[ 8 ] = 0x41 ;
		
		g_uc_cmd_buf[ 9 ] = 0x9D ;
		
		g_uc_cmd_buf[ 10 ] = 0xA9 ;
		
		g_uc_cmd_buf[ 11 ] = 0xD8 ;
		
		g_uc_cmd_buf[ 12 ] = 0x00 ;
		
		g_uc_cmd_buf[ 13 ] = 0x00 ;
		
		g_uc_cmd_buf[ 14 ] = 0x00 ;
		
        g_uc_cmd_buf[ 15 ] = 0x16 ;
	}
	else if( send_flag == _PHASE_B )
	{
		g_uc_cmd_buf[ 0 ] = 0x68 ;
		
		g_uc_cmd_buf[ 1 ] = 0x11 ;
		
		g_uc_cmd_buf[ 2 ] = 0x22 ;
		
		g_uc_cmd_buf[ 3 ] = 0x00 ;
		
		g_uc_cmd_buf[ 4 ] = 0x00 ;
		
		g_uc_cmd_buf[ 5 ] = 0x0F ;
		
		g_uc_cmd_buf[ 6 ] = 0xFF ;
		
		g_uc_cmd_buf[ 7 ] = 0xF4 ;
		
		g_uc_cmd_buf[ 8 ] = 0x41 ;
		
		g_uc_cmd_buf[ 9 ] = 0x9D ;
		
		g_uc_cmd_buf[ 10 ] = 0xA9 ;
		
		g_uc_cmd_buf[ 11 ] = 0xD8 ;
		
		g_uc_cmd_buf[ 12 ] = 0x00 ;
		
		g_uc_cmd_buf[ 13 ] = 0x00 ;
		
		g_uc_cmd_buf[ 14 ] = 0x00 ;
		
        g_uc_cmd_buf[ 15 ] = 0x16 ;
	}
	else if( send_flag == _PHASE_C )
	{
		g_uc_cmd_buf[ 0 ] = 0x68 ;
		
		g_uc_cmd_buf[ 1 ] = 0x11 ;
		
		g_uc_cmd_buf[ 2 ] = 0x22 ;
		
		g_uc_cmd_buf[ 3 ] = 0x00 ;
		
		g_uc_cmd_buf[ 4 ] = 0x00 ;
		
		g_uc_cmd_buf[ 5 ] = 0x0F ;
		
		g_uc_cmd_buf[ 6 ] = 0xFF ;
		
		g_uc_cmd_buf[ 7 ] = 0xF4 ;
		
		g_uc_cmd_buf[ 8 ] = 0x41 ;
		
		g_uc_cmd_buf[ 9 ] = 0x9D ;
		
		g_uc_cmd_buf[ 10 ] = 0xA9 ;
		
		g_uc_cmd_buf[ 11 ] = 0xD8 ;
		
		g_uc_cmd_buf[ 12 ] = 0x00 ;
		
		g_uc_cmd_buf[ 13 ] = 0x00 ;
		
		g_uc_cmd_buf[ 14 ] = 0x00 ;
		
        g_uc_cmd_buf[ 15 ] = 0x16 ;
	}

	else if( send_flag == _PHASE_ALL )
	{
		g_uc_cmd_buf[ 0 ] = 0x68 ;
		
		g_uc_cmd_buf[ 1 ] = 0x11 ;
		
		g_uc_cmd_buf[ 2 ] = 0x22 ;
		
		g_uc_cmd_buf[ 3 ] = 0x00 ;
		
		g_uc_cmd_buf[ 4 ] = 0x00 ;
		
		g_uc_cmd_buf[ 5 ] = 0x0F ;
		
		g_uc_cmd_buf[ 6 ] = 0xFF ;
		
		g_uc_cmd_buf[ 7 ] = 0xF4 ;
		
		g_uc_cmd_buf[ 8 ] = 0x41 ;
		
		g_uc_cmd_buf[ 9 ] = 0x9D ;
		
		g_uc_cmd_buf[ 10 ] = 0xA9 ;
		
		g_uc_cmd_buf[ 11 ] = 0xD8 ;
		
		g_uc_cmd_buf[ 12 ] = 0x00 ;
		
		g_uc_cmd_buf[ 13 ] = 0x00 ;
		
		g_uc_cmd_buf[ 14 ] = 0x00 ;
		
        g_uc_cmd_buf[ 15 ] = 0x16 ;
	}
    g_uc_cmd_buf[ 0 ] = 0x68 ;

    g_uc_cmd_buf[ 1 ] = 0x11 ;

    g_uc_cmd_buf[ 2 ] = 0x22 ;

    g_uc_cmd_buf[ 3 ] = 0x00 ;

    g_uc_cmd_buf[ 4 ] = 0x00 ;

    g_uc_cmd_buf[ 5 ] = 0x0F ;

    g_uc_cmd_buf[ 6 ] = 0xFF ;

    g_uc_cmd_buf[ 7 ] = 0xF4 ;
	
    g_uc_cmd_buf[ 8 ] = 0x41 ;

    g_uc_cmd_buf[ 9 ] = 0x9D ;
	
    g_uc_cmd_buf[ 10 ] = 0xA9 ;
	
    g_uc_cmd_buf[ 11 ] = 0xD8 ;
	
    g_uc_cmd_buf[ 12 ] = 0x00 ;
	
    g_uc_cmd_buf[ 13 ] = 0x00 ;
	
    g_uc_cmd_buf[ 14 ] = 0x00 ;

    g_uc_cmd_buf[ 15 ] = 0x16 ;

    g_uc_cmd_buf[ 14 ] = Fun_CRC_SUM( g_uc_cmd_buf , 16  ) ;

    //在指令发送窗口显示指令
    Fun_Protocol_Show( g_uc_cmd_buf  , _SHOW ) ;

	Fun_PC_Send_Data( g_uc_cmd_buf , 16 ) ;
*/
	int error_flag = 0xFF ;

//	OnBtnThreadTest( ) ;

/*	do 
	{
		Fun_PC_Send_Data( g_uc_cmd_buf , 16  ) ;
	} while ( 1 );

	CString   str1 ;
    //发送指令，接收握手零点，数零点个数，产生触发信号
	error_flag = Fun_Meter_Read_Single_Decode( ) ;
    //显示错误信息，-1代表：操作超时  1：操作成功 
	str1.Format( "%d" , error_flag ) ;
	
	MessageBox( str1 ) ;
*/


}
























#define    _AC_SHAKE_OK     0x53

#define    _TIME_MS_10      0.010

volatile   double     g_db_zero_delta_second = 0 ;

unsigned char         g_uc_trig_angle  ; //全局 ，触发角度 ，整型

HANDLE   hThread_Meter_Read ;

HANDLE   hEvent_Thread_Meter_Read_Enable ;














unsigned char    g_uc_meter_read_cmd_type  ; //读表命令是否是三相同时或者顺序,以便知道需要发送的指令总长度，是否需要发送buf2，buf3
//电流环握手成功后，读取表命令执行到有数据反馈所需的过零点个数
#define   _TIME_TRIG_CMD_READBACK_ZERO_NUMBER    ( 64 + 64 + 2 )  

#define   _MILL_SECOND_2000                 2000  

void CALLBACK CTestDlg:: Thread_Meter_Read( CTestDlg *pDlg )
{
   int   idata ;

   LARGE_INTEGER    time1 ;

   double  db_freq ;

   LONGLONG   shake_point ,  zero_point ;

   double     db_space , db_set_time ; 
   //send data parameter
   //get frequence 
   QueryPerformanceFrequency( &time1 ) ;

   db_freq = ( double ) time1.QuadPart ;
   
if( WaitForSingleObject( hEvent_Thread_Meter_Read_Enable , 0 ) == WAIT_OBJECT_0 )
 { 

	if( g_uc_meter_read_cmd_type = _PHASE_ALL )
	{
	  Fun_PC_Send_Data( g_uc_cmd_buf , 16 ) ;

	  Fun_PC_Send_Data( g_uc_cmd_buf2 , 16 ) ;

	  Fun_PC_Send_Data( g_uc_cmd_buf3 , 16 ) ;
	}
	else 
	{
	  Fun_PC_Send_Data( g_uc_cmd_buf , 16 ) ;
	}

	Fun_Operation_Timer_Set( _MILLSECOND_20 ) ;


		
	
	//read the io level
  //  idata = read_io(  ) ;//三项方波值在io的高位，数据在io的低位，两者互不影响。
	                     //read io返回一个字符类型的数据和一个字符类型的falg，数据为下位机所发送的数据
	                     //falg代表a，b，c三项是否是过零点

	if( idata == _AC_SHAKE_OK ) //handshake  ok
	{
       QueryPerformanceCounter( &time1 ) ;

	   shake_point = time1.QuadPart ;

       db_space = ( double ) ( shake_point - zero_point ) ;
       //以电流环过零点为判断依据，电流环握手时刻始终大于方波过零点时刻，当两者差值大于半个周期时，说明方波过零点在电流环过零点之后
	   //当两者差值小于半个周期时，说明方波过零点在电流环握手点之后。
	   if(  db_space >= _TIME_MS_10  )//电流环零点之后马上是方波过零点，或者电流环之前一个个周期的方波过零点
	   {
	     //方波过零点大于电流环零点
         g_db_zero_delta_second =  ( double ) db_space / db_freq ;
         /*
         db_set_time = _TIME_TRIG_CMD_READBACK_ZERO_NUMBER * _TIME_MS_20 
			             - g_db_zero_delta_second       //130 周波后时间点
						 ( 180 - g_uc_trig_angle ) * 1 / 18.0 ;//下一个周期正向过零点开始触发，
		                        //半个周波后开始触发，半个周波180 - 触发角度，然后转换成对应的时间。         
	     */
		  db_set_time =  0 - g_db_zero_delta_second   +    //130 周波后时间点
						 ( 180 - g_uc_trig_angle ) * 1 / 18.0 ;//下一个周期正向过零点开始触发，
		                        //半个周波后开始触发，半个周波180 - 触发角度，然后转换成对应的时间。         
	     
		 //开始数过零点个数

	//	 break ;
	   }
	   else
	   {
	     //方波过零点小于电流环零点
         g_db_zero_delta_second =  ( double ) db_space / db_freq ;

         db_set_time = _TIME_TRIG_CMD_READBACK_ZERO_NUMBER * _TIME_MS_10 
			             + g_db_zero_delta_second +      //130 周波后时间点
						 ( 180 - g_uc_trig_angle ) * 1 / 18.0 ;//下一个周期正向过零点开始触发，
		
	   }
	   
	 }
	//failing edge of io , 方波过零点
	if( idata == _ZERO )
	{
	  QueryPerformanceCounter( &time1 ) ;

	  zero_point = time1.QuadPart ;
	}

}

}




void CTestDlg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
/*
	g_uc_trig_angle_instent = 6000000 ;

	Fun_Thread_Trig_Timer_Raising_Init( ) ;

	SetEvent( hEvent_Thread_Trig_Timer_Raising_Enable ) ; 
*/
int  error_flag = 0xff ;

int  zero_times = 0 ;

CString  str1 ;
/*
////////////////////////////////
//////////////零点捕捉代码段，一次捕捉到一个零点，零点标志为：0x99 ,即_ZERO_PASS_FLAG宏定义的值////////////////
do 
{
	error_flag = Fun_PC_Zero_Cap( 1 ) ;

	if( error_flag == _OK )
	{
      zero_times ++ ;

	  str1.Format( "%d" , zero_times ) ;
		  
     // MessageBox( "捕捉到零点,零点：" + str1 ) ;
	  g_plab_zero_times->SetWindowText( "捕捉到零点,零点：" + str1 ) ;
	}

} while ( 1 );

//////////////////////trig信号测试代码段/////////////////////////////////////////////////////////////////////////
//trig信号使用PCI采集卡的IO9输出信号线，
//设置trig信号的初始状态设置,_FAILING_EDGE:trig 信号下降沿有效
Fun_PC_Trig_Pulse_Init(  _FAILING_EDGE ) ;
//产生下降沿
Fun_PC_Trig_Pulse(  _FAILING_EDGE ) ;

*/
//Fun_Read_And_Show_Data( ) ;


// int k = 0 ;

//Fun_PC_Zero_Cap( 65536 ) ;
Fun_AD_Trig_Soft( ) ;
//Fun_Data_Info_Get_Per_Tick( ) ;

}


  
void CTestDlg::OnBtnReadAngle() 
{
	// TODO: Add your control notification handler code here
	CButton    * btn ;

	CComboBox  *  combo ;

	unsigned char  uc_cmd_type = 0xFF ;
	////////////////////////////
	combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_SECTION ) ;

    int index = ( combo ->GetCurSel( ) ) ;

	if( index == 0 )
	{
      g_stru_read_angle.uc_section = 0x11 ;
	}
	else if( index == 1 )
	{
		g_stru_read_angle.uc_section = 0x22 ;
	}
	else if( index == 2 )
	{
		g_stru_read_angle.uc_section = 0x33 ;
	}
	else if( index == 3 )
	{
		g_stru_read_angle.uc_section = 0x44 ;
	}
    else
	{
		MessageBox( "请选择母线段！" ) ;

		return ;
	}

    ////////////////
	btn = ( CButton  * ) GetDlgItem( IDC_RBTN_A ) ;
	
	if( btn->GetCheck() )
	{
		g_stru_read_angle.uc_mcu_cmd = _READ_TRIG_ANGLE_A ;

	}

	/////////////////////////////
	btn = ( CButton  * ) GetDlgItem( IDC_RBTN_B ) ;
	
	if( btn->GetCheck() )
	{
		g_stru_read_angle.uc_mcu_cmd = _READ_TRIG_ANGLE_B ;

	}
	//////////////////////
	btn = ( CButton  * ) GetDlgItem( IDC_RBTN_C ) ;
	
	if( btn->GetCheck() )
	{
		g_stru_read_angle.uc_mcu_cmd = _READ_TRIG_ANGLE_C ;

	}
	btn = ( CButton  * ) GetDlgItem( IDC_RBTN_ABC ) ;
	
	if( btn->GetCheck() )
	{
		g_stru_read_angle.uc_mcu_cmd = _READ_TRIG_ANGLE_ALL ;

	}

      Read_Trig_Angle( &g_stru_read_angle  ) ;

	  Fun_Protocol_Show( g_uc_cmd_buf , _SHOW ) ;

	  Fun_PC_Send_Data( g_uc_cmd_buf , 16 ) ;

	  for( int i = 0 ; i < 65530 ; i ++ ) ;

	  Fun_PC_Recv_Data( 16 , 0x68 ) ;
	
}




void CTestDlg::OnRbtnA() 
{
	// TODO: Add your control notification handler code here

	
}


void CTestDlg::OnBtnSetAngle() 
{
	// TODO: Add your control notification handler code here
	CButton    * btn ;
	
	CComboBox  *  combo ;
	
	unsigned char  uc_cmd_type = 0xFF ;

	int index ;
	////////////////////////////
    ////////////////

  combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_SET_ANGLE_SECTION_NUMBER ) ;

  index = ( combo ->GetCurSel( ) ) ;

  if( index == 0x00 )
  {
    g_stru_set_angle_single.uc_section = 0x00 ;
  }
  else if( index == 0x01 )
  {
    g_stru_set_angle_single.uc_section = 0x01 ;
  }
  else
  {

    MessageBox( "请选择所在的母线段！") ;

	return ;

  }
//////////////////////////////////	
  btn = ( CButton  * ) GetDlgItem( IDC_RBTN_SET_A ) ;
	
  if( btn->GetCheck() )
  {
    g_stru_set_angle_single.uc_mcu_phase_number = _PHASE_A ;

	combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_ANGLE_A ) ;
	
    index = ( combo ->GetCurSel( ) ) ;
	
	if( index == 0 )
	{	
		g_stru_set_angle_single.uc_trig_angle = 15 ;
	}
	else if( index == 1 )
	{
		g_stru_set_angle_single.uc_trig_angle = 25 ;
	}
	else if( index == 2 )
	{
		g_stru_set_angle_single.uc_trig_angle = 30 ;
	}
	else if( index == 3 )
	{
		g_stru_set_angle_single.uc_trig_angle = 40 ;
	}
	else
	{
		MessageBox( "请选择A相角度！") ;
		
	    return ;
	}

	Set_Angle_Single( &g_stru_set_angle_single  ) ;

	Fun_Protocol_Show( g_uc_cmd_buf , _SHOW ) ;
  }
  //////////////////////////////////	
  btn = ( CButton  * ) GetDlgItem( IDC_RBTN_SET_B ) ;
  
  if( btn->GetCheck() )
  {
	  g_stru_set_angle_single.uc_mcu_phase_number = _PHASE_B ;
	  
	  combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_ANGLE_B ) ;
	  
	  index = ( combo ->GetCurSel( ) ) ;
	  
	  if( index == 0 )
	  {	
		  g_stru_set_angle_single.uc_trig_angle = 15 ;
	  }
	  else if( index == 1 )
	  {
		  g_stru_set_angle_single.uc_trig_angle = 25 ;
	  }
	  else if( index == 2 )
	  {
		  g_stru_set_angle_single.uc_trig_angle = 30 ;
	  }
	  else if( index == 3 )
	  {
		  g_stru_set_angle_single.uc_trig_angle = 40 ;
	  }
	  else
	  {
		  MessageBox( "请选择B相角度！") ;
		  
		  return ;
	  }

	Set_Angle_Single( &g_stru_set_angle_single  ) ;
	  
	Fun_Protocol_Show( g_uc_cmd_buf , _SHOW ) ;
  } 
  //////////////////////////////////	
  btn = ( CButton  * ) GetDlgItem( IDC_RBTN_SET_C ) ;
  
  if( btn->GetCheck() )
  {
	  g_stru_set_angle_single.uc_mcu_phase_number = _PHASE_C ;
	  
	  combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_ANGLE_C ) ;
	  
	  index = ( combo ->GetCurSel( ) ) ;
	  
	  if( index == 0 )
	  {	
		  g_stru_set_angle_single.uc_trig_angle = 15 ;
	  }
	  else if( index == 1 )
	  {
		  g_stru_set_angle_single.uc_trig_angle = 25 ;
	  }
	  else if( index == 2 )
	  {
		  g_stru_set_angle_single.uc_trig_angle = 30 ;
	  }
	  else if( index == 3 )
	  {
		  g_stru_set_angle_single.uc_trig_angle = 40 ;
	  }
	  else
	  {
		  MessageBox( "请选择C相角度！") ;
		  
		  return ;
	  }

	Set_Angle_Single( &g_stru_set_angle_single  ) ;
	  
	Fun_Protocol_Show( g_uc_cmd_buf , _SHOW ) ;
  }
  ////////////////////////////////////////////////////
  //////////////////////////////////////////////////////
  btn = ( CButton  * ) GetDlgItem( IDC_RBTN_SET_ABC ) ;
  
  if( btn->GetCheck() )
  {
	  g_stru_set_angle_single.uc_mcu_phase_number = _PHASE_ALL ;
	  
	  combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_ANGLE_C ) ;
	  
	  index = ( combo ->GetCurSel( ) ) ;
	  
	  if( index == 0 )
	  {	
		  g_stru_set_angle_all.uc_trig_angle_c = 15 ;
	  }
	  else if( index == 1 )
	  {
		  g_stru_set_angle_all.uc_trig_angle_c = 25 ;
	  }
	  else if( index == 2 )
	  {
		  g_stru_set_angle_all.uc_trig_angle_c = 30 ;
	  }
	  else if( index == 3 )
	  {
		  g_stru_set_angle_all.uc_trig_angle_c = 40 ;
	  }
	  else
	  {
		  MessageBox( "请选择C相角度！") ;
		  
		  return ;
	  }
///////////////////////////////////////
	  combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_ANGLE_A ) ;
	  
	  index = ( combo ->GetCurSel( ) ) ;
	  
	  if( index == 0 )
	  {	
		  g_stru_set_angle_all.uc_trig_angle_a = 15 ;
	  }
	  else if( index == 1 )
	  {
		  g_stru_set_angle_all.uc_trig_angle_a = 25 ;
	  }
	  else if( index == 2 )
	  {
		  g_stru_set_angle_all.uc_trig_angle_a = 30 ;
	  }
	  else if( index == 3 )
	  {
		  g_stru_set_angle_all.uc_trig_angle_a = 40 ;
	  }
	  else
	  {
		  MessageBox( "请选择A相角度！") ;
		  
		  return ;
	  }
	  ///////////////////////////
	  combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_ANGLE_B ) ;
	  
	  index = ( combo ->GetCurSel( ) ) ;
	  
	  if( index == 0 )
	  {	
		  g_stru_set_angle_all.uc_trig_angle_b = 15 ;
	  }
	  else if( index == 1 )
	  {
		  g_stru_set_angle_all.uc_trig_angle_b = 25 ;
	  }
	  else if( index == 2 )
	  {
		  g_stru_set_angle_all.uc_trig_angle_b = 30 ;
	  }
	  else if( index == 3 )
	  {
		  g_stru_set_angle_all.uc_trig_angle_b = 40 ;
	  }
	  else
	  {
		  MessageBox( "请选择B相角度！") ;
		  
		  return ;
	  }

	Set_Angle_All( &g_stru_set_angle_all  ) ;

	Fun_Protocol_Show( g_uc_cmd_buf , _SHOW  ) ;

  //  Fun_Protocol_Show( g_uc_cmd_buf2 , _SHOW_CONTINUE ) ;

//	Fun_Protocol_Show( g_uc_cmd_buf3 , _SHOW_CONTINUE ) ;
  }		
	  	
}



void CTestDlg::OnBtnCongealSend() 
{
	// TODO: Add your control notification handler code here
 /* CComboBox  * p_combo ;

  int index = 0 ;

  CString  str1 , str2 ;

//  int  i ;


  stru_Meter_Congeal   meter_congeal_proto ;

/////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_PHASE ) ;

  index = p_combo->GetCurSel( ) ;

  switch( index )
  {
  case 0 :
	  {
        meter_congeal_proto.uc_phase_number = _PHASE_A ;

		break ;
	  }
  case 1 :
	  {
        meter_congeal_proto.uc_phase_number = _PHASE_B ;

		break ;
	  }
  case 2 :
	  {
        meter_congeal_proto.uc_phase_number = _PHASE_C ;

		break ;
	  }
  case 3 :
	  {
        meter_congeal_proto.uc_phase_number = _PHASE_ALL ;

		break ;
	  }
  default:
	  break;
  }

  /////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_STATION_NUMBER ) ;

  p_combo->EnableWindow( false ) ; //GetWindowText( str1 ) ;

//////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_CONGEAL_TIME ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_congeal_proto.un_congeal_time.idata = atoi( str1 ) ;
//////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_SECTION_NUMBER ) ;

  p_combo->EnableWindow( false ) ; 
  //////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_LINE_NUMBER ) ;

  p_combo->EnableWindow( false ) ; 

  Meter_Congeal_Single( &meter_congeal_proto ) ;

  Fun_Protocol_Show( g_uc_cmd_buf  , _SHOW ) ;
  
 */	
}

void CTestDlg::OnSelendokComboUserCmd() 
{
	// TODO: Add your control notification handler code here    	
}







void CTestDlg::OnBtnAdTest() 
{
	// TODO: Add your control notification handler code here	
	int i = 0 ;
	
	SHORT   data_buf[ 32 ] ;

	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 
	
	unsigned int  data = 0x00 ;
	
//	unsigned char   recv_data ;
	
	//读取指令回复，len字节长度
	bool bflag_recv_start = false ;
	
	
	unsigned char recv_data_index = 0 ;	
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
    db_freq = ( double ) time1.QuadPart  ;

	QueryPerformanceCounter( &time1 ) ;  //得到起始时间
	
	db_start = time1.QuadPart ;	

	if( ! PCI8664_StartDeviceProAD( hDevice_AD ) )		// Start AD
	{
		MessageBox( "PCI8664_StartDeviceProAD Error..." ) ;
		
        return ;
	}

    while( ! PCI8664_ReadDeviceProAD_Npt( hDevice_AD, g_s_ad_fifo_buffer, 3000 , &nRetSizeWords ) ) ;
	
	QueryPerformanceCounter( &time1 ) ;  //得到当前时间
	
	db_end = time1.QuadPart ;
	
	db_space = ( double ) ( db_end- db_start ) ; //时间差
	
	db_space = db_space * 1000000 / db_freq  ;

    CString   str1 ;

	if( nRetSizeWords == 3000 )
	{
	   str1.Format("%lf" , db_space ) ;

       MessageBox( str1 ) ;
	}

    for( i = 0 ;i < 30 ; i ++ )
    {
		data_buf[ i ] = ( g_s_ad_fifo_buffer[ i ] ^ 0x0800 ) & 0x0FFF ;
	}	
	int  m = 0 ;
	
}

void CTestDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	for( int i = 0 ; i < 16 ; i ++ )

	   g_uc_send_io_data[ i ] = 0x00 ;//使CLK引脚输出高电平

	
	PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk信号

    PCI8664_ReleaseDeviceProAD( NULL ) ;

//	delete  hDevice_AD ;




	CDialog::OnClose();
}

void CTestDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	for( int i = 0 ; i < 16 ; i ++ )
		
		g_uc_send_io_data[ i ] = 0x00 ;//使CLK引脚输出高电平
	
	
	PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk信号
	
    PCI8664_ReleaseDeviceProAD( NULL ) ;

	CDialog::PostNcDestroy();
}



void CALLBACK Thread_Read_AD_Test( )
{
	int error_flag ;

	stru_AD_Data_Per_Tick    stru_data ;

	SHORT  data_buf[ 200 ] ;
	
	int  read_len = ( ADPara.LastChannel - ADPara.FirstChannel + 1 ) * 2;
							// first channel
	//ADPara.FirstChannel = 15 ;
	
	//ADPara.LastChannel	= _AD_SAMPLE_CHANNEL_MAX ;							// last channel
	


	LONGLONG   system_tick_count = 0 ;

	LONGLONG   system_tick_count_before = 0 ;

	LARGE_INTEGER    time1 ;

	QueryPerformanceCounter( &time1 ) ;  //得到起始时间
				
	system_tick_count_before = time1.QuadPart ;

	int  i ;

	double     delt_time[ 12000 ] ;

	int  delt_index = 0 ;

	double    time_start = system_tick_count_before ;

	do 
	{
		Fun_Operation_Timer_Set( _MILL_SECOND_2000 ) ;
///*
		if( !PCI8664_StartDeviceProAD( hDevice_AD ) )		// Start AD
		{
			AfxMessageBox( "PCI8664_StartDeviceProAD Error..." ) ;
			
		//	error_flag = _START_AD_CONVERT_ERROR ;
			continue ;
		}
//*/
		memset( data_buf , 0xFF , sizeof( data_buf ) ) ;
		 
        nRetSizeWords  = 0 ;
		
		if( !PCI8664_ReadDeviceProAD_Npt( hDevice_AD, data_buf, read_len, &nRetSizeWords ) )
		{
			char  message[ 256 ] ;
			
			PCI8664_GetLastErrorEx( "PCI8664_ReadDeviceProAD_Npt", message ) ;
			
		////	error_flag = _AD_READ_ERROR ;
			
			//	 break  ;
			continue ;
		}
		if( ( ULONG )nRetSizeWords == read_len )//读取到相应数据长度的数据
		{
			//  ResetEvent( hEvent_AD_Read_Per_Tick_Run ) ；
			
			SetEvent( hEvent_Thread_AD_Read_Data_Info_Run ) ;
			
			// ResetEvent( hEvent_Thread_AD_Read_Data_Run ) ;
			
			//	 PCI8664_StopDeviceProAD( hDevice_AD ) ;
			
			//PCI8664_ReleaseDeviceProAD( hDevice_AD ) ;
			
			//	 PCI8664_ReleaseDevice( hDevice );		// Release device object
	 
			//////////////////////////////////延时			
			QueryPerformanceCounter( &time1 ) ;  //得到起始时间
			
			system_tick_count = time1.QuadPart ;
			
			for( i = 0 ; i < _AD_SAMPLE_CHANNEL_MAX ; i ++ )
			{
				stru_data.data_line[ i ] = data_buf[ i ] ;
			}
			
			 stru_data.time_stamp = system_tick_count ;

			 double  t = ( system_tick_count - system_tick_count_before ) * 1000 / g_db_system_freguence ;

			 system_tick_count_before = system_tick_count ;

			 delt_time[ delt_index ] = t ;

			 delt_index ++ ;

			 if( delt_index == 10000 )
			 {
				 delt_time[ 0 ] = ( system_tick_count - time_start ) * 1000 / g_db_system_freguence ; 
                 
				 int max_times = 0 ;

				 int max_times_index[ 800 ] ;

				 int i , k ;

				 for( i = 0 , k = 0 ; i < 1000 ; i ++ )
				 {
                     if( delt_time[ i ] > 0.0165 )						 
					 {
                         max_times_index[ k ] = i ;

						 k++ ;

						 max_times++ ;                       
					 }
				 }
				 delt_index = 0 ;
			 }

	
		}

	} while ( 1 );

}



void  Fun_Thread_Read_AD_Test_Init( )
{
/////////////create a thread
hThread_Read_AD_Test = CreateThread( 0, 0, ( pfun_callback)Thread_Read_AD_Test , 0 , 
										  0 , &dwThreadID1 ) ; //CREATE_SUSPENDED , &dwThreadID1 ) ;

SetThreadPriority( hThread_Read_AD_Test , THREAD_PRIORITY_TIME_CRITICAL ) ;//THREAD_PRIORITY_NORMAL ) ;//THREAD_PRIORITY_ABOVE_NORMAL ) ; 

//hEvent_Thread_AD_Read_Test_Enable = CreateEvent( NULL , true , false , NULL) ;

}




void CTestDlg::OnBtnThreadTest() 
{
	// TODO: Add your control notification handler code here
//	PCI8664_StopDeviceProAD( hDevice_AD );   //stop AD data conversion
	/*
   Fun_Thread_AD_Read_Data_Info_Init( ) ;

   Fun_Thread_AD_Read_Data_Init( ) ;

   ResumeThread( hThread_AD_Read_Data ) ;

   ResumeThread( hThread_AD_Read_Data_Info ) ;

   SetEvent( hEvent_Thread_AD_Read_Data_Run ) ;

//   SetEvent( hEvent_Thread_AD_Read_Data_Info_Run ) ;
*/
	//	Fun_Operation_Timer_Set( _MILL_SECOND_2000 ) ;

Fun_Thread_Read_AD_Test_Init( ) ;

   
	// Fun_Data_Info_Get_Per_Tick( );


}

void CTestDlg::OnBtnRead() 
{
	// TODO: Add your control notification handler code here
	/////////////////////////////
	CButton     * btn ;

	int  send_flag = 0xFF ;

	/////////////////////////////
	btn = ( CButton  * ) GetDlgItem( IDC_BTN_READ_A ) ;
	
	if( btn->GetCheck() )
	{
		send_flag = _PHASE_A ;
		
	}
	/////////////////////////////
	btn = ( CButton  * ) GetDlgItem( IDC_BTN_READ_B ) ;
	
	if( btn->GetCheck() )
	{
		send_flag = _PHASE_B ;		
	}
	/////////////////////////////
	btn = ( CButton  * ) GetDlgItem( IDC_BTN_READ_C ) ;
	
	if( btn->GetCheck() )
	{
		send_flag = _PHASE_C ;		
	}
	/////////////////////////////
	btn = ( CButton  * ) GetDlgItem( IDC_BTN_READ_ABC ) ;
	
	if( btn->GetCheck() )
	{
		send_flag = _PHASE_ABC ;		
	}
	/////////////////////////////
	btn = ( CButton  * ) GetDlgItem( IDC_BTN_READ_ABC_SEQUENCE ) ;
	
	if( btn->GetCheck() )
	{
		send_flag = _PHASE_ABC_SEQUENCE ;		
	}

	if( send_flag == 0xFF )
	{
		AfxMessageBox( "Please select the phase to read!" ) ;

		return ;
	}

/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
    int  error_flag = 0xFF ;

    unsigned  char  A[ 16 ] ;

    unsigned  char  B[ 16 ] ;

    unsigned  char  C[ 16 ] ;

//    unsigned  char  ABC[ 16 ] ;

	if( send_flag ==  _PHASE_A )
	{
		A[0]=0x68;
		A[1]=0x11;
		A[2]=0x21;
		A[3]=0x00;
		A[4]=0x00;
		A[5]=0x3e;
		A[6]=0xf3;
		A[7]=0x9f;
		A[8]=0x41;
		A[9]=0xf8;
		A[10]=0xff;
		A[11]=0x0f;
		A[12]=0x00;
		A[13]=0x00;
		A[14]=0x00;
		A[15]=0x16;
		
		A[ 14 ] = Fun_CRC_SUM( A , 16  ) ;
		
		Fun_PC_Send_Data( A , 16 ) ;

		error_flag = Fun_PC_Recv_Data( 0x68 ) ;

		if( error_flag == _TIMEOUT )
		{
			MessageBox("Recv Time out!") ;

		    return ;
		}

	//	int a = 0 ;
   } 
  else if( send_flag ==  _PHASE_B )
	{
        B[0]=0x68;
		B[1]=0x11;
		B[2]=0x22;
		B[3]=0x00;
		B[4]=0x00;
		B[5]=0xd8;
		B[6]=0xa9;
		B[7]=0x9d;
		B[8]=0x41;
		B[9]=0xf4;
		B[10]=0xff;
		B[11]=0x0f;
		B[12]=0x00;
		B[13]=0x00;
		B[14]=0x00;
		B[15]=0x16;
		
		B[ 14 ] = Fun_CRC_SUM( B , 16  ) ;
		
		Fun_PC_Send_Data( B , 16 ) ;

		error_flag = Fun_PC_Recv_Data( 0x68 ) ;
		
		if( error_flag == _TIMEOUT )
		{
			MessageBox("Recv Time out!") ;

			return ;
		}

   } 
  else if( send_flag ==  _PHASE_C )
  {
	  C[0]=0x68;
	  C[1]=0x11;
	  C[2]=0x23;
	  C[3]=0x00;
	  C[4]=0x00;
	  C[5]=0x7a;
	  C[6]=0x60;
	  C[7]=0x9c;
	  C[8]=0x41;
	  C[9]=0xf0;
	  C[10]=0xff;
	  C[11]=0x0f;
	  C[12]=0x00;
	  C[13]=0x00;
	  C[14]=0x00;
	  C[15]=0x16;
	  
	  C[ 14 ] = Fun_CRC_SUM( C , 16  ) ;
	  
	  Fun_PC_Send_Data( C , 16 ) ;

		error_flag = Fun_PC_Recv_Data( 0x68 ) ;
		
		if( error_flag == _TIMEOUT )
		{
			MessageBox("Recv Time out!") ;

			return ;
		}

   }



  error_flag = Fun_Get_Info_AD_Start( ) ;



  


}

void CTestDlg::OnBtnThreadTestStop() 
{
	// TODO: Add your control notification handler code here
    HANDLE   hdevice = PCI8664_CreateDevice( 0 ) ;

	PCI8664_ReleaseDeviceProAD( hdevice );
	
	PCI8664_ReleaseDevice( hdevice ) ;
	
//	PCI8664_StopDeviceProAD( ( hDevice_AD ) ) ;
	
	PCI8664_ReleaseDeviceProAD( hDevice_AD );
	
	PCI8664_ReleaseDevice( hDevice_AD ) ;
	
	TerminateThread( hThread_Read_AD_Test  ,  0 ) ;
	
	int   a = 0 ;	
}





