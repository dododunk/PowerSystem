

typedef unsigned long (CALLBACK *pfun_callback)(LPVOID pvUserParam) ;



#define       _AD_SAMPLE_CHANNEL_MAX             ( 10 * 2 )//采集卡最大的采集通道数

#define       _AD_SAMPLE_DATA_NUMBER_PER_ZERO    320  //每个过零点采集的数据点个数


#define       _AD_DATA_FIFO_LEN                     1024*8 

#define       _AD_READ_DATA_LEN_PER_TRIG       ( 320 * 10 ) 


#define      _TRIG_POINT_0     0 

#define      _TRIG_POINT_1     1 

#define      _TRIG_POINT_2     2 

#define      _TRIG_POINT_3     3 

#define      _TRIG_POINT_4     4 

#define      _TRIG_POINT_5     5

#define      _TRIG_POINT_6     6 

#define      _TRIG_POINT_7     7 

extern    HANDLE        hThread_AD_Read  ; 

extern    HANDLE        hEvent_Read_AD_Data  ;

extern    HANDLE        hEvent_AD_Read_Data_Error ;


extern    SHORT   g_s_ad_fifo_buffer[ _AD_DATA_FIFO_LEN ]; // Receive AD data buffer
