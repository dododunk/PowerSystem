#include   "global.h"

#include    "timer.h"

#include     "protocol.h"

#include     "data_transfer.h"

#include     "fifo.h"

#include     "ad_read.h"

#include     "init.h"




CStatic  *  g_plab_zero_times ;

CStatic  *  g_plab_trig_times ;

CStatic  *  g_plab_read_data ;


unsigned char   g_uc_zero_pass_times_before = 0 ;

DWORD       dwThreadID1 ;



#define     _DEBUG_MESSAGE_ZERO_TIMES_SHOW

//************************************
// Method:    Fun_Trig_Angle_RW
// FullName:  Fun_Trig_Angle_RW
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
///*
int  Fun_Trig_Angle_RW( )
{
	int  error_flag = 0 ;
    //发送指令 
    Fun_PC_Send_Data( g_uc_cmd_buf , 16 ) ;
	
    //读取指令回复，16字节长度
    error_flag = Fun_PC_Recv_Data( _TRIG_ANGEL_RW_RECV_LEN , _TRIG_ANGEL_RW_RECV_START ) ;
	
	if( error_flag = _TIMEOUT )
	{
		return -1 ;
	}
	else
		return 1 ;
	
}
//*/

 unsigned char    g_data_show_before = 0  ;

void  Fun_Read_And_Show_Data( unsigned char data )
{
/*
	unsigned char recv_data = 0 ;
	
	PCI8664_GetDeviceDI( hDevice_AD , g_uc_recv_io_data ) ;
	
	recv_data = Fun_Recv_Data_Set( g_uc_recv_io_data ) ;//20ms内自动返回
	
	recv_data = (unsigned char ) recv_data & 0xFF ;
	
*/	
#ifdef   _DEBUG_MESSAGE_ZERO_TIMES_SHOW
	{
		//if( ( g_data_show_before != data ) &&( data != 0x99 || data != 0x00 ) )
	//	if( ( data != 0x99 && data != 0x00 ) )
     //  if( ( g_uc_zero_pass_times_before == g_uc_zero_pass_times ) )
		{
			CString    str1 ;
			
			str1.Format( "%x" , data ) ;
			
			g_plab_read_data->SetWindowText( str1 ) ;
			
			g_data_show_before  = data ;
			
			g_uc_zero_pass_times_before = g_uc_zero_pass_times ;
		}

	}
#endif
}