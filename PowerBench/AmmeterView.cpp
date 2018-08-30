
#include "stdafx.h"
#include "mainfrm.h"
#include "AmmeterView.h"
#include "Resource.h"
#include "PowerBench.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView


static CAmmeterView* pInstance = NULL;;
CAmmeterView::CAmmeterView()
{
	pInstance = this;
}


CAmmeterView::~CAmmeterView()
{

}


BEGIN_MESSAGE_MAP(CAmmeterView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()	
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 消息处理程序

int CAmmeterView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	
	OnChangeVisualStyle();



	m_dlg.Create(IDD_DIALOG_AMMETERVIEWHOD,this);
	m_dlg.ShowWindow(SW_SHOW);
	
	AdjustLayout();

	return 0;
}

void CAmmeterView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	return;
}
void CAmmeterView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	if(m_dlg.GetSafeHwnd())
	{
		CRect rct;
		GetClientRect(rct);
		m_dlg.MoveWindow(rct);
	}
}



void CAmmeterView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CAmmeterView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
}

void CAmmeterView::OnChangeVisualStyle()
{
	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

}




void CAmmeterView::OnDestroy()
{
	m_dlg.DestroyWindow();
	CDockablePane::OnDestroy();
}

CAmmeterView* CAmmeterView::GetCurrentInstance()
{
	return pInstance;
}

PowerBenchSharpLib::AmmeterInfoControl^ CAmmeterView::GetHoldControl()
{
	return m_dlg.GetControl();
}
