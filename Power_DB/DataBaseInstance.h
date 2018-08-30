#pragma once
#include "Power_DBDefinition.h"
class POWERDBAPI CDataBaseInstance
{
public:
	static CDatabase* GetDB();
	static void ExecuteDataBaseSQL(CString StrSql);

	//得到某一表的所有记录数
	static long GetAllRecordsCount(CString Table, CString Condtion = "");


	//得到模块个数
	static long Getmoduls(CString  m_totalsql);





private:
	CDataBaseInstance(void);
	~CDataBaseInstance(void);
};

