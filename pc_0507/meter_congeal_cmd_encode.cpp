
#include   "protocol.h"

#include   "meter_congeal_cmd_encode.h"

#include   "angle_rw_cmd_encode.h"


////////////////////////////////////////////////
int  Fun_Set_Congeal_CMD_Buf( int flag ) 
{
	unsigned char  phase ;
	
	g_uc_cmd_buf[ _DTU_ADDR_BYTE ] =  g_stru_pc2mcu_protocol.uc_section ;//段地址，生成室外机地址
	
	if( flag == _CONGEAL_SINGLE )
	{
		phase = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_phase_number ;
		
		if( phase == _PHASE_A )
		{
			g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_A ;
		}
		else if( phase == _PHASE_B )
		{
			g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_B ;
		}
		else if( phase == _PHASE_C )
		{
			g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_C ;
		}	
		else
			return _CMD_ERROR ;
	}
	else if( flag == _CONGEAL_SYNC )
	{
		g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SYNC ;
	}
	else if( flag == _CONGEAL_SEQU )
	{
		g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SEQU ;
	}
	//set wplc protocol data
	g_stru_pc2mcu_protocol.stru_wplc_protocol = Fun_WPLC_Data_Set( g_stru_pc2mcu_protocol.stru_wplc_protocol ) ;
	//set wplc protocol  commad=nd
	g_uc_cmd_buf[ _DATA_BYTE1 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 0 ] ;
    //module addr set to aero	
	g_uc_cmd_buf[ _DATA_BYTE2 ] = 0x00 ;
	
	g_uc_cmd_buf[ _DATA_BYTE3 ] = 0x00 ;
	//set congeal time
	g_uc_cmd_buf[ _DATA_BYTE4 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 3 ] ;
	
	g_uc_cmd_buf[ _DATA_BYTE5 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 4 ] ;

    g_uc_cmd_buf[ _CRC_BYTE ] = Fun_CRC_SUM( g_uc_cmd_buf ,16 ) ;

	return _OK ;
}


int Meter_Congeal_Single( stru_Meter_Congeal * cmd ) 
{ //pc2mcu protocol need to set : phase number , mcu command ,congeal tiem 
	unsigned char  phase ;
	//set ohase number
	phase = g_stru_pc2mcu_protocol.uc_mcu_phase_number = cmd->uc_phase_number ;

	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_phase_number = cmd->uc_phase_number ;
    //set user cmmand and mcu command 
	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_user_cmd = _CMD_CONGEAL_HOUR ;

	if( phase == _PHASE_A )
	{
      g_stru_pc2mcu_protocol.uc_mcu_cmd = _TRIG_A ;
	}
	else if( phase == _PHASE_B )
	{
		g_stru_pc2mcu_protocol.uc_mcu_cmd = _TRIG_B ;
	}
	else if( phase == _PHASE_C )
	{
		g_stru_pc2mcu_protocol.uc_mcu_cmd = _TRIG_C ;
	}	   
	//set congeal time
	g_stru_pc2mcu_protocol.stru_wplc_protocol.un_congeal_time.idata = cmd->un_congeal_time.idata ;

    //set pc2mcu protocol 
    Fun_Set_Congeal_CMD_Buf( _CONGEAL_SINGLE ) ;

	return _OK ;
	
}





int Meter_Congeal_Sync( stru_Meter_Congeal * cmd_a ,
							 stru_Meter_Congeal * cmd_b ,
							 stru_Meter_Congeal * cmd_c   ) 
{
	int i = 0 ;

    //phase b protocol buffer set
	Meter_Congeal_Single( cmd_b ) ;
	
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf2[ i ] = g_uc_cmd_buf [ i ] ;
	}	
	
	g_uc_cmd_buf2[ _CMD_BYTE ] = _TRIG_SYNC ;
	
	g_uc_cmd_buf2[ _FRAME_NUMBER_BYTE ] = _PHASE_B ;
	
    //phase c protocol buffer set
	Meter_Congeal_Single( cmd_c ) ;
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf3[ i ] = g_uc_cmd_buf [ i ] ;
	}	
	g_uc_cmd_buf3[ _CMD_BYTE ] = _TRIG_SYNC ;
	
    g_uc_cmd_buf3[ _FRAME_NUMBER_BYTE ] = _PHASE_C ;
	
    //phase a protocol buffer set
	Meter_Congeal_Single( cmd_a ) ;
	
	g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SYNC ;
	
	g_uc_cmd_buf[ _FRAME_NUMBER_BYTE ] = _PHASE_A ;

	return _OK ;
}

int Meter_Congeal_Sequence( stru_Meter_Congeal * cmd_a ,
								 stru_Meter_Congeal * cmd_b ,
							      stru_Meter_Congeal * cmd_c   ) 
{
	int i = 0 ;
    //phase b protocol buffer set
	Meter_Congeal_Single( cmd_b ) ;
	
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf2[ i ] = g_uc_cmd_buf [ i ] ;
	}	
	
	g_uc_cmd_buf2[ _CMD_BYTE ] = _TRIG_SEQU ;
	
	g_uc_cmd_buf2[ _FRAME_NUMBER_BYTE ] = _PHASE_B ;
	
    //phase c protocol buffer set
	Meter_Congeal_Single( cmd_c ) ;
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf3[ i ] = g_uc_cmd_buf [ i ] ;
	}	
	g_uc_cmd_buf3[ _CMD_BYTE ] = _TRIG_SEQU ;
	
    g_uc_cmd_buf3[ _FRAME_NUMBER_BYTE ] = _PHASE_C ;
	
    //phase a protocol buffer set
	Meter_Congeal_Single( cmd_a ) ;
	
	g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SEQU ;
	
	g_uc_cmd_buf[ _FRAME_NUMBER_BYTE ] = _PHASE_A ;

	return _OK ;
}
