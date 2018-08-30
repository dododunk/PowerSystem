
/*出线图初始化
定义一个Input_Channel_Map结构体
定义对应个数的Input_Channel结构体数组
将Input_Channel_Map结构体内的指针*p_input_channle与Input_Channel结构体数组地址关联
调用Fun_Channel_Map_Init( Input_Channel_Map * p )，初始化出线map。
*/

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


//===============================================================
typedef  struct
{
  Iput_Channel   *p_input_channle ;

  unsigned char  uc_input_channle_number ;

} Input_Channel_Map ;


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
void    Fun_Card_Number_Init( int  num ) ;

void    Fun_Line_Number_Init( int  num ) ;

void    Fun_AD_Init( int card_number , PPCI8664_PARA_AD * p ) ;

void    Fun_AD_Init( int card_number ) ;//按照默认的参数来初始化该AD采集卡

void    Fun_Channel_Map_Init( Input_Channel_Map * p ) ;

void    Fun_Buf_Len_Init( int line_data_deep , int ad_data_deep ) ;

void    Fun_Uninstall_Device( ) ;

