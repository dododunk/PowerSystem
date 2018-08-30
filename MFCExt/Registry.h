//
//Registry.h
/*
   Registry Class Version 1.00
   Author:xiaojin
   Company:Nanjing BC Foods Co. Limited
   Tel:025-5410950-1809
   E-Mail:xiaoj@njb.swirebev.com
   Date:03-18-2003
   All right reserved.
*/

#if !defined(AFX_REGISTRY_H__E0610A5D_7166_4D02_9D7E_11AF7CF8E229__INCLUDED_)
#define AFX_REGISTRY_H__E0610A5D_7166_4D02_9D7E_11AF7CF8E229__INCLUDED_

//
#include <winreg.h>
/////////////////////////////////////////////////////////////////////////////
// CRegistry window
#include "MFCExtDefiniton.h"
class MFCEXTAPI CRegistry : public CObject
{
// Construction
public:
	CRegistry(HKEY hKey=HKEY_LOCAL_MACHINE);

public:
	BOOL SaveKey(LPCTSTR lpFileName);
	BOOL RestoreKey(LPCTSTR lpFileName);
	BOOL Read(LPCTSTR lpValueName, CString* lpVal);
	BOOL Read(LPCTSTR lpValueName, DWORD* pdwVal);
	BOOL Read(LPCTSTR lpValueName, int* pnVal);
	BOOL Write(LPCTSTR lpSubKey, LPCTSTR lpVal);
	BOOL Write(LPCTSTR lpSubKey, DWORD dwVal);
	BOOL Write(LPCTSTR lpSubKey, int nVal);
	BOOL DeleteKey(HKEY hKey, LPCTSTR lpSubKey);
	BOOL DeleteValue(LPCTSTR lpValueName);
	void Close();
	BOOL Open(LPCTSTR lpSubKey);
	BOOL CreateKey(LPCTSTR lpSubKey);
	virtual ~CRegistry();

protected:
	HKEY m_hKey;
	
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_REGISTRY_H__E0610A5D_7166_4D02_9D7E_11AF7CF8E229__INCLUDED_)
