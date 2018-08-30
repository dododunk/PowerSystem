
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


//***************************************************************************
//==========================================================================
#define       _ERROR_CURRENT_LOOP_OK                0x10

#define       _ERROR_API_TIMEOUT                    0x00
//////////////////////////
#define       _ERROR_CURRENT_LOOP_TIMEOUT           0x01 

#define       _ERROR_CURRENT_LOOP_ERROR             0x02 

#define       _ERROR_API_ERROR                      0x03

#define       _MODULE_ADDR_ERROR                    0x04

#define       _CMD_ERROR                            -1

#define       _PROTOCOL_NOT_SET                     0x05 

#define       _OK                                   0x06

//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================

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


////////////////////////////////////////////////////////////////////////////////
extern stru_Angle_Data Set_Angle_Single( stru_Set_Angle_Single * cmd  ) ;

extern stru_Angle_Data Set_Angle_All( stru_Set_Angle_All * cmd  ) ;	

extern stru_Angle_Data Read_Trig_Angle( stru_Read_Angle * cmd  ) ;

/////////////////////////////////////////////////////////////////////////////////



//////读表内数据结构体//////////////////////////////////////////////////////////////////////////////
//====================================================================================================
struct   stru_Meter_Read
{
	unsigned char   uc_user_cmd ;  //ui cmd  UI命令字：读有A相功。。。
	
	Long_Byte       un_module_addr  ;//模块地址
	
	unsigned char   uc_sub_meter_addr ; //子表地址
	
	unsigned char   uc_phase_number ; //相位
	
	unsigned char   uc_station_number ; //站号
	
	unsigned char   uc_section  ; //母线、段 to outerdoor addr
	
	unsigned char   uc_line_number ;  //线 
} ;

struct   stru_Meter_Congel
{	
	unsigned char   uc_phase_number ; //相位
	
	Int_Byte        un_congeal_time ;//冻结时间
} ;




////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
extern int Meter_Read_Single( stru_Meter_Read * cmd ) ;

extern int Meter_Read_Sync( stru_Meter_Read * cmd_a ,
						    stru_Meter_Read * cmd_b ,
						    stru_Meter_Read * cmd_c   ) ;

extern int Meter_Read_Sequence( stru_Meter_Read * cmd_a ,
							    stru_Meter_Read * cmd_b ,
						        stru_Meter_Read * cmd_c   ) ;
////////////////////////////////////////////////
extern int Meter_Congel_Single( stru_Meter_Congel * cmd ) ;

extern int Meter_Congel_Sync( stru_Meter_Congel * cmd_a ,
							  stru_Meter_Congel * cmd_b ,
							  stru_Meter_Congel * cmd_c   ) ;

extern int Meter_Congel_Sequence( stru_Meter_Congel * cmd_a ,
								  stru_Meter_Congel * cmd_b ,
							      stru_Meter_Congel * cmd_c   ) ;

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/*出线图初始化
定义一个Input_Channel_Map结构体
定义对应个数的Input_Channel结构体数组
将Input_Channel_Map结构体内的指针*p_input_channle与Input_Channel结构体数组地址关联
调用Fun_Channel_Map_Init( Input_Channel_Map * p )，初始化出线map。
*/


//通道所在位置的详细说明结构体，初始化出线拓扑时首先定义并初始化出线总个数的该结构体，
//然后将该结构体的首指针付给*p_input_channle
//===============================================================
typedef  struct 
{
	unsigned char  uc_phase_number ; //相
	
	unsigned char  uc_line_number  ;//线
	
	unsigned char  uc_section_number ; //段
	
	unsigned char  uc_station_number ; //站
	
	unsigned char  uc_occupy_line_number ; //实际所连接的通道
	
	unsigned char  uc_card_number ; //所在的ad采集卡号
	
} Input_Channel ;



//通道拓扑图结构体，*p_input_channle指针指向设定好的通道说明结构体,该结构体数目由出线总个数决定
//===============================================================
typedef  struct
{
	Iput_Channel   *p_input_channle ;
	
	unsigned char  uc_input_channle_number ;
	
} Input_Channel_Map ;



//AD 采集卡参数设置结构体，由采集卡厂商提供
//===============================================================
typedef struct _PCI8664_PARA_AD
{
	LONG ADMode; // AD 模式选择(连续/分组方式)
	
	LONG FirstChannel; // 同步首通道对[0, 31]
	
	LONG LastChannel; // 同步末通道对[0, 31]，要求末通道必须大于或等于首通道
	
	LONG Frequency; // 采集频率，单位为Hz
	
	LONG GroupInterval; // 分组时的组间间隔(单位：微秒) [1, 419430]
	
	LONG LoopsOfGroup; // 组内循环次数[1, 255]
	
	LONG Gains; // 增益设置
	
	LONG InputRange; // 模拟量输入量程范围
	
	LONG TriggerMode; // 触发模式选择
	
	LONG TriggerType; // 触发类型选择(边沿触发/脉冲触发)
	
	LONG TriggerDir; // 触发方向选择(正向/负向触发)
	
	LONG TimeoutForNpt; // 非空查询方式下的超时时间,单位秒,取值范围为[0, 3600]
	
}PCI8664_PARA_AD, *PPCI8664_PARA_AD;




//===============================================================
void    Fun_Card_Number_Init( int  num ) ;//设置系统内采集板个数

void    Fun_Line_Number_Init( int  num ) ; //设置系统内出线总书目

void    Fun_AD_Init( int card_number , PPCI8664_PARA_AD * p ) ;//按照用户定义的参数AD采集卡初始化

void    Fun_AD_Init( int card_number ) ;//按照默认的参数来初始化该AD采集卡

void    Fun_Channel_Map_Init( Input_Channel_Map * p ) ;//初始化出线定义，初始化设定各个通道所在的线、相、段

void    Fun_Buf_Len_Init( int line_data_deep , int ad_data_deep ) ;//初始化ad采集数据缓冲区的大小，各通道解码数据缓冲区大小

void    Fun_Uninstall_Device( ) ;//释放初始化动态开辟的内存单元



