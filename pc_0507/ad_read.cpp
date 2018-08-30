#define   _DEBUG_MESSAGE_ZERO_TIMES_SHOW


#include "header.h"



#define    _DATA_LEN   1600

typedef unsigned long (CALLBACK *pfun_callback)(LPVOID pvUserParam) ;


HANDLE    hThread_Read_AD_Test ;


SHORT         g_s_ad_fifo_buffer[ _AD_DATA_FIFO_LEN ] ; // Receive AD data buffer  

HANDLE        hThread_AD_Read  ; 

HANDLE        hEvent_Read_AD_Data  ;

HANDLE        hEvent_AD_Read_Data_Error ;

UINT          g_trig_number_per_cmd = 0 ;   //每次指令需要触发的总次数


unsigned char g_uc_active_line_index[ _AD_SAMPLE_CHANNEL_MAX ] ;//存储需要读取的出线的下标
//例如g_uc_line_active_number为3，g_uc_active_line_index[ 0 ]为2 ，g_uc_active_line_index[ 1]为6 ，g_uc_active_line_index[ 2 ]为9
//说明第2，，6 ， 9 条出线的数据是有效的,出线下标从0到19 
//需要读取b相数据时，设置为对应出线的A相线的出线，再有该A相线的 g_uc_active_line_phase_index
//得到是否需要同时读取c相的数据做差运算，从而得到b相数据。

unsigned char g_uc_active_line_trig_index[ _AD_SAMPLE_CHANNEL_MAX ] ;
//每条出线上过零点触发的次数，一边将读取的数据存储到与触发位置对应的存储器中，取值为0-7，即一位数据需要8次触发
//比如上面对应激活的出线为9 ，即g_uc_active_line_index[ x ] = 9 ，g_uc_active_line_trig_index【 9 】 = 3 ，
//则下次读取到的320个数据为第3次触发的数据，对应存储到TRIG_POINT3的位置上。

unsigned char      g_uc_active_line_phase_index[ _AD_SAMPLE_CHANNEL_MAX ] ;//记录该条出线是否是b相数据的读取，从而决定是否采集对应的c相出线

unsigned char      g_uc_couple_line_index[ _AD_SAMPLE_CHANNEL_MAX ] ;//记录该出线和那条出线配对，及A C相的配对，如果该出线是A相，该对应位置的couple line index存储与之对应的C相出线的线号
//反之如果该出线是C相，则该couple_line_index中存储对应A相的线号。


unsigned char      g_uc_active_line_bit_index[ _AD_SAMPLE_CHANNEL_MAX ] ;



unsigned char g_uc_line_active_number  ; //需要读取的出线的总数目，比如本次需要读取总共6条出线的数据： 1 - 20

unsigned char g_uc_data_index_line = 0 ;//每次需要读取的出线的指针0 - 19 

unsigned char g_uc_data_index_bit = 0 ;//每次需要读取的64位中的哪一位的指针0 -63

unsigned char g_uc_data_index_trig = 0 ;//每次需要读取的那一次触发的指针，0 - 7 

bool          g_bflag_one_bit_read = false ;

/////////////////////////////////////////////////////////////////////////////////////
//-----------------------------add 04 30--------------------------------------------
bool     g_bflag_data_info_end  = false  ;

HANDLE   hEvent_AD_Data_Info_End ;





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

unsigned char   g_uc_ad_data_frame_naumber = 0 ; //记录ad数据的帧号，以便在缓冲中区分每bit数据属于哪一帧。该帧号随着读表指令的增加而增加，
//在ad_read模块中不会改变该值，该模块中只是读取该值，并在保存每bit数据时把该信息压入对应的fifo结构体单元中


HANDLE     hThread_Data_decode ;

HANDLE     hEvent_Data_Decode ;

HANDLE     hEvent_Data_Decode_Error ;


typedef   struct
{

} stru_Active_Line_Phase ;



unsigned char  Fun_Set_AD_Read_Info( stru_Meter_Read * cmd )
{
   g_uc_line_active_number = 0x01 ;//yi tiao chu xian 

   g_uc_active_line_index[ 0 ] = 0x01 ;//di yi tiao chu xian

   g_uc_active_line_phase_index[ 0 ]  =  _PHASE_A ;

   g_uc_active_line_trig_index[ 0 ] = 0x00 ;

   g_uc_active_line_bit_index[ 0 ] = 0x00 ;

   return 1 ;

}




