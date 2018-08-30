
#include  "header.h"


#define   _DEBUG_MESSAGE_ZERO_TIMES_SHOW


stru_AD_Data_Per_Tick        g_stru_ad_data[ 306300 ] ;

unsigned long                g_stru_ad_data_index = 0 ;

stru_AD_Info_Per_Tick_0506   g_stru_ad_data_info[ 390 ] ;

ULONG                        g_stru_ad_info_index = 0 ;                     

HANDLE      hThread_Read_AD_0506 ;  

ULONG       g_ad_stru_len_per_tick = 0 ; 

HANDLE   	hEvent_Thread_Read_AD_Stop_0506 ;

HANDLE      hThread_Read_AD_Info_0506 ;  

HANDLE   	hEvent_Thread_Read_AD_Info_Stop_0506 ;

ULONG      info_get_times_0506 = 0 ; 


void Fun_Stop_Thread_Read_AD_0506( )
{
 SetEvent( hEvent_Thread_Read_AD_Stop_0506 ) ;
}
void Fun_Start_Thread_Read_AD_0506( )
{
  ResumeThread( hThread_Read_AD_0506 ) ;	
}



void CALLBACK Thread_Read_AD_0506( )
{
//	int error_flag ;
	
    ULONG  len = g_ad_stru_len_per_tick ;

	SHORT    * data_buf ;
    	
	data_buf = new SHORT[ len ] ;
	
	int i = 0 ;
   //  Fun_Operation_Timer_Set( _MILLSECOND_2000  ) ;	
do 
{
	 if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
	 {
         SuspendThread( Thread_Read_AD_0506 ) ; 
		// return   _TIMEOUT ;
	 }  
	 if( WaitForSingleObject( hEvent_Thread_Read_AD_Stop_0506  , 0 ) == WAIT_OBJECT_0 ) 
	{
	   	delete [ ] data_buf ;
		
		break ;
	 }
	 else
	 {
	 // Fun_Operation_Timer_Set( _MILLSECOND_2000 ) ;
		
	  if( !PCI8664_StartDeviceProAD( hDevice_AD ) )		// Start AD
		{
			AfxMessageBox( "PCI8664_StartDeviceProAD Error..." ) ;			
			//	error_flag = _START_AD_CONVERT_ERROR ;
			continue ;
		}
		memset( data_buf , 0xFF , sizeof( data_buf ) ) ;
		
        nRetSizeWords  = 0 ;
		
		if( !PCI8664_ReadDeviceProAD_Npt( hDevice_AD, data_buf, len, &nRetSizeWords ) )
		{
			char  message[ 256 ] ;
			
			PCI8664_GetLastErrorEx( "PCI8664_ReadDeviceProAD_Npt", message ) ;
			
			////	error_flag = _AD_READ_ERROR ;
			
			//	 break  ;
			continue ;
		}
		if( ( ULONG )nRetSizeWords == len )//读取到相应数据长度的数据
		{
			
			LARGE_INTEGER    time1 ;	 
			//////////////////////////////////延时			
			QueryPerformanceCounter( &time1 ) ;  //得到起始时间
						
			for( i = 0 ; i < len ; i ++ )
			{
				g_stru_ad_data[ g_stru_ad_data_index ].data_line[ i ] = data_buf[ i ] ;
			}
			
			g_stru_ad_data[ g_stru_ad_data_index ].time_stamp = time1.QuadPart ;;
			
			g_stru_ad_data_index ++ ; 
/*
			if( g_stru_ad_data_index >= 300 )
			{
			//	g_stru_ad_data_index = 0 ;
				
				SuspendThread( Thread_Read_AD_0506 ) ;
			}
*/			
			if( g_stru_ad_data_index >= 306300 )
			{
				g_stru_ad_data_index = 0 ;

				SuspendThread( Thread_Read_AD_0506 ) ;
			}	
		}
	 }//else run
		
	} while ( 1 );

	return ;
	
}









