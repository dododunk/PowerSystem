// LineLoss.cpp : implementation file
//

#include "stdafx.h"

#include "LineLossDlg.h"


#include "IFRMView.h"
#include "ParameterDlg.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineLoss dialog


CLineLossDlg::CLineLossDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLineLossDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineLoss)
	m_radios = 0;
	m_title = _T("");
	//}}AFX_DATA_INIT
	m_StrSql  = "";
	BeginTime = "";
	EndTime   = "";
}


void CLineLossDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineLoss)
	DDX_Control(pDX, IDC_ENDTIME, m_listend);
	DDX_Control(pDX, IDC_BEGINTIME, m_listbegin);
	DDX_Radio(pDX, IDC_RADIO1, m_radios);
	DDX_Text(pDX, IDC_TITLE, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineLossDlg, CDialog)
//{{AFX_MSG_MAP(CLineLoss)
ON_BN_CLICKED(IDC_TOTAL, OnTotal)
ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_CBN_SELCHANGE(IDC_BEGINTIME, OnSelchangeBegintime)
	ON_CBN_SELCHANGE(IDC_ENDTIME, OnSelchangeEndtime)
	ON_BN_CLICKED(IDC_RADIO41, OnRadio41)
	ON_BN_CLICKED(IDC_RADIO42, OnRadio42)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineLoss message handlers



BOOL CLineLossDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//初始化Combo
	InitializeCombo();

	//报表标题
	CTime t       = CTime::GetCurrentTime();
	GetCompanyNames = GetCompanyName();
	GetCompanyNames.TrimLeft();
    GetCompanyNames.TrimRight();
    m_title.Format("%s%d年%d月抄表清单",GetCompanyNames,t.GetYear(),t.GetMonth());
    
	m_GetDataname = "TB_EXCERPTION";
	UpdateData(FALSE);	
	//窗口居中
	CenterWindow();

	return TRUE;  
}

void CLineLossDlg::OnOK() 
{
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CLineLossDlg::InitializeCombo()
{   
	//打开数据库
	CDatabase   db;
	CString strSql;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//公司级开始
		CDaoRecordset m_CompanySet(m_pDatabase);
		m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT GARRISON_HALTTIME from TB_GARRISON order by GARRISON_HALTTIME "));
		
		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{
			strSql = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
			m_listbegin.AddString(strSql);
			m_listend.AddString(strSql);
			m_CompanySet.MoveNext();
		}
		m_CompanySet.Close();	
		//公司级完
		
		delete m_pDatabase;
		m_pDatabase = NULL; 
	
		//没有选项
		if(m_listbegin.GetCount() > 0  && m_listend.GetCount() > 0)
		{

			m_listbegin.SetCurSel(0);
		    m_listend.SetCurSel(m_listend.GetCount()-1);
			
			//得到起始时间和结束时间
			m_listbegin.GetLBText(0,BeginTime);
			m_listend.GetLBText(m_listend.GetCount() - 1,EndTime);

			BeginTime.TrimLeft();
			BeginTime.TrimRight();
			
			EndTime.TrimLeft();
			EndTime.TrimRight();
		}
		else
		{
			
			//没有发过驻留命令，则没有起始时间和结束时间
			MessageBox("没有起始时间和结束时间!"," ",MB_OK|MB_ICONWARNING);
			CWnd* pt = GetDlgItem(IDC_TOTAL);
			pt->EnableWindow(FALSE);
		}
		
	}
	
}


