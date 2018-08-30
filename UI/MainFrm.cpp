// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"



#include "AppInfo.h"
#include "MainFrm.h"

#include "IFRMView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
const int CXABOUTBUTTON = 25;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_MYDIALOGDATA, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYDIALOGDATA, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_MYDIALOGBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYDIALOGBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_COMMAND(ID_SHOWDIALOGBAR, OnShowdialogbar)
	ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusBar)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_INDICATOR_PROGRESS_PANE,
	ID_ANIMATE,
//	ID_SEPARATOR,         
// status line indicator
//	ID_SEPARATOR,
//	ID_INDICATOR_SCRL,  	
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,

};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bCreated           = FALSE;
	m_IsShowProgressCtrl = FALSE;
	m_pAnimate           =  NULL;
}

CMainFrame::~CMainFrame()
{

	m_pVicinity.DestroyMenu();    //本地菜单销毁
    m_pLongDistance.DestroyMenu();//远程菜单销毁
	StopAnimation();

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}   
		
	//隐藏系统任务栏
	//隐藏WINDOWS系统任务栏
	//::ShowWindow(::FindWindow("Shell_TrayWnd",NULL),SW_HIDE);//显示系统任务栏
	//恢复WINDOWS系统任务栏正常显示
	//::ShowWindow (::FindWindow("Shell_TrayWnd",NULL),SW_SHOW);

	
	/*
	int *num, i, j = m_wndToolBar.GetToolBarCtrl().GetButtonCount();
	num = new int[j + 1];
	memset(num,0,(j + 1)*sizeof(int));
	num[0] = j;
	for(i = 0;i < j;i ++)
	{
		if(ID_SEPARATOR == m_wndToolBar.GetItemID( i ))
			num[i+1] = 1;
	}
	
	//分隔符算是一个按钮，宽度永远为6
	//上面得到的按钮矩形永远比工具栏编辑器里面设定的长宽各大7
	//如果为工具栏设置了位图，按钮的形状永远只与创建位图列表时指定的大小一致，与其他地方的设置无关
	
	
	delete []num;
	*/
	
	//	m_wndToolBar.SetFullColorImage(IDR_MAINFRAME, RGB(255, 0, 255), num);




	if (!m_wndStatusBar.Create(this) ||	!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_bCreated = TRUE;

	m_pVicinity.LoadMenu(IDR_VICINITITYMENU);//调入本地菜单
	HMENU hm=::GetMenu(this->m_hWnd);      //获得远程菜单
	m_pLongDistance.Attach(hm);            //保存远程菜单资源
    
	//pt->m_WhichKind-------TRUE 变电站版本  FALSE电局版
	CIFRMApp* pt = (CIFRMApp*)AfxGetApp();
	
	if(AppInfo::Instance().m_WhichKind)
	{
        SetMenu(&m_pVicinity);    //把菜单设置为本地菜单
	}
	else
	{
		SetMenu(&m_pLongDistance);// 把菜单设置为远程菜单
	}

//  TODO: Delete these three lines if you don't want the toolbar to
//  be dockable
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);
	 CRect     rt;                                                               
	 m_wndStatusBar.GetClientRect(&rt);
	
	 rt.left = rt.left + 358;//298
	 rt.top  = rt.top  +   2;
      
  	 m_progressBar.Create(WS_CHILD | WS_VISIBLE | WS_BORDER,rt,&m_wndStatusBar,ID_INDICATOR_PROGRESS_PANE);//ID_INDICATOR_PROGRESS_PANE);
     m_progressBar.ShowWindow(SW_SHOW);//SW_HIDE);//

	 CRect                rc;
	 VERIFY(m_wndAboutButton.Create(_T(""),WS_VISIBLE,rc,this,ID_APPEARDINGSHI));
 
	 // Create the Ok 256 colors button
     m_wndAboutButton.SubclassDlgItem(ID_APP_ABOUT, this);
 
//	 EnableDocking(CBRS_ALIGN_ANY);
//	 DockControlBar(&m_wndMyDialogData);
	 // Initialize dialog bar m_wndMyDialogData
	 if (!m_wndMyDialogData.Create(this, CG_IDD_MYDIALOGDATA,
		 CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
		 CG_ID_VIEW_MYDIALOGDATA))
	 {
		 TRACE0("Failed to create dialog bar m_wndMyDialogData\n");
		 return -1;		// fail to create
	 }
	 
	 m_wndMyDialogData.EnableDocking(CBRS_ALIGN_BOTTOM);// | CBRS_ALIGN_TOP);

	 
	 if ( !m_wndMyDialogBar.Create(this, CG_IDD_MYDIALOGBAR, CBRS_LEFT,CG_IDD_MYDIALOGBAR))//CBRS_LEFT CBRS_RIGHT
	 {
		 TRACE0("Failed to create dialog bar from CMyDialogBar class\n");
		 return -1;      // fail to create
	 }

	 //m_wndMyDialogBar.CalcDynamicLayout

	 CenterWindow();

	//m_wndMyDialogBar.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndMyDialogBar);
//	DockControlBar(&m_wndMyDialogData);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
//  cs.x=-20;
//	cs.y=-30;

//	cs.style &= ~WS_THICKFRAME;// | ~WS_BORDER;
//	cs.style &= ~WS_DLGFRAME;
//	cs.style &= ~WS_BORDER;
//  cs.style &= FWS_ADDTOTITLE ;////~WS_EX_DLGMODALFRAME;
//  cs.hMenu = NULL;
//  the CREATESTRUCT cs
//	cs.style    &= ~WS_THICKFRAME;//不会改变大小
//  cs.style     = cs.style &~ (WS_MAXIMIZEBOX);//// |WS_MINIMIZEBOX
//  cs.dwExStyle = WS_EX_TOPMOST;//窗口不会被挡住
    cs.style    &=~ (LONG) FWS_ADDTOTITLE;//不改变标题
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::StartAnimation( UINT id, int nPane /*=1*/ )
{
	StopAnimation();

	m_pAnimate = new CStatusbarAnimate;
	m_pAnimate->Create(id, nPane);
}