void CALLBACK Thread_AD_Read_Info_0506( )
{
do 
{
if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
{
	ResetEvent( hEvent_Operation_Timer_Timeout ) ;	
	
	SuspendThread( hThread_Read_AD_Info_0506 ) ;
}	 	
  unsigned  int   tick_valid_times = 0 ;

  unsigned  int   no_data_info_times = 0 ;

  unsigned  char  recv_data = 0xFF ;

 // stru_AD_Data_Info_Per_Tick    data_info ;

  LONGLONG    system_tick_count = 0 ;

  unsigned  char   uc_handshake_ok_times = 0 ;
  
  g_bflag_data_info_end = false ;

  long   info_get_times = 0 ;

  Fun_Operation_Timer_Set( 12000  ) ;// 12s 读取数据相位信息操作是否超时定时器			   ////////////////////////////////	  
	do //
	{					
	  //每次等待接收零点确认时，如果超时，则返回
	  if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
	  {
        int i , k ;

		int delta_data_number_max = 0 ;

	    int delta_data_number_min = 0xFFF ;

		long delta_max_index = 0 ;

		long delta_min_index = 0 ;

		long  delta = 0 ;

		for( i = 0 ; i < 383 ; i += 2 )
		{
          delta = abs( g_stru_ad_data_info[ i + 1 ].ad_data_index - 
			      g_stru_ad_data_info[ i ].ad_data_index ) ;

		  if( delta >= delta_data_number_max )
		  {
            delta_data_number_max = delta ;

			delta_max_index = i ;

		  }
		  if( delta <= delta_data_number_min )
		  {
			  delta_data_number_min = delta ;
			  
			  delta_min_index = i ;			  
		  }

		}

		break ;  
	  }
	  //////////////
	  recv_data = 0xFF ; //初始设置读取的值

	  PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
			
	  recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
			
	  recv_data = (unsigned char ) recv_data & 0xFF ;

	//	Fun_Read_And_Show_Data( recv_data ) ;
			
 	  if( recv_data == _DATA_INFO_A_ECTION1 ||
		  recv_data == _DATA_INFO_A_ECTION2 ||
		  recv_data == _DATA_INFO_A_ECTION3 ||
		  recv_data == _DATA_INFO_END ) //the flag of the DTU zero pass
	  {
		  tick_valid_times ++ ; //连续读取到数据信息计数累加

		  no_data_info_times = 0; //没有数据信息连续读取次数清零

          if( tick_valid_times >= _TICK_VALID_TIMES )//连续读取次数到
		  {
			  info_get_times_0506  ++ ;  //调试用显示次数累加
			 ///////////get the data information
             if( recv_data == _DATA_INFO_END )
			 {
			    g_bflag_data_info_end = true ;

			//	SetEvent( hEvent_AD_Data_Info_End ) ;//停止ad数据读取线程
			 }
			// if( g_bflag_data_info_end == false )
			 {
			   g_stru_ad_data_info[ g_stru_ad_info_index ].data_info = recv_data ;

			   g_stru_ad_data_info[ g_stru_ad_info_index ].ad_data_index = g_stru_ad_data_index ;

			   g_stru_ad_info_index ++ ;

			   //Func_Fifo_Info_Push_Down( ) ;

			  // Fun_Thread_Sync_Show( _DATA ) ;
			 }

			// Fun_Operation_Timer_Stop( ) ; //捕捉成功，停止计时，以防定时器溢出
 
			//产生一个clk周波，即clk拉低200k，完成一个数据接收周期
			 g_uc_send_io_data[ 8 ] = 0x01 ;//使CLK引脚输出gao电平
				
			 PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk high 信号			
			 /////////////////////////////////////////////
                
			 Fun_Delay_Usecond( 3 ) ;  //100us 

			 uc_handshake_ok_times = 0 ; 
            ////////////////////////////////////
            //read 0xAA process
			do 
			{								   
			   recv_data = 0xFF ;

			   PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
				
			   recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
				
			   recv_data = (unsigned char ) recv_data & 0xFF ;

			   //Fun_Read_And_Show_Data( recv_data ) ;

			   if( recv_data == _TICK_VALID_HANDSHAKE )//0xAA ,mcu ack 
			   {
				   uc_handshake_ok_times ++ ;

				   if( uc_handshake_ok_times >= _TICK_VALID_TIMES )
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
				//  return   _TIMEOUT ;
			   }

			} 
			while ( 1 );


            //////////////////out put 0x00 ,low to bus
			g_uc_send_io_data[ 8 ] = 0x00 ;//使CLK引脚输出di电平
					
			PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk low 信号

			info_get_times ++ ;
			
			//Fun_Delay_Usecond( 5 ) ;  //100us  ;
			   ////////////////////////////////
               #ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
				{
					CString    str1 ;
					
					str1.Format( "数据信息条数：%d" , info_get_times  ) ;
					
					g_plab_zero_times->SetWindowText( str1 ) ;
					
				}
              #endif
			//	break ;//捕捉到零点，本次捕捉流程结束，开始下次捕捉流程
		  }//if 3 times

		}//if info cap			 
		else //if( recv_data == _NO_DATA_INFO )//not info cap
		{
		   tick_valid_times = 0 ;

		   no_data_info_times ++ ;

		   if( no_data_info_times > _TICK_VALID_TIMES )
		   {
             no_data_info_times = 0 ;
			 
			 continue ;
		   }
		}//else no dta info 

		if( g_bflag_data_info_end == true )
		{
			info_get_times = 0 ;

			SuspendThread( hThread_Read_AD_Info_0506 ) ;
		}
/*
		if( g_stru_ad_info_index > 10 )
		{
			int t = 0 ;
		}
*/		
	}//不断轮询流程 
	while( 1 ) ;//read info do while
//return _OK ;
}
while( 1 ) ;//resume thread do while 
}





