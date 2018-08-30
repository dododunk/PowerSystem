// TAPILine.h: interface for the CTAPILine class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAPILINE_H__378FA136_FC63_4D63_87AE_CA6F56D70764__INCLUDED_)
#define AFX_TAPILINE_H__378FA136_FC63_4D63_87AE_CA6F56D70764__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "global.h"
#include "TAPI.h"


class CTAPILine  
{
	//标识线路的变量
	DWORD m_nNumLines;
	DWORD m_nCurLineID;

	//TAPI句柄
	HLINEAPP m_hLineApp;
	DWORD m_nAPIVersions[10];
	DWORD m_lowAPIVersion;
	DWORD m_highAPIVersion;
	LINEEXTENSIONID m_extAPIVersions[10];
	DWORD m_nApplicationVersion;
	DWORD m_nLastTAPIError;
	
//表示设备和设备属性的变量
	LINEDEVCAPS m_lineCaps;
	CString m_strLineName;
	CString m_strProviderInfo;
	CString m_strSwitchInfo;
	DWORD m_nPermanentLineID;
	DWORD m_nStringFormat;
	DWORD m_numAddresses;
	LONG m_nMediaModes;
	DWORD m_nAddress;
	DWORD m_nMaxDataRate;
	LONG m_nBearerModes;
	LONG m_nAddressModes;
	DWORD m_nGenerateToneMaxNumFreq;
	DWORD m_nGenerateToneModes;
	DWORD m_nNumTerminals;

//呼叫状态和异步函数返回状态变量
	HLINE m_hLine;
	HCALL m_hCall;
	DWORD m_nRequestingCall;
	DWORD m_nDroppingCall;
	DWORD m_nReqPrivileges;
	DWORD m_nReqMedialModes;
	
public:
	CTAPILine();
	virtual ~CTAPILine();

//成员函数
//这四个函数设定和获取最高版本号和最低版本号
	void SetLowAPI(DWORD ver);
	DWORD GetLowAPI();
	void SetHighAPI(DWORD ver);
	DWORD GetHighAPI();	
//获取当前的TAPI线路数值，并提供给其他模块使用
	DWORD GetNumLines();
	
//获取和设定当前TAPI线路
	DWORD GetCurrentLineID();
	void SetCurrentLineID(DWORD id);

//获取线路信息中的内容
	CString GetLineName();
	CString GetProviderInfo();
	CString GetSwitchInfo();
	CString GetLineErrString(DWORD lErrCode);

	DWORD GetPermanentLineID();
	DWORD GetStringFormat();
	DWORD GetNumAddress();
	DWORD GetmaxDataRate();
	LONG GetBearerModes();
	LONG GetAddressModes();
	LONG GetMediaModes();
	DWORD GetGenerateToneMaxNumFreq();
	DWORD GetGenerateToneModes();
	DWORD GetNumTerminals();
	BOOL GetLineSupportsVoice();

	DWORD GetNegoAPIVersion();
	DWORD GetExtAPIID0();
	DWORD GetExtAPIID1();
	DWORD GetExtAPIID2();
	DWORD GetExtAPIID3();

//对错误代码提供返回错误信息字符串	
	DWORD GetLasterror();
	CString ErrorString(DWORD errCode);

//创建函数
	BOOL Create();

//打开线路信息函数
	BOOL OpenLine(DWORD nPrivileges = LINECALLPRIVILEGE_NONE, DWORD nMediaModes = LINEMEDIAMODE_INTERACTIVEVOICE);
//产生异步呼叫的函数
	BOOL MakeCallAsynch(CString strPhoneNumbers = "");
//异步挂断电话的函数
	BOOL DropCallAsynch();
//关闭线路的函数
	BOOL CloseLine();
//线路配置的函数，该函数调用线路配置对话框
	BOOL ConfigDialog(HWND hWnd = NULL, CString strDeviceClass = "");
//拨号配置的函数，该函数调用拨号配置对话框
	BOOL DialoingPropertiesDialog(HWND hWnd, CString strPhoneNumber);
//回调函数，处理线路信息和状态改变信息
	static void FAR PASCAL LineCallbackProc(DWORD dwDevice, DWORD dwMsg, DWORD dwCallbackInstance, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3);
//获得线路状态字符串
	CString GetLineStateString(DWORD state);
	
//私有成员函数
private:
//获取线路信息
	BOOL GetLineDevCaps();	
};

#endif // !defined(AFX_TAPILINE_H__378FA136_FC63_4D63_87AE_CA6F56D70764__INCLUDED_)


