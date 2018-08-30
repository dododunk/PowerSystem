#include "protocol.h"



stru_PC2MCU_Protocol  g_stru_pc2mcu_protocol ;

unsigned char         g_uc_cmd_buf[ 16 ] ;

unsigned char         g_uc_cmd_buf2[ 16 ] ;

unsigned char         g_uc_cmd_buf3[ 16 ] ;



unsigned   char   g_uc_multi_section_decode_frame_number  ;//多段母线同时调制时，接收到的指令帧数目计数器
//初始化是设定为0 ，每次多段母线调制命令发送完毕后，不管是否成功调制，该变量返回为0


#define      _FRAME_LEN            16  

//多母线段同时调制时，存储命令字节的全局变量，最多为4段母线，最多三相数据，每帧指令长16，因此 12 * 16
unsigned  char    g_uc_multi_section_cmd_buf[ 12 ] [ 16 ] ;

//************************************
// Method:    Fun_WPLC_Data_Set
// FullName:  Fun_WPLC_Data_Set
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_WPLC_Protocol_Data stru
//************************************
stru_WPLC_Protocol_Data    Fun_WPLC_Data_Set( stru_WPLC_Protocol_Data  stru )
{
 unsigned char buf1 = 0 , buf2 = 0 ;

 unsigned long ltemp = 0 ;

 if( stru.un_module_addr.ldata > 0x1FFFF )
 {
   return stru ; // ; _MODULE_ADDR_ERROR ;
 }
 else
 {
//	if( stru.uc_user_cmd & 0xFE == _CMD_CONGEAL
//		|| stru.uc_user_cmd & 0xFE == _CMD_CONGEAL_HOUR ) //congeal command

   if( stru.uc_user_cmd == 0xF2 )
	{		
	   stru.uc_data[ 0 ] = stru.uc_user_cmd & 0xFE ;//set the lowest bit of D0 to zero //get uc_data0
		
	   stru.uc_data[ 1 ] = 0x00 ;
		
	   stru.uc_data[ 2 ] = 0x00;   
	   
       stru.uc_data[ 3 ] = 0x00 ;
	   //ucdata[ 0 ] lower 8 bit of the un_congeal_time  
	   buf1 = ( stru.un_congeal_time.ucdata[ 1 ] & 0x30 ) >> 4 ; //get  higher 2 bit of the time

	   stru.uc_data[ 3 ] = stru.uc_data[ 3 ] | buf1 ; //set the d1,d0 to uc_data3 ,the lowest bit

	   buf1 = stru.un_congeal_time.ucdata[ 1 ] & 0x0F ; //get  lower 4 bit of the time

	   stru.uc_data[ 3 ] = stru.uc_data[ 3 ] | ( buf1 << 4 ) ;//set the bit d4-d7 of the uc_data3 

       stru.uc_data[ 3 ] = stru.uc_data[ 3 ] | ( ( stru.uc_phase_number & 0x03 )<< 2 ) ; //set bit2 - bit3 of uc_data3

	   stru.uc_data[ 4 ] = stru.un_congeal_time.ucdata[ 0 ] ;

	   return stru ;
	}
 	else
	{   //long 0x01 0X 03 04  >> ucdata0 : 0    1    2  3 
	//	                                  04 , 03 , 0X ,01
		buf1 = stru.un_module_addr.ucdata[ 2 ] & 0x01 ; //get the bit 17
		
	//	buf1 = ( unsigned char ) ( ltemp << 16 ) ; //get the bit 17
		
		buf2 = stru.uc_user_cmd &0xF7 ;//set the lowest bit of D0 to zero
		
		stru.uc_data[ 0 ] = buf2 | buf1 ; //get uc_data0
		
		stru.uc_data[ 1 ] = stru.un_module_addr.ucdata[ 1 ] ;
		
	    stru.uc_data[ 2 ] = stru.un_module_addr.ucdata[ 0 ] ;	
		
		stru.uc_data[ 3 ] = ( ( stru.uc_sub_meter_addr & 0x0F ) << 4 )
			              | ( ( stru.uc_phase_number & 0x03 )<< 2 )
		                  | ( stru.uc_station_number & 0x03 ) ;

	   stru.uc_data[ 4 ] = 0x67 ;

	   return stru ;
	}

 } 
}
