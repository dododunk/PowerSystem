// Power_UI.h : main header file for the POWER_UI application
//

#if !defined(AFX_POWER_UI_H__A94B6334_12DA_49CD_A739_3FC079D49868__INCLUDED_)
#define AFX_POWER_UI_H__A94B6334_12DA_49CD_A739_3FC079D49868__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPower_UIApp:
// See Power_UI.cpp for the implementation of this class
//

class CPower_UIApp : public CWinApp
{
public:
	CPower_UIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPower_UIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPower_UIApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWER_UI_H__A94B6334_12DA_49CD_A739_3FC079D49868__INCLUDED_)