//读取数据时知道本次触发需要读取那条接入的线，即1-20的数据如线，而输入线与输入的相相对应，因此不需要知道相的具体内容。
//_AD_READ_DATA_LEN_PER_TRIG    320 * 10
void CALLBACK Thread_AD_Read( )
{
  int i  , k ;

  unsigned  char line_index = 0 ;  //得到需要读取的出线的下标
  
  unsigned  char phase_index = 0 ;
  
  unsigned char  trig_index = 0 ;

  ULONG   read_len = _AD_READ_DATA_LEN_PER_TRIG * 8 * _AD_SAMPLE_CHANNEL_MAX ; //20 line ,8 trig , 320 per trig

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
	   if( ( ULONG )nRetSizeWords == read_len )//读取到相应数据长度的数据
	   {
         for( i = 0 ; i < g_uc_line_active_number ; i ++ )
		 {
			 line_index = g_uc_active_line_index[ i ] ;  //得到需要读取的出线的下标

			 phase_index = g_uc_active_line_phase_index[ i ] ;

			 if( phase_index !=  _PHASE_B )
			 {     				 
				 trig_index = g_uc_active_line_trig_index[ i ] ;
				 
				 switch( trig_index )
				 {
				     case _TRIG_POINT_0 :
					 {
						 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
						 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point0[ k ] = g_s_ad_fifo_buffer[ 
								 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
						 }
						 
						 g_uc_active_line_trig_index[ i ] ++ ;
						 
						 break ;
					 }
					 case _TRIG_POINT_1 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point1[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
					 }
					 case _TRIG_POINT_2 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point2[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
					 }
					 case _TRIG_POINT_3 :
					{
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point3[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
					 }
					 case _TRIG_POINT_4 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point4[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
						 }
					 case _TRIG_POINT_5 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point5[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
						 }
					 case _TRIG_POINT_6 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point6[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
						 }
					 case _TRIG_POINT_7 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point7[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
					 }
					 default :
						 break ;
				 }//switch
	         ////////////////////////////////////////
			 if( g_uc_active_line_trig_index[ i ] >= 8 )//对应出线上的数据接收超过8次，即接收到了一bit的数据
			 {
				g_uc_active_line_trig_index[ i ] = 0 ; //trig次数指针复位到0 ，准备接收下一bit的8次trig数据 
			 
				stru_pro_decode_data.uc_line_index  =  line_index ;

                g_uc_active_line_bit_index[ i ] ++ ; 

				stru_pro_decode_data.uc_bit_index = g_uc_active_line_bit_index[ i ] ;

				stru_pro_decode_data.uc_phase_index = phase_index ;

				stru_pro_decode_data.uc_frame_index = g_uc_ad_data_frame_naumber ;
								
			//	SetEvent( hEvent_Data_Decode ) ;
                //将对应的ad数据及数据的出线和bit位信息压入堆栈
				Fun_Fifo_Push_Down(  &stru_pro_decode_data , 1 ) ;
			 }
				 		 
		 }//if not phase b
		 else if( phase_index ==  _PHASE_B)
		 {    				 
		     unsigned char  couple_line_index = g_uc_couple_line_index[  line_index ] ;

			 trig_index = g_uc_active_line_trig_index[ i ] ;
				 
				 switch( trig_index )
				 {
				     case _TRIG_POINT_0 :
					 {
						 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
						 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point0[ k ] = 
								 g_s_ad_fifo_buffer[ line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] - 
								 g_s_ad_fifo_buffer[ couple_line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
								 
						 }
						 
						 g_uc_active_line_trig_index[ i ] ++ ;
						 
						 break ;
					 }
					 case _TRIG_POINT_1 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point1[ k ] = 
								 g_s_ad_fifo_buffer[ line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] - 
								 g_s_ad_fifo_buffer[ couple_line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
					 }
					 case _TRIG_POINT_2 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point2[ k ] = 
								 g_s_ad_fifo_buffer[ line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] - 
								 g_s_ad_fifo_buffer[ couple_line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
					 }
					 case _TRIG_POINT_3 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point3[ k ] = 
								 g_s_ad_fifo_buffer[ line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] - 
								 g_s_ad_fifo_buffer[ couple_line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
					 }
					 case _TRIG_POINT_4 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point4[ k ] = 
								 g_s_ad_fifo_buffer[ line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] - 
								 g_s_ad_fifo_buffer[ couple_line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
						 }
					 case _TRIG_POINT_5 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point5[ k ] = 
								 g_s_ad_fifo_buffer[ line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] - 
								 g_s_ad_fifo_buffer[ couple_line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
						 }
					 case _TRIG_POINT_6 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point6[ k ] = 
								 g_s_ad_fifo_buffer[ line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] - 
								 g_s_ad_fifo_buffer[ couple_line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
						 }
					 case _TRIG_POINT_7 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point7[ k ] = 
								 g_s_ad_fifo_buffer[ line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] - 
								 g_s_ad_fifo_buffer[ couple_line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 g_uc_active_line_trig_index[ i ] ++ ;
							 
							 break ;
					 }
					 default :
						 break ;
				 }

			 }
	         ////////////////////////////////////////
			 if( g_uc_active_line_trig_index[ i ] >= 8 )//对应出线上的数据接收超过8次，即接收到了一bit的数据
			 {
				g_uc_active_line_trig_index[ i ] = 0 ; //trig次数指针复位到0 ，准备接收下一bit的8次trig数据 
			 
				stru_pro_decode_data.uc_line_index  =  line_index ;

                g_uc_active_line_bit_index[ i ] ++ ; 

				stru_pro_decode_data.uc_bit_index = g_uc_active_line_bit_index[ i ] ;

				stru_pro_decode_data.uc_phase_index = phase_index ;

				stru_pro_decode_data.uc_frame_index = g_uc_ad_data_frame_naumber ;
								
			//	SetEvent( hEvent_Data_Decode ) ;
                //将对应的ad数据及数据的出线和bit位信息压入堆栈
				Fun_Fifo_Push_Down(  &stru_pro_decode_data , 1 ) ;
			 }

		 }

		 //if read data
	   }////for,read line data
	   
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


int  Fun_AD_Trig_Soft( )
{
	//ADPara.TriggerMode = PCI8664_TRIGMODE_SOFT ;

	int channel = ( ADPara.LastChannel - ADPara.FirstChannel + 1 ) * 2 ;
	
	int step = channel / 2 - 1  ;							// first channel
	
	SHORT    a_data[ _DATA_LEN ] ;

	SHORT    b_data[ _DATA_LEN ] ;

	SHORT    c_data[ _DATA_LEN ] ;

	float    a_voltage[ _DATA_LEN ] ;

	float    b_voltage[ _DATA_LEN ] ;

	float    c_voltage[ _DATA_LEN ] ;

    nReadSizeWords = _DATA_LEN * channel  ;

	int i , k ;

	if( !PCI8664_StartDeviceProAD( hDevice_AD ) )		// Start AD
	{
		AfxMessageBox("PCI8664_StartDeviceProAD Error...");

		return -1 ;
	}
do 
{
	memset( ADBuffer , 0 , sizeof( ADBuffer ) ) ;

    nRetSizeWords = 0 ;

    Fun_Operation_Timer_Set( 20000 ) ;

	if( !PCI8664_ReadDeviceProAD_Npt( hDevice_AD, ADBuffer, nReadSizeWords, &nRetSizeWords ) )
	{
		AfxMessageBox("PCI8664_ReadDeviceProAD_Npt Error...") ;	
		
		return -1 ;
	}
 //   PCI8664_StopDeviceProAD( hDevice_AD );   //stop AD data conversion


	if( nReadSizeWords == nRetSizeWords )//read the righe data
	{
		for( i = 0 , k = 0 ; i < nReadSizeWords ;  )		 
		{
			a_data[ k ] = ( ADBuffer[ k * channel + 0 ] ^ 0x0800 ) & 0x0FFF ;

			b_data[ k ] = ( ADBuffer[ k * channel + 2 ] ^ 0x0800 ) & 0x0FFF ;

			c_data[ k ] = ( ADBuffer[ k * channel + 4 ] ^ 0x0800 ) & 0x0FFF ;
			
			i = i + channel  ;

			k ++ ;
		}

		for( i = 0 ; i < _DATA_LEN  ; i ++ )
		{
		//	float  fVolt =  (float)((10000.00/4096) * a_data[ i ] - 5000.00); ;
		float  fVolt ;
		
		fVolt  =  (float)( ( 20000.00/4096 ) * a_data[ i ] - 10000.00 ) ;	

		a_voltage[ i ] = fVolt ;

        /////////////
		fVolt =  (float)( ( 20000.00/4096 ) * b_data[ i ] - 10000.00 ) ;	
		
		b_voltage[ i ] = fVolt ;
        ///////////////
		fVolt =  (float)( ( 20000.00/4096 ) * c_data[ i ] - 10000.00 ) ;	
		
		c_voltage[ i ] = fVolt ;

//	int error_flag = PCI8664_StopDeviceProAD( hDevice_AD );
		
	//	PCI8664_ReleaseDeviceProAD( hDevice_AD );

	//	PCI8664_ReleaseDevice( hDevice_AD ) ;

		int  m ; 

		m= 0 ;

		}
	}

}while( 1 ) ;

}

int   Fun_AD_Read_Data_One_Bit( stru_Pro_Decode_Data_One_Bit    stru_pro_decode_data , int  active_line_number , int  line_index  , int trig_index  , int bit_index  , unsigned char phase_index )
{
	
	int i , k ;

	ULONG   read_len = _AD_READ_DATA_LEN_PER_TRIG * 8 * _AD_SAMPLE_CHANNEL_MAX ; //20 line ,8 trig , 320 per trig 

	if( !PCI8664_StartDeviceProAD( hDevice_AD ) )		// Start AD
	{
		AfxMessageBox("PCI8664_StartDeviceProAD Error...");
		
		return -1 ;
	}
	
	if( !PCI8664_ReadDeviceProAD_Npt( hDevice_AD, ADBuffer, nReadSizeWords, &nRetSizeWords ) )
	{
		AfxMessageBox("PCI8664_ReadDeviceProAD_Npt Error...") ;	
		
		return -1 ;
	}
	else
	{
	   if(!PCI8664_ReadDeviceProAD_Npt( hDevice_AD, g_s_ad_fifo_buffer, read_len , &nRetSizeWords ) )
		{
			AfxMessageBox( "AD Card Read  error!");

			SetEvent( hEvent_AD_Read_Data_Error ) ;	
			
			return -1 ;
		}
	   else if( ( ULONG )nRetSizeWords == read_len )//读取到相应数据长度的数据
	   {
         for( i = 0 ; i < active_line_number ; i ++ )
		 {
			 if( phase_index !=  _PHASE_B )
			 {     				 
				 trig_index = g_uc_active_line_trig_index[ i ] ;
				 
				 switch( trig_index )
				 {
				     case _TRIG_POINT_0 :
					 {
						 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
						 {
							 stru_pro_decode_data.stru_data_one_bit.trig_point0[ k ] = g_s_ad_fifo_buffer[ 
								 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
						 }
						 
						 break ;
					 }
					 case _TRIG_POINT_1 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point1[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 break ;
					 }
					 case _TRIG_POINT_2 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point2[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 break ;
					 }
					 case _TRIG_POINT_3 :
					{
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point3[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 break ;
					 }
					 case _TRIG_POINT_4 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point4[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }
							 
							 break ;
						 }
					 case _TRIG_POINT_5 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point5[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }

							 break ;
						 }
					 case _TRIG_POINT_6 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point6[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }

							 break ;
						 }
					 case _TRIG_POINT_7 :
						 {
							 for( k = 0 ; k < _AD_SAMPLE_DATA_NUMBER_PER_ZERO ; k ++ )//for( k = 0 ; k < 320 ; k ++ )
							 {
								 stru_pro_decode_data.stru_data_one_bit.trig_point7[ k ] = g_s_ad_fifo_buffer[ 
									 line_index * _AD_SAMPLE_DATA_NUMBER_PER_ZERO + k ] ;
							 }						
							 
							 break ;
					 }
					 default :
						 break ;
				 }//switch
	         ////////////////////////////////////////
			 if( trig_index >= 7 )//对应出线上的数据接收超过8次，即接收到了一bit的数据
			 {
 
				stru_pro_decode_data.uc_line_index  =  line_index ;

				stru_pro_decode_data.uc_bit_index = bit_index ;

				stru_pro_decode_data.uc_phase_index = phase_index ;

				stru_pro_decode_data.uc_frame_index = g_uc_ad_data_frame_naumber ;
								
			//	SetEvent( hEvent_Data_Decode ) ;
                //将对应的ad数据及数据的出线和bit位信息压入堆栈
				Fun_Fifo_Push_Down(  &stru_pro_decode_data , 1 ) ;

				PCI8664_StopDeviceProAD( hDevice_AD );   //stop AD data conversion

				return 1 ;
			 }
		}//if not phaseb

	}//for
}//read len data
}//if ad sample ok
return 1 ;
}

//每次外部触发信号tick，读取所有出线数据是否超时线程，线程中如果超时将ad采集流程终止。
HANDLE   hEvent_AD_Read_Per_Tick_Run  ; 





SHORT    g_s_ad_data_tick_buf[ _AD_SAMPLE_CHANNEL_MAX * 2 ] ; //每次trig、tick需要读取的ad值的缓冲区



int  Fun_AD_Read_Per_Tick( )
{
  int i  ;

  LONGLONG   system_tick_count = 0 ;
	
  unsigned    read_len = _AD_SAMPLE_CHANNEL_MAX ; //10 * 2 line
  
  stru_AD_Data_Per_Tick    stru_data ;

  SHORT     data_buf[ _AD_SAMPLE_CHANNEL_MAX * 2 ] ;

  	
  if( !PCI8664_StartDeviceProAD( hDevice_AD ) )		// Start AD
  {
	AfxMessageBox( "PCI8664_StartDeviceProAD Error..." );
		
	return -1 ;
  }

  // SetEvevt( hEvent_AD_Read_Per_Tick_Run ) ;//ad 读取是否超时判断线程
  ////////////////////////////////////////////////////////////
  memset( data_buf , 0 , sizeof( data_buf ) ) ;

  if( !PCI8664_ReadDeviceProAD_Npt( hDevice_AD, data_buf, nReadSizeWords, &nRetSizeWords ) )
  {
	AfxMessageBox("PCI8664_ReadDeviceProAD_Npt Error...") ;	
		  
	return -1 ;
  }
  if( ( ULONG )nRetSizeWords == read_len )//读取到相应数据长度的数据
 {
	//  ResetEvent( hEvent_AD_Read_Per_Tick_Run ) ；

	  LARGE_INTEGER    time1 ;	 
	 //////////////////////////////////延时			
	 QueryPerformanceCounter( &time1 ) ;  //得到起始时间
	 
     system_tick_count = time1.QuadPart ;

	 for( i = 0 ; i < _AD_SAMPLE_CHANNEL_MAX ; i ++ )
	 {
       stru_data.data_line[ i ] = data_buf[ i ] ;
	 }

	 stru_data.time_stamp = system_tick_count ;

	 //Fun_Fifo_Push_Down( stru_AD_Data_Per_Tick data , len ) ;
	 PCI8664_StopDeviceProAD( hDevice_AD ) ;		// Stop AD
 }
return 1 ;

}




int   info_get_times = 0 ;
/*
int  Fun_Data_Info_Get_Per_Tick( )
{	
  unsigned  int   tick_valid_times = 0 ;

  unsigned  char  recv_data = 0xFF ;

  stru_AD_Data_Info_Per_Tick    data_info ;

  LARGE_INTEGER    time1 ;

  LONGLONG    system_tick_count = 0 ;

  unsigned  char   uc_handshake_ok_times = 0 ; 

  // Fun_Operation_Timer_Set( _MILLSECOND_20  ) ;			   ////////////////////////////////	  
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
			
 	  if( recv_data == _DATA_INFO_A_ECTION1 ||
		  recv_data == _DATA_INFO_A_ECTION2 ||
		  recv_data == _DATA_INFO_A_ECTION3 ) //the flag of the DTU zero pass
	  {
		  tick_valid_times ++ ;

          if( tick_valid_times >= _TICK_VALID_TIMES )
		  {
			  info_get_times  ++ ;
			 ///////////get the data information	 			 			
			 QueryPerformanceCounter( &time1 ) ;  //得到起始时间
			  
             system_tick_count = time1.QuadPart ;

			 data_info.data_info = recv_data ;

			 data_info.time_stamp = system_tick_count ;

			 //Fun_Operation_Timer_Stop( ) ; //捕捉成功，停止计时，以防定时器溢出
 
			//产生一个clk周波，即clk拉低200k，完成一个数据接收周期
			 g_uc_send_io_data[ 8 ] = 0x01 ;//使CLK引脚输出gao电平
				
			 PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk high 信号			
			 /////////////////////////////////////////////
                
			 Fun_Delay_Usecond( 100 ) ;  //100us 

			 uc_handshake_ok_times = 0 ; 
            ////////////////////////////////////
			do 
			{								   
			   recv_data = 0xFF ;

			   PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
				
			   recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
				
			   recv_data = (unsigned char ) recv_data & 0xFF ;

			   //Fun_Read_And_Show_Data( recv_data ) ;

			   if( recv_data == _TICK_VALID_HANDSHAKE )//0x00
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
			
			Fun_Delay_Usecond( 100 ) ;  //100us  ;
			   ////////////////////////////////
               #ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
				{
					CString    str1 ;
					
					str1.Format( "数据信息条数：%d" , info_get_times  ) ;
					
					g_plab_zero_times->SetWindowText( str1 ) ;
					
				}
              #endif
				break ;//捕捉到零点，本次捕捉流程结束，开始下次捕捉流程
			  }//if 3 times

		}//if info cap			 
		else //not info cap
		{
		   tick_valid_times = 0 ;
		}

	}//高电平等待零点不断轮询流程 
	while( 1 ) ;
return 1 ;

}
*/

stru_AD_Data_Info_Per_Tick    stru_data_info ;

stru_AD_Data_Per_Tick         stru_data ;

bool      ad_data_get = false ;

bool      ad_data_info_get =  false ;

#define    _DATA   true 

#define   _DATA_INFO    false 


void   Fun_Thread_Sync_Show( bool flag )
{
 if( flag == _DATA )
 {
   ad_data_get = true ;
   
   if( ad_data_info_get == true )
   {
	   int m ;

	   m = 0 ;
   }
 }
 else if( flag == _DATA_INFO )
 {
	 ad_data_info_get = true ;
	 
	 if( ad_data_get == true )
	 {
		 int m ;
		 
		 m = 0 ;
   }
 }

}


int  Fun_Data_Info_Get_Per_Tick( )
{	
  unsigned  int   tick_valid_times = 0 ;

  unsigned  int   no_data_info_times = 0 ;

  unsigned  char  recv_data = 0xFF ;

 // stru_AD_Data_Info_Per_Tick    data_info ;

  LARGE_INTEGER    time1 ;

  LONGLONG    system_tick_count = 0 ;

  unsigned  char   uc_handshake_ok_times = 0 ;
  
  g_bflag_data_info_end = false ;

  Fun_Operation_Timer_Set( _MILLSECOND_1  ) ;// 1ms 读取数据相位信息操作是否超时定时器			   ////////////////////////////////	  
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
		  recv_data == _DATA_INFO_A_ECTION3 ||
		  recv_data == _DATA_INFO_END ) //the flag of the DTU zero pass
	  {
		  tick_valid_times ++ ; //连续读取到数据信息计数累加

		  no_data_info_times = 0; //没有数据信息连续读取次数清零

          if( tick_valid_times >= _TICK_VALID_TIMES )//连续读取次数到
		  {
			  info_get_times  ++ ;  //调试用显示次数累加
			 ///////////get the data information
             if( recv_data == _DATA_INFO_END )
			 {
			    g_bflag_data_info_end = true ;

			//	SetEvent( hEvent_AD_Data_Info_End ) ;//停止ad数据读取线程
			 }
			// if( g_bflag_data_info_end == false )
			 {
			   QueryPerformanceCounter( &time1 ) ;  //得到起始时间
			  
               system_tick_count = time1.QuadPart ;

			   stru_data_info.data_info = recv_data ;

			   stru_data_info.time_stamp = system_tick_count ;

			   //Func_Fifo_Info_Push_Down( ) ;

			  // Fun_Thread_Sync_Show( _DATA ) ;

			 }

			 Fun_Operation_Timer_Stop( ) ; //捕捉成功，停止计时，以防定时器溢出
 
			//产生一个clk周波，即clk拉低200k，完成一个数据接收周期
			 g_uc_send_io_data[ 8 ] = 0x01 ;//使CLK引脚输出gao电平
				
			 PCI8664_SetDeviceDO( hDevice_AD , g_uc_send_io_data ) ;  //输出clk high 信号			
			 /////////////////////////////////////////////
                
			 Fun_Delay_Usecond( 10 ) ;  //100us 

			 uc_handshake_ok_times = 0 ; 
            ////////////////////////////////////
			do 
			{								   
			   recv_data = 0xFF ;

			   PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
				
			   recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
				
			   recv_data = (unsigned char ) recv_data & 0xFF ;

			   //Fun_Read_And_Show_Data( recv_data ) ;

			   if( recv_data == _TICK_VALID_HANDSHAKE )//0x00
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
			
			//Fun_Delay_Usecond( 5 ) ;  //100us  ;
			   ////////////////////////////////
               #ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
				{
					CString    str1 ;
					
					str1.Format( "数据信息条数：%d" , info_get_times  ) ;
					
					g_plab_zero_times->SetWindowText( str1 ) ;
					
				}
              #endif
				break ;//捕捉到零点，本次捕捉流程结束，开始下次捕捉流程
			  }//if 3 times

		}//if info cap			 
		else //if( recv_data == _NO_DATA_INFO )//not info cap
		{
		   tick_valid_times = 0 ;

		   no_data_info_times ++ ;

		   if( no_data_info_times > _TICK_VALID_TIMES )
		   {
             no_data_info_times = 0 ;

			 QueryPerformanceCounter( &time1 ) ;  //得到起始时间
			 
			 system_tick_count = time1.QuadPart ;
			 
			 stru_data_info.data_info = recv_data ;
			 
			 stru_data_info.time_stamp = system_tick_count ;
			 
			 //Func_Fifo_Info_Push_Down( ) ;

		//	 Fun_Thread_Sync_Show( _DATA ) ;
			 
			 break ;
		   }
		}//else no dta info 
		
	}//不断轮询流程 
	while( 1 ) ;
return _OK ;

}




