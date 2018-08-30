
#include "stdafx.h"

#include  "global.h"

#include  "init.h"

#include  "protocol.h"

#include  "angle_rw_cmd_encode.h"

#include  "timer.h"

#include  "data_transfer.h"

#include  "meter_read_cmd_encode.h"

#include  "fifo.h"

#include  "ad_read.h"







unsigned char   g_uc_ad_read_channel_index ;


unsigned char   g_uc_trig_times = 0 ; 


#define   _DEBUG_MESSAGE_ZERO_TIMES_SHOW

HANDLE            hEvent_Timer_Zero_Pass_Ack ;//接收过零点时的等待超时定时器，最长21ms，
//in the wait function the event was set ,when the waiting things occure ,the event would be set again
//when the timer tick upflow the event would be reset  

//************************************
// Method:    Fun_Set_Read_CMD_Buf
// FullName:  Fun_Set_Read_CMD_Buf
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: int flag
//************************************
int  Fun_Set_Read_CMD_Buf( int flag ) 
{
	unsigned char  phase ;
	
	CMD_Buf_Init( ) ;
	
	g_uc_cmd_buf[ _DTU_ADDR_BYTE ] =  g_stru_pc2mcu_protocol.uc_section ;//段地址，生成室外机地址
	
	if( flag == _METER_READ_SINGLE )
	{
		phase = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_phase_number ;
		
		if( phase == _PHASE_A )
		{
			g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_A ;
		}
		else if( phase == _PHASE_B )
		{
			g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_B ;
		}
		else if( phase == _PHASE_C )
		{
			g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_C ;
		}	
		else
			return _CMD_ERROR ;
	}
	else if( flag == _METER_READ_SYNC )
	{
		g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SYNC ;
	}
	else if( flag == _METER_READ_SEQU )
	{
		g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SEQU ;
	}
	
	g_stru_pc2mcu_protocol.stru_wplc_protocol = Fun_WPLC_Data_Set( g_stru_pc2mcu_protocol.stru_wplc_protocol ) ;
	
	g_uc_cmd_buf[ _DATA_BYTE1 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 0 ] ;
	
	g_uc_cmd_buf[ _DATA_BYTE2 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 1 ] ;
	
	g_uc_cmd_buf[ _DATA_BYTE3 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 2 ] ;
	
	g_uc_cmd_buf[ _DATA_BYTE4 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 3 ] ;
	
	g_uc_cmd_buf[ _DATA_BYTE5 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 4 ] ;
	
	g_uc_cmd_buf[ _CRC_BYTE ] = Fun_CRC_SUM( g_uc_cmd_buf ,16 ) ;
	
	return _OK ;
	
} 





int Meter_Read_Single( stru_Meter_Read * cmd ) 
{
	g_stru_pc2mcu_protocol.uc_section = cmd->uc_section ;  //段地址，生成室外机地址

	g_stru_pc2mcu_protocol.uc_line_number = cmd->uc_line_number ;//线

	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_phase_number = cmd->uc_phase_number ;//相

	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_station_number = cmd->uc_station_number ;//站号

	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_sub_meter_addr = cmd->uc_sub_meter_addr ;//模块地址

	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_user_cmd = cmd->uc_user_cmd ;//具体用户指令

	g_stru_pc2mcu_protocol.stru_wplc_protocol.un_module_addr = cmd->un_module_addr ;//模块子地址
    /////////////AD sample channel index set 
//	Fun_AD_Sample_Channel_Set_Single_Read( cmd ) ;

    //encode the cmd to standard cmd protocol
	Fun_Set_Read_CMD_Buf( _METER_READ_SINGLE ) ;






/*
	if( cmd->uc_multi_section_decode_flag == _MULTI_SECTION_DECODE_FLAG )
	{

       for( int i = 0 ;  i < _FRAME_LEN  ; i ++ )
	   {
          g_uc_multi_section_cmd_buf[ g_uc_multi_section_decode_frame_number ] [ i ]
			                = g_uc_cmd_buf[ i ] ;
	   }

	   g_uc_multi_section_decode_frame_number ++ ；

       
		   
	}
	else if( cmd->uc_multi_section_decode_flag == _MULTI_SECTION_DECODE_END_FLAG )
	{			
		for( int i = 0 ;  i < _FRAME_LEN  ; i ++ )
		{				
		   g_uc_multi_section_cmd_buf[ g_uc_multi_section_decode_frame_number ] [ i ]
			   
			   = g_uc_cmd_buf[ i ] ;
		}

	    g_uc_multi_section_decode_frame_number ++ ；
        
	//	Fun_Get_AD_Read_Channel( ) ;


       // Fun_PC_Send_Data( )

	}
	else
	{

	}

*/
	return _OK ;
}


