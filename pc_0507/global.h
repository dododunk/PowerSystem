
#include "stdafx.h"

#include "PCI8664.h"

//#include "protocol.h"



/////////PC io send function parameter////////////////////////
#define    _ZERO   0 

#define    _OK     1

#define   _TIMEOUT   -1



//#define         _100K_CLK       0.00001 

#define         _100K_CLK       0.001 
/////////////////////////////////////////////////////  

#define         _TRIG_ANGEL_RW_RECV_LEN          16

#define         _TRIG_ANGEL_RW_RECV_START        0x68





extern    CStatic  *  g_plab_zero_times ;

extern    CStatic  *  g_plab_trig_times ;

extern    CStatic  *  g_plab_read_data ;


extern    DWORD   dwThreadID1 ;

extern    void  Fun_Read_And_Show_Data( unsigned char data ) ;




extern          int  Fun_Trig_Angle_RW( ) ;

