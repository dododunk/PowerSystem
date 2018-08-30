// Label.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "Label.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CLabel, CStatic)
	//{{AFX_MSG_MAP(CLabel)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLabel Version 1.2
//
// From now on I'll try to keep a log of fixes and enhancements...
// 
// The new feature were added due to the response of people.
// All I ask is to all you programmers out there, is if you add, fix or
// enhance this code, sent me a copy and I'll send the copy on to www.codeguru.com
//
// Happy hacking :)
// 
// New features include:
//
// A. Support for 3D Fonts
// B. Support for background transparency
// C. More comments provided
// D. If alignment is 'centered' and the window text is seperated by '\r\n'
//	  the will be centered accordingly - requested by someone @ nasa ;)
// E. Support for font rotation.
// F. Respond to System Color Change
// G. OnPaint improved performance - using Double Buffering Technique
//
// Thanks to:
// Mark McDowell	- For suggestion on 'Increasing the flexibility of "hypertext" setting...'
// Erich Ruth		- For suggestion on 'Font Rotation'
//

/////////////////////////////////////////////////////////////////////////////
// CLabel Version 1.3
//
// A. Added SS_LEFTNOWORDWRAP to include wordwrap
// B. Fix repainting problem 
// C. Fix SetBkColor
// D. Added SS_CENTER

// Thanks to:
// Marius						- Added styling problem.
// Azing Vondeling & Broker		- Spotting painting Problem.
// Mel Stober					- Back Color & SS_CENTER
// 
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::CLabel
//
// Description:		Default contructor
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel::CLabel()
{
	m_crText = GetSysColor(COLOR_WINDOWTEXT);

// 1.1
	m_hBackBrush = NULL;


	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);

	m_font.CreateFontIndirect(&m_lf);
	m_bTimer =			FALSE;
	m_bState =			FALSE;
	m_bTransparent =	FALSE;
	m_bLink =			TRUE;
	m_hCursor =			NULL;
	m_Type =			None;
	m_bFont3d =			FALSE;
	m_bNotifyParent =	FALSE;
	m_bToolTips =		FALSE;
	m_bRotation =		FALSE;
	
	m_hwndBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::~CLabel
