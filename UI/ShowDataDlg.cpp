// ShowData.cpp : implementation file
//

#include "stdafx.h"

#include "ShowDataDlg.h"

#include "MainFrm.h"
#include "IFRMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowData dialog


CShowDataDlg::CShowDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowData)
	m_radio3 = 0;
	m_radio  = 0;
	//}}AFX_DATA_INIT
}


void CShowDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowData)
	DDX_Radio(pDX, IDC_RADIO3, m_radio3);
	DDX_Control(pDX, IDC_REMOTEDATACTLS, m_remotedatactrl);
	DDX_Control(pDX, IDC_DBGRIDS, m_dbgrid);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowDataDlg, CDialog)
	//{{AFX_MSG_MAP(CShowData)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(ID_SAVEDATA, OnSavedata)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowData message handlers

//CString   m_SelectStr  用户数据选择范围 
//CString   m_DateRange  数据时间范围
void CShowDataDlg::DataSort(CString m_SelectStr,CString m_DateRange)
{
	UpdateData(TRUE);
	CString     fieldname,strSql,sqlstr;
	CString     StrFields,m_RecordStr,m_modulestr;
	CString        StrTime,m_sequence;   
	CStringArray         m_FieldArray;
	
	if(m_radio3 == 0)
	{
		//升序
        m_sequence = "ASC";
	}
	else
	{
		//降序
		m_sequence = "DESC";
	}
	
	//按表卡号排序
	if(whichsel < 4)
	{
		whichsel  =  4;
	}
	
	m_NameArray.RemoveAll(); 
	
	//得到用户表的所有字段
	m_FieldArray.Add("TB_USER.USER_COMPANY");       //公司名称
	m_NameArray.Add("公司名称");                    
	m_FieldArray.Add("TB_USER.USER_STATIONNAME");   //变电站名称
    m_NameArray.Add("变电站名称");
	m_FieldArray.Add("TB_USER.USER_LINENAME");      //线路名称
	m_NameArray.Add("线路名称");
	m_FieldArray.Add("TB_USER.USER_TRANSFORMERNO"); //变台号
    m_NameArray.Add("变台名称");
	m_FieldArray.Add("TB_USER.USER_NO");            //用户编号
	m_NameArray.Add("用户编号");
	m_FieldArray.Add("TB_USER.USER_AMMETERNO");     //电表编号
	m_NameArray.Add("电表编号");

	if(m_Select[7])
	{
		m_FieldArray.Add("TB_USER.USER_NAME");     //用户名
		m_NameArray.Add("用户名");
		m_FieldArray.Add("TB_USER.USER_ADDRESS");  //用户地址
		m_NameArray.Add("用户地址");
	
	}

	switch(m_TableKinds)
	{
	case 0://正式读表
		{

			//有功正式表
			if(m_Select[0])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_WORKDEGREE");      
				m_NameArray.Add("有功电度");
			}
			
			//无功
			if(m_Select[1])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_LOSEDEGREE");
				m_NameArray.Add("无功电度");
			}
			
			//电流
			if(m_Select[2])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_ACURRENT");      
				m_NameArray.Add("A相电流");
				m_FieldArray.Add("TB_REALTIME.REALTIME_BCURRENT");      
				m_NameArray.Add("B相电流");
				m_FieldArray.Add("TB_REALTIME.REALTIME_CCURRENT");      
				m_NameArray.Add("C相电流");
			}
			
			//电压
			if(m_Select[3])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_AVOLTAGE");      
				m_NameArray.Add("A相电压");
				m_FieldArray.Add("TB_REALTIME.REALTIME_BVOLTAGE");      
				m_NameArray.Add("B相电压");
				m_FieldArray.Add("TB_REALTIME.REALTIME_CVOLTAGE");      
				m_NameArray.Add("C相电压");
			}		
			
			//手拉手有功总
			if(m_Select[4])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_WORKDEGREETOTAL");      
				m_NameArray.Add("手拉手有功总");
			}
			
			//手拉手无功总
			if(m_Select[5])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_LOSEDEGREETOTAL");      
				m_NameArray.Add("手拉手无功总");
			}
			
			//尖峰电量
			if(m_Select[8])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_JFDL");       
				m_NameArray.Add("尖峰电量");	
			}
			
			//峰电量
			if(m_Select[9])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_FDL");       
				m_NameArray.Add("峰电量");	
			}
			
			//谷电量
			if(m_Select[10])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_GDL");       
				m_NameArray.Add("谷电量");	
			}
			
			//平电量
			if(m_Select[11])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_PDL");       
				m_NameArray.Add("平电量");	
			}
			
			//功率因素
			if(m_Select[12])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_GLYS");       
				m_NameArray.Add("功率因素");	
			}
			
			m_FieldArray.Add("TB_REALTIME.REALTIME_TRANSCRIBETIME");      
			m_NameArray.Add("抄表时间");
			
			
			if(m_Select[6])
			{
				//母线编号
				m_FieldArray.Add("TB_USER.USER_MOTHERLINE");       
				m_NameArray.Add("母线编号");
				//出线编号
				m_FieldArray.Add("TB_USER.USER_LINENO");       
				m_NameArray.Add("出线编号");
				
				//模块号
				m_FieldArray.Add("TB_REALTIME.REALTIME_MODULENO");       
				m_NameArray.Add("模块号");
				//对应协议
				m_FieldArray.Add("TB_REALTIME.REALTIME_PROTOCOL"); 
				m_NameArray.Add("对应协议");
				//相别
				m_FieldArray.Add("TB_USER.USER_PHASE");   
				m_NameArray.Add("相别");
			}
		
			break;
		}
	case 1://驻留读表
		{	
			
			//有功驻留表
			if(m_Select[0])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_WORKDEGREE");     
				m_NameArray.Add("有功电度");
			}
			
			//无功
			if(m_Select[1])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_LOSEDEGREE");     
				m_NameArray.Add("无功电度");
			}
			
			//电流
			if(m_Select[2])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_ACURRENT");       
				m_NameArray.Add("A相电流");
				m_FieldArray.Add("TB_GARRISON.GARRISON_BCURRENT");       
				m_NameArray.Add("B相电流");
				m_FieldArray.Add("TB_GARRISON.GARRISON_CCURRENT");      
				m_NameArray.Add("C相电流");
			}
			
			//电压
			if(m_Select[3])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_AVOLTAGE");      
				m_NameArray.Add("A相电压");
				m_FieldArray.Add("TB_GARRISON.GARRISON_BVOLTAGE");      
				m_NameArray.Add("B相电压");
				m_FieldArray.Add("TB_GARRISON.GARRISON_CVOLTAGE");       
				m_NameArray.Add("C相电压");
			}
			
			//手拉手有功总
			if(m_Select[4])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_WORKDEGREETOTAL");
				m_NameArray.Add("手拉手有功总");
			}	
			
			//手拉手无功总
			if(m_Select[5])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_LOSEDEGREETOTAL");
				m_NameArray.Add("手拉手无功总");
			}
			
			//尖峰电量
			if(m_Select[8])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_JFDL");       
				m_NameArray.Add("尖峰电量");	
			}
			
			//峰电量
			if(m_Select[9])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_FDL");       
				m_NameArray.Add("峰电量");	
			}
			
			//谷电量
			if(m_Select[10])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_GDL");       
				m_NameArray.Add("谷电量");	
			}
			
			//平电量
			if(m_Select[11])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_PDL");       
				m_NameArray.Add("平电量");	
			}
			
			//功率因素
			if(m_Select[12])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_GLYS");       
				m_NameArray.Add("功率因素");	
			}
			
			if(m_Select[6])
			{
				//母线编号
				m_FieldArray.Add("TB_USER.USER_MOTHERLINE");       
				m_NameArray.Add("母线编号");
				//出线编号
				m_FieldArray.Add("TB_USER.USER_LINENO");       
				m_NameArray.Add("出线编号");
				//模块号
				m_FieldArray.Add("TB_GARRISON.GARRISON_MODULENO");       
				m_NameArray.Add("模块号");
				//对应协议
				m_FieldArray.Add("TB_GARRISON.GARRISON_PROTOCOL"); 
				m_NameArray.Add("对应协议");
				//相别
				m_FieldArray.Add("TB_USER.USER_PHASE");   
				m_NameArray.Add("相别"); 
				//抄表时间
				m_FieldArray.Add("TB_GARRISON.GARRISON_TRANSCRIBETIME");      
				m_NameArray.Add("抄表时间");
			}

			m_FieldArray.Add("TB_GARRISON.GARRISON_HALTTIME");      
			m_NameArray.Add("驻留时间");
			break;
         }
	 case 2:
		 {

	
			 break;
		 }
    }
	
	//字段名称
	for(int i = 0; i < m_FieldArray.GetSize(); i++)
	{
		
		if(i != m_FieldArray.GetSize() - 1)
		{
			StrFields = StrFields + m_FieldArray[i] + " AS " + m_NameArray[i] + ",";
		}
		else
		{
			StrFields = StrFields + m_FieldArray[i] + " AS " + m_NameArray[i];
		}
	
	}

	m_remotedatactrl.SetDataSourceName(_T("ifrm"));
	
	
	switch(m_TableKinds)
	{
	case 0:
		{
			//正式读表数据,用户选择范围
			if(m_DateRange == "ALL")
			{  
				sqlstr.Format("SELECT %s FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) ORDER BY TB_USER.USER_STATIONNAME,TB_USER.USER_LINENAME,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_SelectStr,m_FieldArray[whichsel],m_sequence);
				m_RecordStr.Format("SELECT COUNT(*) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_SelectStr);
				m_modulestr.Format("SELECT COUNT(DISTINCT TB_USER.USER_MODULENO/100) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_SelectStr);
			}
			else
			{	
				sqlstr.Format("SELECT %s FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND (%s) ORDER BY TB_USER.USER_STATIONNAME,TB_USER.USER_LINENAME,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_SelectStr,m_DateRange,m_FieldArray[whichsel],m_sequence);
				m_RecordStr.Format("SELECT COUNT(*) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND (%s)",m_SelectStr,m_DateRange);
				m_modulestr.Format("SELECT COUNT(DISTINCT TB_USER.USER_MODULENO/100) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND (%s)",m_SelectStr,m_DateRange);
			}
			
			break;

		}
	case 1:
		{
			//驻留时间
			if(m_DateRange == "ALL")
			{ 		
				//左边用户选择为部分，时间范围为全部
				sqlstr.Format("SELECT %s FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s) ORDER BY TB_USER.USER_STATIONNO,TB_USER.USER_LINENO,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_SelectStr,m_FieldArray[whichsel],m_sequence);
				m_RecordStr.Format("SELECT COUNT(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_SelectStr);
				m_modulestr.Format("SELECT COUNT(DISTINCT TB_USER.USER_MODULENO/100) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_SelectStr);
				
			}
			else
			{	
				//左边用户选择为部分，时间范围为部分
				sqlstr.Format("SELECT %s FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s) ORDER BY TB_USER.USER_STATIONNO,TB_USER.USER_LINENO,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_DateRange,m_SelectStr,m_FieldArray[whichsel],m_sequence);
				m_RecordStr.Format("SELECT COUNT(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s)",m_DateRange,m_SelectStr);
				m_modulestr.Format("SELECT COUNT(DISTINCT TB_USER.USER_MODULENO/100) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s)",m_DateRange,m_SelectStr);
			}

			break;
			
		}
	case 2:
		{


			break;
		}
	}

	m_remotedatactrl.SetSql(sqlstr);
	m_remotedatactrl.SetUserName(_T("admin"));
	m_remotedatactrl.SetPassword(_T(""));
	m_remotedatactrl.SetCursorDriver(2);
	m_remotedatactrl.SetReadOnly(TRUE);
	m_remotedatactrl.Refresh();
	
	//connect it to IDC_REMOTEDATACTL
	LPUNKNOWN pCursor = m_remotedatactrl.GetDSCCursor();
	ASSERT(pCursor != NULL);
	m_dbgrid.SetDataSource(pCursor); //bind the grid
	m_dbgrid.BindProperty(0x9, &m_remotedatactrl);
	m_dbgrid.Scroll(2, 0);
	m_dbgrid.SetEditActive(FALSE);
	
	//打开数据库
	CDatabase       dbs;	
	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//和CRecordset连上
		CRecordset rs(&dbs);
		
		//用户个数
    	rs.Open(CRecordset::forwardOnly,m_RecordStr);
		rs.GetFieldValue((short)0,m_RecordStr);
		rs.Close();
	    
		//模块个数
		rs.Open(CRecordset::forwardOnly,m_modulestr);
		rs.GetFieldValue((short)0,m_modulestr);
		rs.Close();

		dbs.Close();

		if(m_TableKinds == 0)
		{
			sqlstr.Format("正式读表数据：时间范围[%s]",m_TimeRangeStr);
		}
		else
		{	
			sqlstr.Format("驻留读表数据：时间范围[%s]",m_TimeRangeStr);
		}
		SetWindowText(sqlstr);
		
		sqlstr.Format("读上数记录[%s]条，模块[%s]个",m_RecordStr,m_modulestr);
	    m_remotedatactrl.SetCaption(sqlstr);

		//如果没有数据
		if(atoi(m_RecordStr) < 1)
		{
			CWnd* pt = GetDlgItem(ID_SAVEDATA);
			pt->EnableWindow(FALSE);
			pt       = GetDlgItem(IDC_DELETE);
			pt->EnableWindow(FALSE);
		}
	
	}

}

void CShowDataDlg::OnSavedata() 
{

	UpdateData(TRUE);

	CString        fieldname,strSql,sqlstr,str;
	CString        StrFields,m_RecordStr,DataStr;
	CString        StrTime,m_sequence,filename;   
	CStringArray   m_FieldArray;
	char szFilter[] = "EXCEL文件(*.CSV)|||";

	if(m_radio3 == 0)
	{
		//升序
        m_sequence = "ASC";
	}
	else
	{
		//降序
		m_sequence = "DESC";
	}
		
	if(m_TableKinds == 0)
	{
		DataStr         = "TB_REALTIME";
	}
	else
	{
		DataStr         = "TB_GARRISON";
	}

	m_NameArray.RemoveAll();

	switch(m_Kinds)
	{
	case 0:
		{
			
			//显示没有找上来的数据
			m_FieldArray.Add("USER_COMPANY");          //公司名称
			m_NameArray.Add("公司名称");   
			m_FieldArray.Add("USER_STATIONNO");        //电站编号
			m_NameArray.Add("电站编号");  
			m_FieldArray.Add("USER_STATIONNAME");     //变电站名称
			m_NameArray.Add("变电站名称");
			m_FieldArray.Add("USER_MOTHERLINE");      //母线编号    
			m_NameArray.Add("母线编号");
			m_FieldArray.Add("USER_LINENO");          //线路编号
			m_NameArray.Add("线路编号");
			m_FieldArray.Add("USER_LINENAME");        //线路名称
			m_NameArray.Add("线路名称");
			m_FieldArray.Add("USER_TRANSFORMERNO");   //变台名称
			m_NameArray.Add("变台名称");
			m_FieldArray.Add("USER_MODULENO");        //模块号
			m_NameArray.Add("模块号");
			m_FieldArray.Add("USER_PHASE");           //相
			m_NameArray.Add("相");
			m_FieldArray.Add("USER_NAME");            //姓名
			m_NameArray.Add("姓名");
			m_FieldArray.Add("USER_NO");              //用户编号
			m_NameArray.Add("用户编号");
			m_FieldArray.Add("USER_OLDNO");           //原用户号
			m_NameArray.Add("原用户号");
			m_FieldArray.Add("USER_ADDRESS");         //住址
			m_NameArray.Add("住址");
			m_FieldArray.Add("USER_PHONE");           //电话
			m_NameArray.Add("电话");
			m_FieldArray.Add("USER_ELECTRICITYKIND"); //用电种类
			m_NameArray.Add("用电种类");
			m_FieldArray.Add("USER_AMMETERNO");       //电表编号
			m_NameArray.Add("电表编号");
			m_FieldArray.Add("USER_AMMETERKIND");     //表计种类
			m_NameArray.Add("表计种类");
			m_FieldArray.Add("USER_INSTALLTIME");     //安装时间
			m_NameArray.Add("安装时间");
			m_FieldArray.Add("USER_INITIALVALUE");    //电表初值
			m_NameArray.Add("电表初值");
			m_FieldArray.Add("USER_MULTIPLE");       //倍率
			m_NameArray.Add("倍率");
			m_FieldArray.Add("USER_PROTOCOL");       //抄表协议
			m_NameArray.Add("抄表协议");
			m_FieldArray.Add("USER_DESCRIBE");       //用电描述
			m_NameArray.Add("用电描述");
	        m_FieldArray.Add("USER_RUNSTATUS");      //运行状态
			m_NameArray.Add("运行状态");
			break;

		}
	case 1:
		{
			
			//得到用户表的所有字段
			m_FieldArray.Add("TB_USER.USER_COMPANY");       //公司名称
			m_NameArray.Add("公司名称");                    
			m_FieldArray.Add("TB_USER.USER_STATIONNAME");   //变电站名称
			m_NameArray.Add("变电站名称");
			m_FieldArray.Add("TB_USER.USER_LINENAME");      //线路名称
			m_NameArray.Add("线路名称");
			m_FieldArray.Add("TB_USER.USER_TRANSFORMERNO"); //变台号
			m_NameArray.Add("变台名称");
			m_FieldArray.Add("TB_USER.USER_NO");            //用户编号
			m_NameArray.Add("用户编号");
			m_FieldArray.Add("TB_USER.USER_AMMETERNO");     //电表编号
			m_NameArray.Add("电表编号");
			
			if(m_Select[7])
			{
				m_FieldArray.Add("TB_USER.USER_NAME");     //用户名
				m_NameArray.Add("用户名");
				m_FieldArray.Add("TB_USER.USER_ADDRESS");  //用户地址
				m_NameArray.Add("用户地址");
			}
			
			if(m_TableKinds == 0)
			{
				//正式表
				
				//有功
				if(m_Select[0])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_WORKDEGREE");      
					m_NameArray.Add("有功电度");
				}
				
				//无功
				if(m_Select[1])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_LOSEDEGREE");
					m_NameArray.Add("无功电度");
				}
				
				//电流
				if(m_Select[2])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_ACURRENT");      
					m_NameArray.Add("A相电流");
					m_FieldArray.Add("TB_REALTIME.REALTIME_BCURRENT");      
					m_NameArray.Add("B相电流");
					m_FieldArray.Add("TB_REALTIME.REALTIME_CCURRENT");      
					m_NameArray.Add("C相电流");
				}
				
				//电压
				if(m_Select[3])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_AVOLTAGE");      
					m_NameArray.Add("A相电压");
					m_FieldArray.Add("TB_REALTIME.REALTIME_BVOLTAGE");      
					m_NameArray.Add("B相电压");
					m_FieldArray.Add("TB_REALTIME.REALTIME_CVOLTAGE");      
					m_NameArray.Add("C相电压");
				}		
				
				//手拉手有功总
				if(m_Select[4])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_WORKDEGREETOTAL");      
					m_NameArray.Add("手拉手有功总");
				}
				
				//手拉手无功总
				if(m_Select[5])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_LOSEDEGREETOTAL");      
					m_NameArray.Add("手拉手无功总");
				}
				
				//尖峰电量
				if(m_Select[8])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_JFDL");       
					m_NameArray.Add("尖峰电量");	
				}
				
				//峰电量
				if(m_Select[9])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_FDL");       
					m_NameArray.Add("峰电量");	
				}
				
				//谷电量
				if(m_Select[10])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_GDL");       
					m_NameArray.Add("谷电量");	
				}
				
				//平电量
				if(m_Select[11])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_PDL");       
					m_NameArray.Add("平电量");	
				}
				
				//功率因素
				if(m_Select[12])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_GLYS");       
					m_NameArray.Add("功率因素");	
				}
				
				m_FieldArray.Add("TB_REALTIME.REALTIME_TRANSCRIBETIME");      
				m_NameArray.Add("抄表时间");
				
				if(m_Select[6])
				{ 	
					
					//母线编号
					m_FieldArray.Add("TB_USER.USER_MOTHERLINE");       
					m_NameArray.Add("母线编号");
					//出线编号
					m_FieldArray.Add("TB_USER.USER_LINENO");       
					m_NameArray.Add("出线编号");
					//模块号
					m_FieldArray.Add("TB_REALTIME.REALTIME_MODULENO");       
					m_NameArray.Add("模块号");
					//对应协议
					m_FieldArray.Add("TB_REALTIME.REALTIME_PROTOCOL"); 
					m_NameArray.Add("对应协议");
					//相别
					m_FieldArray.Add("TB_USER.USER_PHASE");   
					m_NameArray.Add("相别");	
				}
				
		}
		else
		{
			//驻留表			
			//有功
			if(m_Select[0])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_WORKDEGREE");     
				m_NameArray.Add("有功电度");
			}
			
			//无功
			if(m_Select[1])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_LOSEDEGREE");     
				m_NameArray.Add("无功电度");
			}
			
			//电流
			if(m_Select[2])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_ACURRENT");       
				m_NameArray.Add("A相电流");
				m_FieldArray.Add("TB_GARRISON.GARRISON_BCURRENT");       
				m_NameArray.Add("B相电流");
				m_FieldArray.Add("TB_GARRISON.GARRISON_CCURRENT");      
				m_NameArray.Add("C相电流");
			}
			
			//电压
			if(m_Select[3])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_AVOLTAGE");      
				m_NameArray.Add("A相电压");
				m_FieldArray.Add("TB_GARRISON.GARRISON_BVOLTAGE");      
				m_NameArray.Add("B相电压");
				m_FieldArray.Add("TB_GARRISON.GARRISON_CVOLTAGE");       
				m_NameArray.Add("C相电压");
			}
			
			//手拉手有功总
			if(m_Select[4])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_WORKDEGREETOTAL");
				m_NameArray.Add("手拉手有功总");
			}	
			
			//手拉手无功总
			if(m_Select[5])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_LOSEDEGREETOTAL");
				m_NameArray.Add("手拉手无功总");
			}
			
			//尖峰电量
			if(m_Select[8])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_JFDL");       
				m_NameArray.Add("尖峰电量");	
			}
			
			//峰电量
			if(m_Select[9])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_FDL");       
				m_NameArray.Add("峰电量");	
			}
			
			//谷电量
			if(m_Select[10])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_GDL");       
				m_NameArray.Add("谷电量");	
			}
			
			//平电量
			if(m_Select[11])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_PDL");       
				m_NameArray.Add("平电量");	
			}
			
			//功率因素
			if(m_Select[12])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_GLYS");       
				m_NameArray.Add("功率因素");	
			}
			
			if(m_Select[6])
			{
				//母线编号
				m_FieldArray.Add("TB_USER.USER_MOTHERLINE");       
				m_NameArray.Add("母线编号");
				//出线编号
				m_FieldArray.Add("TB_USER.USER_LINENO");       
				m_NameArray.Add("出线编号");
				//模块号
				m_FieldArray.Add("TB_GARRISON.GARRISON_MODULENO");       
				m_NameArray.Add("模块号");
				//对应协议
				m_FieldArray.Add("TB_GARRISON.GARRISON_PROTOCOL"); 
				m_NameArray.Add("对应协议");
				//相别
				m_FieldArray.Add("TB_USER.USER_PHASE");   
				m_NameArray.Add("相别"); 
				//抄表时间
				m_FieldArray.Add("TB_GARRISON.GARRISON_TRANSCRIBETIME");      
				m_NameArray.Add("抄表时间");
			}
			
			m_FieldArray.Add("TB_GARRISON.GARRISON_HALTTIME");      
			m_NameArray.Add("驻留时间");
			
		}

		break;
	  }
	
    }
	
	//字段名称
	for(int i = 0; i < m_FieldArray.GetSize(); i++)
	{
		
		if(i != m_FieldArray.GetSize() - 1)
		{
			StrFields = StrFields + m_FieldArray[i] + " AS " + m_NameArray[i] + ",";
		}
		else
		{
			StrFields = StrFields + m_FieldArray[i] + " AS " + m_NameArray[i];
		}
	
	}

	
	switch(m_Kinds)
	{
	case 0:
		{
			
			//只显示没有读上来的模块
			if(m_TableKinds == 0)
			{

				switch(m_radio)
				{
				case 0://全部未上
					{
						//正式读表
						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s ","REALTIME_MODULENO",DataStr,m_Condtion); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s ","REALTIME_MODULENO",DataStr,m_Condtion); 
						}
						else
						{	
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s ","REALTIME_MODULENO",DataStr,m_TimeRange,m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s ","REALTIME_MODULENO",DataStr,m_TimeRange,m_Condtion); 
						}

						break;
					}
				case 1://销户
					{

						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER WHERE USER_RUNSTATUS=3"); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER WHERE USER_RUNSTATUS=3"); 
						}
						else
						{	
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 

						}
						
						break;
					}
				case 2://线路错误
					{

						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
						}
						else
						{	
							str = m_TimeRange;
							str.Replace("TB_REALTIME", "TB_LINEERROR");
						    str.Replace("REALTIME_TRANSCRIBETIME", "LINEERROR_READTIME");
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
						}

						DataStr = "LineConnectError";
						break;
					}
				}

			}
			else
			{	
				
				switch(m_radio)
				{
				case 0://全部未上
					{
						//驻留读表
						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND (%s)","GARRISON_MODULENO",DataStr,m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND (%s)","GARRISON_MODULENO",DataStr,m_Condtion); 
						}
						else
						{
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态 FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND (%s) ","GARRISON_MODULENO",DataStr,m_TimeRange,m_Condtion); //,m_TimeRange
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND (%s) ","GARRISON_MODULENO",DataStr,m_TimeRange,m_Condtion);//,m_TimeRange); 

						}

						break;
					}	
				case 1://销户
					{
                        if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER WHERE USER_RUNSTATUS=3"); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER WHERE USER_RUNSTATUS=3"); 

						}
						else
						{	
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND (%s) ",m_Condtion); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 

						}

						break;
					}
				case 2://线路错误模块
					{	
						
						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=2) AND (%s)",m_Condtion); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=2) AND %s",m_Condtion); 
						}
						else
						{
							sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s' AND LINEERROR_KINDS=2) AND (%s)",m_TimeRange,m_Condtion); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s' AND LINEERROR_KINDS=2) AND (%s)",m_TimeRange,m_Condtion); 
						}

						DataStr = "LineConnectError";
						break;
					}
				}

			}
			
			break;
		}
	case 1:
		{
			//显示读上来的模块
			if(m_TableKinds == 0)
			{
				
				//正式读表数据,用户选择范围
				if(m_TimeRange == "ALL")
				{  
					sqlstr.Format("SELECT %s FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) ORDER BY TB_USER.USER_STATIONNAME,TB_USER.USER_LINENAME,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_Condtion,m_FieldArray[whichsel],m_sequence);
					m_RecordStr.Format("SELECT count(*) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_Condtion);
				}
				else
				{	
					sqlstr.Format("SELECT %s FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND %s ORDER BY TB_USER.USER_STATIONNAME,TB_USER.USER_LINENAME,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_Condtion,m_TimeRange,m_FieldArray[whichsel],m_sequence);
					m_RecordStr.Format("SELECT count(*) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND %s",m_Condtion,m_TimeRange);
				}
				
			}
			else
			{
				//驻留时间
				if(m_TimeRange == "ALL")
				{ 		
					//左边用户选择为部分，时间范围为全部
					sqlstr.Format("SELECT %s FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s) ORDER BY TB_USER.USER_STATIONNO,TB_USER.USER_LINENO,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_Condtion,m_FieldArray[whichsel],m_sequence);
					m_RecordStr.Format("SELECT count(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_Condtion);
				}
				else
				{	
					//左边用户选择为部分，时间范围为部分
					sqlstr.Format("SELECT %s FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s) ORDER BY TB_USER.USER_STATIONNO,TB_USER.USER_LINENO,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_TimeRange,m_Condtion,m_FieldArray[whichsel],m_sequence);
					m_RecordStr.Format("SELECT count(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s)",m_TimeRange,m_Condtion);
				}
				
			}
			
			break;
		}

	}

	//打开数据库
	CDatabase       dbs;	
	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//和CRecordset连上
		CRecordset rs(&dbs);
	
		rs.Open(CRecordset::forwardOnly,m_RecordStr);
		CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
      //  pview->WriteToLog(m_RecordStr);
		
		//得到记录个数
		rs.GetFieldValue((short)0,m_RecordStr);
		
	//	AfxMessageBox(m_RecordStr);

		rs.Close();
		dbs.Close();
		
	

	}

}

void CShowDataDlg::OnDelete() 
{

	CString    StrTime,str;
	CString         Sqlstr;
    CString   LineErrorStr;
	CString      Str1,Str2;
	int k     =          0;
	short     m_kinds = -1;

	if(m_TimeRangeStr.Find("所有")!= -1)
	{
		StrTime = "";
		m_kinds =  0;
	}
	else
	{
		k = m_TimeRangeStr.Find("－");
		
		if(k != -1)
		{
			Str1    = m_TimeRangeStr.Left(m_TimeRangeStr.GetLength() - k - 2);
			Str2    = m_TimeRangeStr.Right(m_TimeRangeStr.GetLength()- k - 2);
			m_kinds = 1;
		}
		else
		{
            StrTime = m_TimeRangeStr;
			StrTime.TrimLeft();
            StrTime.TrimRight();
			m_kinds =  2;
		}
		
	}
    
	if(m_TableKinds  == 0)
	{	
		//正式读表
		switch(m_kinds)
		{
		case  0:
			{	
				str = "你想删除满足条件的所有正式读表数据吗？\r\n警告：数据删除后不能恢复!!";
				break;
			}
		case 1:
			{
				str.Format("你想删除满足条件且时间范围为[%s,%s]\r\n的正式读表数据吗？警告：数据删除后不能恢复!!",Str1,Str2);
				break;
			}
		case 2:
			{		
				str.Format("你想删除满足条件且读表时间为[%s]\r\n的正式读表数据吗？警告：数据删除后不能恢复!!",StrTime);
				break;
			}
		}

	}
	else
	{
		//驻留表
		switch(m_kinds)
		{
		case  0:
			{	
				str = "你想删除满足条件的所有驻留读表数据吗？\r\n警告：数据删除后不能恢复!!";
				break;
			}
		case 1:
			{
				str.Format("你想删除满足条件且时间范围为[%s,%s]\r\n的驻留读表数据吗？警告：数据删除后不能恢复!!",Str1,Str2);
				break;
			}
		case 2:
			{		
				str.Format("你想删除满足条件且读表时间为[%s]\r\n的驻留读表数据吗？警告：数据删除后不能恢复!!",StrTime);
				break;
			}
		}
	}
	

	if(MessageBox(str,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
    

		str.Format("你真的想删除上述数据吗?如果确认要删除,请选择是按钮,\r\n不想删除请选择否按钮!警告：数据删除后不能恢复!!");
		
		if(MessageBox(str,"警告:",MB_YESNO|MB_ICONWARNING) == IDYES)
		{
			//打开数据库
			CDatabase  db;

			if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
			{
			
				//SQl语句
				if(m_TableKinds  == 0)
				{
					
					//正式读表
					switch(m_kinds)
					{
					case  0:
						{	
							Sqlstr.Format("DELETE FROM TB_REALTIME WHERE REALTIME_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",m_Condtion);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",m_Condtion);
							break;
						}
					case 1:
						{
							Sqlstr.Format("DELETE FROM TB_REALTIME WHERE REALTIME_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s AND REALTIME_TRANSCRIBETIME>='%s' AND REALTIME_TRANSCRIBETIME<='%s')",m_Condtion,Str1,Str2);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s AND REALTIME_TRANSCRIBETIME>='%s' AND REALTIME_TRANSCRIBETIME<='%s')  AND LINEERROR_READTIME>='%s' AND LINEERROR_READTIME<='%s'  AND LINEERROR_KINDS=1",m_Condtion,Str1,Str2,Str1,Str2);
							break;
						}
					case 2:
						{	
							Sqlstr.Format("DELETE FROM TB_REALTIME WHERE REALTIME_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s AND REALTIME_TRANSCRIBETIME='%s')",m_Condtion,StrTime);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s AND REALTIME_TRANSCRIBETIME='%s') AND LINEERROR_KINDS=1",m_Condtion,StrTime);
    						break;
						}
					}
					
				}
				else
				{	
				
					//驻留表
					switch(m_kinds)
					{
					case  0:
						{	//满足条件的所有记录
							Sqlstr.Format("DELETE FROM TB_GARRISON WHERE GARRISON_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",m_Condtion);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)  AND LINEERROR_KINDS=2",m_Condtion);
    						break;
						}
					case 1:
						{	
							Sqlstr.Format("DELETE FROM TB_GARRISON WHERE GARRISON_HALTTIME>='%s' AND GARRISON_HALTTIME<='%s' AND GARRISON_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",Str1,Str2,m_Condtion);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME>='%s' AND LINEERROR_HALTTIME<='%s' AND LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s) AND LINEERROR_KINDS=2",Str1,Str2,m_Condtion);
							break;
						}
					case 2:
						{	
							Sqlstr.Format("DELETE FROM TB_GARRISON WHERE GARRISON_HALTTIME='%s' AND GARRISON_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",StrTime,m_Condtion);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s' AND LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)  AND LINEERROR_KINDS=2",StrTime,m_Condtion);
    						break;
						}
					}

				}
			
				db.ExecuteSQL(Sqlstr);
				//删除所有的线路错误模块记录
				db.ExecuteSQL(LineErrorStr);
				
				db.Close();
				
				//重新刷新列表
				if(m_TableKinds == 1)
				{
					CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
					pMainFrm->m_wndMyDialogBar.InitializeCombo();
				}

				//显示数据
		        DataSort(m_Condtion,m_TimeRange);

			}  

		}

	} 

}

