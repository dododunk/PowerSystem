
//***************************************************************************
//========================================================================= 
#define         _ACTRUAL_ADDR_END          9000 

#define         _SIMULATIVE_ADDR_START     10000 

#define         _SIMULATIVE_ADDR_END       20000 


//***************************************************************************
//========================================================================
#define        _READ_TRIG_ANGLE_ALL     0x00	 //读三相角度

#define        _READ_TRIG_ANGLE_A       0x01	//读A相角度

#define        _READ_TRIG_ANGLE_B       0x02	//读B相角度

#define        _READ_TRIG_ANGLE_C       0x03	//读C相角度

#define        _SET_TRIG_ANGLE_ALL      0x10	//设置三相角度

#define        _SET_TRIG_ANGLE_A        0x11	//设置A相角度

#define        _SET_TRIG_ANGLE_B        0x12	//设置B相角度

#define        _SET_TRIG_ANGLE_C        0x13	//设置C相角度

#define        _TRIG_SYNC               0x20	//三相触同时触发数据

#define        _TRIG_A                  0x21	//A相触发数据

#define        _TRIG_B                  0x22	//B相触发数据

#define        _TRIG_C                  0x23	//C相触发数据

#define        _TRIG_SEQU               0x24	//三相触顺序触发数据

#define        _CONF_DTU                0x70	//设置室外机字段

#define        _TRIG_AD                 0x0F  //触发命令，没有回馈



#define        _CMD_CONGEAL             0xF2  //广播冻结命令

#define        _CMD_CONGEAL_HOUR        0xF4  //每小时广播冻结命令

#define        _CONGEAL_SINGLE          0x00  //广播冻结命令，单项调制

#define        _CONGEAL_SYNC            0x01  //广播冻结命令，三项同时调制

#define        _CONGEAL_SEQU            0x02  //广播冻结命令，三项顺序调制
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

#define      _PHASE_A                1

#define      _PHASE_B                2

#define      _PHASE_C                3

#define      _PHASE_ABC                4

#define      _PHASE_ABC_SEQUENCE                5



#define      _PHASE_ALL              0  //A B C

#define      _READ_TRIG_ANGLE        5  //read the angle of trig

//meter read type define

#define      _METER_READ_SINGLE      1

#define      _METER_READ_SYNC        2

#define      _METER_READ_SEQU        3
//////////////pc to mcu 协议数据帧各bit排布定义

#define      _START_BYTE             0 

#define      _DTU_ADDR_BYTE          1

#define      _CMD_BYTE               2 

#define      _ANGLE_DATA_BYTE        3

#define      _FRAME_NUMBER_BYTE      4

#define      _DATA_BYTE1             5

#define      _DATA_BYTE2             6

#define      _DATA_BYTE3             7

#define      _DATA_BYTE4             8

#define      _DATA_BYTE5             9

#define      _DATA_BYTE6             10

#define      _DATA_BYTE7             11

#define      _DATA_BYTE8             12

#define      _DATA_BYTE9             13

#define      _CRC_BYTE               14

#define      _END_BYTE               15



#define      _PROTOCOL_DATA_LEN      0x08


#define      _MULTI_SECTION_DECODE_END_FLAG  0x5A

#define      _MULTI_SECTION_DECODE_FLAG      0xA5  //多段母线同时调制标志位


extern   unsigned   char   g_uc_multi_section_decode_frame_number  ;//多段母线同时调制时，接收到的指令帧数目计数器
            //初始化是设定为0 ，每次多段母线调制命令发送完毕后，不管是否成功调制，该变量返回为0


#define      _FRAME_LEN            16 

#define      _READBACK_FRAME_LEN   256 

//多母线段同时调制时，存储命令字节的全局变量，最多为4段母线，最多三相数据，每帧指令长16，因此 12 * 16
extern   unsigned  char    g_uc_multi_section_cmd_buf[ 12 ] [ 16 ] ;



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


typedef  struct
{
	Long_Byte       un_ldata_a ;

	Long_Byte       un_ldata_b ;
	
	Long_Byte       un_ldata_c ;

} Line_Data ;

/*
typedef  struct
{
	unsigned char   ucline_number ;

	Line_Data    *  p_line_data ;
	
} Card_Data ;
*/
//////读写触发角度结构体//////////////////////////////////////////////////////////////////////////////
//====================================================================================================
struct   stru_Set_Angle_Single
{	
	unsigned char   uc_section  ; //母线、段 to outerdoor addr   
	
