#if !defined(AFX_HOVEREDIT_H__372AC76D_6B84_435C_8300_9519EB021C8C__INCLUDED_)
#define AFX_HOVEREDIT_H__372AC76D_6B84_435C_8300_9519EB021C8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HoverEdit.h : header file
// Modified by jingzhou xu	

#include "TrackControl.h"
#include "MFCExtDefiniton.h"
/////////////////////////////////////////////////////////////////////////////
// CHoverEdit window

class MFCEXTAPI CHoverEdit : public CTrackControl<CEdit>
{
// Construction
public:
	CHoverEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHoverEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void OnHoverLeave();
	virtual void OnHoverEnter();
	virtual ~CHoverEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHoverEdit)
	afx_msg void OnNcPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	inline void Redraw();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOVEREDIT_H__372AC76D_6B84_435C_8300_9519EB021C8C__INCLUDED_)
