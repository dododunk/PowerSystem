
#pragma  once
/******************
»ù´¡ºê¶¨Òå
*******************/

#ifdef __cplusplus
#define MFCEXT_EXTERN_C extern"C"
#else
#define MFCEXT_EXTERN_C extern
#endif

#ifdef WIN32	
#ifdef MFCEXT_BUILD_DLL										//dll build.
#define MFCEXT_DLL_PORT __declspec(dllexport)		
#elif  defined MFCEXT_USE_DLL									//use dll.
#define MFCEXT_DLL_PORT __declspec(dllimport)
#else
#define MFCEXT_DLL_PORT	
#endif	
#else
#define MFCEXT_DLL_PORT
#endif

#define MFCEXTAPI	MFCEXT_DLL_PORT