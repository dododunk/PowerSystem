#include "StdAfx.h"
#include "testload.h"




//#define AUTOSWITCH(szActionName)	\	
//	HMODULE hcurInstance = 	GetModuleHandleA(#szActionName);					\
//CAutoHandle	switcher(hcurInstance);




class CAutoHandle
{
public:
    CAutoHandle(HINSTANCE hnew)
	{
		m_hmain = AfxGetResourceHandle();
		
		AfxSetResourceHandle(hnew);
	}
    ~CAutoHandle()	
	{
		AfxSetResourceHandle(m_hmain);
	}
protected:
private:
    HINSTANCE	m_hmain;
};


LIBCAPI void* CallForm( CWnd* pParent )
{
AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CAutoHandle a(GetModuleHandleA("test.exe"));
	CTestDlg* plg = new CTestDlg(pParent);
	plg->Create(CTestDlg::IDD,pParent);
	plg->ModifyStyle(0, WS_EX_CONTROLPARENT);
	plg->ShowWindow(SW_SHOW);
	return plg;
}

LIBCAPI int CallDialog()
{
	try
	{
		auto x = GetModuleHandleA("test.exe");
		CAutoHandle a(x);
		//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CTestDlg dlg;
		return	dlg.DoModal();
	}
	catch (...)
	{
		
	}
	
	
}
