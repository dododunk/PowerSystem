// Search.cpp : implementation file
//

#include "stdafx.h"

#include "SearchDlg.h"
#include "RuntimeAccount.h"
#include "ReplaceDataDlg.h"


#include "IFRMView.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearch dialog


//CSearch::CSearch(CWnd* pParent /*=NULL*/)
//	: CDialog(CSearch::IDD, pParent)
CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
: CExpandingDlg(CSearchDlg::IDD,pParent,IDC_DEFAULTBOX,IDC_SEARCH,
				   _T("显示查询"),_T("隐藏查询"))	
{
	//{{AFX_DATA_INIT(CSearch)
	m_radio    =      0;
	m_dividsql = _T("");
	m_totalsql = _T("");
	m_FieldName = _T("");
	//}}AFX_DATA_INIT
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearch)
	DDX_Control(pDX, ID_START, m_ok);
	DDX_Control(pDX, IDC_SEND, m_send);
	DDX_Control(pDX, IDC_SEARCH, m_search);
	DDX_Control(pDX, IDC_CLEAR, m_clear);
	DDX_Control(pDX, IDC_ADDTO, m_addto);
	DDX_Control(pDX, ID_WRITETOTEXTFILE, m_writetotxt);
	DDX_Control(pDX, ID_WRITETOEXCELFILE, m_writetoexcel);
	DDX_Control(pDX, ID_REPLACE, m_replace);
	DDX_Control(pDX, ID_GETFROM, m_getfrom);
	DDX_Control(pDX, ID_DELETE, m_delete);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_OPERATE, m_operate);
	DDX_Control(pDX, IDC_COMBODATAINFO, m_CombDataInfo);
	DDX_Control(pDX, IDC_REMOTEDATACTL, m_remotedatactrl);
	DDX_Control(pDX, IDC_DBGRID, m_dbgrid);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Text(pDX, IDC_DIVIDESQL, m_dividsql);
	DDX_Text(pDX, IDC_TOTALSQLS, m_totalsql);
	DDX_CBIndex(pDX, IDC_COMBODATAINFO, m_FieldPositionm);
	DDX_CBIndex(pDX, IDC_OPERATE, m_symbol);
	DDX_Text(pDX, IDC_VALUE, m_FieldName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
//{{AFX_MSG_MAP(CSearch)
ON_BN_CLICKED(IDC_SEARCH, OnSearch)
ON_BN_CLICKED(IDC_SEND, OnSend)
ON_BN_CLICKED(IDC_ADDTO, OnAddto)
ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
ON_BN_CLICKED(IDC_CLEAR, OnClear)
ON_BN_CLICKED(ID_DELETE, OnDelete)
ON_BN_CLICKED(ID_REPLACE, OnReplace)
	ON_BN_CLICKED(ID_GETFROM, OnGetfrom)
	ON_BN_CLICKED(ID_START, OnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearch message handlers

void CSearchDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CSearchDlg::initializeFieldInfo(CString DataName)
{	
	//打开数据库
	CDatabase db;
	
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset rs(&db );
		CString      strSql;
		strSql.Format("SELECT DISTINCT * FROM %s",DataName);
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到字段个数
		short nFields = rs.GetODBCFieldCount( );
		CODBCFieldInfo fieldinfo;
	
		m_CombDataInfo.ResetContent();
		DataName.TrimLeft();
		DataName.TrimRight();
		
		if(DataName ==  "TB_ELECTRICITY")
		{
            
			//用电种类和电价
			for(int i = 0; i < 2*nFields;i ++)
			{
			
				if(i%2 != 0)
				{

					if(i <= (pview->TB_ELECTRICITYS.GetSize() - 1))
					{
						m_CombDataInfo.AddString(pview->TB_ELECTRICITYS[i]);
					}

				}
			
			}
				
		}
		else if(DataName == "TB_TRANSFORMER")
		{

			//变台信息数据表
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{

					if(i <= (pview->TB_TRANSFORMERS.GetSize() - 1))
					{
						m_CombDataInfo.AddString(pview->TB_TRANSFORMERS[i]);
					}

				}

			}
			
		}
		else if(DataName == "TB_AMMETER")
		{
		
			//电表信息数据表
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{

					if(i <= (pview->TB_AMMETERS.GetSize() - 1))
					{
						m_CombDataInfo.AddString(pview->TB_AMMETERS[i]);
					}

				}

			}
		
		}
		else if(DataName == "TB_USER")
		{
            
			//用户信息库数据表
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{
				    
					if(i <= (pview->TB_USERS.GetSize() - 1))
					{
						m_CombDataInfo.AddString(pview->TB_USERS[i]);
					}

				}

			}
			
		}
		else if(DataName == "TB_GARRISON")
		{

			//驻留数据表
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{

					if(i <= (pview->TB_GARRISONS.GetSize() - 1))
					{
						m_CombDataInfo.AddString(pview->TB_GARRISONS[i]);
					}

				}

			}
		
		}
		else if(DataName == "TB_REALTIME")
		{
            
			//正式读表数据表
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{
				
					if(i <= (pview->TB_REALTIMES.GetSize() - 1))
					{
						m_CombDataInfo.AddString(pview->TB_REALTIMES[i]);
					}

				}

			}
		
		}
		else if(DataName == "TB_CHANGEAMMETER")
		{
            
			//正式读表数据表
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{

					if(i <= (pview->TB_CHANGEAMMETERS.GetSize() - 1))
					{
						m_CombDataInfo.AddString(pview->TB_CHANGEAMMETERS[i]);
					}

				}

			}
		
		}
		else
		{
		
			for(int i = 0;i < nFields; i++)
			{
				//字段名
				rs.GetODBCFieldInfo(i,fieldinfo);
				m_CombDataInfo.AddString(fieldinfo.m_strName);
			}

		}
		
		rs.Close( );
		db.Close( );
	}
	
}

