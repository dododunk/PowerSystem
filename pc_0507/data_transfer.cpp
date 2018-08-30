
#include "stdafx.h"

#include   "global.h"

#include   "init.h"

#include   "timer.h"

#include   "data_transfer.h"






BYTE    g_uc_send_io_data[ 16 ] ;

BYTE    g_uc_recv_io_data[ 16 ] ;

unsigned char   g_uc_PC_RX_Buf[ 16 ] ; //pc机读写指令即触发引脚读写和设置指令的反馈数据


unsigned char     g_uc_zero_pass_times = 0 ;//接收到的过零点个数

unsigned char     g_uc_zero_times = 0 ;


#define           _ZERO_TIMES    5


#define     _DEBUG_MESSAGE_ZERO_TIMES_SHOW
 //************************************




// Method:    Fun_PC_CLK_Init
// FullName:  Fun_PC_CLK_Init
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void  Fun_PC_CLK_Init()
{
	int i ;

	if( g_ad_device_init == false )
	{
		hDevice_AD = PCI8664_CreateDevice( 0 );
		
		if( hDevice_AD == INVALID_HANDLE_VALUE ) 
		{
			AfxMessageBox( "init error!") ;
			
			g_ad_device_init =  false ;
		}
		else
		{
			g_ad_device_init = true ;
		}
	}
    
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_send_io_data[ i ] = 0x00 ;
	}
	
    g_uc_send_io_data[ 8 ] = 0x00 ;//clk  低电平。上升沿pc放数据，mcu下降沿读取数据。

    g_uc_send_io_data[ 9 ] = 0x00 ;//trig  低电平。上升沿mcu开始trig信号。
				
	PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出数据和clk信号
	
}
//************************************
// Method:    Fun_Send_Data_Set
// FullName:  Fun_Send_Data_Set
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned char data
//************************************
void Fun_Send_Data_Set( unsigned char data )
{
	g_uc_send_io_data[0] = data & 0x01 ;  
    
	g_uc_send_io_data[1] = ( data >> 1 ) & 0x01 ; 
	
	g_uc_send_io_data[2] = ( data >> 2 ) & 0x01 ; 
	
	g_uc_send_io_data[3] = ( data >> 3 ) & 0x01 ; 
	
	g_uc_send_io_data[4] = ( data >> 4 ) & 0x01 ; 
	
	g_uc_send_io_data[5] = ( data >> 5 ) & 0x01 ;
	
	g_uc_send_io_data[6] = ( data >> 6 ) & 0x01 ; 
	
	g_uc_send_io_data[7] = ( data >> 7 ) & 0x01 ; 
	
	g_uc_send_io_data[8] = 0x00 ;
	
	g_uc_send_io_data[9] = 0x00 ; 
	
	g_uc_send_io_data[10] = 0x00 ;
	
	g_uc_send_io_data[11] = 0x00 ;
	
	g_uc_send_io_data[12] = 0x00 ;
	
	g_uc_send_io_data[13] = 0x00 ;
	
	g_uc_send_io_data[14] = 0x00 ;
	
	g_uc_send_io_data[15] = 0x00 ; 
	
}



//************************************
// Method:    Fun_Recv_Data_Set
// FullName:  Fun_Recv_Data_Set
// Access:    public 
// Returns:   unsigned char
// Qualifier:
// Parameter: BYTE * data
//************************************
unsigned char Fun_Recv_Data_Set( BYTE  * data )
{
	unsigned char   recv_data = 0x00 ;
	
	int  i ;
	
	for( i = 0 ;i < 8 ; i ++ )
	{
		recv_data += ( * ( data + i ) & 0x01 ) << i  ;
	} 
    return  recv_data ; 
	
}

//************************************
// Method:    Fun_PC_Recv_Data
// FullName:  Fun_PC_Recv_Data
// Access:    public 
// Returns:   int,1:read or write ok ,the caller get the feedback 
                    //datas from the buffer g_uc_PC_RX_Buf[ 16 ]
// Qualifier:
// Parameter: int len
// Parameter: unsigned char start_flag
//************************************
int  Fun_PC_Recv_Data( int len , unsigned char start_flag ) 
{
	return  1 ;
}


