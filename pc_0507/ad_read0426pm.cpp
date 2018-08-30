
#include "stdafx.h"

#include "mmsystem.h" 

#include "timer.h"

#include "protocol.h"

#include  "meter_read_cmd_encode.h"

#include  "global.h"

#include  "init.h"

#include  "fifo.h"

#include  "ad_read.h"






SHORT         g_s_ad_fifo_buffer[ _AD_DATA_FIFO_LEN ] ; // Receive AD data buffer  

HANDLE        hThread_AD_Read  ; 

HANDLE        hEvent_Read_AD_Data  ;

HANDLE        hEvent_AD_Read_Data_Error ;

unsigned char g_uc_active_line_index[ _AD_SAMPLE_CHANNEL_MAX ] ;//存储需要读取的出线的下标
//例如g_uc_line_active_number为3，g_uc_active_line_index[ 0 ]为2 ，g_uc_active_line_index[ 1]为6 ，g_uc_active_line_index[ 2 ]为9
//说明第2，，6 ， 9 条出线的数据是有效的,出线下标从0到19  

unsigned char g_uc_active_line_trig_index[ _AD_SAMPLE_CHANNEL_MAX ] ;
//每条出线上过零点触发的次数，一边将读取的数据存储到与触发位置对应的存储器中，取值为0-7，即一位数据需要8次触发
//比如上面对应激活的出线为9 ，即g_uc_active_line_index[ x ] = 9 ，g_uc_active_line_trig_index【 9 】 = 3 ，
//则下次读取到的320个数据为第3次触发的数据，对应存储到TRIG_POINT3的位置上。



unsigned char g_uc_line_active_number  ; //需要读取的出线的总数目，比如本次需要读取总共6条出线的数据： 1 - 20

unsigned char g_uc_data_index_line = 0 ;//每次需要读取的出线的指针0 - 19 

unsigned char g_uc_data_index_bit = 0 ;//每次需要读取的64位中的哪一位的指针0 -63

unsigned char g_uc_data_index_trig = 0 ;//每次需要读取的那一次触发的指针，0 - 7 

bool          g_bflag_one_bit_read = false ;







void  Fun_AD_Read_Index_Init( )
{
	g_uc_data_index_line = 0 ;
	
    g_uc_data_index_bit = 0 ;

    g_uc_data_index_trig = 0 ;
}


//10 * 2 line , 64 bit ,8 trig , 320 data
SHORT  uc_s_line_data[ 20 ] [ 64 ][ 8 ] [ 320 ] ;

 

stru_AD_Sample_Data_One_Bit      g_stru_ad_data_one_bit_line[ _AD_SAMPLE_CHANNEL_MAX ] ;

//数据接收读取完毕后，当某条出线上的数据读取了8次，
//即读取到了8次trig数据，需要进行解码，一下参数传递给解码线程
unsigned char    uc_data_decode_line_index  ;//本次解码的数据位那条出线

unsigned char    uc_data_decode_bit_index[ _AD_SAMPLE_CHANNEL_MAX ] ; //每条出线上本次解码的为第几个bit数据，取值范围0 - 63
//每收到8次trig数据后，该标志位会增加1，代表有新的一bit数据需要解码。


HANDLE     hThread_Data_decode ;

HANDLE     hEvent_Data_Decode ;

HANDLE     hEvent_Data_Decode_Error ;


typedef   struct
{

} stru_Active_Line_Phase ;


