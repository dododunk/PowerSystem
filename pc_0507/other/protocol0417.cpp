#include "protocol.h"



stru_PC2MCU_Protocol  g_stru_pc2mcu_protocol ;

unsigned char         g_uc_cmd_buf[ 16 ] ;

unsigned char         g_uc_cmd_buf2[ 16 ] ;

unsigned char         g_uc_cmd_buf3[ 16 ] ;

bool  g_b_pc2mcu_protocol_set = false ;

bool  g_b_wplc_protocol_set   = false ;

bool  g_b_angle_stru_set = false ;
//***************************************************************************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: g_uc_cmd_buf
//***************************************************************************************************

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


//***************************************************************************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: g_uc_cmd_buf
//***************************************************************************************************

int  Set_CMD_User( stru_PC2MCU_Protocol *user_cmd )
{
	g_b_pc2mcu_protocol_set = true ;
	
	return _OK ;
	
}


//************************************
// Method:    Set_CMD_WPLC
// FullName:  Set_CMD_WPLC
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_WPLC_Protocol_Data * wplc_cmd
//************************************
int  Set_CMD_WPLC( stru_WPLC_Protocol_Data * wplc_cmd )
{	
	g_b_wplc_protocol_set = true ;
	
	return _OK ;
	
}

//************************************
// Method:    Send_CMD_Trig
// FullName:  Send_CMD_Trig
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_PC2MCU_Protocol * mcu_cmd
// Parameter: stru_WPLC_Protocol_Data * wplc_cmd
//************************************
int Send_CMD_Trig( stru_PC2MCU_Protocol * mcu_cmd ,stru_WPLC_Protocol_Data * wplc_cmd )
{
	if( g_b_wplc_protocol_set== true 
		&& g_b_pc2mcu_protocol_set== true )
	{
		g_b_pc2mcu_protocol_set = false ;
		
		g_b_wplc_protocol_set = false ;
		
		return _OK ;
	}
	else
	{
		return _PROTOCOL_NOT_SET ;
	}
}

void  Set_CMD_Angle( void * p )
{  
  g_b_angle_stru_set = true ;
}

//***************************************************************************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: g_uc_cmd_buf
//***************************************************************************************************
unsigned char Fun_CRC_SUM( unsigned char *buf , int len )
{
  unsigned char temp = 0 ;

  for( int i = 0 ; i < ( len - 2 ) ; i ++ )
  {
     temp += * ( buf + i ) ;
  }

  return temp ;
}
//***************************************************************************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: g_uc_cmd_buf
//***************************************************************************************************
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
//***************************************************************************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: g_uc_cmd_buf
//*************************************************************************************************** 
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

//***************************************************************************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: g_uc_cmd_buf
//*************************************************************************************************** 

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
//***************************************************************************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: g_uc_cmd_buf
//*************************************************************************************************** 

int Read_Trig_Angle( stru_Read_Angle * cmd  ) 
{
	int  error_flag = 0 ;

    g_stru_pc2mcu_protocol.uc_mcu_cmd = cmd->uc_mcu_cmd ;

    g_stru_pc2mcu_protocol.uc_section = cmd->uc_section ;

	Fun_Set_RW_CMD_Buf( _READ_TRIG_ANGLE ) ; 

	error_flag = Fun_Trig_Angle_RW( ) ;
	
    return  error_flag ;
}

//***************************************************************************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: g_uc_cmd_buf
//*************************************************************************************************** 

int Send_CMD_RW( stru_PC2MCU_Protocol * mcu_cmd  )
{
	if( g_b_pc2mcu_protocol_set== true )
	{
		g_b_pc2mcu_protocol_set = false ;
		
		return _OK ;
	}
	else
	{
		return  _PROTOCOL_NOT_SET ;
		
	}
	if( ( mcu_cmd->uc_mcu_cmd & 0x20 ) == 0x20 )//the command is trig 
	{
		return _CMD_ERROR ;
	}
	
}