	unsigned char   uc_mcu_phase_number ;//相
	
	unsigned char   uc_trig_angle ;//相角度
	
};

struct   stru_Set_Angle_All
{	
	unsigned char   uc_section  ; //母线、段 to outerdoor addr
	
	unsigned char   uc_trig_angle_a ;//A相角度
	
	unsigned char   uc_trig_angle_b ;//B相角度
	
	unsigned char   uc_trig_angle_c ;//C相角度
	
};

struct   stru_Read_Angle
{	
	unsigned char   uc_mcu_cmd ;  //PC-mcu  cmd  PC机到地板命令
	
	unsigned char   uc_section  ; //母线、段 to outerdoor addr	
	
};

struct   stru_Angle_Data
{
	unsigned char   uc_trig_angle_a ;//A相角度，同时也是数据反馈内容
	
	unsigned char   uc_trig_angle_b ;//B相角度，同时也是数据反馈内容
	
	unsigned char   uc_trig_angle_c ;//C相角度，同时也是数据反馈内容
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////
struct   stru_Meter_Read
{
//	unsigned char   uc_trig_mode ;    //触发\调制方式,三项同时，三项顺序，单相

	unsigned char   uc_user_cmd ;  //ui cmd  UI命令字：读有A相功。。。
	
	Long_Byte       un_module_addr  ;//模块地址
	
	unsigned char   uc_sub_meter_addr ; //子表地址
	
	unsigned char   uc_phase_number ; //相位
	
	unsigned char   uc_station_number ; //站号
	
	unsigned char   uc_section  ; //母线、段 to outerdoor addr
	
	unsigned char   uc_line_number ;  //线 

	unsigned char   uc_multi_section_decode_flag ;//是否是多段母线同时调制命令标志
	                      //0x5A代表后续有指令需要连发，为0xA5时代表为最有一个指令。
} ;

struct   stru_Meter_Congeal
{	
	unsigned char   uc_phase_number ; //相位
	
	Int_Byte        un_congeal_time ;//冻结时间
} ;

/*
typedef   struct 
{
	unsigned char  ucdata ;

	unsigned char  bit0 =  ucdata & 0x01 >> 0 ;		

	unsigned char  bit1 =  ucdata & 0x02 >> 1 ;	

	unsigned char  bit2 =  ucdata & 0x04 >> 2 ;		

	unsigned char  bit3 =  ucdata & 0x08 >> 3 ;	
	
	
	unsigned char  bit4 =  ucdata & 0x10 >> 4 ;		
	
	unsigned char  bit5 =  ucdata & 0x20 >> 5 ;		
	
	unsigned char  bit6 =  ucdata & 0x40 >> 6 ;		
	
	unsigned char  bit7 =  ucdata & 0x80 >> 7 ;	

} Bit_8 ;


typedef   struct 
{
	unsigned int   idata ;
	
	unsigned char  bit0 =  idata & 0x01 >> 0 ;		
	
	unsigned char  bit1 =  idata & 0x02 >> 1 ;	
	
	unsigned char  bit2 =  idata & 0x04 >> 2 ;		
	
	unsigned char  bit3 =  idata & 0x08 >> 3 ;	
		
	unsigned char  bit4 =  idata & 0x10 >> 4 ;		
	
	unsigned char  bit5 =  idata & 0x20 >> 5 ;		
	
	unsigned char  bit6 =  idata & 0x40 >> 6 ;		
	
	unsigned char  bit7 =  idata & 0x80 >> 7 ;	

	
	unsigned char  bit8 =  idata & 0x01 >> 8 ;		
	
	unsigned char  bit9 =  idata & 0x02 >> 9 ;	
	
	unsigned char  bit10 =  idata & 0x04 >> 10 ;		
	
	unsigned char  bit11 =  idata & 0x08 >> 11 ;	
	
	
	unsigned char  bit12 =  idata & 0x10 >> 12 ;		
	
	unsigned char  bit13 =  idata & 0x20 >> 13 ;		
	
	unsigned char  bit14 =  idata & 0x40 >> 14 ;		
	
	unsigned char  bit15 =  idata & 0x80 >> 15 ;	
} Bit_16 ;

typedef   struct 
{
   unsigned int    idata ;

   unsigned int    ad_data = idata & 0x3F ;

   unsigned char   trig_flag = ( idata & 80 ) >> 15 ;

}AD_Data ; 
*/
typedef   struct 
{
	unsigned int    idata ;
	
	unsigned int    ad_data : 2 ;
	
	unsigned char   trig_flag : 1 ;
	
}AD_Data ; 
//////////////////////////////////////////////////////////////////////////////////////////////////
//================================================================================================
struct   stru_WPLC_Protocol_Data
{
	unsigned char   uc_user_cmd ;  //ui cmd  UI命令字：读有A相功。。。
	
