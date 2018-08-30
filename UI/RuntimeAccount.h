#pragma once
class CRuntimeAccount
{
public:
	enum AccountPrivilege
	{
		AdvancedAdministrator=0,
		Administrator =1 ,
		AdvancedUser=2,
		User=3,
	};
	static AccountPrivilege GetCurrentPrivilege();

	
	static CString GetType(AccountPrivilege privilege);
private:
	CRuntimeAccount(void);
	~CRuntimeAccount(void);
};