void CLineLossDlg::OnTotal() 
{
	
	UpdateData(TRUE);

	CString TableName,StrSql;
	
	m_title.TrimLeft();
    m_title.TrimRight();
	
	//如果长度大于100的话
	if(m_title.GetLength() >  100)
	{
        MessageBox("报表标题太长，应为1－50个汉字(含数字或英文字母)！"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	//如果长度为0的话
	if(m_title.GetLength() ==  0)
	{
        MessageBox("请输入报表标题，应为1－50个汉字(含数字或英文字母)！"," ",MB_OK|MB_ICONWARNING);
		return;
	}
	
	//标题长度
	BOOL m_GetChanged  = FALSE;

	for(int i = 0;i < m_title.GetLength();i ++)
	{
		char c = m_title.GetAt(i);
		
		//30  - 39  61-7A  41-5A
		if(!((c < 0x00 || c > 0xFF) || (c >= 0x30 && c <= 0x39) || (c >= 0x61 && c <= 0x7a) || (c >= 0x41 && c <= 0x5a)))
		{
		    m_GetChanged  = TRUE;
			break;
		}
	}
	
	if(m_GetChanged)
	{
	   MessageBox("为了方便存成EXCEL文件，报表标题\r\n只能限于英文、数字或汉字字符！"," ",MB_OK|MB_ICONWARNING);
	   return;   
	}

	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CWnd* pt = GetDlgItem(IDCANCEL);
	pt->EnableWindow(FALSE);

	//如果没有电价表
	if(m_radios == 0 || m_radios == 1)
	{

		if(CDataBaseInstance::GetAllRecordsCount("TB_ELECTRICITY","ALL") < 1)
		{
		
			CWnd* pt = GetDlgItem(IDCANCEL);
			pt->EnableWindow(TRUE);
           	MessageBox("此报表要用到电价表信息，请先在电价表中输入信息\r\n且和用户信息表中用电编号相对应再统计！"," ",MB_OK|MB_ICONWARNING);
			return;
		
		}

	}
	
	//处理换表
	if(pview->IsCurveTableExist("TB_GARRISONBAK"))
	{
		//删除原来的库表
		StrSql.Format("DROP TABLE TB_GARRISONBAK");
		CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	}

	//按照时间提取数据
	StrSql.Format("SELECT * INTO TB_GARRISONBAK FROM TB_GARRISON  WHERE GARRISON_HALTTIME='%s' OR GARRISON_HALTTIME='%s'",BeginTime,EndTime);
	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

	//把原来的模块号换现在的号
	StrSql.Format("UPDATE TB_GARRISONBAK SET  GARRISON_MODULENO=b.CHANGEAMMETER_MODULENO FROM TB_GARRISONBAK a,TB_CHANGEAMMETER b WHERE a.GARRISON_MODULENO=b.CHANGEAMMETER_MODULENOOLD");
    CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

    //有功电度,减差值
	StrSql.Format("UPDATE TB_GARRISONBAK SET GARRISON_WORKDEGREE = GARRISON_WORKDEGREE - b.CHANGEAMMETER_WORKDEGREE FROM TB_GARRISONBAK a,TB_CHANGEAMMETER b WHERE a.GARRISON_HALTTIME>b.CHANGEAMMETER_UPDATETIME AND a.GARRISON_MODULENO=b.CHANGEAMMETER_MODULENO");
    CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

	//统计各种参数
	if(m_radios == 1)
	{
		//手拉手有功总
	    StrSql.Format("UPDATE TB_GARRISONBAK SET GARRISON_WORKDEGREETOTAL = GARRISON_WORKDEGREETOTAL-b.CHANGEAMMETER_WORKDEGREETOTAL,\
		                                         GARRISON_LOSEDEGREE      = GARRISON_LOSEDEGREE-b.CHANGEAMMETER_LOSEDEGREE,\
											     GARRISON_LOSEDEGREETOTAL = GARRISON_LOSEDEGREETOTAL-b.CHANGEAMMETER_LOSEDEGREETOTAL,\
												 GARRISON_JFDL            = GARRISON_JFDL-b.CHANGEAMMETER_JFDL,\
												 GARRISON_FDL             = GARRISON_FDL -b.CHANGEAMMETER_FDL,\
												 GARRISON_PDL             = GARRISON_PDL -b.CHANGEAMMETER_PDL,\
												 GARRISON_GDL             = GARRISON_GDL -b.CHANGEAMMETER_GDL \
												 FROM TB_GARRISONBAK a,TB_CHANGEAMMETER b WHERE a.GARRISON_HALTTIME>b.CHANGEAMMETER_UPDATETIME AND a.GARRISON_MODULENO=b.CHANGEAMMETER_MODULENO");
	    CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	 
	}

    switch(m_radios)
	{
	case 0:
		{
			//生成抄表清单
			pview->FormChaoBiaoData(m_AppearCondtion,BeginTime,EndTime);
			TableName = "TB_EXCERPTION";
			break;
		}
	case 1:
		{	
			//生成各种参数统计表
			TableName = "TB_TOTAL";	
			CParameterDlg  dlg;
			if(dlg.DoModal() != IDOK)
			{
				pt->EnableWindow(TRUE);
				return;
			}	
			pview->ComingIntoBeing(m_AppearCondtion,BeginTime,EndTime,dlg.m_parameter1,dlg.m_parameter2,dlg.m_parameter3,dlg.m_parameter4,dlg.m_parameter5,dlg.m_parameter6,dlg.m_parameter7,dlg.m_parameter8);
			break;
		}
	case 2:
		{
			//变台供电量统计表
			TableName = "TB_ELECTRICITYTOTAL";
			SubSupply(m_AppearCondtion);
			break;
		}
	case 3:
		{	
			//开始线损统计
			pview->BeginTotalLoss(m_AppearCondtion,BeginTime,EndTime);
			TableName = "TB_ELECTRICITYLOSS";
			break;
		}
	case 4:
		{	
			TableName = "TB_WARN";	
			//生成报警报表
			pview->ElectricityWarning(m_AppearCondtion,BeginTime,EndTime);
			break;
		}	
	} 
	
	if(CDataBaseInstance::GetAllRecordsCount(TableName,"ALL") == 0)
	{
        pt->EnableWindow(TRUE);
		pview->status("");
		MessageBox("没有找到满足条件的数据！"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	//生成报表列表
	pview->InitGrid(TableName,BeginTime,EndTime);
	
	//报表标题
	pview->m_Grid.m_title = m_title;
	pview->m_Grid.AutoSize();

	//删除抄表库中原来的记录
	StrSql.Format("DELETE FROM %s",TableName);
    CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	
	//处理换表
	if(pview->IsCurveTableExist("TB_GARRISONBAK"))
	{
		//删除原来的库表
		StrSql.Format("DROP TABLE TB_GARRISONBAK");
		CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	}

	CDialog::OnOK();
}


//得到公司的授电量
//CString Order    所求字段名 TB_GARRISON.GARRISON_WORKDEGREE
//CString CompanyName  公司名
double CLineLossDlg::GetCompanyElc(CString Order,CString CompanyName)
{
    //打开数据库
	CString   strValue;
	CDatabase       db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db);
		CString     strSql;
		//统计总公司下的所有变电站的总表和
		strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=5",Order,CompanyName,BeginTime,EndTime);
		rs.Open(CRecordset::forwardOnly,strSql);
		//和
		rs.GetFieldValue((short)0,strValue);
		strValue.Format("%.2f",atof(strValue));	
		rs.Close( );
		db.Close( );
		return atof(strValue);
	}
	return 0;
	
}

//得到某变电站本身的总表值及下所有线总表的和
//CString FieldName       所求字段名命令 TB_GARRISON.有功电度
//CString CompanyName     公司名
//CString SubstationName  变电站名
//short   kinds           种类 0－－－本身的表值 1－－下面所有线路的表和
double CLineLossDlg::GetSubStaitonElc(CString Order,CString CompanyName, CString SubstationName,short kinds)
{
    //打开数据库
	CString   strValue;
	CDatabase       db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db);
		CString     strSql;
		if(kinds == 0)
		{
			//某变电站本身表
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=4",Order,CompanyName,SubstationName,BeginTime,EndTime);
			
		}
		else
		{
			//统计某变电站下所有线总表的和
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=3",Order,CompanyName,SubstationName,BeginTime,EndTime);
		}
		rs.Open(CRecordset::forwardOnly,strSql);
		//和
		rs.GetFieldValue((short)0,strValue);
		strValue.Format("%.2f",atof(strValue));
		rs.Close( );
		db.Close( );
		return atof(strValue);
	}
	return 0;
}

