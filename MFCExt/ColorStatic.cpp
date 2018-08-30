// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ColorStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorStatic

CColorStatic::CColorStatic()
{
	m_TextColor=RGB(0,0,0);
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatic message handlers



int CColorStatic::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}

void CColorStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	dc.SetBkColor(m_BackColor);
	dc.SetBkMode(TRANSPARENT);
	CFont *pFont=GetParent()->GetFont();
	CFont *pOldFont;
	pOldFont=dc.SelectObject(pFont);
	dc.SetTextColor(m_TextColor);
	dc.DrawText(m_strCaption,&rect,DT_CENTER);
	dc.SelectObject(pOldFont);

	// Do not call CStatic::OnPaint() for painting messages
}

void CColorStatic::Create(CString strCaption, COLORREF BackColor)
{
	
	
}

void CColorStatic::SetCaption(CString strCaption)
{
	m_strCaption=strCaption;
}

void CColorStatic::SetBackColor(COLORREF BackColor)
{
	m_BackColor=BackColor;
}

void CColorStatic::SetTextColor(COLORREF TextColor)
{
	m_TextColor=TextColor;
}
