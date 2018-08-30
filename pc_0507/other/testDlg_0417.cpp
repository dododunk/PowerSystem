// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "protocol.h"




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
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_LAB_PROTO_SEND, m_static_protocol_data);
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

	Fun_PC_CLK_Init() ;

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

  if( meter_read_proto.uc_phase_number == _PHASE_ALL )
  {
      //Meter_Read_Single( & meter_read_proto ) ;
  }
  else
  {
    Meter_Read_Single( & meter_read_proto ) ;



	Fun_PC_Send_Data( g_uc_cmd_buf , 16 ) ;

    Fun_Protocol_Show( g_uc_cmd_buf  , _SHOW ) ;
  }






}
























#define    _AC_SHAKE_OK     0x53

#define    _TIME_MS_10      0.010

volatile   double     g_db_zero_delta_second = 0 ;

unsigned char         g_uc_trig_angle  ; //全局 ，触发角度 ，整型

HANDLE   hThread_Meter_Read ;

HANDLE   hEvent_Thread_Meter_Read_Enable ;














unsigned char    g_uc_meter_read_cmd_type  ; //读表命令是否是三相同时或者顺序,以便知道需要发送的指令总长度，是否需要发送buf2，buf3
//电流环握手成功后，读取表命令执行到有数据反馈所需的过零点个数
#define   _TIME_TRIG_CMD_READBACK_ZERO_NUMBER    ( 64 + 2 )   

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






void CTestDlg:: Fun_PC_Zero_Cap_init( )
{
  /////////////create a thread
  hThread_Meter_Read = CreateThread( 0, 0, ( pfun_callback)Thread_Meter_Read, this , 
											  CREATE_SUSPENDED , &dwThreadID1 ) ;

  SetThreadPriority( hThread_Meter_Read , THREAD_PRIORITY_ABOVE_NORMAL ) ; 

  hEvent_Thread_Meter_Read_Enable = CreateEvent( NULL , true , false , NULL) ; 
}


void CTestDlg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
//	

//	else
	{
    g_uc_cmd_buf[ 0 ] = 0xFA ;
	
    g_uc_cmd_buf[ 1 ] = 0x0A ;

	g_uc_cmd_buf[ 2 ] = 0xFF ;

    g_uc_cmd_buf[ 3 ] = 0xA0 ;
			
	g_uc_cmd_buf[ 4 ] = 0x5A ;
	///////

    g_uc_cmd_buf[ 0 ] = 0x68 ;

    g_uc_cmd_buf[ 15 ] = 0x99 ;

	    g_uc_cmd_buf[ 12 ] = 0xAA ;

  //  do  
   // {
		
		Fun_PC_Send_Data( g_uc_cmd_buf , 16 ) ;



		Fun_PC_Recv_Data( 16 , 0x68 ) ;

	//	Fun_PC_Send_Data( &g_uc_cmd_buf[ 0 ] , 1 ) ;

		//g_uc_recv_io_data

		int k = 0 ;

  //  } while ( 1 );
	}

	int i = 0 ;
}


stru_Set_Angle_Single   g_stru_set_angle_single ;

stru_Set_Angle_All      g_stru_set_angle_all ;

stru_Read_Angle         g_stru_read_angle ;


  
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