void CMainFrame::StopAnimation()
{
	delete m_pAnimate;
	m_pAnimate = NULL;
}

BOOL CMainFrame::IsAnimationActive()
{
	return (m_pAnimate != NULL);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);

	if(m_bCreated == TRUE)
	{
	
		CRect           rc;
		GetClientRect(&rc);
      //  m_wndMyDialogBar.GetWindowRect(&rc1);
	  //  m_wndMyDialogBar.SetWindowPos(&wndTop,rc1.left, rc1.top, rc1.Width(),600.top, SWP_SHOWWINDOW);

		m_wndStatusBar.GetClientRect(&rc);
		rc.left = rc.left + 298;//210;
		rc.top  = rc.top   +  2;

		if(m_IsShowProgressCtrl)
		{
			m_progressBar.SetWindowPos(&wndTop, rc.left, rc.top, rc.right - rc.left,rc.bottom - rc.top, SWP_SHOWWINDOW);
		}
		else
		{	m_progressBar.SetWindowPos(&wndTop, rc.left, rc.top, rc.right - rc.left,rc.bottom - rc.top, SWP_HIDEWINDOW);
		
		}
		
		CenterWindow();
    
//		DockControlBar(&m_wndMyDialogData,2,&rc);
		
		//表格控件大小
	 	m_wndMyDialogData.ChangeSize();
	}
	
}

void CMainFrame::ShowProgressCtrl(BOOL m_IsShow)
{
	m_IsShowProgressCtrl = m_IsShow;
	if(m_IsShow)
	{
		m_progressBar.ShowWindow(SW_SHOW);
		
	}
	else
	{
		m_progressBar.ShowWindow(SW_HIDE);
		
	}
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	/***************/

	/*	
	//全屏幕显示的处理函数
	CRect rectDesktop;
	WINDOWPLACEMENT wpNew;
	::GetWindowRect(::GetDesktopWindow(), &rectDesktop );
//  rectDesktop.SetRect(315,0,1282,960);
//  rectDesktop.left = rectDesktop.left;
//  rectDesktop.top = rectDesktop.top;
//	rectDesktop.right = rectDesktop.right;
//	rectDesktop.bottom = rectDesktop.bottom;


	::AdjustWindowRectEx(&rectDesktop, GetStyle(),FALSE,GetExStyle());//TRUE
	wpNew.showCmd  = SW_SHOWNORMAL;//MAXIMIZED;
	wpNew.rcNormalPosition = rectDesktop;
    SetWindowPlacement (&wpNew ); //设置窗口显示状态
  
	lpMMI->ptMaxSize.y = rectDesktop.Height()-9;
	lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y-9; 
	lpMMI->ptMaxSize.x = rectDesktop.Width(); 
	lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;


//	lpMMI->ptMinTrackSize.y = rectDesktop.Height();
//	lpMMI->ptMinTrackSize.x = rectDesktop.Width(); 
*/
	//窗口最小值
    lpMMI->ptMinTrackSize.y = 530;
    lpMMI->ptMinTrackSize.x = 720; 	

//	lpMMI->ptMinTrackSize.y = 0;
//	lpMMI->ptMinTrackSize.x = 0;
	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnClose() 
{
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//	pview->DisConnect(pview->m_sendkind);
	
	if(!pview->DeleteViewThread())
	{
		return;
	}
		
	//强制退出
	if(MessageBox("退出本系统吗？"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{

		CFrameWnd::OnClose();
	}

}

void CMainFrame::OnShowdialogbar() 
{	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//窗口变化
	if(m_wndMyDialogBar.IsWindowVisible())
	{
		m_wndMyDialogBar.ShowWindow(SW_HIDE);
		m_wndMyDialogData.ShowWindow(SW_HIDE);

		pview->m_DialogBarVisible     = FALSE;
	}
	else
	{
		m_wndMyDialogBar.ShowWindow(SW_SHOW);
		m_wndMyDialogData.ShowWindow(SW_SHOW);
		RecalcLayout(TRUE);
		m_wndMyDialogData.ChangeSize();
		pview->m_DialogBarVisible     = TRUE;
	}

	//重新布局
	RecalcLayout();
	
}


void CMainFrame::RecalcLayout(BOOL bNotify) 
{

	CFrameWnd::RecalcLayout(bNotify);
	CRect rc;
	
	if (m_wndStatusBar.m_hWnd)
	{
		m_wndStatusBar.GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.left += CXABOUTBUTTON;
		m_wndStatusBar.SetWindowPos(NULL,rc.left,rc.top,rc.Width(),rc.Height(),
			SWP_NOZORDER);

		rc.left  = 0;
		rc.right = CXABOUTBUTTON;
		m_wndAboutButton.SetWindowPos(NULL,rc.left,rc.top,rc.Width(),rc.Height(),
				SWP_NOZORDER);	
		m_wndAboutButton.SetFlatFocus(TRUE,TRUE);
	}	
}

void CMainFrame::OnViewStatusBar() 
{
	// call base class handler
	OnBarCheck(AFX_IDW_STATUS_BAR);

	// now make button visible state same as status bar's
	BOOL bShow = m_wndStatusBar.GetStyle() & WS_VISIBLE;
	m_wndAboutButton.SetWindowPos(NULL, 0, 0, 0, 0,
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|
		(bShow ? SWP_SHOWWINDOW : SWP_HIDEWINDOW));	
}
