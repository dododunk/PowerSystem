#include "stdafx.h"
#include "RuntimeAccount.h"


CRuntimeAccount::CRuntimeAccount(void)
{
}


CRuntimeAccount::~CRuntimeAccount(void)
{
}

CString CRuntimeAccount::GetType( AccountPrivilege privilege )
{
	CString UseName;
	switch(privilege)
	{
	case 0:
		{
			UseName = "高级管理员";
			break;
		}
	case 1:
		{
			UseName = "普通管理员";
			break;
		}
	case 2:
		{
			UseName = "高级用户";
			break;
		}
	case 3:
		{
			UseName = "普通用户";
			break;
		}
	}
	return UseName;
}

CRuntimeAccount::AccountPrivilege CRuntimeAccount::GetCurrentPrivilege()
{
	static AccountPrivilege val = AccountPrivilege::AdvancedAdministrator;
	return val;
}
