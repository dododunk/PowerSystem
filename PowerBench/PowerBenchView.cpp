
// PowerBenchView.cpp : CPowerBenchView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PowerBench.h"
#endif

#include "PowerBenchDoc.h"
#include "PowerBenchView.h"
#include "BaseForm.h"
#include "BaseFormFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPowerBenchView

IMPLEMENT_DYNCREATE(CPowerBenchView, CFormView)

BEGIN_MESSAGE_MAP(CPowerBenchView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CPowerBenchView 构造/析构

CPowerBenchView::CPowerBenchView()
	: CFormView(CPowerBenchView::IDD),m_pChildTransForm(NULL)
{
	// TODO: 在此处添加构造代码

}

CPowerBenchView::~CPowerBenchView()
{
}

void CPowerBenchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CPowerBenchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CPowerBenchView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CString title = m_pChildTransForm->GetTitle();
	if(title != "")
	{
		this->GetDocument()->SetTitle(title);
	}
	else
	{
		//title = m_pChildTransForm->GetTitle();
		//this->SetWindowText(title);
		this->GetDocument()->SetTitle(title);	;
	}
	GetParent()->SetWindowText(title);
	ResizeParentToFit();

}

void CPowerBenchView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPowerBenchView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPowerBenchView 诊断

#ifdef _DEBUG
void CPowerBenchView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPowerBenchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPowerBenchDoc* CPowerBenchView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPowerBenchDoc)));
	return (CPowerBenchDoc*)m_pDocument;
}
#endif //_DEBUG


// CPowerBenchView 消息处理程序


int CPowerBenchView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_pChildTransForm = CBaseFormFactory::Instance().RunCurrentAction(this);
	CenterChildTransForm();
	
	//title = "shit";
		
	//this->GetParentFrame()->SetWindowText(title)		;
	return 0;
	
	
}


void CPowerBenchView::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	if(m_pChildTransForm != NULL)
	{
		m_pChildTransForm->DestroyWindow();
		delete m_pChildTransForm;
		m_pChildTransForm = NULL;
	}
	CFormView::PostNcDestroy();
}

void CPowerBenchView::CenterChildTransForm()
{
	if (m_pChildTransForm != NULL)
	{
		RECT merect;
		RECT childrect;

		this->GetClientRect(&merect);		
		m_pChildTransForm->GetWindowRect(&childrect);

		int mewidth = merect.right - merect.left;
		int childwidth = childrect.right - childrect.left;

		if (mewidth > childwidth)
		{
			int left = (mewidth - childwidth )/2;
			m_pChildTransForm->MoveWindow(left,0,childrect.right-childrect.left,childrect.bottom-childrect.top);
		}
	}
}


void CPowerBenchView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	CenterChildTransForm();
	// TODO: Add your message handler code here
}