//得到某线路本身的总表值及下所有变台总表的和
//CString FieldName       所求字段名 TB_GARRISON.GARRISON_WORKDEGREE
//CString CompanyName     公司名
//CString SubstationName  变电站名
//CString LineName        线路名称
//short   kinds           种类 0－－－本身的表值 1－－下面所有变台的表和
double CLineLossDlg::GetLineElc(CString Order,CString CompanyName, CString SubstationName,CString LineName,short kinds)
{
	
    //打开数据库
	CString   strValue;
	CDatabase       db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db);
		CString     strSql;	
		
		if(kinds == 0)
		{
			//某线路本身表值
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=3",Order,CompanyName,SubstationName,LineName,BeginTime,EndTime);
		}
		else
		{
			//统计某变电站下所有线总表的和
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=2",Order,CompanyName,SubstationName,LineName,BeginTime,EndTime);
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		//和
		rs.GetFieldValue((short)0,strValue);
		strValue.Format("%.2f",atof(strValue));
		rs.Close( );
		db.Close( );
		return atof(strValue);
	}
	return 0;
}




long CLineLossDlg::GetRecords(CString SqlStr)
{
	
	CDatabase         dbs;
	CString           sql;
	CString strValue = ""; 

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
	{  
		//和CRecordset连上
		CRecordset rss(&dbs );
		SqlStr.TrimLeft();
		SqlStr.TrimRight();
        
		rss.Open(CRecordset::forwardOnly,SqlStr);
		
		//得到记录个数
	
		rss.GetFieldValue((short)0,strValue);
		//记录个数 atol(strValue); 
		rss.Close();
		dbs.Close();
		return atol(strValue);
	}
	return 0;
}