//
// Description:		
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel::~CLabel()
{
	// Clean up
	m_font.DeleteObject();
	::DeleteObject(m_hwndBrush);
	::DeleteObject(m_hBackBrush);
	
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::ReconstructFont
//
// Description:		Helper function to build font after it was changed
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CLabel::ReconstructFont()
{
	m_font.DeleteObject();
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);

	ASSERT(bCreated);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::OnPaint
//
// Description:		Handles all the drawing code for the label
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			Called by Windows... not by USER
//					Probably needs tiding up a some point.
//					Different states will require this code to be reworked.
//
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////

void CLabel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	DWORD dwFlags = 0;

	CRect rc;
	GetClientRect(rc);
	CString strText;
	GetWindowText(strText);
	CBitmap bmp;


	///////////////////////////////////////////////////////
	//
	// Set up for double buffering...
	//
	CDC* pDCMem;

	if (!m_bTransparent)
	{
		pDCMem = new CDC;
		pDCMem->CreateCompatibleDC(&dc);
		bmp.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
		pDCMem->SelectObject(&bmp);
	}
	else
	{
		pDCMem = &dc;
	}

	UINT nMode = pDCMem->SetBkMode(TRANSPARENT);


	COLORREF crText = pDCMem->SetTextColor(m_crText);
	CFont *pOldFont = pDCMem->SelectObject(&m_font);


	// Fill in backgound if not transparent
	if (!m_bTransparent)
	{
		CBrush br;
		
		if (m_bState && m_Type == Background)
		{
			if (m_hBackBrush != NULL)
				br.Attach(m_hBackBrush);
			else
				br.Attach(m_hwndBrush);
		}
		else
		{
			if (m_hBackBrush != NULL)
				br.Attach(m_hBackBrush);
			else
				br.Attach(m_hwndBrush);
		}
				
		pDCMem->FillRect(rc,&br);

		br.Detach();
	}
	

	// If the text is flashing turn the text color on
	// then to the color of the window background.

	LOGBRUSH lb;
	ZeroMemory(&lb,sizeof(lb));
	::GetObject(m_hBackBrush,sizeof(lb),&lb);


	// Something to do with flashing
	if (!m_bState && m_Type == Text)
		pDCMem->SetTextColor(lb.lbColor);


	if (!(GetStyle() & SS_LEFTNOWORDWRAP))
		dwFlags |= DT_WORDBREAK;

	if (GetStyle() & SS_LEFT)
		dwFlags = DT_LEFT;

	if (GetStyle() & SS_RIGHT)
		dwFlags = DT_RIGHT;

	if (GetStyle() & SS_CENTER)
		dwFlags = DT_CENTER;



	// If the text centered make an assumtion that
	// the will want to center verticly as well
	if (GetStyle() & SS_CENTERIMAGE)
	{
		dwFlags = DT_CENTER;

		// Apply 
		if (strText.Find("\r\n") == -1)
		{
			dwFlags |= DT_VCENTER;

			// And because DT_VCENTER only works with single lines
			dwFlags |= DT_SINGLELINE; 
		}
	}

	//
	// 3333   DDDDD
	//     3  D    D
	//   33   D     D    E F X 
	//     3  D    D
	// 3333   DDDDD
	//
	//
	if (m_bRotation)
	{
		int nAlign = pDCMem->SetTextAlign (TA_BASELINE);

		CPoint pt;
		GetViewportOrgEx (pDCMem->m_hDC,&pt) ;
		SetViewportOrgEx (pDCMem->m_hDC,rc.Width() / 2, rc.Height() / 2, NULL) ;
		pDCMem->TextOut (0, 0, strText) ;
		SetViewportOrgEx (pDCMem->m_hDC,pt.x / 2, pt.y / 2, NULL) ;
		pDCMem->SetTextAlign (nAlign);
	}
	else
	{
		pDCMem->DrawText(strText,rc,dwFlags);
		if (m_bFont3d)
		{
			pDCMem->SetTextColor(RGB(255,255,255));

			if (m_3dType == Raised)
				rc.OffsetRect(-1,-1);
			else
				rc.OffsetRect(1,1);

			pDCMem->DrawText(strText,rc,dwFlags);
			m_3dType;

		}
	}

	// Restore DC's State
	pDCMem->SetBkMode(nMode);
	pDCMem->SelectObject(pOldFont);
	pDCMem->SetTextColor(crText);

	if (!m_bTransparent)
	{
		dc.BitBlt(0,0,rc.Width(),rc.Height(),pDCMem,0,0,SRCCOPY);
		delete pDCMem;
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::OnTimer
//
// Description:		Used in conjunction with 'FLASH' functions
//
// INPUTS:          Windows API
// 
// RETURNS:         Windows API
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CLabel::OnTimer(UINT nIDEvent) 
{

	m_bState = !m_bState;

	InvalidateRect(NULL,TRUE);
	UpdateWindow();
	
	CStatic::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::OnSetCursor
//
// Description:		Used in conjunction with 'LINK' function
//
// INPUTS:          Windows API
// 
// RETURNS:         Windows API
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
BOOL CLabel::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{

	if (m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::OnLButtonDown
//
// Description:		Called when a link is click on
//
// INPUTS:          Windows API
// 
// RETURNS:         Windows API
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CLabel::OnLButtonDown(UINT nFlags, CPoint point) 
{

	if (m_bNotifyParent)
	{
		CString strLink;

		GetWindowText(strLink);
		ShellExecute(NULL,"open",strLink,NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		// To use notification in parent window
		// Respond to a OnNotify in parent and disassemble the message
		//
		NMHDR nm;

		nm.hwndFrom = GetSafeHwnd();
		nm.idFrom  = GetDlgCtrlID();
		nm.code = NM_LINKCLICK;
		GetParent()->SendMessage(WM_NOTIFY,nm.idFrom,(LPARAM) &nm);
	}
		
	CStatic::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// THE FUNCTIONS START HERE :----
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetText
//
// Description:		Short cut to set window text - caption - label
//
// INPUTS:          Text to use
// 
// RETURNS:         Reference to this
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetText(const CString& strText)
{

	SetWindowText(strText);
	Invalidate(FALSE);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetTextColor
//
// Description:		Sets the text color 
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetTextColor(COLORREF crText)
{

	m_crText = crText;
	RedrawWindow();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontBold
//
// Description:		Sets the font ot bold 
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontBold(BOOL bBold)
{	

	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	ReconstructFont();
	RedrawWindow();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontUnderline
//
// Description:		Sets font underline attribue
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontUnderline(BOOL bSet)
{	
	m_lf.lfUnderline = bSet;
	ReconstructFont();
	RedrawWindow();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontItalic
//
// Description:		Sets font italic attribute
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontItalic(BOOL bSet)
{

	m_lf.lfItalic = bSet;
	ReconstructFont();
	RedrawWindow();
	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetSunken
//
// Description:		Sets sunken effect on border
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetSunken(BOOL bSet)
{

	if (!bSet)
		ModifyStyleEx(WS_EX_STATICEDGE,0,SWP_DRAWFRAME);
	else
		ModifyStyleEx(0,WS_EX_STATICEDGE,SWP_DRAWFRAME);
		
	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetBorder
//
// Description:		Toggles the border on/off
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetBorder(BOOL bSet)
{

	if (!bSet)
		ModifyStyle(WS_BORDER,0,SWP_DRAWFRAME);
	else
		ModifyStyle(0,WS_BORDER,SWP_DRAWFRAME);
		
	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontSize
//
// Description:		Sets the font size
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontSize(int nSize)
{

	CFont cf;
	LOGFONT lf;

	cf.CreatePointFont(nSize * 10, m_lf.lfFaceName);
	cf.GetLogFont(&lf);

	m_lf.lfHeight = lf.lfHeight;
	m_lf.lfWidth  = lf.lfWidth;

//	nSize*=-1;
//	m_lf.lfHeight = nSize;
	ReconstructFont();
	RedrawWindow();
	return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetBkColor
//
// Description:		Sets background color
//
// INPUTS:          Colorref of background color
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetBkColor(COLORREF crBkgnd)
{

	if (m_hBackBrush)
		::DeleteObject(m_hBackBrush);
	
	m_hBackBrush = ::CreateSolidBrush(crBkgnd);

	Invalidate(FALSE);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontName
//
// Description:		Sets the fonts face name
//
// INPUTS:          String containing font name
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontName(const CString& strFont)
{	

	strcpy(m_lf.lfFaceName,strFont);
	ReconstructFont();
	RedrawWindow();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::FlashText
//
// Description:		As the function states
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::FlashText(BOOL bActivate)
{

	if (m_bTimer)
		KillTimer(1);

	if (bActivate)
	{
		m_bState = FALSE;
		
		m_bTimer = TRUE;
		
		SetTimer(1,500,NULL);

		m_Type = Text;
	}
	else
		m_Type = None; // Fix

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::FlashBackground
//
// Description:		As the function states
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::FlashBackground(BOOL bActivate)
{

	if (m_bTimer)
		KillTimer(1);

	if (bActivate)
	{
		m_bState = FALSE;

		m_bTimer = TRUE;
		SetTimer(1,500,NULL);

		m_Type = Background;
	}

	return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetLink
//
// Description:		Indicates the string is a link
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
// NT ALMOND				26/08/99	1.2		Added flexbility of
//												Sending Click meessage to parent
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetLink(BOOL bLink,BOOL bNotifyParent)
{

	m_bLink = bLink;
	m_bNotifyParent = bNotifyParent;

	if (bLink)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetLinkCursor
//
// Description:		Sets the internet browers link
//
// INPUTS:          Handle of cursor
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetLinkCursor(HCURSOR hCursor)
{

	m_hCursor = hCursor;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetTransparent
//
// Description:		Sets the Label window to be transpaent
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetTransparent(BOOL bSet)
{

	m_bTransparent = bSet;
	InvalidateRect(NULL,TRUE);
	UpdateWindow();

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFont3D
//
// Description:		Sets the 3D attribute of the font.
//
// INPUTS:          True or false, Raised or Sunken
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFont3D(BOOL bSet,Type3D type)
{

	m_bFont3d = bSet;
	m_3dType = type;
	RedrawWindow();

	return *this;
}

void CLabel::OnSysColorChange() 
{

	if (m_hwndBrush)
		::DeleteObject(m_hwndBrush);

	m_hwndBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	
	RedrawWindow();
		
}



//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetRotationAngle
//
// Description:		Sets the 3D attribute of the font.
//
// INPUTS:          True or false, Raised or Sunken
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetRotationAngle(UINT nAngle,BOOL bRotation)
{
	// Arrrrh...
	// Your looking in here why the font is rotating, aren't you?
	// Well try setting the font name to 'Arial' or 'Times New Roman'
	// Make the Angle 180 and set bRotation to true.
	//
	// Font rotation _ONLY_ works with TrueType fonts...
	//
	// 
	m_lf.lfEscapement = m_lf.lfOrientation = (nAngle * 10);
	m_bRotation = bRotation;
	
	ReconstructFont();
	
	RedrawWindow();

	return *this;
}