int  Fun_Read_Info_And_Data( ) //Info_Get_Per_Tick( )
{
 unsigned int error_flag = 0xf ;

 int i  ;
 
 LONGLONG   system_tick_count = 0 ;
	
 unsigned    read_len = _AD_SAMPLE_CHANNEL_MAX ; //10 * 2 line
 
 //stru_AD_Data_Per_Tick    stru_data ;

 SHORT     data_buf[ _AD_SAMPLE_CHANNEL_MAX * 2 ] ;
 ////////////////////////////////////
 if( !PCI8664_StartDeviceProAD( hDevice_AD ) )		// Start AD
 {
	 AfxMessageBox( "PCI8664_StartDeviceProAD Error..." );
	 
	 return -1 ;
 }
 ////////////////////////////	
 error_flag = Fun_Data_Info_Get_Per_Tick( ) ;

 if( error_flag != _TIMEOUT )//get data information suscessfult
 {
	 // SetEvevt( hEvent_AD_Read_Per_Tick_Run ) ;
     ////////////////////////////////////////////////////////////	 
	 memset( data_buf , 0 , sizeof( data_buf ) ) ;
	 
	 if( !PCI8664_ReadDeviceProAD_Npt( hDevice_AD, data_buf, nReadSizeWords, &nRetSizeWords ) )
	 {
		 AfxMessageBox("PCI8664_ReadDeviceProAD_Npt Error...") ;	
		 
		 return -1 ;
	 }
	 if( ( ULONG )nRetSizeWords == read_len )//读取到相应数据长度的数据
	 {
		 LARGE_INTEGER    time1 ;	 
		 //////////////////////////////////延时			
		 QueryPerformanceCounter( &time1 ) ;  //得到起始时间
		 
		 system_tick_count = time1.QuadPart ;
		 
		 for( i = 0 ; i < _AD_SAMPLE_CHANNEL_MAX ; i ++ )
		 {
			 stru_data.data_line[ i ] = data_buf[ i ] ;
		 }
		 
		 stru_data.time_stamp = system_tick_count ;
		 
		 //Fun_Fifo_Push_Down( stru_AD_Data_Per_Tick data , len ) ;
		// PCI8664_StopDeviceProAD( hDevice_AD ) ;		// Stop AD

	//	 Fun_Thread_Sync_Show( _DATA_INFO ) ;
		 int a = 0 ;
	 }
     return 1 ;
 }
 else
 {
	 return -1 ;
 }

}


