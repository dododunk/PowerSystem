// Power_UIView.cpp : implementation of the CPower_UIView class
//

#include "stdafx.h"
#include "Power_UI.h"

#include "Power_UIDoc.h"
#include "Power_UIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPower_UIView

IMPLEMENT_DYNCREATE(CPower_UIView, CFormView)

BEGIN_MESSAGE_MAP(CPower_UIView, CFormView)
	//{{AFX_MSG_MAP(CPower_UIView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPower_UIView construction/destruction

CPower_UIView::CPower_UIView()
	: CFormView(CPower_UIView::IDD)
{
	//{{AFX_DATA_INIT(CPower_UIView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CPower_UIView::~CPower_UIView()
{
}

void CPower_UIView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPower_UIView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CPower_UIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CPower_UIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CPower_UIView printing

BOOL CPower_UIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPower_UIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPower_UIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPower_UIView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CPower_UIView diagnostics

#ifdef _DEBUG
void CPower_UIView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPower_UIView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPower_UIDoc* CPower_UIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPower_UIDoc)));
	return (CPower_UIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPower_UIView message handlers
