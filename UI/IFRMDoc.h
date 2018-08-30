// IFRMDoc.h : interface of the CIFRMDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IFRMDOC_H__665FDE8A_93D3_41F6_91AC_FA17851B9AEA__INCLUDED_)
#define AFX_IFRMDOC_H__665FDE8A_93D3_41F6_91AC_FA17851B9AEA__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CIFRMSrvrItem;

class CIFRMDoc : public CDocument
{
protected: // create from serialization only
	CIFRMDoc();
	DECLARE_DYNCREATE(CIFRMDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFRMDoc)
	protected:
	
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	

	virtual ~CIFRMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	

// Generated message map functions
protected:
	//{{AFX_MSG(CIFRMDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CIFRMDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFRMDOC_H__665FDE8A_93D3_41F6_91AC_FA17851B9AEA__INCLUDED_)