void CLineLossDlg::CheckNumbers()
{
	
	long begins = 0;
	long Ends   = 0;
	long Equals = 0; 
	CString  strSql;
	
	m_listbegin.GetLBText(m_listbegin.GetCurSel(),BeginTime);
	
	//统计开始时间的个数
	strSql.Format("SELECT count(*) FROM TB_GARRISON WHERE GARRISON_HALTTIME='%s'",BeginTime);
	begins = GetRecords(strSql);
    
	//统计结束时间的个数
	m_listend.GetLBText(m_listend.GetCurSel(),EndTime); 
    strSql.Format("SELECT count(*) FROM TB_GARRISON WHERE GARRISON_HALTTIME='%s'",EndTime);
	Ends   = GetRecords(strSql);
		
	strSql.Format("Select  COUNT(DISTINCT GARRISON_MODULENO) from TB_GARRISON WHERE GARRISON_HALTTIME='%s' OR GARRISON_HALTTIME='%s'",BeginTime,EndTime);
    Equals = GetRecords(strSql);


}

//得到变台的地址名称
CString CLineLossDlg::GetSubName(CString Sql)
{
	//打开数据库
	CDatabase           db;
	CString         strSql;
	CString       strValue;
	CString fieldname = "";
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		//和CRecordset连上
		CRecordset rs(&db );
		
		Sql.TrimLeft();
		Sql.TrimRight();
		
		if(Sql.IsEmpty())
		{
       	    strSql = "SELECT count(*) FROM TB_TRANSFORMER";
		}
		else
		{
			strSql.Format("SELECT count(*) FROM TB_TRANSFORMER WHERE %s",Sql);
			
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到记录个数
		CString strValue;
		rs.GetFieldValue((short)0,strValue);
		
		//记录个数
		long fields = atol(strValue); 
		rs.Close();
		
		if(Sql.IsEmpty())
		{
       	    strSql = "SELECT TRANSFORMER_POSITION FROM TB_TRANSFORMER";
		}
		else
		{
			strSql.Format("SELECT TRANSFORMER_POSITION FROM TB_TRANSFORMER WHERE %s",Sql);
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//读用户信息
		for(int j = 0;j < fields; j++)
		{
			rs.GetFieldValue((short)0,strValue);
			strValue.TrimLeft();
			strValue.TrimRight();
			
			fieldname = fieldname + strValue;
			
			//库下滑一个记录
			rs.MoveNext();
		}
		
		
		
		//关闭数据库
		rs.Close( );
		db.Close( );
	}
	
	if(!fieldname.IsEmpty())
	{
        fieldname = "【" + fieldname + "】";
	}
	return fieldname;
	
}


//抄表清单
void CLineLossDlg::OnRadio1() 
{
	m_radios  =   0;
	CTime t = CTime::GetCurrentTime();
	m_title.Format("%s%d年%d月用户抄表清单及电费台帐",GetCompanyNames,t.GetYear(),t.GetMonth());
	m_GetDataname = "TB_EXCERPTION";
	UpdateData(FALSE);
	
}

//台区线损统计报表
void CLineLossDlg::OnRadio10() 
{
	m_radios  =   3;
	CTime t = CTime::GetCurrentTime();
	m_title.Format("%s%d年%d月台区线损统计报表",GetCompanyNames,t.GetYear(),t.GetMonth());
	m_GetDataname = "TB_ELECTRICITYLOSS";
	UpdateData(FALSE);
	
}


//变台供电量统计表
void CLineLossDlg::OnRadio5() 
{
	m_radios  =   2;
	CTime t = CTime::GetCurrentTime();	
	m_title.Format("%s%d年%d月变台供电量统计表",GetCompanyNames,t.GetYear(),t.GetMonth());
	m_GetDataname =  "TB_ELECTRICITYTOTAL";
	UpdateData(FALSE);
}


//统计变台供电量 
void CLineLossDlg::SubSupply(CString m_Condtion)
{
		
	CDatabase                db;
	CString  m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,strsql;
	int    doors       =       0;//户数
	int    m_records   =       0;//记录数

   	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();


	//判断表是否存在
	if(pview->IsCurveTableExist("TB_TOTLE"))
	{
		//删除原来的表
		strsql.Format("DROP TABLE %s","TB_TOTLE");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);
	}
	
	//生成临时表
    strsql.Format("SELECT * INTO TB_TOTLE FROM TB_USER WHERE %s",m_Condtion);
    CDataBaseInstance::ExecuteDataBaseSQL(strsql);

	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//公司级开始
		CDaoRecordset m_CompanySet(m_pDatabase);
		strsql = "SELECT count(*)  FROM TB_TOTLE  GROUP BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO ORDER BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO";
		m_CompanySet.Open(dbOpenSnapshot,strsql);
		
		m_records = V_I4(&m_CompanySet.GetFieldValue(0));
        m_CompanySet.Close();
	
		strsql = "SELECT USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO FROM TB_TOTLE  GROUP BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO ORDER BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO";
        m_CompanySet.Open(dbOpenSnapshot,strsql);

	    pview->ShowProgressCtrl(TRUE);
        pview->SetProgressCtrlRange(0, m_records,1);
		
		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{
			m_CompanyName    = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
            m_STATIONNAME    = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(1));
            m_LINENAME       = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(2));
            m_TRANSFORMERNO  = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(3));
			
	        pview->status("正在计算变台:" + m_TRANSFORMERNO);
		
			//算出变台的各项值
			GetSubSupply(m_CompanyName, m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,m_TRANSFORMERNO,BeginTime,EndTime);

			m_CompanySet.MoveNext();
            pview->SetProgressCtrlSetIt();

		}

		m_CompanySet.Close();
		delete m_pDatabase;	
		
		//删除原来的表
		strsql.Format("DROP TABLE %s","TB_TOTLE");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);
		pview->ShowProgressCtrl(FALSE);
	}


}

