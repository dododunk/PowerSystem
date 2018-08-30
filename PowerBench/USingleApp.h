#pragma once
class USingleApp
{
public:
	
	static bool IsSingleByMutex(const TCHAR* mutexname );
	BOOL IsSingleByWnd(const TCHAR* wndname);
	BOOL IsSingleByAppName(const TCHAR* appname	);
	
private:
	USingleApp(void);
	//CString m_mutexname


};

