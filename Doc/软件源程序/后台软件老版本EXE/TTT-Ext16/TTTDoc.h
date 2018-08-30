// TTTDoc.h : interface of the CTTTDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTTDOC_H__7CAB494C_40E7_4FB4_A915_512B3239A5E0__INCLUDED_)
#define AFX_TTTDOC_H__7CAB494C_40E7_4FB4_A915_512B3239A5E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTTTDoc : public CDocument
{
protected: // create from serialization only
	CTTTDoc();
	DECLARE_DYNCREATE(CTTTDoc)

// Attributes
public:
//   CP9111 *m_pP9111;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTTDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTTTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTTTDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTTDOC_H__7CAB494C_40E7_4FB4_A915_512B3239A5E0__INCLUDED_)
