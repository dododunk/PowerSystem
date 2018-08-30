


#define    _FIFO_WRITE_ENABLE   1

#define    _FIFO_READ_ENABLE    2 

#define    _FIFO_RW_ENABLE     3

#define    _FIFO_FLAG_NULL     0xFF 


///////////////////
#define    _FIFO_OVERFLOW    -1

#define    _FIFO_EMPTY       -2 



//////////////////////
#define  _FIFO_LEN_FRAME         10 


#define  _FIFO_LEN_LINE          20 


#define  _FIFO_STRUCT_LEN_BYTE    ( _AD_SAMPLE_DATA_NUMBER_PER_ZERO * 8 + 3 )  //一个fifo单元的长度，以字节为单位




/////////fifo中数据结构定义
typedef   struct
{
	stru_AD_Sample_Data_One_Bit   stru_data_one_bit ;  //320 * 8 
	
	unsigned  char               uc_line_index ;

	unsigned  char               uc_phase_index ; //_PHASE_A , _PHASE_B , _PHASE_C 
	
	unsigned  char               uc_bit_index ;

	unsigned char                uc_frame_index ;
	
	unsigned  char               uc_rw_flag ;
	
}  stru_Pro_Decode_Data_One_Bit ;   //



extern     unsigned int  g_fifo_read_index  ;   //fifo 

extern     unsigned int  g_fifo_write_index ;


extern     unsigned char g_uc_fifo_rw_falg ;  
//   _FIFO_WRITE_ENABLE   1

//   _FIFO_READ_ENABLE    2 

//   _FIFO_RW_DISABLE     3

extern     unsigned  int   g_i_fifo_len_frame   ; //fifo的长度，即fifo中要存储多少帧的数据

extern     unsigned  int   g_i_fifo_len_line   ;//fifo的长度，即fifo中要存储多少条出线的数据


extern     stru_Pro_Decode_Data_One_Bit   *  g_p_stru_fifo ;

extern     unsigned int     g_fifo_len_struct ; //fifo的深度，以待解码的每一位数据结构为单位



extern     void   Fun_Fifo_Len_Init( unsigned int line_len , unsigned  int frame_len ) ;

extern     void   Fun_Fifo_Delete( ) ;

extern     int    Fun_Fifo_Pop_Up(  stru_Pro_Decode_Data_One_Bit  * p_data  , unsigned int len ) ;

extern     int    Fun_Fifo_Push_Down(  stru_Pro_Decode_Data_One_Bit  * p_data  , unsigned int len ) ;