int   Fun_PC_Recv_Data( unsigned char start_flag )
{

	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 
	
	unsigned int  data = 0x00 ;

	unsigned char   recv_data ;
	
	//读取指令回复，len字节长度
	bool bflag_recv_start = false ;

	int len = 0x0F ; 
	
	
	unsigned char recv_data_index = 0 ;	
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
    db_freq = ( double ) time1.QuadPart  ;

	Fun_Operation_Timer_Set( 600 ) ;
	
  do 
  {  
	 if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
	 {
        return   _TIMEOUT ;
	 }
	 else
	 {
	   g_uc_send_io_data[ 8 ] = 0x01 ;//使CLK引脚输出高电平
		
	   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk信号
		
		QueryPerformanceCounter( &time1 ) ;  //得到起始时间
		
		db_start = time1.QuadPart ;
		
		do
		{    
			QueryPerformanceCounter( &time1 ) ;  //得到当前时间
			
			db_end = time1.QuadPart ;
			
			db_space = ( double ) ( db_end- db_start ) ; //时间差
			
			db_space = db_space / db_freq ;
			
		}   
		while( db_space < _100K_CLK ) ;  //时间差小于100K
		
		//低电平时间到,读取数据
		
		PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;

		recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;

        //recv_data = (unsigned char ) data & 0xFF ;
		
		if( recv_data == start_flag && bflag_recv_start ==  false ) //the start of readback data
		{
			bflag_recv_start = true ;
			
			g_uc_PC_RX_Buf[ 0 ] = recv_data ;
			
			recv_data_index ++ ; 

		    Fun_Operation_Timer_Set( 600 ) ;
		}
		else if( bflag_recv_start == true )
		{
			g_uc_PC_RX_Buf[ recv_data_index ] = recv_data ;

			recv_data_index ++ ;

		//	if( recv_data_index == _UP_FRAME_DATA_LEN_BYTE )

			//	 len = g_uc_PC_RX_Buf[ recv_data_index ] + _UP_FRAME_DATA_LEN_BYTE + 2 ;

		//	len = 16 ;
		    Fun_Operation_Timer_Set( 600 ) ;
			
		}

		/////////////////////////////
		g_uc_send_io_data[ 8 ] = 0x00 ;  //使CLK引脚输出di电平
		
		PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;

		//定时100K，保持低电平
		QueryPerformanceCounter( &time1 ) ;  //得到起始时间
		
		db_start = time1.QuadPart ;
		
		do
		{    
			QueryPerformanceCounter( &time1 ) ;  //得到当前时间
			
			db_end = time1.QuadPart ;
			
			db_space = ( double ) ( db_end- db_start ) ; //时间差
			
			db_space = db_space / db_freq ;
			
		}   while( db_space < _100K_CLK ) ;  //时间差小于100K
		
	} //else , not timeout
  }
  while( recv_data_index < len  ) ;//判断读取数据的个数
                          //是否达到协议规定的数据长度，否则返回继续读取下一个字节

//   Fun_Protocol_Show_Recv( g_uc_PC_RX_Buf  , _SHOW ) ;

  //return g_uc_PC_RX_Buf ;
  return  1 ;

}


//************************************
// Method:    Fun_PC_Send_Data
// FullName:  Fun_PC_Send_Data
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned char * buf
// Parameter: int len
//************************************
void  Fun_PC_Send_Data( unsigned char * buf , int len )
{
	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 

	int i ;		
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
    db_freq = ( double ) time1.QuadPart  ;

   //发送指令 
   for( i = 0 ; i < len ; i ++ )
   {     
	  // send_data = buf[ i ] | _BIT8_CLK_HIGH  ;  //使CLK引脚输出高电平，同时输出数据放置到低八位

	   Fun_Send_Data_Set( buf[ i ] ) ; 

	   g_uc_send_io_data[ 8 ] = 0x01 ;

	   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出数据和clk信号
	   
	   QueryPerformanceCounter( &time1 ) ;  //得到起始时间
	   
	   db_start = time1.QuadPart ;
	   ////////定时100k , 保持高电平
	   do
	   {    
		   QueryPerformanceCounter( &time1 ) ;  //得到当前时间
		   
		   db_end = time1.QuadPart ;
		   
		   db_space = ( double ) ( db_end- db_start ) ; //时间差
		   
		   db_space = db_space / db_freq ;
		   
	   }   
	   while( db_space < _100K_CLK ) ;  //时间差小于100K
	   
	   g_uc_send_io_data[ 8 ] = 0x00   ;  //使CLK引脚输出di电平，同时输出数据放置到低八位
	   
	   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;
	   ////////定时100k ，保持低电平
	   QueryPerformanceCounter( &time1 ) ;  //得到起始时间
	   
	   db_start = time1.QuadPart ;
	   
	   do
	   {    
		   QueryPerformanceCounter( &time1 ) ;  //得到当前时间
		   
		   db_end = time1.QuadPart ;
		   
		   db_space = ( double ) ( db_end- db_start ) ; //时间差
		   
		   db_space = db_space / db_freq ;
		   
	   }   
	   while( db_space < _100K_CLK ) ;  //时间差小于100K
   }//for
	
}



