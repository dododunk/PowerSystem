// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TTT.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(IDM_WAVE_REAL, OnWaveReal)
	ON_UPDATE_COMMAND_UI(IDM_WAVE_REAL, OnUpdateWaveReal)
	ON_COMMAND(IDM_WAVE_ANALYZE, OnWaveAnalyze)
	ON_UPDATE_COMMAND_UI(IDM_WAVE_ANALYZE, OnUpdateWaveAnalyze)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_nMenuItem=IDM_WAVE_ANALYZE;
}

CMainFrame::~CMainFrame()
{
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

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
    cs.style &=~ (LONG) FWS_ADDTOTITLE;//不改变标题	//  the CREATESTRUCT cs	//  the CREATESTRUCT cs

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


BOOL CMainFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
   
	return CFrameWnd::DestroyWindow();
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	

	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnWaveReal() 
{
	// TODO: Add your command handler code here
	m_nMenuItem=IDM_WAVE_REAL;
	MenuCommand();
}

void CMainFrame::OnUpdateWaveReal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nMenuItem==IDM_WAVE_REAL);
}

void CMainFrame::OnWaveAnalyze() 
{
	// TODO: Add your command handler code here
	m_nMenuItem=IDM_WAVE_ANALYZE;
	MenuCommand();
}

void CMainFrame::OnUpdateWaveAnalyze(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nMenuItem==IDM_WAVE_ANALYZE);
}

void CMainFrame::MenuCommand()
{/*
   UINT  m_nViewType;
   m_nViewType=m_nMenuItem;

   
   CDocument* pDoc = GetActiveDocument();
   if( pDoc == NULL ) return;

   CView *pView1,*pView2=NULL;
   CRuntimeClass *pViewClass=NULL;
   CCreateContext context;
   
   pView1=GetActiveView();

   switch(m_nViewType)
   {
   case IDM_WAVE_REAL:
	   pViewClass=RUNTIME_CLASS(CRealWaveView);
	   break;
   case IDM_WAVE_ANALYZE:
	   pViewClass=RUNTIME_CLASS(CTTTView);
	   break;
   }


    if( pViewClass == NULL ) return;

	pView2 = (CView *)(pViewClass->CreateObject());	//new object
	if( pView2==NULL ) return;

   	context.m_pCurrentFrame = this;
	context.m_pCurrentDoc = pDoc;
	context.m_pNewViewClass = pViewClass;
	context.m_pNewDocTemplate = pDoc->GetDocTemplate();

	if( !pView2->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,	rectDefault, this, AFX_IDW_PANE_FIRST + 1, &context) )
	{
		delete pView2;
		pView2 = NULL;
		return;
	}
   
//	if( pView2->IsKindOf( RUNTIME_CLASS( CFormView) ) )
//		pView2->OnInitialUpdate();	//WM_INITIALUPDATE 0x0364

	int nSwitchChildID = pView2->GetDlgCtrlID();
	pView2->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
	if( pView1 ) pView1->SetDlgCtrlID(nSwitchChildID);


//	pDoc->AddView(pView2);
//	pDoc->RemoveView(pView1);
   
	
	SetActiveView(pView2);
	RecalcLayout();
	
//	 if( pView2->IsKindOf( RUNTIME_CLASS( CFormView) ) )
//	pView2->OnInitialUpdate();	//WM_INITIALUPDATE 0x0364

	pView2->ShowWindow(SW_SHOW);
	pView1->ShowWindow(SW_HIDE);
*/
/*		
	if( m_pCommandView ){
	m_pCommandView->DestroyWindow();

	}m_pCommandView = NULL;
	m_pCommandView = pView2;

*/
}