//得到某变台供电量
//CString CompanyName     公司名
//CString SubstationName  变电站名
//int     SubNo           变台号  
//CString LineName        线路名称
//CString SubNo           变台号
//CString SubName         变台名
//CString BeginTime       开始时间
//CString EndTime         结束时间
void  CLineLossDlg::GetSubSupply(CString CompanyName, CString SubstationName, CString LineName, CString SubNo,CString SubName,CString BeginTime,CString EndTime)
{
	
	CString           strValue;
	CString             strSql;  
	long            fields = 0;
	CDatabase               db;	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		
		//和CRecordset连上
		CRecordset rs(&db);
		CString     str[5];
		
		//记录个数
		strSql.Format("SELECT COUNT(*) FROM TB_USER,TB_GARRISONBAK WHERE TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s' AND (TB_USER.USER_COMPANY='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4))",BeginTime,CompanyName,LineName,SubNo);//SubstationName,
		rs.Open(CRecordset::forwardOnly,strSql);
		rs.GetFieldValue((short)0,strSql);
		rs.Close();
		
		if(atoi(strSql) < 1)
		{	
			db.Close( );
			return;
		}
		
		//上月读数
		strSql.Format("SELECT SUM(TB_GARRISONBAK.GARRISON_WORKDEGREE) FROM TB_USER,TB_GARRISONBAK WHERE TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s' AND (TB_USER.USER_COMPANY='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4))",BeginTime,CompanyName,LineName,SubNo);//SubstationName,
		rs.Open(CRecordset::forwardOnly,strSql);
		rs.GetFieldValue((short)0,str[3]);
		rs.Close();	
		
		//本月读数
		strSql.Format("SELECT SUM(TB_GARRISONBAK.GARRISON_WORKDEGREE) FROM TB_USER,TB_GARRISONBAK WHERE TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s' AND (TB_USER.USER_COMPANY='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s'  AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4))",EndTime,CompanyName,LineName,SubNo);//SubstationName,
		rs.Open(CRecordset::forwardOnly,strSql);
		rs.GetFieldValue((short)0,str[4]);
		rs.Close();
		
		//某变台本身的表值
		strSql.Format("SELECT TB_USER.USER_AMMETERNO,TB_USER.USER_MULTIPLE FROM TB_USER,TB_GARRISONBAK WHERE TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s' AND (TB_USER.USER_COMPANY='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s')",BeginTime,CompanyName,LineName,SubNo);
		
		rs.Open(CRecordset::forwardOnly,strSql);
		//变台名称
		str[0]      =          SubName;
		//电表编号
		rs.GetFieldValue((short)0,str[1]);
		//倍率
		rs.GetFieldValue((short)1,str[2]);

		//算出数据，并写入库中
		strSql.Format("INSERT INTO TB_ELECTRICITYTOTAL(变台名称,电能表编号,上月读数,本月读数,倍率) VALUES ('%s','%s',%.2f,%.2f,%d)",SubName,str[1],atof(str[3]),atof(str[4]),atoi(str[2]));
		CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		
		//算出电量
		strSql = "UPDATE  TB_ELECTRICITYTOTAL SET 电量 = ROUND((本月读数-上月读数)*倍率,2)";
		CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		
		rs.Close( );
		db.Close( );
		
	}
	
	
}

