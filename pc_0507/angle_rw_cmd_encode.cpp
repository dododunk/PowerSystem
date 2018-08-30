
#include  "protocol.h"

#include  "angle_rw_cmd_encode.h"
 
#include  "global.h"
/*
stru_PC2MCU_Protocol  g_stru_pc2mcu_protocol ;

unsigned char         g_uc_cmd_buf[ 16 ] ;

unsigned char         g_uc_cmd_buf2[ 16 ] ;

unsigned char         g_uc_cmd_buf3[ 16 ] ;
*/

stru_Set_Angle_Single   g_stru_set_angle_single ;

stru_Set_Angle_All      g_stru_set_angle_all ;

stru_Read_Angle         g_stru_read_angle ;

//************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   unsigned char
// Qualifier:
// Parameter: unsigned char * buf
// Parameter: int len
//************************************
unsigned char Fun_CRC_SUM( unsigned char *buf , int len )
{
	unsigned char temp = 0 ;
	
	for( int i = 0 ; i < ( len - 2 ) ; i ++ )
	{
		temp += * ( buf + i ) ;
	}
	
	return temp ;
}
//************************************
// Method:    CMD_Buf_Init
// FullName:  CMD_Buf_Init
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void  CMD_Buf_Init( )
{
	g_uc_cmd_buf[ _START_BYTE ] = 	  
		g_uc_cmd_buf2[ _START_BYTE ] = g_uc_cmd_buf3[ _START_BYTE ]  = 0x68 ;
	
	g_uc_cmd_buf[ _END_BYTE ] = 
		g_uc_cmd_buf2[ _START_BYTE ] = g_uc_cmd_buf3[ _START_BYTE ] = 0x16 ;
	
	g_uc_cmd_buf[ _DATA_BYTE1 ] = 
		g_uc_cmd_buf2[ _DATA_BYTE1 ] = g_uc_cmd_buf3[ _DATA_BYTE1 ] = 0xFF ;
	
	g_uc_cmd_buf[ _DATA_BYTE2 ] =
		g_uc_cmd_buf2[ _DATA_BYTE2 ] = g_uc_cmd_buf3[ _DATA_BYTE2 ] = 0xFF ;
	
	g_uc_cmd_buf[ _DATA_BYTE3 ] =
		g_uc_cmd_buf2[ _DATA_BYTE3 ] = g_uc_cmd_buf3[ _DATA_BYTE3 ] = 0xFF ;
	
	g_uc_cmd_buf[ _DATA_BYTE4 ] = 
		g_uc_cmd_buf2[ _DATA_BYTE4 ] = g_uc_cmd_buf3[ _DATA_BYTE4 ] = 0xFF ;
	
	g_uc_cmd_buf[ _DATA_BYTE5 ] = 
		g_uc_cmd_buf2[ _DATA_BYTE5 ] = g_uc_cmd_buf3[ _DATA_BYTE5 ] = 0xFF ;
	
	g_uc_cmd_buf[ _DATA_BYTE6 ] = 
		g_uc_cmd_buf2[ _DATA_BYTE6 ] = g_uc_cmd_buf3[ _DATA_BYTE6 ] = 0xFF ;
	
	g_uc_cmd_buf[ _DATA_BYTE7 ] = 
		g_uc_cmd_buf2[ _DATA_BYTE7 ] = g_uc_cmd_buf3[ _DATA_BYTE7 ] = 0xFF ;
	
	g_uc_cmd_buf[ _DATA_BYTE8 ] = 
		g_uc_cmd_buf2[ _DATA_BYTE8 ] = g_uc_cmd_buf3[ _DATA_BYTE8 ] = 0x00 ;
	
	g_uc_cmd_buf[ _DATA_BYTE9 ] = 
		g_uc_cmd_buf2[ _DATA_BYTE9 ] = g_uc_cmd_buf3[ _DATA_BYTE9 ] = 0x00 ;
}


