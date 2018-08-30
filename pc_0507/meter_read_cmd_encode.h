
#define     _ZERO_PASS_FIRSTLY    2



extern   unsigned  char   g_uc_trig_angle_a ;  //全局，a相触发角度

extern   unsigned  char   g_uc_trig_angle_b ;  //全局，b相触发角度

extern   unsigned  char   g_uc_trig_angle_c ;  //全局，a相触发角度

extern   unsigned  char   g_uc_trig_angle_instent ;   //全局，当前需要发送的触发角度

extern   int   Fun_AD_Sample_Channel_Set_Single_Read( stru_Meter_Read * cmd ) ;


/////////////////////////////////////////////////////////////////////////////////
extern int Meter_Read_Single( stru_Meter_Read * cmd ) ;

extern int Meter_Read_Sync( stru_Meter_Read * cmd_a ,
						   stru_Meter_Read * cmd_b ,
						   stru_Meter_Read * cmd_c   ) ;

extern int Meter_Read_Sequence( stru_Meter_Read * cmd_a ,
							   stru_Meter_Read * cmd_b ,
							   stru_Meter_Read * cmd_c   ) ;
////////////////////////////////////////////////

extern int   Fun_Meter_Read_Single_Decode( ) ;