BOOL CSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//设置窗口的图标
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_SQL);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

    initializeFieldInfo(m_dataname);
	m_CombDataInfo.SetCurSel(0);
    m_operate.SetCurSel(0);
	ExpandBox(FALSE);	
	UpdateData(FALSE);
	
	CButton* pt = (CButton*)GetDlgItem(ID_REPLACE);
	pt->EnableWindow(IsExpanded());	
	
	if(!m_showbuttons)
	{
		pt->ShowWindow(SW_HIDE);
	}
    pt = (CButton*)GetDlgItem(ID_DELETE);
	pt->EnableWindow(IsExpanded());
	if(!m_showbuttons)
	{
		pt->ShowWindow(SW_HIDE);
	}
	pt = (CButton*)GetDlgItem(ID_WRITETOTEXTFILE);
	pt->EnableWindow(IsExpanded());
	if(!m_showbuttons)
	{
		pt->ShowWindow(SW_HIDE);
	}
	pt = (CButton*)GetDlgItem(ID_WRITETOEXCELFILE);
	pt->EnableWindow(IsExpanded());
	if(!m_showbuttons)
	{
		pt->ShowWindow(SW_HIDE);
	}
	pt = (CButton*)GetDlgItem(ID_GETFROM);
	pt->EnableWindow(IsExpanded());
	if(!m_showbuttons)
	{
		pt->ShowWindow(SW_HIDE);
	}


	m_modified = FALSE;

	//用户权限
	//CIFRMApp* Apppt = (CIFRMApp*)AfxGetApp();

	if(CRuntimeAccount::GetCurrentPrivilege()> 1)
	{
	    pt = (CButton*)GetDlgItem(ID_DELETE);
		pt->EnableWindow(FALSE);
		pt = (CButton*)GetDlgItem(ID_REPLACE);
		pt->EnableWindow(FALSE);
		pt = (CButton*)GetDlgItem(ID_GETFROM);
		pt->EnableWindow(FALSE);
	}

    CenterWindow();

	return TRUE; 
}

void CSearchDlg::SetDataBaseName(CString name)
{
	m_dataname = name;
}

