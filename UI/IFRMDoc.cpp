// IFRMDoc.cpp : implementation of the CIFRMDoc class
//

#include "stdafx.h"
#include "IFRMDoc.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFRMDoc

IMPLEMENT_DYNCREATE(CIFRMDoc, CDocument)

BEGIN_MESSAGE_MAP(CIFRMDoc, CDocument)
	





END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CIFRMDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CIFRMDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IIFRM to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {289B6134-D862-4066-9E9C-7A3A163EEE8B}
static const IID IID_IIFRM =
{ 0x289b6134, 0xd862, 0x4066, { 0x9e, 0x9c, 0x7a, 0x3a, 0x16, 0x3e, 0xee, 0x8b } };

BEGIN_INTERFACE_MAP(CIFRMDoc, CDocument)
	INTERFACE_PART(CIFRMDoc, IID_IIFRM, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFRMDoc construction/destruction

CIFRMDoc::CIFRMDoc()
{
	// Use OLE compound files
	
}

CIFRMDoc::~CIFRMDoc()
{
	
}

BOOL CIFRMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CIFRMDoc serialization

void CIFRMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CDocument enables serialization
	//  of the container document's COleClientItem objects.
	CDocument::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CIFRMDoc diagnostics

#ifdef _DEBUG
void CIFRMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIFRMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIFRMDoc commands
