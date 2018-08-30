#if !defined(AFX_EXPANDINGDIALOG_H__CC371CE2_1DD1_11D2_96D3_841605C10627__INCLUDED_)
#define AFX_EXPANDINGDIALOG_H__CC371CE2_1DD1_11D2_96D3_841605C10627__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "MFCExtDefiniton.h"
class MFCEXTAPI CExpandingDlg : public CDialog
{
// Construction and destruction
public:
	CExpandingDlg(
		UINT nIDTemplate,
		CWnd* pParent,
		int nIDFrame,
		int nIDButton,
		LPCTSTR strExpand   = _T("ÏÔÊ¾°ïÖú"),
		LPCTSTR strContract = _T("Òþ²Ø°ïÖú"),
		BOOL bAllowContract = TRUE
		);
		
	virtual ~CExpandingDlg();

public:
	// a public function so that the dialog can query whether or not
	// we are in "advanced" mode.
	BOOL IsExpanded() const {return m_bExpanded;};
	
	// allow the user to expand or contract the dialog whenever they
	// please.  This is only needed in extreme circumstances, when the
	// dialog should expand or contract based on something else besides
	// the "Advanced" button.
	BOOL Expand(BOOL bExpand);
   	void ExpandBox(BOOL fExpand);
	// a virtual notification function so that the expanding or contracting
	// can be aborted if need be.  The function should return TRUE if the
	// expanding should happen, or FALSE if it should not.
	virtual BOOL OnDialogExpanding(BOOL bExpanded);

	// a virtual notification function that is called after the expansion
	// takes place
	virtual void OnDialogExpanded(BOOL bExpanded);

// Dialog Data
	//{{AFX_DATA(CExpandingDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpandingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	



// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExpandingDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

private:
	// property data
	CString m_strExpand;	// string to put on the expand/contract button, when
							// the dialog is currently contracted.
	CString m_strContract;	// string to pu on the expand/contract button, when
							// the dialog is currently expanded.
	int m_nIDFrame;			// resource ID of the frame that defines the contracted
							// dimensions of the dialog.
	int m_nIDButton;		// resource ID of the expand/contract button on the 
							// dialog
	BOOL m_bAllowContract;	// whether or not to allow the user to contract the dialog
							// after expanding it for the first time.

	// state data
	CSize * m_pSize;		// records the original size of the dialog before 
							// contraction
	BOOL m_bExpanded;		// records whether the dialog is currently expanded or not.

private:
	void OnClickAdvanced();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPANDINGDIALOG_H__CC371CE2_1DD1_11D2_96D3_841605C10627__INCLUDED_)