int Meter_Read_Sync( stru_Meter_Read * cmd_a ,
					stru_Meter_Read * cmd_b ,
					stru_Meter_Read * cmd_c   ) 
{
	int i = 0 ;
	//phase b protocol buffer set
	Meter_Read_Single( cmd_b ) ;
	
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf2[ i ] = g_uc_cmd_buf [ i ] ;
	}
	
	g_uc_cmd_buf2[ _CMD_BYTE ] = _TRIG_SYNC ;
	
	g_uc_cmd_buf2[ _FRAME_NUMBER_BYTE ] = _PHASE_B ;
	
	//phase c protocol buffer set
	Meter_Read_Single( cmd_c ) ;
	
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf3[ i ] = g_uc_cmd_buf [ i ] ;
	}  
	g_uc_cmd_buf3[ _CMD_BYTE ] = _TRIG_SYNC ;
	
	g_uc_cmd_buf3[ _FRAME_NUMBER_BYTE ] = _PHASE_C ;
	
	//phase a protocol buffer set
	Meter_Read_Single( cmd_a ) ;
	
	g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SYNC ;
	
	g_uc_cmd_buf[ _FRAME_NUMBER_BYTE ] = _PHASE_A ;
	
	return _OK ;
}




int Meter_Read_Sequence( stru_Meter_Read * cmd_a ,
						stru_Meter_Read * cmd_b ,
						stru_Meter_Read * cmd_c   ) 
{
	int i  = 0 ;
    //phase b protocol buffer set
	Meter_Read_Single( cmd_b ) ;
	
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf2[ i ] = g_uc_cmd_buf [ i ] ;
	}	
	
	g_uc_cmd_buf2[ _CMD_BYTE ] = _TRIG_SEQU ;
	
	g_uc_cmd_buf2[ _FRAME_NUMBER_BYTE ] = _PHASE_B ;
	
    //phase c protocol buffer set
	Meter_Read_Single( cmd_c ) ;
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf3[ i ] = g_uc_cmd_buf [ i ] ;
	}	
	g_uc_cmd_buf3[ _CMD_BYTE ] = _TRIG_SEQU ;
	
    g_uc_cmd_buf3[ _FRAME_NUMBER_BYTE ] = _PHASE_C ;
	
    //phase a protocol buffer set
	Meter_Read_Single( cmd_a ) ;
	
	g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SEQU ;
	
	g_uc_cmd_buf[ _FRAME_NUMBER_BYTE ] = _PHASE_A ;
	
	return _OK ;
}














//************************************
// Method:    Fun_AD_Sample_Channel_Set_Single_Read
// FullName:  Fun_AD_Sample_Channel_Set_Single_Read
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_Meter_Read * cmd
//************************************
int   Fun_AD_Sample_Channel_Set_Single_Read( stru_Meter_Read * cmd )
{
/*
	int  i ;

   if( cmd->un_module_addr >= _SIMULATIVE_ADDR_START 
	   && cmd->un_module_addr <= _SIMULATIVE_ADDR_END )  //虚拟地址，需要多条出线的同一条相同时调制
   {
     for( i = 0 ; i < ) 

   
   }
*/
return 1 ;
}








unsigned  char   g_uc_trig_angle_a ;  //全局，a相触发角度

