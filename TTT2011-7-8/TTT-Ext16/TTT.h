// TTT.h : main header file for the TTT application
//

#if !defined(AFX_TTT_H__9A7B7413_5012_4D2C_8EFD_D0CB104DEE18__INCLUDED_)
#define AFX_TTT_H__9A7B7413_5012_4D2C_8EFD_D0CB104DEE18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTTTApp:
// See TTT.cpp for the implementation of this class
//

class CTTTApp : public CWinApp
{
public:
	BOOL m_ifcardis9111dr;
	CTTTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTTApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTTTApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTT_H__9A7B7413_5012_4D2C_8EFD_D0CB104DEE18__INCLUDED_)