HANDLE   hThread_AD_Read_Data ;

HANDLE   hEvent_Thread_AD_Read_Data_Run ; 

#define  _START_AD_CONVERT_ERROR   -1

#define  _AD_READ_ERROR            -2 



void CALLBACK Thread_AD_Read_Data( )
{
	int i  ;

	int        error_flag = 0 ; 
	
	LONGLONG   system_tick_count = 0 ;
	
	unsigned   read_len = _AD_SAMPLE_CHANNEL_MAX ; //10 * 2 line
	
//	stru_AD_Data_Per_Tick    stru_data ;
	
	SHORT     data_buf[ _AD_SAMPLE_CHANNEL_MAX * 2 ] ;



  do 
  {
/*	
	  if(!PCI8664_InitDeviceProAD( hDevice_AD ,  &ADPara ) )		// Initial AD
	  {
		  AfxMessageBox( "PCI采集卡AD参数设置失败！" ) ;
		  
          error_flag = 0 ; //_START_AD_INIT_ERROR ;  
	  }
*/	 
	  if( !PCI8664_StartDeviceProAD( hDevice_AD ) )		// Start AD
	  {
		  AfxMessageBox( "PCI8664_StartDeviceProAD Error..." ) ;
		  
		  error_flag = _START_AD_CONVERT_ERROR ;
	}

	 if( WaitForSingleObject( hEvent_Thread_AD_Read_Data_Run  , 0 ) == WAIT_OBJECT_0 ) 
	  {		 	 
		 // SetEvevt( hEvent_AD_Read_Per_Tick_Run ) ;//ad 读取是否超时判断线程
		 ////////////////////////////////////////////////////////////
	//	 PCI8664_StartDeviceProAD( hDevice_AD ) ;

		 memset( data_buf , 0xFF , sizeof( data_buf ) ) ;
		 
		 if( !PCI8664_ReadDeviceProAD_Npt( hDevice_AD, data_buf, read_len, &nRetSizeWords ) )
		 {
             char  message[ 256 ] ;
			 
			 PCI8664_GetLastErrorEx( "PCI8664_ReadDeviceProAD_Npt", message ) ;

			 error_flag = _AD_READ_ERROR ;
			 
		//	 break  ;
		 }
		 else if( ( ULONG )nRetSizeWords == read_len )//读取到相应数据长度的数据
		 {
			 //  ResetEvent( hEvent_AD_Read_Per_Tick_Run ) ；

			 SetEvent( hEvent_Thread_AD_Read_Data_Info_Run ) ;

			// ResetEvent( hEvent_Thread_AD_Read_Data_Run ) ;

		//	 PCI8664_StopDeviceProAD( hDevice_AD ) ;

			 PCI8664_ReleaseDeviceProAD( hDevice_AD ) ;

		//	 PCI8664_ReleaseDevice( hDevice );		// Release device object


			 
			 LARGE_INTEGER    time1 ;	 
			 //////////////////////////////////延时			
			 QueryPerformanceCounter( &time1 ) ;  //得到起始时间
			 
			 system_tick_count = time1.QuadPart ;
			 
			 for( i = 0 ; i < _AD_SAMPLE_CHANNEL_MAX ; i ++ )
			 {
				 stru_data.data_line[ i ] = data_buf[ i ] ;
			 }
			 
			 stru_data.time_stamp = system_tick_count ;
             /*
			// error_flag = PCI8664_StopDeviceProAD( hDevice_AD ) ;

			 if( error_flag == true )
			 {
				 AfxMessageBox( "STOP OK!") ;
			 }
			 
			 //Fun_Fifo_Push_Down( stru_AD_Data_Per_Tick data , len ) ;
			// PCI8664_StopDeviceProAD( hDevice_AD ) ;		// Stop AD
           */
			 int  a = 0 ;
		 }
	  }//if run 
  } 
  while ( 1 );

}

