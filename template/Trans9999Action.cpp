///////////////////////////////////////////////////////////////
/**
*\file		Trans9999Action.cpp
*\brief
*
*\version	1.0 	
*
*\author 	enigma
*\date		2007/03/13
*
* Copyright (C) 2007 - All Rights Reserved
*/
///////////////////////////////////////////////////////////////
#include "StdAfx.h"


#include "maindll.h"
#include "D9999A.h"
#include <exception>
#include <memory>
//#include <debugutils.h>

///////////////////////////////////////////////////////////////
#include "StdAfx.cpp"
#include "maindll.cpp"

///////////////////////////////////////////////////////////////
class stAppInfo;

BASAPI int MakeTransDialog(stAppInfo* pMgr,void* pIn,void* pOut)
{
	DBG_ASSERT(pMgr != NULL);
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//设置交易动态库业务变量
	

	CD9999A dlg;
	dlg.Show();
	return dlg.GetReturnCode();	
}

BASAPI void* MakeTransForm(stAppInfo* pMgr,void* pIn,void* pOut)
{
	DBG_ASSERT(pMgr !=NULL);	
	AUTOSWITCH("9999");
	
	//设置交易动态库业务变量
	//SetAppInfo(pMgr);
	

	CD9999A*	pForm = new CD9999A();
	DBG_ASSERT(pForm != NULL);
	//pForm->Create(CD9999A::IDD,pMgr->m_pFormParent);
	
	pForm->ModifyStyle(0, WS_EX_CONTROLPARENT);
	pForm->ShowWindow(SW_SHOW);
	
	return pForm;
}


BASAPI const char* DllGetVersion()
{
#ifdef CUR_DLL_VER
#undef CUR_DLL_VER
#endif
	
#define CUR_DLL_VER	"1.0.0"
	
	static char strVersion[256];
	sprintf(strVersion,"%s%s",CUR_DLL_VER,GetBuildInfo());
	return strVersion;
}