unsigned  char   g_uc_trig_angle_b ;  //全局，b相触发角度

unsigned  char   g_uc_trig_angle_c ;  //全局，a相触发角度

unsigned  char   g_uc_trig_angle_instent ;   //全局，当前需要发送的触发角度



//************************************
// Method:    Fun_Meter_Read_Single_Decode
// FullName:  Fun_Meter_Read_Single_Decode
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int   Fun_Meter_Read_Single_Decode( )
{
   int error_flag = 0 ; 
   
   //发送指令////////////////////////////
   g_uc_zero_pass_times = 0 ;

   Fun_PC_Send_Data( g_uc_cmd_buf , 16 ) ;


   //等待并捕捉第一个零点////////////////////
   error_flag = Fun_PC_Zero_Cap_Firstly() ;

#ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
   {
      CString    str1 ;

	  str1.Format( "过零点个数：%d" , g_uc_zero_pass_times ) ;

	  g_plab_zero_times->SetWindowText( str1 ) ;
       
   }
#endif

   if( error_flag != _OK )
   {
	   return error_flag ;
   }
   //等待并捕捉其余64 * 2 + 2 个零点/////////////////////
   error_flag = Fun_PC_Zero_Cap( 130 ) ;//_ZER_PASS_NUMBER_BEFORE_MODULATE ) ;

   if( error_flag != _OK )
   {
	   return error_flag ;
   }
   //
    g_uc_trig_times = 0 ;

   for( int i = 0 ; i < _READBACK_FRAME_LEN ; i ++ )
   {
	   error_flag = Fun_PC_Zero_Cap( 1 ) ;

	   
	   if( error_flag != _OK )
	   {
		   return error_flag ;
	   }

	    g_uc_trig_times ++ ;

#ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
		{
			CString    str1 ;
			
			str1.Format( "触发过零点个数：%d" , g_uc_trig_times ) ;
			
			g_plab_trig_times->SetWindowText( str1 ) ;
			
		}
#endif
       //成功得到一个过零点，设置触发定时 ， 开始采集数据
       //启动上升沿定时线程，定时到进行第1个过零点采集，正过零点

	   SetEvent( hEvent_Thread_Trig_Timer_Raising_Enable ) ;

	   ResumeThread( hThread_Trig_Timer_Raising ) ;

       //启动下降沿定时线程，定时到进行第2个过零点采集，负过零点
	   SetEvent( hEvent_Thread_Trig_Timer_Falling_Enable ) ;

	   ResumeThread( hThread_Trig_Timer_Falling ) ;

	   //以上延时是循环等待，函数返回说明延时时间到
	   //产生触发的下降沿信号，给地板，通过IO9
	  // Fun_Operation_Timer_Set( _MILLSECOND_20 ) ;//start other circle timer

	   do 
	   {		   
		 if( WaitForSingleObject( hEvent_Thread_Trig_Timer_Raising_Enable , 
			                        0 ) != WAIT_OBJECT_0 ) 
		 {
             Fun_PC_Trig_Pulse(  _RAISING_EDGE ) ;

			 SetEvent( hEvent_Read_AD_Data ) ;
			 
	       //  ResumeThread( hThread_Read_AD_Process ) ;
		 }

		if( WaitForSingleObject( hEvent_Thread_Trig_Timer_Falling_Enable , 
			   0 ) != WAIT_OBJECT_0 ) 
		 {
			   Fun_PC_Trig_Pulse(  _RAISING_EDGE ) ;

			   Fun_Operation_Timer_Stop( ) ; //停止计时，以防定时器溢出

			   break ;
		 }
			//每次如果超时，则返回
		 if( WaitForSingleObject( hEvent_Operation_Timer_Timeout  ,
			                        0 ) == WAIT_OBJECT_0 ) 
		 {
			return   _TIMEOUT ;
		 }
	   } 
	   while ( 1 );

	  
   }
   return 1 ; 
}