void CSearchDlg::OnSearch() 
{
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	m_remotedatactrl.SetDataSourceName(_T("ifrm"));
    m_totalsql.TrimLeft();
	m_totalsql.TrimRight();
	CString         Sqlstr;	
	
    //如果是用户表
	if(m_dataname=="TB_USER")
	{	
		if(m_totalsql.IsEmpty())
		{	
		   CWnd* pt = GetDlgItem(ID_START);
		   pt->EnableWindow(TRUE);
		   Sqlstr.Format("    找到符合条件的记录有:%d个,其中模块个数为%d个!",CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL"),CDataBaseInstance::Getmoduls("ALL"));
		}
		else
		{	
			long   m_records  =  CDataBaseInstance::GetAllRecordsCount("TB_USER",m_totalsql);
			
			CWnd* pt = GetDlgItem(ID_START);

			if(m_records < 0)
			{
				pt->EnableWindow(FALSE);
                return;
			}
			else
			{
				pt->EnableWindow(TRUE);
			}
			
			Sqlstr.Format("    找到符合条件的记录有:%d个,其中模块个数为%d个!",m_records,CDataBaseInstance::Getmoduls(m_totalsql));//CDataBaseInstance::GetAllRecordsCount("TB_USER",m_totalsql)
		}
        m_remotedatactrl.SetCaption(Sqlstr);
	}
	else
	{   
		//其它表的话
		if(m_totalsql.IsEmpty())
		{  
		
		   CWnd* pt = GetDlgItem(ID_START);
		   pt->EnableWindow(TRUE);
		   Sqlstr.Format("    找到符合条件的记录有:%d个!",CDataBaseInstance::GetAllRecordsCount(m_dataname,"ALL"));
		
		}
		else
		{	
			long   m_records  =  CDataBaseInstance::GetAllRecordsCount(m_dataname,m_totalsql);
			
			CWnd* pt = GetDlgItem(ID_START);
			
			if(m_records < 0)
			{	
				pt->EnableWindow(FALSE);
                return;
			}
			else
			{
				pt->EnableWindow(TRUE);
			}

			Sqlstr.Format("    找到符合条件的记录有:%d个!",m_records);//CDataBaseInstance::GetAllRecordsCount(m_dataname,m_totalsql)
		}
        m_remotedatactrl.SetCaption(Sqlstr);
	}
	
	if(m_totalsql.IsEmpty())
	{
		Sqlstr.Format("SELECT %s FROM %s ",EnglishToChineseStr(),m_dataname);
	}
	else
	{
		Sqlstr.Format("SELECT %s FROM %s WHERE %s",EnglishToChineseStr(),m_dataname, m_totalsql);
	}
	m_GetSqlStr = Sqlstr;
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
	m_dbgrid.SetEditActive(FALSE);
    
	CButton* pt = (CButton*)GetDlgItem(ID_REPLACE);
	pt->EnableWindow(IsExpanded());
    pt = (CButton*)GetDlgItem(ID_DELETE);
	pt->EnableWindow(IsExpanded());
	pt = (CButton*)GetDlgItem(ID_WRITETOTEXTFILE);
	pt->EnableWindow(IsExpanded());	
	pt = (CButton*)GetDlgItem(ID_WRITETOEXCELFILE);
	pt->EnableWindow(IsExpanded());
	pt = (CButton*)GetDlgItem(ID_GETFROM);
	pt->EnableWindow(IsExpanded());	
	
	
	//用户权限
	

	if(CRuntimeAccount::GetCurrentPrivilege()  > 1)
	{
	    CButton* pt = (CButton*)GetDlgItem(ID_DELETE);
		pt->EnableWindow(FALSE);
		pt = (CButton*)GetDlgItem(ID_REPLACE);
		pt->EnableWindow(FALSE);
		pt = (CButton*)GetDlgItem(ID_GETFROM);
		pt->EnableWindow(FALSE);
	}

}

void CSearchDlg::OnSend() 
{	
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	UpdateData(TRUE);

	CString FieldInfo,OperateInfo,ValueInfo;
	if(m_CombDataInfo.GetCurSel() == CB_ERR)
	{
		return;
	}

	if(m_dataname ==  "TB_ELECTRICITY")
	{
		FieldInfo = pview->TB_ELECTRICITYS[2 * m_CombDataInfo.GetCurSel()];
	}
	else if(m_dataname == "TB_TRANSFORMER")
	{
		FieldInfo = pview->TB_TRANSFORMERS[2 * m_CombDataInfo.GetCurSel()];
	}
	else if(m_dataname == "TB_AMMETER")
	{
		FieldInfo = pview->TB_AMMETERS[2 * m_CombDataInfo.GetCurSel()];
	}
	else if(m_dataname == "TB_USER")
	{
		FieldInfo = pview->TB_USERS[2 * m_CombDataInfo.GetCurSel()];
	}
	else if(m_dataname == "TB_GARRISON")
	{
		FieldInfo = pview->TB_GARRISONS[2 * m_CombDataInfo.GetCurSel()];
		
	}
	else if(m_dataname == "TB_REALTIME")
	{
		FieldInfo = pview->TB_REALTIMES[2 * m_CombDataInfo.GetCurSel()];
	}
	else if(m_dataname == "TB_CHANGEAMMETER")
	{
		FieldInfo = pview->TB_CHANGEAMMETERS[2 * m_CombDataInfo.GetCurSel()];
	}
	else
	{
		m_CombDataInfo.GetLBText(m_CombDataInfo.GetCurSel(),FieldInfo);
	}
	
	m_operate.GetLBText(m_operate.GetCurSel(),OperateInfo); 

	CEdit * pt = (CEdit *)GetDlgItem(IDC_VALUE);
    pt->GetWindowText(ValueInfo);
	
	m_dividsql = FieldInfo+OperateInfo+ValueInfo;
	UpdateData(FALSE);
}

void CSearchDlg::OnAddto() 
{
    UpdateData(TRUE);
	m_totalsql = m_totalsql + m_dividsql;
	UpdateData(FALSE);
	
}

void CSearchDlg::OnRadio1() 
{
	UpdateData(TRUE);
	m_totalsql = m_totalsql + " AND ";
	UpdateData(FALSE);	
}



void CSearchDlg::OnRadio2() 
{
	m_radio = 1;
	m_totalsql = m_totalsql + " OR ";
	UpdateData(FALSE);	
}

void CSearchDlg::OnClear() 
{
	UpdateData(TRUE);
	m_totalsql = "";
	UpdateData(FALSE);		
}

void CSearchDlg::OnDelete() 
{	
	
	CString        Sqlstr;
	m_totalsql.TrimLeft();
    m_totalsql.TrimRight();

	if(m_totalsql.IsEmpty())
	{
		Sqlstr = "你想删除所有记录吗？警告：数据删除后不能恢复！！";
	}
	else
	{
		Sqlstr = "你想删除满足上述条件的这些记录吗？警告：数据删除后不能恢复！！";
	}
	
	
	if(MessageBox(Sqlstr,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
		if(m_totalsql.IsEmpty())
		{
			Sqlstr = "你真的想删除所有记录吗?如果确认要删除,请选择是按钮,\r\n不想删除请选择否按钮!警告：数据删除后不能恢复!!";
			
		}
		else
		{	
			Sqlstr = "你真的想删除满足上述条件的这些记录吗?如果确认要删除,请选择是按钮,\r\n不想删除请选择否按钮!!警告：数据删除后不能恢复！！";
			
		}
		
		if(MessageBox(Sqlstr,"警告:",MB_YESNO|MB_ICONWARNING) == IDYES)
		{
			//打开数据库
			CDatabase db;
		
			if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
			{
			//	db.SetLoginTimeout(0);

				if(m_totalsql.IsEmpty())
				{
					Sqlstr.Format("DELETE FROM %s",m_dataname);
				}
				else
				{
					Sqlstr.Format("DELETE FROM %s WHERE %s",m_dataname, m_totalsql);
				}

				//delete data
				db.ExecuteSQL(Sqlstr);
				//Close database
				db.Close();

				OnSearch();
				//MessageBox("已保存报表名称和公司名称!","提示:",MB_OK);
			}  

		}

	} 

}


void CSearchDlg::OnReplace() 
{
	
	CReplaceDataDlg	        dlg; 
	dlg.m_dataname = m_dataname;
	
	CString       FieldStr = "";
	CString            StrValue;
	CString              Sqlstr;
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

    if(dlg.DoModal() == IDOK)
    {
		
		// m_CombDataInfo.GetLBText(dlg.m_index,FieldStr);
		
		//如果替换字段对话框为空
		if(dlg.m_index == CB_ERR)
		{
			return;
		}
		
		//找到替换后的字段
		if(m_dataname ==  "TB_ELECTRICITY")
		{
			FieldStr = pview->TB_ELECTRICITYS[2 * dlg.m_index];
		}
		else if(m_dataname == "TB_TRANSFORMER")
		{
			FieldStr = pview->TB_TRANSFORMERS[2 * dlg.m_index];
		}
		else if(m_dataname == "TB_AMMETER")
		{
			FieldStr = pview->TB_AMMETERS[2 * dlg.m_index];
		}
		else if(m_dataname == "TB_USER")
		{
			FieldStr = pview->TB_USERS[2 * dlg.m_index];
		}
		else if(m_dataname == "TB_GARRISON")
		{
			FieldStr = pview->TB_GARRISONS[2 * dlg.m_index];
			
		}
		else if(m_dataname == "TB_REALTIME")
		{
			FieldStr = pview->TB_REALTIMES[2 * dlg.m_index];
		}
		else
		{
			m_CombDataInfo.GetLBText(dlg.m_index,FieldStr);
		}
		
		//替换后的值
		StrValue = dlg.m_value;
		
		//替换的范围
		m_totalsql.TrimLeft();
		m_totalsql.TrimRight();

		if(m_totalsql.IsEmpty())
		{
			Sqlstr = "你想替换所有记录的这个字段吗？\r\n警告：数据替换后不能恢复！！";
		}
		else
		{
			Sqlstr = "你想替换满足上述条件的这些记录的这个字段吗？\r\n警告：数据替换后不能恢复！！";
		}
		
		
		if(MessageBox(Sqlstr,"询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			//打开数据库
			CDatabase db;
			if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
			{
				
				if(m_totalsql.IsEmpty())
				{
					Sqlstr.Format("UPDATE %s SET %s = %s",m_dataname,FieldStr,StrValue);
				}
				else
				{
					Sqlstr.Format("UPDATE %s SET %s = %s WHERE %s",m_dataname,FieldStr,StrValue,m_totalsql);
					//	Sqlstr.Format("DELETE FROM %s WHERE %s",m_dataname, m_totalsql);
				}
				
				//delete data
				db.ExecuteSQL(Sqlstr);
				//Close database
				db.Close();
				OnSearch();
				//MessageBox("已保存报表名称和公司名称!","提示:",MB_OK);
				
			}  
			
		} 

    }

}




void CSearchDlg::OnGetfrom() 
{
	
	UpdateData(TRUE);
	CString    MessageStr;
    CString        SqlStr;

	//视图指针
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	if(m_dataname       == "TB_ELECTRICITY")
	{
		MessageStr = "电类电价数据表"; 
	}
	else if(m_dataname	== "TB_TRANSFORMER")
	{
		MessageStr = "变台信息数据表"; 
	}
	else if(m_dataname	== "TB_AMMETER")
	{
		MessageStr = "电表信息数据表"; 
	}
	else if(m_dataname	== "TB_USER")
	{
		MessageStr = "用户信息数据表";
	}
	else if(m_dataname	==  "TB_REALTIME")
	{
		MessageStr = "正式读表数据表";
	}
	else if(m_dataname	== 	"Garrison")
	{
		MessageStr = "驻留数据数据表";
	}
	else 
	{
		MessageStr = "数据表";
	}

	char szFilter[]="导入数据表文本文件(*.TXT)|*.TXT||";
   	CFileDialog dlg(TRUE,"TXT","*.TXT",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	
	if(dlg.DoModal() == IDOK)
	{

		if(MessageBox("导入文本文件" + dlg.GetPathName() + "\r\n数据到" + MessageStr + "中去吗？"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{

			//处理重复数据记录 m_DataName   表名,TxtFileName  导入文本文件
			pview->DealRepeatRecord(m_dataname,dlg.GetPathName());
					
			//如果是用户库和变台库
			if(m_dataname == "TB_USER" || m_dataname == "TB_TRANSFORMER")
			{
			   m_modified  = TRUE;
			}	
			
			MessageBox("恭喜，文本文件数据成功导入用户信息表中！\r\n如有重复记录则删除，详情见日志！！","",MB_OK|MB_ICONASTERISK);

		}

	}
	
}



void CSearchDlg::OnStart() 
{
	UpdateData(TRUE);
	CDialog::OnOK();	
}

//英文变成中文,变成  英文 AS 中文1，英文 AS 中文2...处理
CString CSearchDlg::EnglishToChineseStr()
{
	//字符条件
    CString      str;
	//字段个数
	int m_fileds = 0;
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	if(m_CombDataInfo.GetCurSel() == CB_ERR)
	{
		str = "*";
		return str;
	}
    
	//字段个数
	m_fileds = m_CombDataInfo.GetCount();
    
	
	if(m_dataname == "TB_ELECTRICITY")
	{
		//用电种类和电价表
		for(int i = 0; i < 2 * m_fileds; i = i + 2)
		{

			if( i != 2 * m_fileds - 2)
			{
			   str = str + pview->TB_ELECTRICITYS[i] + " AS " + pview->TB_ELECTRICITYS[i + 1] + ",";
			}
			else
			{
               str = str + pview->TB_ELECTRICITYS[i] + " AS " + pview->TB_ELECTRICITYS[i + 1];
			}

		}

	}
	else if(m_dataname == "TB_TRANSFORMER")
	{
        
		//变台信息数据表
		for(int i = 0; i < 2 * m_fileds; i = i + 2)
		{

			if( i != 2 * m_fileds - 2)
			{
			   str = str + pview->TB_TRANSFORMERS[i] + " AS " + pview->TB_TRANSFORMERS[i + 1] + ",";
			}
			else
			{
               str = str + pview->TB_TRANSFORMERS[i] + " AS " + pview->TB_TRANSFORMERS[i + 1];
			}

		}

	}
	else if(m_dataname == "TB_AMMETER")
	{
		
		//电表信息数据表
		for(int i = 0; i < 2 * m_fileds; i = i + 2)
		{

			if( i != 2 * m_fileds - 2)
			{
			   str = str + pview->TB_AMMETERS[i] + " AS " + pview->TB_AMMETERS[i + 1] + ",";
			}
			else
			{
               str = str + pview->TB_AMMETERS[i] + " AS " + pview->TB_AMMETERS[i + 1];
			}

		}

	}
	else if(m_dataname == "TB_USER")
	{
		
		//用户信息库数据表
		for(int i = 0; i < 2 * m_fileds; i = i + 2)
		{

			if( i != 2 * m_fileds - 2)
			{
			   str = str + pview->TB_USERS[i] + " AS " + pview->TB_USERS[i + 1] + ",";
			}
			else
			{
               str = str + pview->TB_USERS[i] + " AS " + pview->TB_USERS[i + 1];
			}

		}

	}
	else if(m_dataname == "TB_GARRISON")
	{
		
		//驻留数据表
		for(int i = 0; i < 2 * m_fileds; i = i + 2)
		{

			if( i != 2 * m_fileds - 2)
			{
			   str = str + pview->TB_GARRISONS[i] + " AS " + pview->TB_GARRISONS[i + 1] + ",";
			}
			else
			{
               str = str + pview->TB_GARRISONS[i] + " AS " + pview->TB_GARRISONS[i + 1];
			}

		}

	}	
	else if(m_dataname == "TB_CHANGEAMMETER")
	{
		
		//模块更换信息表
		for(int i = 0; i < 2 * m_fileds; i = i + 2)
		{

			if( i != 2 * m_fileds - 2)
			{
			   str = str + pview->TB_CHANGEAMMETERS[i] + " AS " + pview->TB_CHANGEAMMETERS[i + 1] + ",";
			}
			else
			{
               str = str + pview->TB_CHANGEAMMETERS[i] + " AS " + pview->TB_CHANGEAMMETERS[i + 1];
			}

		}

	}
	else if(m_dataname == "TB_REALTIME")
	{
		//正式读表数据表
		for(int i = 0; i < 2 * m_fileds; i = i + 2)
		{

			if( i != 2 * m_fileds - 2)
			{
			   str = str + pview->TB_REALTIMES[i] + " AS " + pview->TB_REALTIMES[i + 1] + ",";
			}
			else
			{
               str = str + pview->TB_REALTIMES[i] + " AS " + pview->TB_REALTIMES[i + 1];
			}

		}

	}
	else
	{
		str = "*";
	}

	return str;
}