int  Fun_PC_Zero_Cap( int zero_pass_number )
{
	unsigned char recv_data = 0 ; 
	
	g_uc_zero_pass_times = 0 ;

	unsigned char    uc_handshake_ok_times = 0 ;
	
	//发送指令 
	do
	{   
	   g_uc_zero_times = 0 ;

	   do //
	   {					
			//每次等待接收零点确认时，如果超时，则返回
			if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
			{
				return   _TIMEOUT ;
			}
			//////////////
			recv_data = 0xFF ;

			PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
			
			recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
			
			recv_data = (unsigned char ) recv_data & 0xFF ;

		//	Fun_Read_And_Show_Data( recv_data ) ;
			
 			if( recv_data == _ZERO_PASS_FLAG  ) //the flag of the DTU zero pass
			{
			  g_uc_zero_times ++ ;

              if( g_uc_zero_times >= _ZERO_TIMES )
			  {
				g_uc_zero_times = 0 ;

				Fun_Operation_Timer_Stop( ) ; //捕捉成功，停止计时，以防定时器溢出
				
                g_uc_zero_pass_times ++ ;
 
				//产生一个clk周波，即clk拉低200k，完成一个数据接收周期
				g_uc_send_io_data[ 8 ] = 0x01 ;//使CLK引脚输出gao电平
				
				PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk high 信号			
				/////////////////////////////////////////////

			//	Fun_Operation_Timer_Set( _MILLSECOND_20  ) ; //捕捉成功，停止计时，以防定时器溢出
                Fun_Delay_Usecond( 1000 ) ;  //100us 

				uc_handshake_ok_times = 0 ; 



				do 
				{								   
				   recv_data = 0xFF ;

				   PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
				
				   recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
				
			       recv_data = (unsigned char ) recv_data & 0xFF ;

				   //Fun_Read_And_Show_Data( recv_data ) ;

				   if( recv_data == _ZERO_HANDSHAKE_FLAG )//0x00
				   {
					   uc_handshake_ok_times ++ ;

					   if( uc_handshake_ok_times >= _ZERO_TIMES )
					   {
						   break ;
					   }
				   }
				   else //if recv_dat not 0x00
				   {
                       uc_handshake_ok_times = 0 ;
				   }

				   if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
				   {
					   return   _TIMEOUT ;
				   }

				} while ( 1 );

			   g_uc_send_io_data[ 8 ] = 0x00 ;//使CLK引脚输出di电平
					
			   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk high 信号			

           //    Fun_Operation_Timer_Set( _MILLSECOND_20  ) ;
			   ////////////////////////////////
               #ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
				{
					CString    str1 ;
					
					str1.Format( "过零点个数：%d" , g_uc_zero_pass_times ) ;
					
					g_plab_zero_times->SetWindowText( str1 ) ;
					
				}
              #endif
				break ;//捕捉到零点，本次捕捉流程结束，开始下次捕捉流程
			  }//if 3 times

			}//if zero cap			 
		    else //not zero cap
			{
		       g_uc_zero_times = 0 ;
			}

		}//高电平等待零点不断轮询流程 
		while( 1 ) ;
	}
	while( g_uc_zero_pass_times < zero_pass_number  ) ;//判断读取数据的个数
                          //是否达到协议规定的数据长度，否则返回继续读取下一个字节 ;//，单次捕捉流程循环
 return 1 ;
}



