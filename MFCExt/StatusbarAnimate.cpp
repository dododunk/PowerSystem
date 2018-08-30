// StatusbarAnimate.cpp : implementation file
//

#include "stdafx.h"
#include "StatusbarAnimate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CStatusbarAnimate, CAnimateCtrl) 

/////////////////////////////////////////////////////////////////////////////
// CStatusbarAnimate

CStatusbarAnimate::CStatusbarAnimate()
{
	m_Rect.SetRect(0,0,0,0);
}

CStatusbarAnimate::~CStatusbarAnimate()
{
}


BEGIN_MESSAGE_MAP(CStatusbarAnimate, CAnimateCtrl)
	//{{AFX_MSG_MAP(CStatusbarAnimate)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusbarAnimate message handlers

BOOL CStatusbarAnimate::Create( UINT nIDanimation, int nPane /*=1*/ )
{
	CStatusBar *pStatusBar = GetStatusBar();
	if (!pStatusBar)
		return FALSE;

	DWORD dwStyle = WS_CHILD|WS_VISIBLE|ACS_AUTOPLAY|ACS_TRANSPARENT|ACS_CENTER;
	// Get CRect coordinates for requested status bar pane
	CRect paneRect;
	pStatusBar->GetItemRect(nPane, &paneRect);

	paneRect.InflateRect(-1,-1);

	if (!CAnimateCtrl::Create( dwStyle, paneRect, pStatusBar, 0 ))
		return FALSE;

	m_nPane = nPane;

	Resize();
//	ModifyStyleEx( 0, WS_EX_STATICEDGE );

	return Open( nIDanimation );
}

CStatusBar* CStatusbarAnimate::GetStatusBar()
{
	CWnd *pMainWnd = AfxGetMainWnd();
	if (!pMainWnd)
		return NULL;

    // If main window is a frame window, use normal methods...
    if (pMainWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
    {
        CWnd* pMessageBar = ((CFrameWnd*)pMainWnd)->GetMessageBar();
        return DYNAMIC_DOWNCAST(CStatusBar, pMessageBar);
    }
    // otherwise traverse children to try and find the status bar...
    else
	    return DYNAMIC_DOWNCAST(CStatusBar, 
                                pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR));
}

BOOL CStatusbarAnimate::Resize()
{
	if (!IsWindow(GetSafeHwnd()))
		return FALSE;

	CStatusBar *pStatusBar = GetStatusBar();
	if (!pStatusBar)
		return FALSE;

	// Now calculate the rectangle in which we will draw
	CRect rc;
	pStatusBar->GetItemRect(m_nPane, rc);

	rc.InflateRect(-1,-1);

	// If the window size has changed, resize the window
	if (rc != m_Rect) 
	{
		MoveWindow(&rc);
		m_Rect = rc;
	}

	return TRUE;
}

BOOL CStatusbarAnimate::OnEraseBkgnd(CDC* pDC) 
{
	Resize();
	return CAnimateCtrl::OnEraseBkgnd(pDC);
}
