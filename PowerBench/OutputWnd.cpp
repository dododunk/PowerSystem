
#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
	pInstance = this;

	PowerBenchSharpLib::ForwardLogger::OnMsg +=
		 MAKE_DELEGATE(System::EventHandler<PowerBenchSharpLib::LogEventArgs^> ,OnLogMsg);
	exportapi::CLogger::OnMsg += 
		MAKE_DELEGATE(System::EventHandler<exportapi::LogEventArgs^>, OnLogMsg1);
}

COutputWnd::~COutputWnd()
{
}


void COutputWnd::OnLogMsg(System::Object^ Sender,PowerBenchSharpLib::LogEventArgs^ eventargs)
{
	WriteLog(eventargs->Data);
}

void COutputWnd::OnLogMsg1(System::Object^ Sender,exportapi::LogEventArgs^ eventargs)
{
	WriteLog(eventargs->Get_Data());
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建选项卡窗口:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("未能创建输出选项卡窗口\n");
		return -1;      // 未能创建
	}

	// 创建输出窗格:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_wndOutputLog.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutputDebug.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputFind.Create(dwStyle, rectDummy, &m_wndTabs, 4))
	{
		TRACE0("未能创建输出窗口\n");
		return -1;      // 未能创建
	}

	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// 将列表窗口附加到选项卡:
	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputLog, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputFind, strTabName, (UINT)2);

	// 使用一些虚拟文本填写输出选项卡(无需复杂数据)
	FillBuildWindow();
	FillDebugWindow();
	FillFindWindow();

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// 选项卡控件应覆盖整个工作区:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void COutputWnd::FillBuildWindow()
{
	//m_wndOutputLog.AddString(_T("生成输出正显示在此处。"));
	//m_wndOutputLog.AddString(_T("输出正显示在列表视图的行中"));
	//m_wndOutputLog.AddString(_T("但您可以根据需要更改其显示方式..."));
}

void COutputWnd::FillDebugWindow()
{
	
}

void COutputWnd::FillFindWindow()
{
	
}

void COutputWnd::UpdateFonts()
{
	m_wndOutputLog.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputDebug.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputFind.SetFont(&afxGlobalData.fontRegular);
}

void COutputWnd::WriteLog( const CString& msg )
{
	if(pInstance != NULL )
	{
		pInstance->m_wndOutputLog.AddString(msg);
	}
}

/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputEdit::COutputEdit()
{
}

COutputEdit::~COutputEdit()
{
}

BEGIN_MESSAGE_MAP(COutputEdit, CEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList 消息处理程序


void COutputEdit::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}

void COutputEdit::AddString(const CString& data )
{
	m_datas.AddString(data);
	this->SetWindowText(m_datas.ToCString());
}


COutputWnd* COutputWnd::pInstance = NULL;

FixlinesList::FixlinesList() :m_linenum(100)
{
	
}
//define this function as ref,which should reduce tmp obj ctr&dtr.still low eff
CString& FixlinesList::ToCString() const
{
	static CString Result;
	Result.Empty();
	for (auto item  = m_datas.begin(); item != m_datas.end(); ++item)
	{
		Result += "\r\n" + *item;
	}
	return Result;	
}

void FixlinesList::AddString( const CString& data )
{
	m_datas.push_front(data);
	if(m_datas.size() > m_linenum)
	{
		m_datas.pop_back();			
	}
}

void FixlinesList::SetLineNum( int linenum )
{
	m_linenum = linenum;
}
