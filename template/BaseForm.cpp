#include "StdAfx.h"
#include "BaseForm.h"


IMPLEMENT_DYNAMIC(CBaseForm, CDialogEx)


CBaseForm::CBaseForm( UINT nIDTemplate,CWnd* pParent /*= NULL*/ ) : CDialogEx(nIDTemplate,pParent)
{
	//m_ret = 0;
}


CBaseForm::~CBaseForm(void)
{
}

CSize CBaseForm::GetDlgRectFromResource( int ResourceDlgID,HMODULE hmodule /*= GetModuleHandle(NULL)*/ )
{
	CSize size = CSize(-1,-1);
	
	HRSRC hDlg = ::FindResource(hmodule,MAKEINTRESOURCE(ResourceDlgID), (LPTSTR)RT_DIALOG);
	ASSERT(hDlg != NULL);

	HGLOBAL hResource = ::LoadResource(hmodule, hDlg);
	ASSERT(hResource != NULL);


#pragma message("this is a bug in windows see http://social.msdn.microsoft.com/Forums/en/vcgeneral/thread/0d6715c4-0f72-40d5-8758-a0fc2ac9fd1b")

#pragma pack(push, 1)
	typedef struct
	{
		WORD dlgVer;
		WORD signature;
		DWORD helpID;
		DWORD exStyle;
		DWORD style;
		WORD cDlgItems;
		short x;
		short y;
		short cx;
		short cy;
	} DLGTEMPLATEEX;



	DLGTEMPLATEEX  * pDlgTemplate = (DLGTEMPLATEEX  *) LockResource(hResource); 
	ASSERT(pDlgTemplate != NULL);

	ASSERT(pDlgTemplate->cx >0 && pDlgTemplate->cx < 3000 && pDlgTemplate->cy >0 && pDlgTemplate->cy < 3000);
	size = CSize(pDlgTemplate->cx,pDlgTemplate->cy);		
#pragma pack(pop)
	UnlockResource(hResource);
	FreeResource(hResource);

	return size;
}


BOOL CBaseForm::ShowInView( CFormView* pParent,ShowInPos pos)
{
//	CSize size = GetDlgRectFromResource(this->IDD,NULL);
	//pParent->SetScrollSizes()
	return FALSE;
}
