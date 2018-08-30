// Dialog9999A.cpp : implementation file
//

#include "stdafx.h"
#include "D9999A.h"


/////////////////////////////////////////////////////////////////////////////
// CD9999A dialog


CD9999A::CD9999A(CWnd* pParent /*=NULL*/)
: CBaseForm(CD9999A::IDD, pParent)
{
	//{{AFX_DATA_INIT(CD9999A)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


CD9999A::~CD9999A()
{
	
}
void CD9999A::DoDataExchange(CDataExchange* pDX)
{
	CBaseForm::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CD9999A)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

CString	CD9999A::GetActionName()
{
	return _T("Trans9999Action");
}

CString CD9999A::GetFormName()
{
//	ZeroMemory()
	return _T("CD9999A");
}


BOOL CD9999A::Initialize()
{
	//0.调用基类初始化函数(主要设置各种控件的默认属性)
	if(CBaseForm::Initialize() == FALSE)
	{
		return FALSE;
	}	



	return TRUE;
}

BOOL CD9999A::OnInitDialog()
{
	CBaseForm::OnInitDialog();
	//TO DO 界面初始化的内容较多,因此提取出一个Initialize函数.
	if (Initialize() == FALSE)
	{
		return FALSE;
	}
	
	
	return TRUE;
}

BEGIN_MESSAGE_MAP(CD9999A, CBaseForm)
//{{AFX_MSG_MAP(CD9999A)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////

int	CD9999A::RunTransAction(void *FORM)
{
	//TO DO 这边添加业务...
	
	
	
	
	
	
	//由于无法把结果传到外层，因此使用m_ret变量保存.框架程序可以用CBaseForm::GetReturnCode()获取此值
	this->SetReturnCode(SUCCESS);	
	return m_ret;
}
