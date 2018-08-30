
#include "stdafx.h"

#include "mmsystem.h" 



void CALLBACK TimeProc_Operation_Timer(UINT uID,UINT uMsg,
								DWORD dwUser,DWORD dw1,DWORD dw2 )
{
  SetEvent( hEvent_Operation_Timer_Timeout ) ;   
}


void Fun_Operation_Timer_Set( UINT  ui_msecond )//run once
{
	if( g_bflag_operation_timer_set == false )
	{
		g_operation_timer_id = timeSetEvent( ui_msecond , 0 , (LPTIMECALLBACK) TimeProc_Operation_Timer ,0 , TIME_ONESHOT ) ; //TIME_PERIODIC ) ;	
		
		g_bflag_operation_timer_set = true ;

		ResetEvent( hEvent_Operation_Timer_Timeout ) ;
	}
	else
	{
		timeKillEvent( g_operation_timer_id ) ;
		
		g_operation_timer_id = timeSetEvent( ui_msecond , 0 , (LPTIMECALLBACK) TimeProc_Operation_Timer ,0 , TIME_ONESHOT ) ;  //TIME_PERIODIC ) ;	
		
	    //g_bflag_operation_timer_set = true ;

		ResetEvent( hEvent_Operation_Timer_Timeout ) ;
		
	 }  
}

void Fun_Operation_Timer_Stop(  )
{
	if( g_bflag_operation_timer_set == true )
	{
		timeKillEvent( g_operation_timer_id ) ;

		g_bflag_operation_timer_set = false ;

		ResetEvent( hEvent_Operation_Timer_Timeout ) ;
	}
}