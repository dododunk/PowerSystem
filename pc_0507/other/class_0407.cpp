
/*出线图初始化
定义一个Input_Channel_Map结构体
定义对应个数的Input_Channel结构体数组
将Input_Channel_Map结构体内的指针*p_input_channle与Input_Channel结构体数组地址关联
调用Fun_Channel_Map_Init( Input_Channel_Map * p )，初始化出线map。
*/
#include "class0407.h"

Input_Channel_Map   *   g_p_stru_channel_map ;//全局，出线布局结构体指针

unsigned char           g_uc_line_number ;//全局，出线总书目

unsigned char           g_uc_channel_number ;//全局，出线总书目


Input_Channel       *   g_p_stru_input_channel ;//全局，出线结构体指针

bool                    g_uc_channel_map_init = false ; //全局，出线布局是否被初始化
//////////////////////////
HANDLE                  h_AD_Card_Device ;

unsigned char           g_uc_card_number = 0 ; //全局 ，系统中ad 采集卡个数

HANDLE              *   g_p_hcard_device ; 、、各个AD卡对象的句柄，new出来的

//==================================================================================================

void Struct_Copy(
     void *  p_struct1,    /*结构指针1*/
     void *  p_struct2,    /*结构指针2*, to be copy*/
     unsigned int struct_size    /*结构类型长度，可以用sizeof(STRUCT_TYPE)代入*/
     )
{
 int count = 0 ;

 char * p_char1 , * p_char2 ;
 
 p_char1 = ( char * ) p_struct1 ;

 p_char2 = ( char * ) p_struct2 ;
 
 while( count != struct_size )
 {
   * p_char1 = * p_char2 ;

   p_char1 ++ ;

   p_char2 ++ ;

   count ++ ;
 }
}

//==================================================================================================

void  Fun_Card_Number_Init( int  num )
{
	g_uc_card_number = num ;

	g_p_hcard_device = new HANDLE[ g_uc_card_number ] ;
}

void  Fun_Line_Number_Init( int  num )
{
	g_uc_line_number = num ;

	g_uc_channel_number = num * 2 ;
	
   //	g_p_hcard_device = new HANDLE[ g_uc_card_number ] ;
}


void  Fun_Channel_Map_Init( Input_Channel_Map * p  )
{
  int  number ;

  Iput_Channel   * p_line ;

  number = g_uc_line_number = ( p -> ucinput_channle_number ) ;  //get the number of channel used

  g_p_stru_channel_map = p ;

  g_p_stru_input_channel = p->p_input_channle ;

  number = sizeof( Input_Channel ) ;

  g_p_stru_input_channel = new  Input_Channel[ number ]  ;

  for( int i = 0 ; i < g_uc_line_number ; i ++ )
  {
    Struct_Copy( g_p_stru_input_channel + i ; p->p_input_channle + i , number ) ; //copy the inoput_line struct into the structtion of my own
  }

}

void  Fun_Uninstall_Device( )
{
	delete [ ] g_p_stru_input_channel ;

	delete [ ] g_p_hcard_device ;
}

//==================================================================================================
//card_number：begin with 0 ,
int    Fun_AD_Init( int card_number , PPCI8664_PARA_AD * p )
{
  if( card_number > g_uc_card_number )
  {
	  return _CMD_ERROR
  }
  else
  {
    g_p_hcard_device[ card_number ] = CreateDevice ( card_number ) ; //create device

    InitDeviceProAD( g_p_hcard_device[ card_number ] , p ) ;  //init the device
  }

}
/*
void    Fun_AD_Init( int card_number )
{
  h_AD_Card_Device = CreateDevice ( card_number ) ; //create device

  PPCI8664_PARA_AD  ad_card ;

  ad_card.ADMode = 0x00 ;

  InitDeviceProAD( h_AD_Card_Device, p ) ;  //init the device

}
*/

void    Fun_Buf_Len_Init( int channel_data_deep , int ad_data_deep ) ;
{
  unsigned  long     //16 line ,  a ,b,c three phase , every frame 32 bit = 1 ulong , 16 * 3 unsigned long 

  unsigned int i_AD_data_buf_len ; //the length of ad read dates buffer ,12 bit per ad data

  unsigned int i_valid_bit_len ; //the length of valid data bit per frame , 32 bit per frame

  unsigned int i_decoded_data_buf_len ; //the length of decoded data buffer length , 32 bit per frame
/*  
  Long_Byte *  g_p_line_data = new 
	           Long_Byte[ g_uc_card_number ] [ line_data_deep ] [ g_uc_line_number ] [ 3 ] ;

  Long_Byte *  g_p_line_data_flag = new
	           Long_Byte[ g_uc_card_number ] [ line_data_deep ] [ g_uc_line_number ] [ 3 ] ;
*/
  Long_Byte *  g_p_channel_data = new 
	           Long_Byte[ g_uc_card_number ] [ channel_data_deep ] [ g_uc_channel_number ] ;

  Bit_16    *  g_p_channel_data_flag = new 
	           Bit_16   [ g_uc_card_number ] [ channel_data_deep ] ;
}










  