/*
       HANDLE    g_hArray_Trig_Singnal_Send_Event[ 2 ] ;

       g_hArray_Trig_Singnal_Send_Event[ 0 ]  = hEvent_Thread_Trig_Timer_Falling_Enable ;

       g_hArray_Trig_Singnal_Send_Event[ 1 ]  = hEvent_Thread_Trig_Timer_Raising_Enable ;

	   unsigned  char 
	   do 
	   {
		   if( WaitForMultipleObjects( 2 , g_hArray_Trig_Singnal_Send_Event ,
			                           0 ) != WAIT_OBJECT_0 ) 
		   {
			   Fun_PC_Trig_Pulse(  _FAILING_EDGE ) ;
		   }

	   } while ( 1 );
*/	  


//	   SetEvent( hEvent_Read_AD_Data ) ;

//	   ResumeThread( hThread_Read_AD_Process ) ;

//************************************
// Method:    Fun_Meter_Read_Single_Decode
// FullName:  Fun_Meter_Read_Single_Decode
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int   Fun_Meter_Read_Single_Decode_Test( )
{
   int error_flag = 0 ; 
   
   //发送指令////////////////////////////
   g_uc_zero_pass_times = 0 ;

   stru_Pro_Decode_Data_One_Bit    stru_pro_decode_data ;

   int    trig_times = 0 ;

   int    bit_index = 0 ;

   Fun_PC_Send_Data( g_uc_cmd_buf , 16 ) ;


   //等待并捕捉第一个零点////////////////////
   error_flag = Fun_PC_Zero_Cap_Firstly() ;

#ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
   {
      CString    str1 ;

	  str1.Format( "过零点个数：%d" , g_uc_zero_pass_times ) ;

	  g_plab_zero_times->SetWindowText( str1 ) ;
       
   }
#endif

   if( error_flag != _OK )
   {
	   return error_flag ;
   }
   //等待并捕捉其余64 * 2 + 2 个零点/////////////////////
   error_flag = Fun_PC_Zero_Cap( 130 ) ;//_ZER_PASS_NUMBER_BEFORE_MODULATE ) ;

   if( error_flag != _OK )
   {
	   return error_flag ;
   }
   //
    g_uc_trig_times = 0 ;

   for( int i = 0 ; i < _READBACK_FRAME_LEN ; i ++ )
   {
	   error_flag = Fun_PC_Zero_Cap( 1 ) ;

	   
	   if( error_flag != _OK )
	   {
		   return error_flag ;
	   }

#ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
		{
			CString    str1 ;
			
			str1.Format( "触发过零点个数：%d" , g_uc_trig_times ) ;
			
			g_plab_trig_times->SetWindowText( str1 ) ;
			
		}
#endif
       //成功得到一个过零点，设置触发定时 ， 开始采集数据
       //启动上升沿定时线程，定时到进行第1个过零点采集，正过零点
       Fun_Set_Trig_Timer( 60 , _RAISING_EDGE ) ; //60 度采集
     
       Fun_PC_Trig_Pulse(  _RAISING_EDGE ) ;

//	   int   Fun_AD_Read_Data_One_Bit( stru_Pro_Decode_Data_One_Bit    stru_pro_decode_data , 
//	  int  active_line_number , int  line_index  , int trig_index  , int bit_index  , unsigned char phase_index ) ;
	   Fun_AD_Read_Data_One_Bit( stru_pro_decode_data , 1 , 1 , trig_times , bit_index , _PHASE_A ) ;

	   trig_times ++ ;

	   /////////////////////////////////////
       Fun_Set_Trig_Timer( 60 , _RAISING_EDGE ) ; //60 度采集
	   
       Fun_PC_Trig_Pulse(  _RAISING_EDGE ) ;

	   Fun_AD_Read_Data_One_Bit( stru_pro_decode_data , 1 , 1 , trig_times , bit_index , _PHASE_A ) ;
	   
	   trig_times ++ ;
	   
	   if( trig_times >=8 )
	   {
		   trig_times = 0 ;
		   
		   bit_index ++ ;
		}
	  
   }//for
   return 1 ; 
}