//************************************
// Method:    Fun_PC_Zero_Cap_Firstly
// FullName:  Fun_PC_Zero_Cap_Firstly
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int  Fun_PC_Zero_Cap_Firstly( )
{
	
	int error_flag = 0  ;	
	
	unsigned char recv_data = 0 ; 
 		
//	Fun_Operation_Timer_Set( _MILLSECOND_20 ) ;//start other circle timer

	g_uc_zero_times = 0 ;
		
	do //
	{					
	  //每次等待接收零点确认时，如果超时，则返回
	  if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
	  {
		 return   _TIMEOUT ;
	  }
	  //////////////
	  recv_data = 0xFF ;

	  PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
			
	  recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
			
	  recv_data = (unsigned char ) recv_data & 0xFF ;
			
	  if( recv_data == _ZERO_PASS_FLAG  ) //the flag of the DTU zero pass
	  {
        g_uc_zero_times ++ ;

		if( g_uc_zero_times >= _ZERO_TIMES )
		{
		  g_uc_zero_times = 0 ;
		  
		  Fun_Operation_Timer_Stop( ) ; //捕捉成功，停止计时，以防定时器溢出

		  for( int i = 0 ; i < 65535 ; i ++ ) ;
				
		  //产生一个clk周波，即clk拉低200k，完成一个数据接收周期
		  g_uc_send_io_data[ 8 ] = 0x01 ;//使CLK引脚输出gao电平
				
		  PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk high 信号			
	
		  //第一个零点后，马上开始接收电流环数据		
          error_flag = Fun_PC_Recv_Data( 16 , 0x68 ) ;

		  if( error_flag == _TIMEOUT )
		  {
            return _TIMEOUT ;
		  }
				
		  ////////////////////////////////
		  break ;//捕捉到零点，本次捕捉流程结束，开始下次捕捉流程
		}//if three times

	  }//if zero cap 
	  else
	  {
		  g_uc_zero_times = 0 ;
	  }
	}//高电平等待零点不断轮询流程 
	while( 1 ) ;

  return 1 ;
}




int  Fun_PC_Trig_Pulse_Init(  bool   edge_type )
{
  if( edge_type == _FAILING_EDGE )
  {
	/////clk high 	
	g_uc_send_io_data[ 9 ] = 0x01 ;
	  
	PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出数据和clk信号
  }
  if( edge_type == _RAISING_EDGE )
  {
	  /////clk high 	
	  g_uc_send_io_data[ 9 ] = 0x00 ;
	  
	  PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出数据和clk信号
  }

  return 1 ;
}



int  Fun_PC_Trig_Pulse(  bool   edge_type )
{
	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 
		
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
	db_freq = ( double ) time1.QuadPart  ;

	if( edge_type == _RAISING_EDGE )
	{
	    /////clk high and wait fot the zero pass	
	    g_uc_send_io_data[ 9 ] = 0x01 ;
	
	    PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出数据和clk信号

		//////////////////////////////////延时			
	    QueryPerformanceCounter( &time1 ) ;  //得到起始时间
	
	    db_start = time1.QuadPart ;
	    //延时输出clk信号		
	   do
	   {    
		  QueryPerformanceCounter( &time1 ) ;  //得到当前时间
		
		  db_end = time1.QuadPart ;
		
		  db_space = ( double ) ( db_end- db_start ) ; //时间差
		
		  db_space = db_space / db_freq ;
		
	   }   
	   while( db_space < _100K_CLK ) ;  //时间差小于100K
	   /////clk low	
	   g_uc_send_io_data[ 9 ] = 0x00 ;
	   
	   PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出数据和clk信号	
	}
	else if( edge_type == _FAILING_EDGE )
	{
		/////clk high and wait fot the zero pass	
		g_uc_send_io_data[ 9 ] = 0x00 ;
		
		PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出数据和clk信号
		
		//////////////////////////////////延时			
		QueryPerformanceCounter( &time1 ) ;  //得到起始时间
		
		db_start = time1.QuadPart ;
		//延时输出clk信号		
		do
		{    
			QueryPerformanceCounter( &time1 ) ;  //得到当前时间
			
			db_end = time1.QuadPart ;
			
			db_space = ( double ) ( db_end- db_start ) ; //时间差
			
			db_space = db_space / db_freq ;
			
		}   
		while( db_space < _100K_CLK ) ;  //时间差小于100K
		/////clk low	
		g_uc_send_io_data[ 9 ] = 0x01 ;
		
		PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出数据和clk信号	
	}
	   return 1 ;
}



