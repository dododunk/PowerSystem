// credits.cpp : implementation file
//**************************************************************************

// NOTE: Be sure you have defined your bitmaps by assigning them a resource
//       id of a quoted string (i.e. "BITMAP1" instead of ID_BITMAP1) since 
//       you will be designating the bitmaps by their quoted resource string
//       in this file.

//       Be sure that you do not leave a space between the quoted bitmap
//       resource name and the \b identifier when setting up your array.
//       "BITMAP1\b" = correct
//       "BITMAP1 \b" = incorrect

//      Thanks to Gerry Shaw for submitting code to fix the redraw so that only
//      the actual display window refreshes each time instead of the entire 
//      dialog which was causing annoying flicker.

#include "stdafx.h"
#include "resource.h"
#include "creditsDlg.h"

#include<fstream> // 文件流 ++
#include<iostream> // 标准流++ 
#include<string> // 字符串对象++ 
using namespace std; // 使用std名字空间++

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define SCROLLAMOUNT				-1
#define DISPLAY_SLOW				70
#define DISPLAY_MEDIUM				40
#define DISPLAY_FAST				10
#define DISPLAY_SPEED				DISPLAY_MEDIUM

#define RED						RGB(255,0,0)
#define GREEN					RGB(0,255,0)
#define BLUE					RGB(0,0,255)
#define WHITE   				RGB(255,255,255)
#define YELLOW  				RGB(255,255,0)
#define TURQUOISE 				RGB(0,255,255)
#define PURPLE  				RGB(255,0,255)
#define BLACK       			RGB(0,0,0)

#define BACKGROUND_COLOR        BLACK
#define TOP_LEVEL_TITLE_COLOR	RED
#define TOP_LEVEL_GROUP_COLOR   YELLOW
#define GROUP_TITLE_COLOR       TURQUOISE
#define NORMAL_TEXT_COLOR		WHITE

// You can set font heights here to suit your taste
#define TOP_LEVEL_TITLE_HEIGHT	21		
#define TOP_LEVEL_GROUP_HEIGHT  19     
#define GROUP_TITLE_HEIGHT    	17     
#define	NORMAL_TEXT_HEIGHT		15



// these define the escape sequences to suffix each array line with. They
// are listed in order of descending font size.
#define TOP_LEVEL_TITLE			1 //'\n'
#define TOP_LEVEL_GROUP         2 //'\r'
#define GROUP_TITLE           	3 //'\t'
#define NORMAL_TEXT				0 //'\f' 
#define DISPLAY_BITMAP			'\b'

// Enter the text and bitmap resource string identifiers which are to
// appear in the scrolling list. Append each non-empty string entry with
// an escape character corresponding to the desired font effect. Empty
// strings do not get a font assignment.
// (see #defines above)
// 
// Array count. Make sure this keeps up with how many lines there are
// in the array!
#define ARRAYCOUNT		20

	ifstream inFile; 

//char *pArrCredit[] ;
 /*= { 	"工频畸变远程抄表系统1.90k版\n",
						"",
						"版权 (c) 2006 \f",
						"北京英康通用电力技术有限公司 \f",//	"All Rights Reserved \f",
						//	"BITMAP1\b",                  // MYBITMAP is a quoted bitmap resource 
						"电话:(010)62904513     邮编:100086\f",
						"",
						"",
						"",	
						"",
						"",	
						"－－－主要高科技产品－－－\t",
						"",
						"工频畸变远程抄表系统\t",
						//" \t",
						//" \f",
						//" \t",
					
						//" \f",
						//" \t",
					//	"",
					//	"",
					//	"",
					//	"\f",
					//	"  \t",
					//	"",
					//	" \f",
						" \f",
						" \f",
						"  ",
						"",
						"  \f",
						" \f",
						" \n ",
					//	"BITMAP1\b",  // BARGRAPH1 is a quoted bitmap resource 
						"以上产品全都由 \n",
						"北京英康通用电力技术有限公司 \n",
						"独自拥有知识产权 \n",
						"谢谢您的支持!",
						""
						};*/

