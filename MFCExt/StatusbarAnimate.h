#if !defined(AFX_StatusbarAnimate_H__6D425C96_266E_11D3_842C_00A0C9422E56__INCLUDED_)
#define AFX_StatusbarAnimate_H__6D425C96_266E_11D3_842C_00A0C9422E56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusbarAnimate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatusbarAnimate window
#include "MFCExtDefiniton.h"
class MFCEXTAPI CStatusbarAnimate : public CAnimateCtrl
{
// Construction
public:
	DECLARE_DYNAMIC(CStatusbarAnimate)
	CStatusbarAnimate();

// Attributes
public:
protected:
	int		m_nPane;
	CRect	m_Rect;

// Operations
public:
	BOOL Create( UINT nIDanimation, int nPane = 1 );
protected:
	CStatusBar *GetStatusBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusbarAnimate)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStatusbarAnimate();

	// Generated message map functions
protected:
	BOOL Resize();
	//{{AFX_MSG(CStatusbarAnimate)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_StatusbarAnimate_H__6D425C96_266E_11D3_842C_00A0C9422E56__INCLUDED_)