//得到公司名称
CString CLineLossDlg::GetCompanyName()
{	
	
	CDatabase                db;
	CString  m_CompanyName = "";
	CString              strsql;

	//打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//公司级开始
		CDaoRecordset m_CompanySet(m_pDatabase);
		m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT USER_COMPANY from TB_USER order by USER_COMPANY "));
		
		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{
			m_CompanyName = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
			m_CompanySet.MoveNext();
		}
		m_CompanySet.Close();

		delete m_pDatabase;
		
	}
	return m_CompanyName;
}

//起始时间
void CLineLossDlg::OnSelchangeBegintime() 
{	
	m_listbegin.GetLBText(m_listbegin.GetCurSel(),BeginTime);
    BeginTime.TrimLeft();
	BeginTime.TrimRight();
}

//结束时间
void CLineLossDlg::OnSelchangeEndtime() 
{
    m_listend.GetLBText(m_listend.GetCurSel(),EndTime);
    EndTime.TrimLeft();
	EndTime.TrimRight();	
}

BOOL CLineLossDlg::PreTranslateMessage(MSG* pMsg) 
{
	return CDialog::PreTranslateMessage(pMsg);
}

void CLineLossDlg::OnRadio41() 
{
	m_radios  =   1;
	CTime t = CTime::GetCurrentTime();	
	m_title.Format("%s%d年%d月有功无功电压电流统计表",GetCompanyNames,t.GetYear(),t.GetMonth());
	m_GetDataname =  "TB_ELECTRICITYTOTAL";
	UpdateData(FALSE);
}



void CLineLossDlg::OnRadio42() 
{
	m_radios  =   4;
	CTime t = CTime::GetCurrentTime();	
	m_title.Format("%s%d年%d月电量报警统计表",GetCompanyNames,t.GetYear(),t.GetMonth());
	UpdateData(FALSE);
}