/////////////////////////////////////////////////////////////////////////////
// CCredits dialog

CCreditsDlg::CCreditsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreditsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCredits)
	//}}AFX_DATA_INIT
	inFile.open("Company.txt"); // 打开文件 
}


void CCreditsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCredits)
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CCreditsDlg, CDialog)
	//{{AFX_MSG_MAP(CCredits)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCredits message handlers

void CCreditsDlg::OnOK() 
{
	KillTimer(DISPLAY_TIMER_ID);
	CDialog::OnOK();
}

//************************************************************************
//	 InitDialog
//
//	 	Setup the display rect and start the timer.
//************************************************************************
BOOL CCreditsDlg::OnInitDialog() 
{ 

	CDialog::OnInitDialog();

	//设置定时器,10秒钟
    SetTimer(12,10*1000,NULL);
	
	BOOL bRet;
    UINT nRet;

	nCurrentFontHeight = NORMAL_TEXT_HEIGHT;
	
	CClientDC dc(this);
	bRet = m_dcMem.CreateCompatibleDC(&dc);
	
	
	m_bProcessingBitmap=FALSE;
	
	nArrIndex=0;
	nCounter=1;
	nClip=0;
	m_bFirstTime=TRUE;
	m_bDrawText=FALSE;
	m_hBmpOld = 0;
	
	m_pDisplayFrame=(CWnd*)GetDlgItem(IDC_DISPLAY_STATIC);	


	// If you assert here, you did not assign your static display control
	// the IDC_ value that was used in the GetDlgItem(...). This is the
    // control that will display the credits.
	_ASSERTE(m_pDisplayFrame);
				 
	m_pDisplayFrame->GetClientRect(&m_ScrollRect);


	nRet = SetTimer(DISPLAY_TIMER_ID,DISPLAY_SPEED,NULL);
    _ASSERTE(nRet != 0);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//************************************************************************
//	 OnTimer
//
//	 	On each of the display timers, scroll the window 1 unit. Each 20
//      units, fetch the next array element and load into work string. Call
//      Invalidate and UpdateWindow to invoke the OnPaint which will paint 
//      the contents of the newly updated work string.
//************************************************************************
void CCreditsDlg::OnTimer(UINT nIDEvent) 
{
	string str[ARRAYCOUNT]; // 行字符串缓存 


	if( nIDEvent == 10)
	{
		KillTimer(10);
		CDialog::OnOK();
	}

	if (nIDEvent != DISPLAY_TIMER_ID)
	{
		CDialog::OnTimer(nIDEvent);
		return;
	}


	if(inFile.is_open())
	{ // 若成功打开文件 ++
	if (!m_bProcessingBitmap)
		if (nCounter++ % nCurrentFontHeight == 0)	 // every x timer events, show new line
		{
			nCounter=1;
			getline(inFile, str[nArrIndex], '\n'); //++
			//m_szWork = str[nArrIndex++].c_str();//pArrCredit[nArrIndex++];
			m_szWork.Format("%s",str[nArrIndex++].c_str());
			if (nArrIndex > ARRAYCOUNT-1)
			{

				nArrIndex=0;
			}
			nClip = 0;
			m_bDrawText=TRUE;
		}

	}	

	m_pDisplayFrame->ScrollWindow(0,SCROLLAMOUNT,&m_ScrollRect,&m_ScrollRect);
	nClip = nClip + abs(SCROLLAMOUNT);	
	
    CRect r;
    CWnd* pWnd = GetDlgItem(IDC_DISPLAY_STATIC);
    ASSERT_VALID(pWnd);
    pWnd->GetClientRect(&r);
    pWnd->ClientToScreen(r);
    ScreenToClient(&r);
    InvalidateRect(r,FALSE); // FALSE does not erase background

	CDialog::OnTimer(nIDEvent);
}


//************************************************************************
//	 OnPaint
//
//	 	Send the newly updated work string to the display rect.
//************************************************************************
void CCreditsDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	PAINTSTRUCT ps;
	CDC* pDc = m_pDisplayFrame->BeginPaint(&ps);
	
	pDc->SetBkMode(TRANSPARENT);


	//*********************************************************************
	//	FONT SELECTION
   	CFont m_fntArial;
	CFont* pOldFont;
	BOOL bSuccess;
	BOOL bUnderline;
	BOOL bItalic;


	if (!m_szWork.IsEmpty())
	switch (nArrIndex%4)//(m_szWork[m_szWork.GetLength()-1] )
		{
		case NORMAL_TEXT:
		default:
			bItalic = FALSE;
			bUnderline = FALSE;
			nCurrentFontHeight = NORMAL_TEXT_HEIGHT;
   			bSuccess = m_fntArial.CreateFont(NORMAL_TEXT_HEIGHT, 0, 0, 0, 
   								FW_THIN, bItalic, bUnderline, 0, 
   								ANSI_CHARSET,
                               	OUT_DEFAULT_PRECIS,
                               	CLIP_DEFAULT_PRECIS,
                               	PROOF_QUALITY,
                               	VARIABLE_PITCH | 0x04 | FF_DONTCARE,
                               	(LPSTR)"宋体");//(LPSTR)"Arial");
			pDc->SetTextColor(NORMAL_TEXT_COLOR);
			pOldFont  = pDc->SelectObject(&m_fntArial);
			break;

		case TOP_LEVEL_GROUP:
			bItalic = FALSE;
			bUnderline = FALSE;
			nCurrentFontHeight = TOP_LEVEL_GROUP_HEIGHT;
   			bSuccess = m_fntArial.CreateFont(TOP_LEVEL_GROUP_HEIGHT, 0, 0, 0, 
   								FW_BOLD, bItalic, bUnderline, 0, 
   								ANSI_CHARSET,
                               	OUT_DEFAULT_PRECIS,
                               	CLIP_DEFAULT_PRECIS,
                               	PROOF_QUALITY,
                               	VARIABLE_PITCH | 0x04 | FF_DONTCARE,
                               	(LPSTR)"宋体");//(LPSTR)"Arial");
			pDc->SetTextColor(TOP_LEVEL_GROUP_COLOR);
			pOldFont  = pDc->SelectObject(&m_fntArial);
			break;
		
		
		
		case GROUP_TITLE:
			bItalic = FALSE;
			bUnderline = FALSE;
			nCurrentFontHeight = GROUP_TITLE_HEIGHT;
   			bSuccess = m_fntArial.CreateFont(GROUP_TITLE_HEIGHT, 0, 0, 0, 
   								FW_BOLD, bItalic, bUnderline, 0, 
   								ANSI_CHARSET,
                               	OUT_DEFAULT_PRECIS,
                               	CLIP_DEFAULT_PRECIS,
                               	PROOF_QUALITY,
                               	VARIABLE_PITCH | 0x04 | FF_DONTCARE,
                               	(LPSTR)"宋体");//(LPSTR)"Arial");
			pDc->SetTextColor(GROUP_TITLE_COLOR);
			pOldFont  = pDc->SelectObject(&m_fntArial);
			break;
		
		
		case TOP_LEVEL_TITLE:
			bItalic = FALSE;
			bUnderline = TRUE;
			nCurrentFontHeight = TOP_LEVEL_TITLE_HEIGHT;
			bSuccess = m_fntArial.CreateFont(TOP_LEVEL_TITLE_HEIGHT, 0, 0, 0, 
								FW_BOLD, bItalic, bUnderline, 0, 
								ANSI_CHARSET,
	                           	OUT_DEFAULT_PRECIS,
	                           	CLIP_DEFAULT_PRECIS,
	                           	PROOF_QUALITY,
	                           	VARIABLE_PITCH | 0x04 | FF_DONTCARE,
	                           	(LPSTR)"宋体");//(LPSTR)"Arial");
			pDc->SetTextColor(TOP_LEVEL_TITLE_COLOR);
			pOldFont  = pDc->SelectObject(&m_fntArial);
			break;
		
		case DISPLAY_BITMAP:
			if (!m_bProcessingBitmap)
				{
				CString szBitmap = m_szWork.Left(m_szWork.GetLength()-1);
	   			if (!m_bmpWork.LoadBitmap((const char *)szBitmap))
					{
					CString str; 
					str.Format("Could not find bitmap resource \"%s\". "
                               "Be sure to assign the bitmap a QUOTED resource name", szBitmap); 
					KillTimer(DISPLAY_TIMER_ID); 
					MessageBox(str); 
					return; 
					}
				m_bmpCurrent = &m_bmpWork;
	   			m_bmpCurrent->GetObject(sizeof(BITMAP), &m_bmpInfo);
			
				m_size.cx = m_bmpInfo.bmWidth;	// width  of dest rect
				RECT workRect;
				m_pDisplayFrame->GetClientRect(&workRect);
				m_pDisplayFrame->ClientToScreen(&workRect);
				ScreenToClient(&workRect);
				// upper left point of dest
				m_pt.x = (workRect.right - 
							((workRect.right-workRect.left)/2) - (m_bmpInfo.bmWidth/2));
				m_pt.y = workRect.bottom;
				
				
				pBmpOld = m_dcMem.SelectObject(m_bmpCurrent);
				if (m_hBmpOld == 0)
					m_hBmpOld = (HBITMAP) pBmpOld->GetSafeHandle();
				m_bProcessingBitmap = TRUE;
				}
			break;

		}
	
	
	
	
	CBrush bBrush(BLACK);
	CBrush* pOldBrush;
	pOldBrush  = pDc->SelectObject(&bBrush);
	// Only fill rect comprised of gap left by bottom of scrolling window
	r=m_ScrollRect;
	r.top = r.bottom-abs(SCROLLAMOUNT); 
	pDc->DPtoLP(&r);
	
	if (m_bFirstTime)
		{
		m_bFirstTime=FALSE;
		pDc->FillRect(&m_ScrollRect,&bBrush);
		}
	else
		pDc->FillRect(&r,&bBrush);
	
	r=m_ScrollRect;
	r.top = r.bottom-nClip;
	
	
	if (!m_bProcessingBitmap)
		{
		int x = pDc->DrawText((const char *)m_szWork,m_szWork.GetLength()-1,&r,DT_TOP|DT_CENTER|
					DT_NOPREFIX | DT_SINGLELINE);	
		m_bDrawText=FALSE;
		}
	else
		{
    	dc.StretchBlt( m_pt.x, m_pt.y-nClip, m_size.cx, nClip, 
                   		&m_dcMem, 0, 0, m_bmpInfo.bmWidth-1, nClip,
                   		SRCCOPY );
		if (nClip > m_bmpInfo.bmHeight)
			{
			m_bmpWork.DeleteObject();
			m_bProcessingBitmap = FALSE;
			nClip=0;
			m_szWork.Empty();
			nCounter=1;
			}
		pDc->SelectObject(pOldBrush);
		bBrush.DeleteObject();
		m_pDisplayFrame->EndPaint(&ps);
		return;
		}
	
	
	pDc->SelectObject(pOldBrush);
	bBrush.DeleteObject();
	
	if (!m_szWork.IsEmpty())
		{
		pDc->SelectObject(pOldFont);
		m_fntArial.DeleteObject();
		}

	m_pDisplayFrame->EndPaint(&ps);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CCreditsDlg::OnDestroy() 
{
	inFile.close(); //++

	CDialog::OnDestroy();

	
    m_dcMem.SelectObject(CBitmap::FromHandle(m_hBmpOld));
    m_bmpWork.DeleteObject();

}

void CCreditsDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{  
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
   
}

void CCreditsDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	OnOK();
	CDialog::OnLButtonDown(nFlags, point);



}

