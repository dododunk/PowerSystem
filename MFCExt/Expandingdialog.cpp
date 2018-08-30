// ExpandingDialog.cpp : implementation file
//
// MFC Expanding/Contracting Dialog Implementation
//
// Written by Daniel G. Hyams
//      dhyams@ebicom.net or dhyams@altavista.net
//
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. If the source code in this file is used in 
// any  commercial application then a statement along the lines of 
// "Portions copyright (c) Daniel G. Hyams, 1998" must be included in 
// the startup banner, "About" box or printed documentation. An email 
// letting me know that you are using it would be nice as well. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// 
// Please use and enjoy, and let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into 
// this file. 
//
// History: 1.0     8/6/98
//        
//            
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <windowsx.h>
#include "ExpandingDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExpandingDialog dialog

CExpandingDlg::CExpandingDlg(UINT nIDTemplate,CWnd* pParent,int nIDFrame,int nIDButton,
								   LPCTSTR strExpand,LPCTSTR strContract,int bAllowContract) 
				 : CDialog(nIDTemplate, pParent)
				 
{
	//{{AFX_DATA_INIT(CExpandingDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_strExpand = strExpand;
	m_strContract = strContract;
	m_nIDFrame = nIDFrame;
	m_nIDButton = nIDButton;
	m_bExpanded = TRUE;
	m_bAllowContract = bAllowContract;

	m_pSize = NULL;
}

CExpandingDlg::~CExpandingDlg()
{
	delete m_pSize;
}


void CExpandingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpandingDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpandingDlg, CDialog)
	//{{AFX_MSG_MAP(CExpandingDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpandingDialog message handlers

void CExpandingDlg::ExpandBox(BOOL fExpand)
{
	// if the dialog is already in the requested state, return
	// immediately.
	if (fExpand == m_bExpanded) return;

	CRect rcWnd, rcDefaultBox, rcChild, rcIntersection;
	CWnd * wndChild=NULL;
	CWnd * wndDefaultBox=NULL;
	
	// get the window of the button 
	CWnd * pCtrl = GetDlgItem(m_nIDButton);
	if (pCtrl==NULL) return;

	wndDefaultBox = GetDlgItem(m_nIDFrame);
	if (wndDefaultBox==NULL) return;

	// retrieve coordinates for the default child window
	wndDefaultBox->GetWindowRect(&rcDefaultBox);

	// enable/disable all of the child window outside of the default box.
	wndChild = GetTopWindow();

	for ( ; wndChild != NULL; wndChild = wndChild->GetWindow(GW_HWNDNEXT))
	{
		// get rectangle occupied by child window in screen coordinates.
		wndChild->GetWindowRect(&rcChild);

		if (!rcIntersection.IntersectRect(&rcChild,&rcDefaultBox))
		{
			wndChild->EnableWindow(fExpand);
		}
	}

	if (!fExpand)  // we are contracting
	{
		_ASSERT(m_bExpanded);
		GetWindowRect(&rcWnd);
		if (m_pSize == NULL)
		{
			// this is the first time we are being called to shrink the dialog
			// box.  The dialog box is currently in its expanded size and we must
			// save the expanded width and height so that it can be restored
			// later when the dialog box is expanded.
			m_pSize = new CSize;
			m_pSize->cx = rcWnd.right - rcWnd.left;
			m_pSize->cy = rcWnd.bottom - rcWnd.top;

			// we also hide the default box here so that it is not visible
			wndDefaultBox->ShowWindow(SW_HIDE);
		}

		// shrink the dialog box so that it encompasses everything from the top,
		// left up to and including the default box.
		SetWindowPos(NULL,0,0,
			rcDefaultBox.right - rcWnd.left, 
			rcDefaultBox.bottom - rcWnd.top,
			SWP_NOZORDER|SWP_NOMOVE);

		pCtrl->SetWindowText(m_strExpand);

		// record that the dialog is contracted.
		m_bExpanded = FALSE;
	}
	else // we are expanding
	{
		_ASSERT(!m_bExpanded);
		_ASSERT(m_pSize != NULL);
		SetWindowPos(NULL,0,0,m_pSize->cx,m_pSize->cy,SWP_NOZORDER|SWP_NOMOVE);

		// make sure that the entire dialog box is visible on the user's
		// screen.
		SendMessage(DM_REPOSITION,0,0);

		if (m_bAllowContract)
		{
			pCtrl->SetWindowText(m_strContract);
		}
		else
		{
			pCtrl->EnableWindow(FALSE);
		}

		// record that the dialog is expanded
		m_bExpanded = TRUE;
	}
}
 


void CExpandingDlg::OnClickAdvanced() 
{
	Expand(!m_bExpanded);
}

BOOL CExpandingDlg::Expand(BOOL bExpand)
{
	BOOL bShouldExpand;

	// if the current state matches the flag passed into this
	// routine, then there is no need to do anything.  Note that
	// the virtual functions OnDialogExpanding and OnDialogExpanded
	// are not called.
	if (bExpand == m_bExpanded) return TRUE;

	// call the virtual function to see if it is OK to expand the dialog.
	bShouldExpand = OnDialogExpanding(m_bExpanded);

	
	// if OnDialogExpanding returns OK (TRUE), then call the appropriate
	// functions to expand the dialog.
	if (bShouldExpand)
	{
		ExpandBox(bExpand);

		// set the focus to the desired control
		CWnd * pCtrl;
		pCtrl = GetDlgItem(m_nIDButton);
		if (pCtrl != NULL)
		{
			GetNextDlgTabItem(pCtrl,0)->SetFocus();
		}

		// call the notification for the post-expand
		OnDialogExpanded(m_bExpanded);
	}

	return(m_bExpanded == bExpand);
}


BOOL CExpandingDlg::OnDialogExpanding(BOOL /*bExpanded*/) 
{
	return (TRUE);
}

void CExpandingDlg::OnDialogExpanded(BOOL /*bExpanded*/) 
{
	return;
}



BOOL CExpandingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// during initialization, before any windows are shown, shrink the
	// dialog box so that only the default portion is shown.
	ExpandBox(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CExpandingDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	HWND hwndCtl;
	int id;
	UINT codeNotify;

	// crack the WM_COMMAND message
	id = GET_WM_COMMAND_ID(wParam,lParam);
	hwndCtl = GET_WM_COMMAND_HWND(wParam,lParam);
	codeNotify = GET_WM_COMMAND_CMD(wParam,lParam);
	
	// if the "Advanced" button was clicked, then call the 
	// message handler.
	if ((id == m_nIDButton)&&(codeNotify==BN_CLICKED))
	{
		OnClickAdvanced();
	}
	return CDialog::OnCommand(wParam, lParam);
}
