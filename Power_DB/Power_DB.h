// Power_DB.h : main header file for the POWER_DB DLL
//

#if !defined(AFX_POWER_DB_H__E64EE478_090E_4CE5_83A3_23CBA36A80F8__INCLUDED_)
#define AFX_POWER_DB_H__E64EE478_090E_4CE5_83A3_23CBA36A80F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPower_DBApp
// See Power_DB.cpp for the implementation of this class
//

class CPower_DBApp : public CWinApp
{
public:
	CPower_DBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPower_DBApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPower_DBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWER_DB_H__E64EE478_090E_4CE5_83A3_23CBA36A80F8__INCLUDED_)
