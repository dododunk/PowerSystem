
#include "stdafx.h"

extern    HANDLE   hEvent_Operation_Timer_Timeout ; 

extern    bool     g_bflag_operation_timer_set  ;

extern    int      g_operation_timer_id ;

#define         _MILLSECOND_20            20   //ms

#define         _MILLSECOND_2000          2000  //ms 

#define         _MILLSECOND_1             1  //ms 


#define         _EVENT_AD_READ_TIMER               1 

extern   unsigned int           g_uc_trig_timer_raising_usecond  ; 

extern   unsigned int           g_uc_trig_timer_failing_usecond  ;


extern   HANDLE          hThread_Trig_Timer_Raising ; 

extern   HANDLE          hThread_Trig_Timer_Falling ;

extern   HANDLE        hEvent_Thread_Trig_Timer_Raising_Enable ;

extern   HANDLE        hEvent_Thread_Trig_Timer_Falling_Enable ;


extern   double        g_db_system_freguence ;

////////////////////////////////////////////////////////
extern    void   TimeProc_Operation_Init() ;


extern    void   CALLBACK TimeProc_Operation_Timer(UINT uID,UINT uMsg,
									   DWORD dwUser,DWORD dw1,DWORD dw2 ) ;


extern    void   Fun_Operation_Timer_Set( UINT  ui_msecond ) ;//run once


extern    void   Fun_Operation_Timer_Stop(  ) ;

extern    int    Fun_Precious_Timer_Set( UINT  ui_usecond ) ;

extern    int    Fun_Trig_Timer_Set( UINT  ui_degree ) ;


extern    void  Fun_Thread_Trig_Timer_Raising_Init( ) ;

extern    void  Fun_Thread_Trig_Timer_Falling_Init( ) ;

extern    void  Fun_Get_Sys_Frequence( ) ;


extern    void  Fun_Delay_Usecond( unsigned int ui_msecond ) ;

extern    void Fun_Set_Trig_Timer( int  angle  , unsigned char   edge_flag ) ;