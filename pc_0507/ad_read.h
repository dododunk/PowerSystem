

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

//////////////////////////////////////////////////////////////////
//-------------------------add 04 30-----------------------------
#define   _DATA_INFO_A_ECTION1    0x11 

#define   _DATA_INFO_A_ECTION2    0x21 

#define   _DATA_INFO_A_ECTION3    0x31 

#define   _DATA_INFO_END          0x55 


#define   _TICK_VALID_TIMES       5

#define   _TICK_VALID_HANDSHAKE    0xAA 

#define   _NO_DATA_ONFO           0x00


extern     bool     g_bflag_data_info_end   ;

extern     HANDLE   hEvent_AD_Data_Info_End ;

typedef    struct  
{
	SHORT   data_line[ _AD_SAMPLE_CHANNEL_MAX ] ;
	
	LONGLONG  time_stamp ;
	
} stru_AD_Data_Per_Tick ;  



typedef   struct  
{
	unsigned char     data_info ;
	
	LONGLONG          time_stamp ;
	
} stru_AD_Data_Info_Per_Tick ;



extern    HANDLE        hThread_AD_Read  ; 

extern    HANDLE        hEvent_Read_AD_Data  ;

extern    HANDLE        hEvent_AD_Read_Data_Error ;


extern    SHORT   g_s_ad_fifo_buffer[ _AD_DATA_FIFO_LEN ]; // Receive AD data buffer


extern   int  Fun_AD_Trig_Soft( ) ;

extern   int   Fun_AD_Read_Data_One_Bit( stru_Pro_Decode_Data_One_Bit    stru_pro_decode_data , 
	           int  active_line_number , int  line_index  , int trig_index  , 
			           int bit_index  , unsigned char phase_index ) ;


extern   int  Fun_Data_Info_Get_Per_Tick( ) ;

extern   int  Fun_AD_Read_Per_Tick( ) ;


extern   void Fun_Thread_AD_Read_Data_Info_Init( ) ;

extern   void Fun_Thread_AD_Read_Data_Init( ) ;

extern   HANDLE   hEvent_Thread_AD_Read_Data_Run  ;

extern   HANDLE   hEvent_Thread_AD_Read_Data_Info_Run  ;

extern   HANDLE   hThread_AD_Read_Data_Info ;

extern   HANDLE   hThread_AD_Read_Data ;



extern   HANDLE    hThread_Read_AD_Test ;

