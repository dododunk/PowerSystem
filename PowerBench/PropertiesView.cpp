
#include "stdafx.h"

#include "PropertiesView.h"
#include "Resource.h"
#include "MainFrm.h"
#include "PowerBench.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar



CPropertiesView::CPropertiesView()
{
}

CPropertiesView::~CPropertiesView()
{
}

BEGIN_MESSAGE_MAP(CPropertiesView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()	
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

	 

int CPropertiesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	

	m_dlg.Create(IDD_DIALOG_AMMETERVIEWHOD,this);
	
	m_dlg.ShowWindow(SW_SHOW);
	m_dlg->Enabled = false;
	
	CAmmeterView::GetCurrentInstance()->GetHoldControl()->Tree->OnNodePropertyShow += MAKE_DELEGATE(System::EventHandler<PowerBenchSharpLib::NodeEventArgs^> ,OnChanged);
	
	return 0;
}


 void CPropertiesView:: OnChanged(System::Object^ Sender,PowerBenchSharpLib::NodeEventArgs^ eventargs)
{
	this->m_dlg->SelectedObject = eventargs->Obj;
}

void CPropertiesView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if(m_dlg.GetSafeHwnd())
	{
		CRect rct;
		GetClientRect(rct);
		m_dlg.MoveWindow(rct);
	}
	
}
void CPropertiesView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	
}

void CPropertiesView::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	
}