int  Fun_Get_Info_AD_Start( )
{	
  unsigned  int   tick_valid_times = 0 ;

  unsigned  int   no_data_info_times = 0 ;

  unsigned  char  recv_data = 0xFF ;

 // stru_AD_Data_Info_Per_Tick    data_info ;

  LONGLONG    system_tick_count = 0 ;

  unsigned  char   uc_handshake_ok_times = 0 ;
  
  g_bflag_data_info_end = false ;

 // Fun_Operation_Timer_Set( _MILLSECOND_1  ) ;// 1ms 读取数据相位信息操作是否超时定时器			   ////////////////////////////////	  
	do //
	{					
	  //每次等待接收零点确认时，如果超时，则返回
	  if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  , 0 ) == WAIT_OBJECT_0 ) 
	  {
		return   _TIMEOUT ;
	  }
	  //////////////
	  recv_data = 0xFF ; //初始设置读取的值

	  PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
			
	  recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
			
	  recv_data = (unsigned char ) recv_data & 0xFF ;

	//	Fun_Read_And_Show_Data( recv_data ) ;
			
 	  if( recv_data == _DATA_INFO_A_ECTION1 ||
		  recv_data == _DATA_INFO_A_ECTION2 ||
		  recv_data == _DATA_INFO_A_ECTION3  ) //the flag of the DTU zero pass
	  {
		  tick_valid_times ++ ; //连续读取到数据信息计数累加

          if( tick_valid_times >= _TICK_VALID_TIMES )//连续读取次数到
		  {
			 ///////////get the data information
             ResumeThread( hThread_Read_AD_0506 ) ;

			 ResumeThread( hThread_Read_AD_Info_0506 ) ;

			 Fun_Operation_Timer_Stop( ) ; //捕捉成功，停止计时，以防定时器溢出
 
			//产生一个clk周波，即clk拉低200k，完成一个数据接收周期
			 g_uc_send_io_data[ 8 ] = 0x01 ;//使CLK引脚输出gao电平
				
			 PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk high 信号			
			 /////////////////////////////////////////////
                
			 Fun_Delay_Usecond( 3 ) ;  //3us 

			 uc_handshake_ok_times = 0 ; 
            ////////////////////////////////////
			do 
			{								   
			   recv_data = 0xFF ;

			   PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
				
			   recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
				
			   recv_data = (unsigned char ) recv_data & 0xFF ;

			   //Fun_Read_And_Show_Data( recv_data ) ;

			   if( recv_data == _TICK_VALID_HANDSHAKE )//0xAA ,mcu ack 
			   {
				   uc_handshake_ok_times ++ ;

				   if( uc_handshake_ok_times >= _TICK_VALID_TIMES )
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

			} 
			while ( 1 );

			g_uc_send_io_data[ 8 ] = 0x00 ;//使CLK引脚输出di电平
					
			PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk low 信号
			
			break ;//捕捉到零点，本次捕捉流程结束，开始下次捕捉流程
		}//if 3 times

	}//if info cap
			 
	else //if( recv_data == _NO_DATA_INFO )//not info cap
	{
	   tick_valid_times = 0 ;
	}//else no dta info 
		
}//不断轮询流程 
while( 1 ) ;
return _OK ;

}


void  Fun_Thread_AD_Read_Info_Init_0506( )
{
	/////////////create a thread
	hThread_Read_AD_Info_0506 = CreateThread( 0, 0, ( pfun_callback)Thread_AD_Read_Info_0506 , 0 , 
		CREATE_SUSPENDED , &dwThreadID1 ) ;
	
	SetThreadPriority( hThread_Read_AD_Info_0506 , THREAD_PRIORITY_TIME_CRITICAL ) ;//THREAD_PRIORITY_HIGHEST ) ; //THREAD_PRIORITY_ABOVE_NORMAL ) ; 
	
	hEvent_Thread_Read_AD_Info_Stop_0506 = CreateEvent( NULL , true , false , NULL) ; 

	g_ad_stru_len_per_tick = ( ADPara.LastChannel - ADPara.FirstChannel + 1 ) * 2 ;

}


void  Fun_Thread_AD_Read_Init_0506( )
{
	/////////////create a thread
	hThread_Read_AD_0506 = CreateThread( 0, 0, ( pfun_callback)Thread_Read_AD_0506 , 0 , 
		CREATE_SUSPENDED , &dwThreadID1 ) ;
	
	SetThreadPriority( hThread_Read_AD_0506 , THREAD_PRIORITY_TIME_CRITICAL ) ;//THREAD_PRIORITY_ABOVE_NORMAL ) ; //THREAD_PRIORITY_ABOVE_NORMAL ) ; 
	
	hEvent_Thread_Read_AD_Stop_0506 = CreateEvent( NULL , true , false , NULL) ; 
}


