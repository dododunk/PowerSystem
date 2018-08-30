// IFRM.h : main header file for the IFRM application
//

#if !defined(AFX_IFRM_H__3C7C97FB_91B1_4D74_A864_BF8E3F4A7F1C__INCLUDED_)
#define AFX_IFRM_H__3C7C97FB_91B1_4D74_A864_BF8E3F4A7F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIFRMApp:
// See IFRM.cpp for the implementation of this class
//

class CIFRMApp : public CWinApp
{
public:
	
	CIFRMApp();	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFRMApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CIFRMApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFRM_H__3C7C97FB_91B1_4D74_A864_BF8E3F4A7F1C__INCLUDED_)
