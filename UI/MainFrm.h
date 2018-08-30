// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__81B06FF7_CF44_4946_BF3C_61D3E0BE74D2__INCLUDED_)
#define AFX_MAINFRM_H__81B06FF7_CF44_4946_BF3C_61D3E0BE74D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyDialogBar.h"
#include "MyDialogDataBar.h"
#include "EnBitmap.h"
#include "BtnST.h"
#include "StatusbarAnimate.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsAnimationActive();
	void StartAnimation( UINT id, int nPane =1 );
	void StopAnimation();
	CStatusbarAnimate* m_pAnimate;
	CButtonST    m_wndAboutButton;
	CMyDialogBar      m_wndMyDialogBar;
	CMyDialogDataBar  m_wndMyDialogData;
	CMenu             m_pVicinity; //本地菜单
	CMenu         m_pLongDistance; //远程菜单
	void ShowProgressCtrl(BOOL m_IsShow);
	CProgressCtrl m_progressBar;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
    CToolBar      m_wndToolBar;
    // CToolBar24    m_wndToolBar;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnClose();
	afx_msg void OnShowdialogbar();
	afx_msg void OnViewStatusBar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_IsShowProgressCtrl;
	BOOL m_bCreated;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__81B06FF7_CF44_4946_BF3C_61D3E0BE74D2__INCLUDED_)
