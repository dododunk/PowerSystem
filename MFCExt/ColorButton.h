#if !defined(AFX_COLORBUTTON_H__3342913E_7E9C_480D_853A_DF4528875309__INCLUDED_)
#define AFX_COLORBUTTON_H__3342913E_7E9C_480D_853A_DF4528875309__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{
// Construction
public:
	CColorButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	CBrush m_brush;
	void SetBackColor(COLORREF BackColor);

	virtual ~CColorButton();

	// Generated message map functions
protected:
	COLORREF m_BackColor;

	//{{AFX_MSG(CColorButton)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBUTTON_H__3342913E_7E9C_480D_853A_DF4528875309__INCLUDED_)
