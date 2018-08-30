// Power_UIView.h : interface of the CPower_UIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWER_UIVIEW_H__CB92F5B1_5EC8_4D5A_B415_61D11B211683__INCLUDED_)
#define AFX_POWER_UIVIEW_H__CB92F5B1_5EC8_4D5A_B415_61D11B211683__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPower_UIView : public CFormView
{
protected: // create from serialization only
	CPower_UIView();
	DECLARE_DYNCREATE(CPower_UIView)

public:
	//{{AFX_DATA(CPower_UIView)
	enum{ IDD = IDD_POWER_UI_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CPower_UIDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPower_UIView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPower_UIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPower_UIView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Power_UIView.cpp
inline CPower_UIDoc* CPower_UIView::GetDocument()
   { return (CPower_UIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWER_UIVIEW_H__CB92F5B1_5EC8_4D5A_B415_61D11B211683__INCLUDED_)