BOOL CShowDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_DATAAPPEAR);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	switch(m_Kinds)
	{
	case 0:
		{
			CWnd* pt = GetDlgItem(IDC_DELETE);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO3);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO4);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO1);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_RADIO2);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_RADIO5);
			pt->EnableWindow(TRUE);

			//查找没有读上来的模块
			Findnoreadmodule(0);
			break;
		}
	case 1:
		{	
			whichsel  =   0;
			CWnd* pt  = GetDlgItem(IDC_RADIO1);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO2);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO5);
			pt->EnableWindow(FALSE);
			//显示数据
			DataSort(m_Condtion,m_TimeRange);
			break;
		}

	}
	return TRUE;  
}



void CShowDataDlg::Findnoreadmodule(short kinds)
{	

	CString                str,filename;
   	CString  Sqlstr,DataStr,ModuleFieldName,m_modulestr;
    long      m_Records      =  0,m_ModuleRecords  =  0;
   
	CStringArray  m_NameArrays;
	CDatabase              dbs;
	
	switch(m_TableKinds)
	{
	case  0:
		{
			//显示正式读表没有上来的
			DataStr         = "TB_REALTIME";
			ModuleFieldName = "REALTIME_MODULENO";
			break;
		}
	case 1:
		{
			//显示驻留读表没有上来的
			DataStr         = "TB_GARRISON";
			ModuleFieldName = "GARRISON_MODULENO";
			break;
		}

	}

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//和CRecordset连上
		CRecordset rs(&dbs);

		switch(m_TableKinds)
		{
		case 0:
			{
				switch(kinds)
				{
				case 0://全部未上
					{
						//正式读表
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
							
						}
						else
						{	
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
						}

						break;
					}
				case 1://销户
					{
						
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							
						}
						else
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER WHERE USER_RUNSTATUS=3 AND %s",m_Condtion); 
						}
						break;
					}
				case 2://线路错误
					{

						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
							
						}
						else
						{
							str = m_TimeRange;
							str.Replace("TB_REALTIME", "TB_LINEERROR");
						    str.Replace("REALTIME_TRANSCRIBETIME", "LINEERROR_READTIME");

							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
						}
						
						break;
					}

				}
				
				break;
			}
		case 1://驻留表
			{
				
				switch(kinds)
				{
				case 0://全部未上
					{
						
						//驻留读表
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
							
						}
						else
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND %s",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND %s",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
						}
						
						break;
					}
				case 1://销户
					{
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s",m_Condtion); 
							
						}
						else
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER WHERE USER_RUNSTATUS=3 AND %s",m_Condtion); 
						}
						
						break;
					}
				case 2://线路错误
					{
							
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR) AND %s",m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR) AND %s",m_Condtion); 
							
						}
						else
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s') AND %s",m_TimeRange,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s') AND %s",m_TimeRange,m_Condtion); 
						}

						break;
					}
					
				}
				
				break;
			}
		}

	    //得到用户记录个数
	  	rs.Open(CRecordset::forwardOnly,Sqlstr);
		rs.GetFieldValue((short)0,Sqlstr);
		rs.Close();
        m_Records = atoi(Sqlstr);
        
		//得到模块数
	  	rs.Open(CRecordset::forwardOnly,m_modulestr);
		rs.GetFieldValue((short)0,m_modulestr);
		rs.Close();

		m_ModuleRecords = atoi(m_modulestr);
		
		//显示没有读上来的数据
		switch(m_TableKinds)
		{
		case 0:
			{
				switch(kinds)
				{
				case 0://全部未上
					{
						//正式读表
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s ",ModuleFieldName,DataStr,m_Condtion); 
						}
						else
						{	
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s ",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
						}
						break;
					}
				case 1://销户
					{

	                    if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述  FROM TB_USER WHERE USER_RUNSTATUS=3"); 
						}
						else
						{	
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 
						}
						
						break;
					}
				case 2://线路错误
					{

						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
						}
						else
						{	
							str = m_TimeRange;
							str.Replace("TB_REALTIME", "TB_LINEERROR");
						    str.Replace("REALTIME_TRANSCRIBETIME", "LINEERROR_READTIME");
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
						}

						break;
					}
				}
				
				break;
				
			}
		case 1:
			{	
				
				switch(kinds)
				{
				case 0://全部未上
					{
						//驻留读表
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
						}
						else
						{
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态 FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND %s ",ModuleFieldName,DataStr,m_TimeRange,m_Condtion,m_TimeRange); 
						}
						break;
					}	
				case 1://销户
					{
                        if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述  FROM TB_USER WHERE USER_RUNSTATUS=3"); 
						}
						else
						{	
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 
						}
						break;
					}
				case 2://线路错误模块
					{	
						
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=2) AND %s",m_Condtion); 
						}
						else
						{
							Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNO AS 电站编号,USER_STATIONNAME AS 变电站名称,USER_MOTHERLINE AS 母线编号,USER_LINENO AS 线路编号,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_MODULENO AS 模块号,USER_PHASE AS 相,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_PROTOCOL AS 抄表协议,USER_DESCRIBE AS 用电描述,USER_RUNSTATUS AS 运行状态  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s' AND LINEERROR_KINDS=2) AND %s",m_TimeRange,m_Condtion); 
						}

						break;
					}
				}
	
				break;
			}
		}

		
		rs.Open(CRecordset::forwardOnly,Sqlstr);
		
		//得到字段个数
		short m_fileds = rs.GetODBCFieldCount( );
		CODBCFieldInfo fieldinfo;
	
		for(int i = 0;i < m_fileds; i++)
		{
			//字段名
			rs.GetODBCFieldInfo(i,fieldinfo);
			fieldinfo.m_strName.TrimLeft();
			fieldinfo.m_strName.TrimRight();
			m_NameArrays.Add(fieldinfo.m_strName);
		}
		
		rs.Close();
		dbs.Close();
	}

	m_remotedatactrl.SetDataSourceName(_T("ifrm"));
	m_remotedatactrl.SetSql(Sqlstr);

	m_remotedatactrl.SetUserName(_T("admin"));
	m_remotedatactrl.SetPassword(_T(""));
	m_remotedatactrl.SetCursorDriver(2);
	m_remotedatactrl.SetReadOnly(TRUE);
	m_remotedatactrl.Refresh();

	//connect it to IDC_REMOTEDATACTL
	LPUNKNOWN pCursor=m_remotedatactrl.GetDSCCursor();
	ASSERT(pCursor!=NULL);
	m_dbgrid.SetDataSource(pCursor); //bind the grid
	m_dbgrid.BindProperty(0x9, &m_remotedatactrl);
	m_dbgrid.SetEditActive(FALSE);	//打开数据库
    m_dbgrid.Scroll(4,0);
	
	switch(m_TableKinds)
	{
	   case 0:
		   {	
			   switch(kinds)
			   {
			   case 0:
				   { 
					   Sqlstr.Format("正式读表：时间范围[%s]",m_TimeRangeStr);
					   m_modulestr.Format("未上数记录(含欠费停电、销户、模块与电表通讯错误)%d个、模块%d个",m_Records,m_ModuleRecords);
					   break;
				   }
			   case 1:
				   { 
					   Sqlstr.Format("正式读表：时间范围[%s]",m_TimeRangeStr);
					   m_modulestr.Format("由于模块销户未上数记录%d户、模块%d个",m_Records,m_ModuleRecords);
					   break;
				   }
			   case 2:
				   { 
					   Sqlstr.Format("正式读表：时间范围[%s]",m_TimeRangeStr);
					   m_modulestr.Format("由于模块与电表通讯错误未上数记录%d个、模块%d个",m_Records,m_ModuleRecords);
					   break;
				   }
			   }
			  
			   break;
		   }
	   case 1:
		   {
			   
			   switch(kinds)
			   {
			   case 0:
				   {
					   Sqlstr.Format("驻留读表：时间范围[%s]",m_TimeRangeStr);
					   m_modulestr.Format("未上数记录(含欠费停电、销户、模块与电表通讯错误)%d个、模块%d个",m_Records,m_ModuleRecords);
					   break;
				   }
			   case 1:
				   {
					   Sqlstr.Format("驻留读表：时间范围[%s]",m_TimeRangeStr);
					   m_modulestr.Format("由于模块销户未上数记录%d户、模块%d个",m_Records,m_ModuleRecords);
					   break;
				   }
			   case 2:
				   {
					   Sqlstr.Format("驻留读表：时间范围[%s]",m_TimeRangeStr);
					   m_modulestr.Format("由于模块与电表通讯错误未上数记录%d个、模块%d个",m_Records,m_ModuleRecords);
					   break;
				   }
			   }

			   break;
		   } 
	}

	SetWindowText(Sqlstr);
	m_remotedatactrl.SetCaption(m_modulestr);

	
	CWnd* pt = GetDlgItem(ID_SAVEDATA);
	
	//如果没有数据
	if(m_Records <= 0)
	{
		pt->EnableWindow(FALSE);
	}
	else
	{
		pt->EnableWindow(TRUE);
	}	

	pt = GetDlgItem(IDC_DELETE);
	pt->EnableWindow(FALSE);
	
}

BEGIN_EVENTSINK_MAP(CShowDataDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CShowData)
	ON_EVENT(CShowDataDlg, IDC_DBGRIDS, 10 /* HeadClick */, OnHeadClickDbgrids, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CShowDataDlg::OnHeadClickDbgrids(short ColIndex) 
{
	// TODO: Add your control notification handler code here
	whichsel = ColIndex;
	UpdateData(TRUE);
	
	if(m_Kinds > 0)
	{
		//显示数据
		DataSort(m_Condtion,m_TimeRange);
	}
	
}

void CShowDataDlg::OnRadio3() 
{
	UpdateData(TRUE);
	
	//显示数据
	DataSort(m_Condtion,m_TimeRange);
}

void CShowDataDlg::OnRadio4() 
{
	UpdateData(TRUE);
	
	//显示数据
	DataSort(m_Condtion,m_TimeRange);	
}


//显示满足条件的未上数据模块
void CShowDataDlg::OnRadio1() 
{
	Findnoreadmodule(0);	
}

//显示满足条件的销户用户
void CShowDataDlg::OnRadio2() 
{
	Findnoreadmodule(1);
}

//显示满足条件的接线错误模块
void CShowDataDlg::OnRadio5() 
{
	Findnoreadmodule(2);

}
