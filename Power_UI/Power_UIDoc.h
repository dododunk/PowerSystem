// Power_UIDoc.h : interface of the CPower_UIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWER_UIDOC_H__AA84C250_F466_4002_B68D_9B445009F6C1__INCLUDED_)
#define AFX_POWER_UIDOC_H__AA84C250_F466_4002_B68D_9B445009F6C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPower_UIDoc : public CDocument
{
protected: // create from serialization only
	CPower_UIDoc();
	DECLARE_DYNCREATE(CPower_UIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPower_UIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPower_UIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPower_UIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWER_UIDOC_H__AA84C250_F466_4002_B68D_9B445009F6C1__INCLUDED_)
