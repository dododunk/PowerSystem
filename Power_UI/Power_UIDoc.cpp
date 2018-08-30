// Power_UIDoc.cpp : implementation of the CPower_UIDoc class
//

#include "stdafx.h"
#include "Power_UI.h"

#include "Power_UIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPower_UIDoc

IMPLEMENT_DYNCREATE(CPower_UIDoc, CDocument)

BEGIN_MESSAGE_MAP(CPower_UIDoc, CDocument)
	//{{AFX_MSG_MAP(CPower_UIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPower_UIDoc construction/destruction

CPower_UIDoc::CPower_UIDoc()
{
	// TODO: add one-time construction code here

}

CPower_UIDoc::~CPower_UIDoc()
{
}

BOOL CPower_UIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPower_UIDoc serialization

void CPower_UIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPower_UIDoc diagnostics

#ifdef _DEBUG
void CPower_UIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPower_UIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPower_UIDoc commands
