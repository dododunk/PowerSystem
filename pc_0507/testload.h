#ifndef _TEST_LOAD_H_
#define _TEST_LOAD_H_
#include "StdAfx.h"
#include "resource.h"
#include "testDlg.h"


#pragma message("build dll")
#define  LIB_BUILD_DLL


#ifdef __cplusplus
#define LIBUTILS_EXTERN_C extern"C"
#else
#define LIBUTILS_EXTERN_C extern
#endif

#ifdef WIN32	
#ifdef LIB_BUILD_DLL										//dll build.
#pragma message("build dll")
#define LIBUTIL_DLL_PORT __declspec(dllexport)	
#else
#define LIBUTIL_DLL_PORT __declspec(dllimport)	
#endif
#else
#define LIBUTIL_DLL_PORT
#endif

#define LIBAPI	LIBUTIL_DLL_PORT
#define LIBCAPI	LIBUTILS_EXTERN_C	LIBUTIL_DLL_PORT





LIBCAPI int CallDialog();


LIBCAPI void* CallForm(CWnd* pParent);


#endif