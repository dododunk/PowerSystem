
#include "stdafx.h"

#include "header.h"

#include "mmsystem.h" 
/*
#include "timer.h"

#include "protocol.h"

#include  "meter_read_cmd_encode.h"

#include  "global.h"
*/



HANDLE   hEvent_Operation_Timer_Timeout ; 

bool     g_bflag_operation_timer_set  ;

int      g_operation_timer_id ;

unsigned int    g_uc_trig_timer_raising_usecond = 0 ;  //发送触发命令时，第1个过零点触发时刻延时

unsigned int    g_uc_trig_timer_falling_usecond = 0 ; //发送触发命令时，第二个过零点触发时刻延时



HANDLE          hThread_Trig_Timer_Raising ;

HANDLE          hThread_Trig_Timer_Falling ;

HANDLE          hEvent_Thread_Trig_Timer_Raising_Enable ;

HANDLE          hEvent_Thread_Trig_Timer_Falling_Enable ;

double          g_db_system_freguence ;


typedef unsigned long (CALLBACK *pfun_callback)(LPVOID pvUserParam) ;




void   TimeProc_Operation_Init()
{

hEvent_Operation_Timer_Timeout = CreateEvent( NULL ,true ,false , NULL ) ; 

g_bflag_operation_timer_set = false ;

g_operation_timer_id = 0 ;
}