/*
unsigned char  Fun_Get_Phase_Index( unsigned char line_index )
{
   unsigned char  phase_index = 0 ;

   switch( line_index )
   {
     case _PHASE_A :
	{

			 break ;
	}
}

}
*/
//读取数据时知道本次触发需要读取那条接入的线，即1-20的数据如线，而输入线与输入的相相对应，因此不需要知道相的具体内容。
//_AD_READ_DATA_LEN_PER_TRIG    320 * 10
void CALLBACK Thread_AD_Read( )
{
  int i  , k ;

  unsigned  char line_index = 0 ;  //得到需要读取的出线的下标
  
//  unsigned  char phase_index = 0 ;
  
  unsigned char  trig_index = 0 ;

  ULONG   read_len = _AD_READ_DATA_LEN_PER_TRIG * 8 * 20 ; //20 line ,8 trig , 320 per trig

  stru_Pro_Decode_Data_One_Bit    stru_pro_decode_data ; 

  do //主循环
  {
    if( WaitForSingleObject( hEvent_Read_AD_Data , 0 ) == WAIT_OBJECT_0 )//start read ad data 
	{
	   if(!PCI8664_ReadDeviceProAD_Npt( hDevice_AD, g_s_ad_fifo_buffer, read_len , &nRetSizeWords ) )
		{
			AfxMessageBox( "AD Card Read  error!");

			SetEvent( hEvent_AD_Read_Data_Error ) ;			
		}
	   if( nRetSizeWords == read_len )//读取到相应数据长度的数据
	   {
         for( i = 0 ; i < g_uc_line_active_number ; i ++ )
		 {
			 line_index = g_uc_active_line_index[ i ] ;  //得到需要读取的出线的下标

			 trig_index = g_uc_active_line_trig_index[ line_index ] ;

			 switch( trig_index )
			 {
			 case _TRIG_POINT_0 :
				 {
				   for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
				   {
					 g_stru_ad_data_one_bit_line[ line_index ].trig_point0[ k ] = g_s_ad_fifo_buffer[ 
					    line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
				   }

                   g_uc_active_line_trig_index[ i ] ++ ;

                   break ;
				 }
			 case _TRIG_POINT_1 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point1[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }

                     g_uc_active_line_trig_index[ i ] ++ ;					 

					 break ;
				 }
			 case _TRIG_POINT_2 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point2[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_3 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point3[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_4 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point4[ k ] = g_s_ad_fifo_buffer[ 
							line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_5 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point5[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_6 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point6[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			 case _TRIG_POINT_7 :
				 {
					 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
					 {
						 g_stru_ad_data_one_bit_line[ line_index ].trig_point7[ k ] = g_s_ad_fifo_buffer[ 
							 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }
					 
                     g_uc_active_line_trig_index[ i ] ++ ;					 
					 
					 break ;
				 }
			   default:
				 break ;
			 }//switch 

			 if( g_uc_active_line_trig_index[ i ] >= 8 )//对应出线上的数据接收超过8次，即接收到了一bit的数据
			 {
				g_uc_active_line_trig_index[ i ] = 0 ; //trig次数指针复位到0 ，准备接收下一bit的8次trig数据 
			 
				uc_data_decode_line_index =  line_index ;
				
				uc_data_decode_bit_index[ line_index ] ++ ;					  
				
			//	SetEvent( hEvent_Data_Decode ) ;
                //将对应的ad数据及数据的出线和bit位信息压入堆栈
				Fun_Fifo_Push_Down(  &g_stru_ad_data_one_bit_line[ line_index ] , 1 ) ;;
			 }
				 		 
		 }//for,read line data
	   }//
	   
	 }
  } 
  while ( 1 ) ;//主循环

}

void  Fun_Thread_AD_Read_Init( )
{
	/////////////create a thread
	hThread_AD_Read = CreateThread( 0, 0, ( pfun_callback)Thread_AD_Read , 0 , 
		0 , &dwThreadID1 ) ;
	
	SetThreadPriority( hThread_AD_Read , THREAD_PRIORITY_NORMAL ) ; 
	
	hEvent_Read_AD_Data = CreateEvent( NULL , true , false , NULL) ;
	
	hEvent_AD_Read_Data_Error = CreateEvent( NULL , true , false , NULL) ;
}


void CALLBACK Thread_Data_Decode( )
{
//uc_data_decode_line_index =  line_index ;
				
//uc_data_decode_bit_index[ line_index ] ++ ;
/*
int  i , k ;

	for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
	{
		g_stru_ad_data_one_bit_line[ line_index ].trig_point7[ k ] = g_s_ad_fifo_buffer[ 
			line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
					 }	
*/
}


void  Fun_Thread_Data_Decode_Init( )
{
	/////////////create a thread
	hThread_Data_decode = CreateThread( 0, 0, ( pfun_callback)Thread_Data_Decode , 0 , 
		0 , &dwThreadID1 ) ;
	
	SetThreadPriority( Thread_Data_Decode , THREAD_PRIORITY_NORMAL ) ; 
	
	hEvent_Data_Decode  = CreateEvent( NULL , true , false , NULL) ;
	
	hEvent_Data_Decode_Error = CreateEvent( NULL , true , false , NULL) ;
}