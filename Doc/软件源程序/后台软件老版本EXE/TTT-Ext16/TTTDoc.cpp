// TTTDoc.cpp : implementation of the CTTTDoc class
//

#include "stdafx.h"
#include "TTT.h"

#include "TTTDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTTTDoc
extern CDWordArray array;

IMPLEMENT_DYNCREATE(CTTTDoc, CDocument)

BEGIN_MESSAGE_MAP(CTTTDoc, CDocument)
	//{{AFX_MSG_MAP(CTTTDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTTDoc construction/destruction

CTTTDoc::CTTTDoc()
{
}

CTTTDoc::~CTTTDoc()
{
 
}

BOOL CTTTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTTTDoc serialization

void CTTTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		
	}
	else
	{
		// TODO: add loading code here
		for(int i=0;i<50;i++)
		{
//	    	ar>>graph;
//		    array.Add(graph);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTTTDoc diagnostics

#ifdef _DEBUG
void CTTTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTTTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