int  Fun_Set_Read_CMD_Buf( int flag ) 
{
	unsigned char  phase ;

	CMD_Buf_Init( ) ;

	g_uc_cmd_buf[ _DTU_ADDR_BYTE ] =  g_stru_pc2mcu_protocol.uc_section ;//段地址，生成室外机地址

	if( flag == _METER_READ_SINGLE )
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
   else if( flag == _METER_READ_SYNC )
	{
      g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SYNC ;
	}
	else if( flag == _METER_READ_SEQU )
	{
	  g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SEQU ;
	}

	g_stru_pc2mcu_protocol.stru_wplc_protocol = Fun_WPLC_Data_Set( g_stru_pc2mcu_protocol.stru_wplc_protocol ) ;
	
	g_uc_cmd_buf[ _DATA_BYTE1 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 0 ] ;
	
	g_uc_cmd_buf[ _DATA_BYTE2 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 1 ] ;

	g_uc_cmd_buf[ _DATA_BYTE3 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 2 ] ;

	g_uc_cmd_buf[ _DATA_BYTE4 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 3 ] ;

	g_uc_cmd_buf[ _DATA_BYTE5 ] = g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_data[ 4 ] ;

	g_uc_cmd_buf[ _CRC_BYTE ] = Fun_CRC_SUM( g_uc_cmd_buf ,16 ) ;

	return _OK ;

} 

//***************************************************************************************************
// Method:    Fun_CRC_SUM
// FullName:  Fun_CRC_SUM
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: g_uc_cmd_buf
//*************************************************************************************************** 
int Meter_Read_Single( stru_Meter_Read * cmd ) 
{
	g_stru_pc2mcu_protocol.uc_section = cmd->uc_section ;  //段地址，生成室外机地址

	g_stru_pc2mcu_protocol.uc_line_number = cmd->uc_line_number ;//线

	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_phase_number = cmd->uc_phase_number ;//相

	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_station_number = cmd->uc_station_number ;//站号

	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_sub_meter_addr = cmd->uc_sub_meter_addr ;//模块地址

	g_stru_pc2mcu_protocol.stru_wplc_protocol.uc_user_cmd = cmd->uc_user_cmd ;//具体用户指令

	g_stru_pc2mcu_protocol.stru_wplc_protocol.un_module_addr = cmd->un_module_addr ;//模块子地址

	Fun_Set_Read_CMD_Buf( _METER_READ_SINGLE ) ;

	return _OK ;
}

int Meter_Read_Sync( stru_Meter_Read * cmd_a ,
					 stru_Meter_Read * cmd_b ,
					 stru_Meter_Read * cmd_c   ) 
{
  int i = 0 ;
  //phase b protocol buffer set
  Meter_Read_Single( cmd_b ) ;

  for( i = 0 ; i < 16 ; i ++ )
  {
   g_uc_cmd_buf2[ i ] = g_uc_cmd_buf [ i ] ;
  }
  
  g_uc_cmd_buf2[ _CMD_BYTE ] = _TRIG_SYNC ;
  
  g_uc_cmd_buf2[ _FRAME_NUMBER_BYTE ] = _PHASE_B ;

  //phase c protocol buffer set
  Meter_Read_Single( cmd_c ) ;

  for( i = 0 ; i < 16 ; i ++ )
  {
	  g_uc_cmd_buf3[ i ] = g_uc_cmd_buf [ i ] ;
  }  
  g_uc_cmd_buf3[ _CMD_BYTE ] = _TRIG_SYNC ;
  
  g_uc_cmd_buf3[ _FRAME_NUMBER_BYTE ] = _PHASE_C ;

  //phase a protocol buffer set
  Meter_Read_Single( cmd_a ) ;
  
  g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SYNC ;
  
  g_uc_cmd_buf[ _FRAME_NUMBER_BYTE ] = _PHASE_A ;

  return _OK ;
}

