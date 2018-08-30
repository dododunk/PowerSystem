// ChildStation.cpp : implementation file
//

#include "stdafx.h"

#include "ChildStationDlg.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildStation dialog


CChildStationDlg::CChildStationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChildStationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChildStation)
	m_AddStation = _T("");
	//}}AFX_DATA_INIT
}


void CChildStationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChildStation)
	DDX_Control(pDX, IDC_LIST, m_ListBox);
	DDX_Text(pDX, IDC_ADDSTATION, m_AddStation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChildStationDlg, CDialog)
	//{{AFX_MSG_MAP(CChildStation)
	ON_BN_CLICKED(ID_ADD, OnAdd)
	ON_BN_CLICKED(ID_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildStation message handlers

//得到变电站信息
void CChildStationDlg::GetAllStationInfo()
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
	    strSql = "SELECT count(*) FROM TB_MANAGERANGE";
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//得到记录个数
		rs.GetFieldValue((short)0,strValue);
		
		//记录个数
		long fields = atol(strValue); 
		rs.Close();
		
		//删除原来的列表数据
		m_ListBox.ResetContent();

		if(fields  > 0)	
		{
      	    strSql = "SELECT USER_MANAGENO FROM TB_MANAGERANGE";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//读用户信息
			for(int j = 0;j < fields; j++)
			{
				
				//得到变电站编号信息
				rs.GetFieldValue((short)0,strValue);
				strValue.TrimLeft();
				strValue.TrimRight();
							
				//加入列表框
				m_ListBox.AddString(strValue);
						
				//库下滑一个记录
				rs.MoveNext();

			}
		
			//关闭数据库
		    rs.Close( );
		
		}
		
		db.Close( );
	}

}



BOOL CChildStationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//得到变电站编号信息
    GetAllStationInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//增加分局所管娈电站
void CChildStationDlg::OnAdd() 
{
    UpdateData(TRUE);
	CString   StrSql;

	m_AddStation.TrimLeft();
	m_AddStation.TrimRight();
		
	if(m_AddStation.IsEmpty())
	{
		MessageBox("新增分区管理机构编号不能为空!"," ",MB_OK|MB_ICONWARNING);
		return;
	}
	else
	{	
		
		
        
		StrSql.Format("RTRIM(USER_MANAGENO)='%s'",m_AddStation);

		if(CDataBaseInstance::GetAllRecordsCount("TB_MANAGERANGE",StrSql) < 1)
		{
			//没有此电话号码,则保存此电话
	    	StrSql.Format("INSERT INTO TB_MANAGERANGE(USER_MANAGENO) VALUES ('%s')",m_AddStation);
			CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
			m_AddStation =  "";
			UpdateData(FALSE);
			
			//得到变电站信息
            GetAllStationInfo();

		}
		else
		{
	     	MessageBox("此分局管理机构编号已经已经存在！"," ",MB_OK|MB_ICONWARNING);
		}

	}
	
}

//删除分局所管娈电站
void CChildStationDlg::OnDelete() 
{
	
	CString     StrSql;
	CString   StrValue;
	
	if(m_ListBox.GetCurSel() != LB_ERR)
	{
		
		if(MessageBox("你想删除这个分局管理机构编号吗？"," ",MB_YESNO|MB_ICONQUESTION)== IDYES)
		{
			
			//CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
			
			m_ListBox.GetText(m_ListBox.GetCurSel(),StrValue);
			
			StrSql.Format("RTRIM(USER_MANAGENO)='%s'",StrValue);
			
			if(CDataBaseInstance::GetAllRecordsCount("TB_MANAGERANGE",StrSql) > 0)
			{
				//有这个管理机构的号则删除
				StrValue.Format("DELETE FROM TB_MANAGERANGE WHERE %s",StrSql);
				CDataBaseInstance::ExecuteDataBaseSQL(StrValue);
				
				//得到变电站信息
                GetAllStationInfo();
			}
			
		}
		
	}
	
}
