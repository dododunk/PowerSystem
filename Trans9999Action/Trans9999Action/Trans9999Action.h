// Trans9999Action.h : main header file for the Trans9999Action DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTrans9999ActionApp
// See Trans9999Action.cpp for the implementation of this class
//

class CTrans9999ActionApp : public CWinApp
{
public:
	CTrans9999ActionApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
