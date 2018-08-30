
#include "stdafx.h"

/*
extern       stru_PC2MCU_Protocol  g_stru_pc2mcu_protocol ;

extern       unsigned char         g_uc_cmd_buf[ 16 ] ;

extern       unsigned char         g_uc_cmd_buf2[ 16 ] ;

extern       unsigned char         g_uc_cmd_buf3[ 16 ] ;
*/

extern       stru_Set_Angle_Single   g_stru_set_angle_single ;

extern       stru_Set_Angle_All      g_stru_set_angle_all ;

extern       stru_Read_Angle         g_stru_read_angle ;


extern       unsigned char Fun_CRC_SUM( unsigned char *buf , int len ) ;

extern       void  CMD_Buf_Init( ) ;

extern       void  Fun_Set_RW_CMD_Buf( int phase )  ;

extern       int   Set_Angle_Single( stru_Set_Angle_Single * cmd  ) ;

extern       int   Set_Angle_All( stru_Set_Angle_All * cmd  ) ;

extern       int   Read_Trig_Angle( stru_Read_Angle * cmd  ) ;

////////////////////////////////////////////////////////////////////////////////