	Long_Byte       un_module_addr  ;//模块地址
	
	unsigned char   uc_sub_meter_addr ; //子表地址
	
	unsigned char   uc_phase_number ; //相位
	
	unsigned char   uc_station_number ; //站号
	
	unsigned char   uc_end_flag ; //特征码
	
	unsigned char   uc_data[ 5 ] ;//指令数据项
	
	Int_Byte        un_congeal_time ;//冻结时间
	
};

/**/
struct   stru_PC2MCU_Protocol
{
unsigned char   uc_start ;

unsigned char   uc_mcu_cmd ;        //PC-mcu  cmd  PC机到地板命令字

unsigned char   uc_section  ; //母线、段 to outerdoor addr

unsigned char   uc_line_number ;  //线 

unsigned char   uc_mcu_phase_number ;//相

//unsigned char   uc_data[ _PROTOCOL_DATA_LEN ] ;

unsigned char   uc_trig_angle_a ;//A相角度

unsigned char   uc_trig_angle_b ;//B相角度

unsigned char   uc_trig_angle_c ;//C相角度

unsigned char   uc_frame_number ;//数据包号

stru_WPLC_Protocol_Data  stru_wplc_protocol ;//工频畸变下行协议数据包

unsigned char   uc_crc ;//CRC校验

unsigned char   uc_data_len ;

unsigned char   uc_end ;

};



#define    _AD_SAMPLE_TIMES_PER_TRIG   320

#define    _AD_CHANNEL_TOTAL_NUMBER    10 

#define    _AD_SAMPLE_TIMES_PER_BIT    8
     

typedef     struct  
{
  short    trig_point0 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;

  short    trig_point1 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;

  short    trig_point2 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
  
  short    trig_point3 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
  
  short    trig_point4 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
  
  short    trig_point5 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;

  short    trig_point6 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
  
  short    trig_point7 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
  
} stru_AD_Sample_Data_One_Bit ;








/*
typedef     struct  
{
	AD_Sample_Data_One_Bit   trig_point1 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
	
	unsigned  int   trig_point2 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
	
	unsigned  int   trig_point3 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
	
	unsigned  int   trig_point4 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
	
	unsigned  int   trig_point5 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
	
	unsigned  int   trig_point6 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
	
	unsigned  int   trig_point7 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
	
	unsigned  int   trig_point8 [ _AD_SAMPLE_TIMES_PER_TRIG ] ;
	
} AD_Sample_Data_One_Bit ;
*/


#define   _MODULE_ADDR_ERROR        0x00

#define   _USER_CMD_CONGEAL         0xF2 

#define   _USER_CMD_CONGEAL_HOUR    0xF4

#define   _MODULE_ADDR_ERROR        0x00


#define   _CMD_ERROR          -1

#define   _PROTOCOL_NOT_SET   0 

#define   _OK                 1

extern void  CMD_Buf_Init( ) ;

extern int Set_CMD_User( stru_PC2MCU_Protocol *user_cmd ) ;

extern int Set_CMD_WPLC( stru_WPLC_Protocol_Data * wplc_cmd ) ;

extern int Send_CMD_Trig( stru_PC2MCU_Protocol * mcu_cmd ,stru_WPLC_Protocol_Data * wplc_cmd ) ;

extern stru_WPLC_Protocol_Data Fun_WPLC_Data_Set( stru_WPLC_Protocol_Data  stru ) ;




///*
extern stru_PC2MCU_Protocol  g_stru_pc2mcu_protocol ;

extern unsigned char         g_uc_cmd_buf[ 16 ] ;

extern unsigned char         g_uc_cmd_buf2[ 16 ] ;

extern unsigned char         g_uc_cmd_buf3[ 16 ] ;


//*/

//extern     int  Fun_Trig_Angle_RW( ) ;