//************************************
// Method:    Fun_Set_RW_CMD_Buf
// FullName:  Fun_Set_RW_CMD_Buf
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int phase
//************************************
void  Fun_Set_RW_CMD_Buf( int phase ) 
{
	CMD_Buf_Init( ) ;
	
	g_uc_cmd_buf[ _DTU_ADDR_BYTE ] = g_stru_pc2mcu_protocol.uc_section  ;
	
	g_uc_cmd_buf[ _CMD_BYTE ] = g_stru_pc2mcu_protocol.uc_mcu_cmd ;
	
	if( phase == _PHASE_A )
	{
		g_uc_cmd_buf[ _ANGLE_DATA_BYTE] = g_stru_pc2mcu_protocol.uc_trig_angle_a ;
		
	}
	else if( phase == _PHASE_B )
	{
		g_uc_cmd_buf[ _ANGLE_DATA_BYTE ] = g_stru_pc2mcu_protocol.uc_trig_angle_b ;
	}  
	
	else if( phase == _PHASE_C )
	{
		g_uc_cmd_buf[ _ANGLE_DATA_BYTE ] = g_stru_pc2mcu_protocol.uc_trig_angle_c ;
	}
	
	else if( phase == _PHASE_ALL )
	{
		g_uc_cmd_buf[ _ANGLE_DATA_BYTE ] = g_stru_pc2mcu_protocol.uc_trig_angle_a ;
		
		g_uc_cmd_buf[ _FRAME_NUMBER_BYTE ] = g_stru_pc2mcu_protocol.uc_trig_angle_b ;
		
		g_uc_cmd_buf[ _DATA_BYTE1 ] = g_stru_pc2mcu_protocol.uc_trig_angle_c ;
	}
	
	g_uc_cmd_buf[ _CRC_BYTE ] = Fun_CRC_SUM( g_uc_cmd_buf , 16 ) ;
	
}

//************************************
// Method:    Set_Angle_Single
// FullName:  Set_Angle_Single
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_Set_Angle_Single * cmd
//************************************
int Set_Angle_Single( stru_Set_Angle_Single * cmd  ) 
{
	unsigned char phase ;
	
	int error_flag = 0 ;
	
	g_stru_pc2mcu_protocol.uc_section= cmd->uc_section ;
	
	phase = cmd->uc_mcu_phase_number ;
	
	if( phase == _PHASE_A )
	{
		g_stru_pc2mcu_protocol.uc_mcu_cmd = _SET_TRIG_ANGLE_A ;
		
		g_stru_pc2mcu_protocol.uc_trig_angle_a = cmd->uc_trig_angle ;
		
	}
	
	else if( phase == _PHASE_B )
	{
		g_stru_pc2mcu_protocol.uc_mcu_cmd = _SET_TRIG_ANGLE_B ;
		
		g_stru_pc2mcu_protocol.uc_trig_angle_b = cmd->uc_trig_angle ;
		
	}
	else if( phase == _PHASE_C )
	{
		g_stru_pc2mcu_protocol.uc_mcu_cmd = _SET_TRIG_ANGLE_C ;
		
		g_stru_pc2mcu_protocol.uc_trig_angle_c = cmd->uc_trig_angle ;
	}
	
	
	Fun_Set_RW_CMD_Buf( phase ) ;  //read the cmd parameter from structure and write its into cmd buffer
	
	error_flag = Fun_Trig_Angle_RW( ) ;
	
	return error_flag ;
}



//************************************
// Method:    Set_Angle_All
// FullName:  Set_Angle_All
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_Set_Angle_All * cmd
//************************************
int Set_Angle_All( stru_Set_Angle_All * cmd  ) 
{
	int   error_flag = 0 ;
	
	unsigned char phase ;
	
    g_stru_pc2mcu_protocol.uc_section = cmd->uc_section ;
	
	phase = _PHASE_ALL ;
	
    g_stru_pc2mcu_protocol.uc_mcu_cmd = _SET_TRIG_ANGLE_ALL ;
	
    g_stru_pc2mcu_protocol.uc_trig_angle_a = cmd->uc_trig_angle_a ;
	
    g_stru_pc2mcu_protocol.uc_trig_angle_b = cmd->uc_trig_angle_b ;
	
    g_stru_pc2mcu_protocol.uc_trig_angle_c = cmd->uc_trig_angle_c ;	
	
	Fun_Set_RW_CMD_Buf( _PHASE_ALL ) ;  //read the cmd parameter from structure and write its into cmd buffer
	
	error_flag = Fun_Trig_Angle_RW( ) ;
	
    return error_flag ;
}	



//************************************
// Method:    Read_Trig_Angle
// FullName:  Read_Trig_Angle
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_Read_Angle * cmd
//************************************
int Read_Trig_Angle( stru_Read_Angle * cmd  ) 
{
	int  error_flag = 0 ;
	
    g_stru_pc2mcu_protocol.uc_mcu_cmd = cmd->uc_mcu_cmd ;
	
    g_stru_pc2mcu_protocol.uc_section = cmd->uc_section ;
	
	Fun_Set_RW_CMD_Buf( _READ_TRIG_ANGLE ) ; 
	
	error_flag = Fun_Trig_Angle_RW( ) ;
	
    return  error_flag ;
}



