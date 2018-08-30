#include "stdafx.h"
#include "DataBaseInstance.h"


CDataBaseInstance::CDataBaseInstance(void)
{
}


CDataBaseInstance::~CDataBaseInstance(void)
{
}

CDatabase* CDataBaseInstance::GetDB()
{
	static CDatabase db;
	if(!db.IsOpen())
	{
		db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog);
	}
	return &db;
}

void CDataBaseInstance::ExecuteDataBaseSQL( CString StrSql )
{
	//CDatabase dbs;
	//if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
	//{	

	TRY
	{
		GetDB()->ExecuteSQL(StrSql);

	}
	CATCH(CDBException, e)
	{

	}
	END_CATCH

		//dbs.Close();
		//}
}

long CDataBaseInstance::GetAllRecordsCount( CString Table, CString Condtion )
{
	//打开数据库

	CString strSql;
	//和CRecordset连上
	CRecordset rs(GetDB());

	Condtion.TrimLeft();
	Condtion.TrimRight();

	if(Condtion == "ALL" || Condtion == "")
	{
		strSql.Format("SELECT count(*) FROM %s",Table);
	}
	else
	{
		strSql.Format("SELECT count(*) FROM %s  WHERE %s",Table,Condtion);
	}

	try
	{
		rs.Open(CRecordset::forwardOnly,strSql);
	}
	catch(CDBException* e) 
	{
		e->Delete();
		rs.Close();
		//关闭数据库

		::MessageBox(NULL,"查询条件错误，数据表查询出现错误！\r\n如果是字段值为字符，请加上单引号！"," ",MB_OK|MB_ICONWARNING);
		return  -1;
	}

	//得到记录个数
	rs.GetFieldValue((short)0,strSql);
	rs.Close();
	//返回记录个数
	return atol(strSql); 
}

//得到模块个数
long CDataBaseInstance::Getmoduls( CString m_totalsql )
{
	//打开数据库
	
	CString      str = "";

	
		//和CRecordset连上
		CRecordset   rs(GetDB());
		m_totalsql.TrimLeft();
		m_totalsql.TrimRight();


		if(m_totalsql == "ALL")
		{
			str = "Select COUNT(DISTINCT USER_MODULENO/100) from TB_USER";
		}
		else
		{
			str.Format("Select COUNT(DISTINCT USER_MODULENO/100) from TB_USER WHERE %s",m_totalsql);
		}

		/*
		str = "Select COUNT(DISTINCT  CAST(USER_MODULENO AS INT)/100) from TB_USER";
		*/

		rs.Open(CRecordset::forwardOnly,str);

		//得到记录个数
		rs.GetFieldValue((short)0,str);
		rs.Close();

		//关闭数据库
	//	dbs.Close();
	

	//返回记录个数
	return atol(str);
}

