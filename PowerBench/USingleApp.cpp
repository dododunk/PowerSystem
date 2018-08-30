#include "StdAfx.h"
#include "USingleApp.h"



bool USingleApp::IsSingleByMutex( const TCHAR* mutexname )
{
	HANDLE m_hMutex = CreateMutex(NULL,TRUE, mutexname); 

	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{ 
		return false; 
	}
	return true;
}

BOOL USingleApp::IsSingleByWnd( const TCHAR* wndname )
{
	return FALSE;
}

BOOL USingleApp::IsSingleByAppName( const TCHAR* appname )
{
	return FALSE;
}
