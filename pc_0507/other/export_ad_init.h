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
	
}PCI8664_PARA_AD ;




//===============================================================
void    Fun_Card_Number_Init( int  num ) ;//设置系统内采集板个数

void    Fun_Line_Number_Init( int  num ) ; //设置系统内出线总书目

void    Fun_AD_Init( int card_number , PPCI8664_PARA_AD * p ) ;//按照用户定义的参数AD采集卡初始化

void    Fun_AD_Init( int card_number ) ;//按照默认的参数来初始化该AD采集卡

void    Fun_Channel_Map_Init( Input_Channel_Map * p ) ;//初始化出线定义，初始化设定各个通道所在的线、相、段

void    Fun_Buf_Len_Init( int line_data_deep , int ad_data_deep ) ;//初始化ad采集数据缓冲区的大小，各通道解码数据缓冲区大小

void    Fun_Uninstall_Device( ) ;//释放初始化动态开辟的内存单元