void CALLBACK TimeProc_Operation_Timer(UINT uID,UINT uMsg,
								DWORD dwUser,DWORD dw1,DWORD dw2 )
{
  SetEvent( hEvent_Operation_Timer_Timeout ) ;

/*
    PCI8664_CreateDevice( 0 ) ;

	PCI8664_StopDeviceProAD( ( hDevice_AD ) ) ;

	PCI8664_ReleaseDeviceProAD( hDevice_AD );
	
	PCI8664_ReleaseDevice( hDevice_AD ) ;

	TerminateThread( hThread_Read_AD_Test  ,  0 ) ;

	int   a ;

*/

//	PCI8684_
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
/*
void Fun_Operation_Timer_Set( UINT  ui_msecond , int  event_flag )//run once
{
	if( g_bflag_operation_timer_set == false )
	{
		g_operation_timer_id = timeSetEvent( ui_msecond , 0 , (LPTIMECALLBACK) TimeProc_Operation_Timer ,( DWORD ) event_flag , TIME_ONESHOT ) ; //TIME_PERIODIC ) ;	
		
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
*/
void Fun_Operation_Timer_Stop(  )
{
	if( g_bflag_operation_timer_set == true )
	{
		timeKillEvent( g_operation_timer_id ) ;

		g_bflag_operation_timer_set = false ;

		ResetEvent( hEvent_Operation_Timer_Timeout ) ;
	}
}


int  Fun_Precious_Timer_Set( UINT  ui_usecond )
{
	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 
	
	int error_flag = 0  ;	
	
	unsigned char recv_data = 0 ; 

	double   set_time_us = ui_usecond / 1000000 ;
	
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
	db_freq = ( double ) time1.QuadPart  ;
	
    //////////////////////////////////延时			
	QueryPerformanceCounter( &time1 ) ;  //得到起始时间
			
	db_start = time1.QuadPart ;
	//延时输出clk信号		
	do
	{    
	    QueryPerformanceCounter( &time1 ) ;  //得到当前时间
				
	    db_end = time1.QuadPart ;
				
		db_space = ( double ) ( db_end- db_start ) ; 
				
	    db_space = db_space / db_freq ; //时间差 s 
				
	}   
	while( db_space < ui_usecond ) ;  //s

	return 1 ;
}



int  Fun_Trig_Timer_Set( UINT  ui_degree )
{
	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 
	
	int error_flag = 0  ;	
	
	unsigned char recv_data = 0 ; 
	
	double   set_time_us = 10 - ( ui_degree * 1 / 18 ) ;//ms: 10ms - degree * ( 20 / 360 )

    set_time_us = set_time_us / 1000 ; //set to second 
	
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
	db_freq = ( double ) time1.QuadPart  ;
	
    //////////////////////////////////延时			
	QueryPerformanceCounter( &time1 ) ;  //得到起始时间
	
	db_start = time1.QuadPart ;
	//延时输出clk信号		
	do
	{    
		QueryPerformanceCounter( &time1 ) ;  //得到当前时间
		
		db_end = time1.QuadPart ;
		
		db_space = ( double ) ( db_end- db_start ) ; 
		
		db_space = db_space / db_freq ; //时间差 s 
		
	}   
	while( db_space < set_time_us ) ;  //s
	
	return 1 ;
}





///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void CALLBACK Thread_Trig_Timer_Raising( )
{
  LARGE_INTEGER    time1 ;
	
  double   db_freq ,  db_space ;
	
  LONGLONG db_start , db_end ; 

  //get frequence 
  QueryPerformanceFrequency( &time1 ) ;
		
  db_freq = ( double ) time1.QuadPart  ;
		
  do 
  {
    if( WaitForSingleObject( hEvent_Thread_Trig_Timer_Raising_Enable , 0 ) == WAIT_OBJECT_0 ) 
	{		
		double   set_time_us = 10 - ( g_uc_trig_angle_instent * 1 / 18 ) ;//ms: 10ms - degree * ( 20 / 360 )
		
		set_time_us = set_time_us / 1000 ; //set to second 
	
		//////////////////////////////////延时			
		QueryPerformanceCounter( &time1 ) ;  //得到起始时间
		
		db_start = time1.QuadPart ;
		//延时输出clk信号		
		do
		{    
			QueryPerformanceCounter( &time1 ) ;  //得到当前时间
			
			db_end = time1.QuadPart ;
			
			db_space = ( double ) ( db_end- db_start ) ; 
			
			db_space = db_space / db_freq ; //时间差 s 
			
		}   
	   while( db_space < set_time_us ) ;  //s 
	   
	   ResetEvent( hEvent_Thread_Trig_Timer_Raising_Enable ) ;

	   SuspendThread( hThread_Trig_Timer_Raising ) ;

	  // AfxMessageBox("timer ok" ) ;
	}//timer start 

  } 
  while ( 1 ) ;
}


void CALLBACK Thread_Trig_Timer_Falling( )
{
	LARGE_INTEGER    time1 ;
	
	double   db_freq ,  db_space ;
	
	LONGLONG db_start , db_end ; 
	
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
	db_freq = ( double ) time1.QuadPart  ;
	
	do 
	{
		if( WaitForSingleObject( hEvent_Thread_Trig_Timer_Falling_Enable , 0 ) == WAIT_OBJECT_0 ) 
		{		
			double   set_time_us = 20 - ( g_uc_trig_angle_instent * 1 / 18 ) ;//ms: 10ms - degree * ( 20 / 360 )
			
			set_time_us = set_time_us / 1000 ; //set to second 
			
			//////////////////////////////////延时			
			QueryPerformanceCounter( &time1 ) ;  //得到起始时间
			
			db_start = time1.QuadPart ;
			//延时输出clk信号		
			do
			{    
				QueryPerformanceCounter( &time1 ) ;  //得到当前时间
				
				db_end = time1.QuadPart ;
				
				db_space = ( double ) ( db_end- db_start ) ; 
				
				db_space = db_space / db_freq ; //时间差 s 
				
			}   
			while( db_space < set_time_us ) ;  //s 
			
			ResetEvent( hEvent_Thread_Trig_Timer_Falling_Enable ) ;

			SuspendThread( hThread_Trig_Timer_Falling ) ;
			
		//	AfxMessageBox("timer ok" ) ;
		}//timer start 
		
	} 
	while ( 1 ) ;
}


void  Fun_Thread_Trig_Timer_Raising_Init( )
{
	/////////////create a thread
	hThread_Trig_Timer_Raising = CreateThread( 0, 0, ( pfun_callback)Thread_Trig_Timer_Raising , 0 , 
		CREATE_SUSPENDED , &dwThreadID1 ) ;
	
	SetThreadPriority( hThread_Trig_Timer_Raising , THREAD_PRIORITY_ABOVE_NORMAL ) ; 
	
	hEvent_Thread_Trig_Timer_Raising_Enable = CreateEvent( NULL , true , false , NULL) ; 
}

void  Fun_Thread_Trig_Timer_Falling_Init( )
{
	/////////////create a thread
	hThread_Trig_Timer_Falling = CreateThread( 0, 0, ( pfun_callback)Thread_Trig_Timer_Falling , 0 , 
		CREATE_SUSPENDED , &dwThreadID1 ) ;
	
	SetThreadPriority( hThread_Trig_Timer_Falling , THREAD_PRIORITY_ABOVE_NORMAL ) ; 
	
	hEvent_Thread_Trig_Timer_Falling_Enable = CreateEvent( NULL , true , false , NULL) ; 
}


void  Fun_Get_Sys_Frequence( )
{
	LARGE_INTEGER    time1 ;
		
	//get frequence 
	QueryPerformanceFrequency( &time1 ) ;
	
	g_db_system_freguence = ( double ) time1.QuadPart  ;
}


void  Fun_Delay_Usecond( unsigned int ui_msecond )
{

  double times = ui_msecond * g_db_system_freguence / 1000000 ;

  for( int i = 0 ; i < times ; i ++ ) ;
  	
}



void Fun_Set_Trig_Timer( int  angle  , unsigned char   edge_flag )
{
	LARGE_INTEGER    time1 ;
	
	double   db_space ;
	
	LONGLONG db_start , db_end ; 

	double   set_time_us = 0 ;

	if( edge_flag == _RAISING_EDGE )
	{
       set_time_us = 10 - ( g_uc_trig_angle_instent * 1 / 18 ) ;//ms: 10ms - degree * ( 20 / 360 )
	}

	if( edge_flag == _FAILING_EDGE )
	{
		set_time_us = 10 ;// - ( g_uc_trig_angle_instent * 1 / 18 ) ;//ms: 10ms - degree * ( 20 / 360 )
	}
    

set_time_us = set_time_us / 1000 ; //set to second 

//////////////////////////////////延时			
QueryPerformanceCounter( &time1 ) ;  //得到起始时间

db_start = time1.QuadPart ;
//延时输出clk信号		
do
{    
	QueryPerformanceCounter( &time1 ) ;  //得到当前时间
	
	db_end = time1.QuadPart ;
	
	db_space = ( double ) ( db_end- db_start ) ; 
	
	db_space = db_space / g_db_system_freguence ; //时间差 s 
	
}   
while( db_space < set_time_us ) ;  //s

}
