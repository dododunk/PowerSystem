
//***************************************************************************
//========================================================================= 
#define         _ACTRUAL_ADDR_END          9000 

#define         _SIMULATIVE_ADDR_START     10000 

#define         _SIMULATIVE_ADDR_END       20000 


//***************************************************************************
//========================================================================
#define        _READ_TRIG_DEGREE_ALL     0x00	 //读三相角度

#define        _READ_TRIG_DEGREE_A       0x01	//读A相角度

#define        _READ_TRIG_DEGREE_B       0x02	//读B相角度

#define        _READ_TRIG_DEGREE_C       0x03	//读C相角度

#define        _SET_TRIG_DEGREE_ALL      0x10	//设置三相角度

#define        _SET_TRIG_DEGREE_A        0x11	//设置A相角度

#define        _SET_TRIG_DEGREE_B        0x12	//设置B相角度

#define        _SET_TRIG_DEGREE_C        0x13	//设置C相角度

#define        _TRIG_SYNC_DATA_ALL       0x20	//三相触同时发数据

#define        _TRIG_DATA_A              0x21	//A相触发数据

#define        _TRIG_DATA_B              0x22	//B相触发数据

#define        _TRIG_DATA_C              0x23	//C相触发数据

#define        _TRIG_SEQU_DATA_ALL       0x24	//三相触顺序发数据

#define        _CONF_DTU_CMD             0x70	//设置室外机字段


//***************************************************************************
//==========================================================================
#define       _ERROR_CURRENT_LOOP_OK                0x10

#define       _ERROR_API_TIMEOUT                    0x00
//////////////////////////
#define       _ERROR_CURRENT_LOOP_TIMEOUT           0x01 

#define       _ERROR_CURRENT_LOOP_ERROR             0x02 

#define       _ERROR_API_ERROR                      0x03



//***************************************************************************
//==========================================================================
#define      _PROTOCOL_DATA_LEN      0x08

struct   stru_PC2MCU_Protocol
{
unsigned char   uc_start_falg1 ;

unsigned char   uc_start_flag2 ;

unsigned char   uc_api_cmd ;        //PC-mcu  cmd  PC机到地板命令字

unsigned char   uc_primary_line  ;

unsigned char   uc_line_number ;  

unsigned char   uc_api_phase_number ;

unsigned char   uc_delay_zero_number ;

unsigned char   data[ _PROTOCOL_DATA_LEN ] ;

unsigned char   crc ;

unsigned char   data_len ;

};


typedef  union
{
unsigned long   ldata ;

unsigned char   ucdata[ 4 ] ;
} Long_Byte ;


typedef  union
{
  unsigned int   idata ;
	
  unsigned char   ucdata[ 2 ] ;
} Int_Byte ;


struct   stru_WPLC_Protocol_Data
{
unsigned char   uc_user_cmd ;  //ui cmd  UI命令字：读有A相功。。。

Long_Byte       un_module_addr  ;//模块地址

unsigned char   uc_sub_meter_addr ; //子表地址

unsigned char   uc_phase_number ; //相位

unsigned char   uc_station_number ; //

unsigned char   uc_end_flag ; //

unsigned char   data[ 5 ] ;

Int_Byte        un_congeal_time ;

};


#define   MODULE_ADDR_ERROR        0x00

#define   USER_CMD_CONGEAL         0xF2 

#define   USER_CMD_CONGEAL_HOUR    0xF4

#define   MODULE_ADDR_ERROR        0x00

int   Fun_WPLC_Data_Set( stru_WPLC_Protocol_Data  stru )
{
 unsigned char buf1 = 0 , buf2 = 0 ;

 unsigned long ltemp = 0 ;

 if( stru.module_addr.ldata > 0x1FFFFFFFF )
 {
   return MODULE_ADDR_ERROR ;
 }
 else
 {


	if( stru.uc_user_cmd &0xF7 == USER_CMD_CONGEAL
		|| stru.uc_user_cmd &0xF7 == USER_CMD_CONGEAL_HOUR ) //congeal command
	{		
	   stru.data[ 0 ] = stru.uc_user_cmd &0xF7 ;//set the lowest bit of D0 to zero //get data0
		
	   stru.data[ 1 ] = 0x00 ;
		
	   stru.data[ 2 ] = 0x00;   
	   
       stru.data[ 3 ] = 0x00 ;
	   
	   buf1 = ( stru.un_congeal_time.ucdata[ 0 ] & 0x30 ) >> 4 ; //get  higher 2 bit of the time

	   stru.data[ 3 ] = stru.data[ 3 ] | buf1 ; //set the d1,d0 to data3 ,the lowest bit

	   buf1 = stru.un_congeal_time.ucdata[ 0 ] & 0x0F ; //get  lower 4 bit of the time

	   stru.data[ 3 ] = stru.data[ 3 ] | ( buf1 << 4 ) ;//set the bit d4-d7 of the data3 

       stru.data[ 3 ] = stru.data[ 3 ] | ( ( stru.uc_phase_number & 0x03 )<< 2 ) ; //set bit2 - bit3 of data3

	   stru.data[ 4 ] = stru.un_congeal_time.ucdata[ 1 ] ;

	   return 1 ;
	}
 	else
	{
		buf1 = stru.un_module_addr.ucdata[ 1 ] & 0x01 ; //get the bit 17
		
		buf1 = ( unsigned char ) ( ltemp >> 16 ) ; //get the bit 17
		
		buf2 = stru.uc_user_cmd &0xF7 ;//set the lowest bit of D0 to zero
		
		stru.data[ 0 ] = buf1 | buf2 ; //get data0
		
		stru.data[ 1 ] = stru.un_module_addr.ucdata[ 2 ] ;
		
	    stru.data[ 2 ] = stru.un_module_addr.ucdata[ 3 ] ;	
		
		stru.data[ 3 ] = ( ( stru.uc_sub_meter_addr & 0x0F ) << 4 )
			              | ( ( stru.uc_phase_number & 0x03 )<< 2 )
		                  | ( stru.uc_station_number & 0x03 ) ;

	   stru.data[ 4 ] = 0x67 ;

	   return 1 ;
	}

} ;