void  Fun_Thread_AD_Read_Data_Init( )
{
	/////////////create a thread
	hThread_AD_Read_Data = CreateThread( 0, 0, ( pfun_callback)Thread_AD_Read_Data , 0 , 
		CREATE_SUSPENDED , &dwThreadID1 ) ;
	
	SetThreadPriority( hThread_AD_Read_Data, THREAD_PRIORITY_NORMAL ) ;//THREAD_PRIORITY_ABOVE_NORMAL ) ; 
	
	hEvent_Thread_AD_Read_Data_Run = CreateEvent( NULL , true , false , NULL) ; 
}


HANDLE   hThread_AD_Read_Data_Info ;

HANDLE   hEvent_Thread_AD_Read_Data_Info_Run ;

 

void CALLBACK Thread_AD_Read_Data_Info( )
{
int   error_flag = 0 ;
/*
do 
{
  if( WaitForSingleObject( hEvent_Thread_AD_Read_Data_Info_Run  , 0 ) == WAIT_OBJECT_0 ) 
  {		 
    error_flag = Fun_Data_Info_Get_Per_Tick( ) ;

	if( error_flag == _OK)
	{
       ResetEvent( hEvent_Thread_AD_Read_Data_Info_Run ) ;

	   double   time = ( stru_data_info.time_stamp - stru_data.time_stamp ) * 1000.0 / g_db_system_freguence ;

	   int a = 0 ;
	}

  } 
}
while ( 1 );
*/		
}

void  Fun_Thread_AD_Read_Data_Info_Init( )
{
	/////////////create a thread
	hThread_AD_Read_Data_Info = CreateThread( 0, 0, ( pfun_callback)Thread_AD_Read_Data_Info , 0 , 
		CREATE_SUSPENDED , &dwThreadID1 ) ;
	
	SetThreadPriority( hThread_AD_Read_Data_Info, THREAD_PRIORITY_ABOVE_NORMAL ) ; //THREAD_PRIORITY_ABOVE_NORMAL ) ; 
	
	hEvent_Thread_AD_Read_Data_Info_Run = CreateEvent( NULL , true , false , NULL) ; 
}