int Meter_Read_Sequence( stru_Meter_Read * cmd_a ,
							   stru_Meter_Read * cmd_b ,
							   stru_Meter_Read * cmd_c   ) 
{
     int i  = 0 ;
    //phase b protocol buffer set
	Meter_Read_Single( cmd_b ) ;

	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf2[ i ] = g_uc_cmd_buf [ i ] ;
	}	

	g_uc_cmd_buf2[ _CMD_BYTE ] = _TRIG_SEQU ;
	
	g_uc_cmd_buf2[ _FRAME_NUMBER_BYTE ] = _PHASE_B ;
	
    //phase c protocol buffer set
	Meter_Read_Single( cmd_c ) ;
	for( i = 0 ; i < 16 ; i ++ )
	{
		g_uc_cmd_buf3[ i ] = g_uc_cmd_buf [ i ] ;
	}	
	g_uc_cmd_buf3[ _CMD_BYTE ] = _TRIG_SEQU ;
	
    g_uc_cmd_buf3[ _FRAME_NUMBER_BYTE ] = _PHASE_C ;

    //phase a protocol buffer set
	Meter_Read_Single( cmd_a ) ;
	
	g_uc_cmd_buf[ _CMD_BYTE ] = _TRIG_SEQU ;
	
	g_uc_cmd_buf[ _FRAME_NUMBER_BYTE ] = _PHASE_A ;

	return _OK ;
}
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

//************************************
// Method:    Fun_WPLC_Data_Set
// FullName:  Fun_WPLC_Data_Set
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: stru_WPLC_Protocol_Data stru
//************************************
stru_WPLC_Protocol_Data    Fun_WPLC_Data_Set( stru_WPLC_Protocol_Data  stru )
{
 unsigned char buf1 = 0 , buf2 = 0 ;

 unsigned long ltemp = 0 ;

 if( stru.un_module_addr.ldata > 0x1FFFF )
 {
   return stru ; // ; _MODULE_ADDR_ERROR ;
 }
 else
 {
//	if( stru.uc_user_cmd & 0xFE == _CMD_CONGEAL
//		|| stru.uc_user_cmd & 0xFE == _CMD_CONGEAL_HOUR ) //congeal command

   if( stru.uc_user_cmd == 0xF2 )
	{		
	   stru.uc_data[ 0 ] = stru.uc_user_cmd & 0xFE ;//set the lowest bit of D0 to zero //get uc_data0
		
	   stru.uc_data[ 1 ] = 0x00 ;
		
	   stru.uc_data[ 2 ] = 0x00;   
	   
       stru.uc_data[ 3 ] = 0x00 ;
	   //ucdata[ 0 ] lower 8 bit of the un_congeal_time  
	   buf1 = ( stru.un_congeal_time.ucdata[ 1 ] & 0x30 ) >> 4 ; //get  higher 2 bit of the time

	   stru.uc_data[ 3 ] = stru.uc_data[ 3 ] | buf1 ; //set the d1,d0 to uc_data3 ,the lowest bit

	   buf1 = stru.un_congeal_time.ucdata[ 1 ] & 0x0F ; //get  lower 4 bit of the time

	   stru.uc_data[ 3 ] = stru.uc_data[ 3 ] | ( buf1 << 4 ) ;//set the bit d4-d7 of the uc_data3 

       stru.uc_data[ 3 ] = stru.uc_data[ 3 ] | ( ( stru.uc_phase_number & 0x03 )<< 2 ) ; //set bit2 - bit3 of uc_data3

	   stru.uc_data[ 4 ] = stru.un_congeal_time.ucdata[ 0 ] ;

	   return stru ;
	}
 	else
	{   //long 0x01 0X 03 04  >> ucdata0 : 0    1    2  3 
	//	                                  04 , 03 , 0X ,01
		buf1 = stru.un_module_addr.ucdata[ 2 ] & 0x01 ; //get the bit 17
		
	//	buf1 = ( unsigned char ) ( ltemp << 16 ) ; //get the bit 17
		
		buf2 = stru.uc_user_cmd &0xF7 ;//set the lowest bit of D0 to zero
		
		stru.uc_data[ 0 ] = buf2 | buf1 ; //get uc_data0
		
		stru.uc_data[ 1 ] = stru.un_module_addr.ucdata[ 1 ] ;
		
	    stru.uc_data[ 2 ] = stru.un_module_addr.ucdata[ 0 ] ;	
		
		stru.uc_data[ 3 ] = ( ( stru.uc_sub_meter_addr & 0x0F ) << 4 )
			              | ( ( stru.uc_phase_number & 0x03 )<< 2 )
		                  | ( stru.uc_station_number & 0x03 ) ;

	   stru.uc_data[ 4 ] = 0x67 ;

	   return stru ;
	}

 } 
}
