#if !defined(AFX_DIALOG9999A_H__D41DCE6A_4FFE_45B9_B16C_BA0EC5846245__INCLUDED_)
#define AFX_DIALOG9999A_H__D41DCE6A_4FFE_45B9_B16C_BA0EC5846245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog9999A.h : header file
//
#include"BaseForm.h"
//#include "dlgutils.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CD9999A dialog

class CD9999A : public CBaseForm
{
	// Construction
public:
	CD9999A(CWnd* pParent = NULL);   // standard constructor
	virtual ~CD9999A();;
	virtual CString	GetActionName();
	virtual CString GetFormName();
	int	RunTransAction(void *FORM);
	
	// Dialog Data
	//{{AFX_DATA(CD9999A)
	enum { IDD = IDD_DIALOG_D9999A };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	BOOL Initialize();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD9999A)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	virtual BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(CD9999A)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG9999A_H__D41DCE6A_4FFE_45B9_B16C_BA0EC5846245__INCLUDED_)
