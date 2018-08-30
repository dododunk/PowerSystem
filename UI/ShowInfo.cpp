// ShowInfo.cpp : implementation file
//

#include "stdafx.h"

#include "ShowInfoDlg.h"


#include "IFRMView.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowInfo dialog


CShowInfoDlg::CShowInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowInfo)
	m_info = _T("");
	//}}AFX_DATA_INIT
}


void CShowInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowInfo)
	DDX_Text(pDX, IDC_INFO, m_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CShowInfo)
	ON_BN_CLICKED(ID_SAVEFILE, OnSavefile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowInfo message handlers

//保存信息
void CShowInfoDlg::OnSavefile() 
{	

	char szFilter[]="文本文件(*.TXT)|||";
	CFileDialog dlg(FALSE,"TXT","*.TXT",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	dlg.m_ofn.lpstrTitle = "保存文本文件为";
		  
	if(dlg.DoModal() == IDOK)
	{	
		m_info.TrimLeft();
        m_info.TrimRight();
	
		//写入文本文件
		FILE *text;
	
		if((text = fopen(dlg.GetPathName(),"wb")) != NULL)
		{
			
			fputs(m_info + "\r\n",text);
			fclose(text);
			MessageBox("文本文件保存成功！"," ",MB_OK);
			
		}

	}

}

//检查更新的情况
void CShowInfoDlg::CheckUseData()
{
	//打开数据库
	CDatabase            db;
	CString strSql,strValue,strValue1,strValue2,strValue3,strValue4,strValue5;
	long       fields =   0;
	m_info            =  "";
	int           j   =   0;

	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//如果时间不同的话
	strValue = pview->GetRefreshTime();
    strValue.TrimLeft();
    strValue.TrimRight();

	if(!strValue.IsEmpty())
	{   
		m_info = m_info + "服务器用户数据文件更新时间：" + strValue + "\r\n";
	
		if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
		{
			//和CRecordset连上
			CRecordset rs(&db );
		/*	strSql = "SELECT  count(*) FROM TB_USER  WHERE USER_AMMETERNO NOT IN (SELECT USER_AMMETERNO FROM TB_USERBAK)";
			rs.Open(CRecordset::forwardOnly,strSql);
			//得到记录个数
			rs.GetFieldValue((short)0,strValue);
			//记录个数
			fields = atol(strValue); 
			rs.Close();

			if(fields > 0)
			{
				
				strSql = "SELECT  USER_STATIONNAME,USER_STATIONNO,USER_MODULENO,USER_IDNO FROM TB_USER  WHERE USER_AMMETERNO NOT IN (SELECT USER_AMMETERNO FROM TB_USERBAK) ORDER BY USER_STATIONNO,USER_MODULENO";
				
				m_info = m_info + "新增的模块如下表：\r\n";
				
				strValue.Format("%20.20s   %s   %s   %s","变电站名","变电站号","模块号","模块索引号");;
				m_info = m_info  +  strValue + "\r\n";
				
				rs.Open(CRecordset::forwardOnly,strSql);
				
				//读用户信息
				for( j = 0;j < fields; j++)
				{
					rs.GetFieldValue((short)0,strValue1);
					strValue1.TrimRight();
					rs.GetFieldValue((short)1,strValue2);
					strValue2.TrimRight();
					rs.GetFieldValue((short)2,strValue3);
					strValue3.TrimRight();
					rs.GetFieldValue((short)3,strValue4);
					strValue4.TrimRight();  
					strValue.Format("%20.20s      %5.5s       %8.8s        %4.4s",strValue1,strValue2,strValue3,strValue4);
					m_info = m_info  +  strValue + "\r\n";
					
					//库下滑一个记录
					rs.MoveNext();
				}
				
				//关闭数据库
				rs.Close( );
			}
			
			strSql = "SELECT count(*) FROM TB_USERBAK  WHERE USER_AMMETERNO NOT IN (SELECT USER_AMMETERNO FROM TB_USER)";
			rs.Open(CRecordset::forwardOnly,strSql);
			//得到记录个数
			rs.GetFieldValue((short)0,strValue);
			//记录个数
			fields = atol(strValue); 
			rs.Close();
			
			if(fields > 0)
			{
				//删除的模块号
				strSql = "SELECT USER_STATIONNAME,USER_STATIONNO,USER_MODULENO,USER_IDNO FROM TB_USERBAK  WHERE USER_AMMETERNO NOT IN (SELECT USER_AMMETERNO FROM TB_USER) ORDER BY USER_STATIONNO,USER_MODULENO";
				
				m_info = m_info + "\r\n\r\n删除的模块如下表：\r\n ";
				
				strValue.Format("%20.20s   %s   %s   %s","变电站名","变电站号","模块号","模块索引号");;
				m_info = m_info  +  strValue + "\r\n";
				
				rs.Open(CRecordset::forwardOnly,strSql);
				
				//读用户信息
				for( j = 0;j < fields; j++)
				{
					rs.GetFieldValue((short)0,strValue1);
					strValue1.TrimRight();
					rs.GetFieldValue((short)1,strValue2);
					strValue2.TrimRight();
					rs.GetFieldValue((short)2,strValue3);
					strValue3.TrimRight();
					rs.GetFieldValue((short)3,strValue4);
					strValue4.TrimRight();  
					strValue.Format("%20.20s      %5.5s       %8.8s        %4.4s",strValue1,strValue2,strValue3,strValue4);
					m_info = m_info  +  strValue + "\r\n";
					
					//库下滑一个记录
					rs.MoveNext();
				}
				
				//关闭数据库
				rs.Close( ); 
			}
            */
	
			strValue = "USER_MODULENO IS NULL OR USER_MODULENO<101 OR USER_MODULENO>13107115 OR USER_MODULENO%100 > 15 OR USER_LINENO IS NULL OR USER_LINENO> 16 OR USER_LINENO<1 OR USER_MOTHERLINE IS NULL OR USER_MOTHERLINE<1 OR USER_MOTHERLINE>4";
			fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",strValue);
			
			if(fields > 0)
			{
				strValue.Format("\r\n模块输入参数检查：   \r\n     有%d条记录其输入的参数不符合模块采集要求！模块号\r\n范围为［101，13107115］，最后二位应小于15，母线编号\r\n应为［1，4］，出线编号应为［1，16］",fields);
			}
			else
			{	
				strValue.Format("模块输入参数检查：   \r\n     暂时没有找到有错误的记录！");
				m_info = m_info + strValue;
				UpdateData(FALSE);
				return;
			}
			m_info = m_info + strValue;
			
			//参数不合格的模块号
			strValue = "USER_MODULENO IS NULL OR USER_MODULENO<101 OR USER_MODULENO>13107115 OR USER_MODULENO%100 > 15 OR USER_LINENO IS NULL OR USER_LINENO> 16 OR USER_LINENO<1 OR USER_MOTHERLINE IS NULL OR USER_MOTHERLINE<1 OR USER_MOTHERLINE>4";
			strSql.Format("SELECT USER_STATIONNAME,USER_STATIONNO,USER_MOTHERLINE,USER_LINENO,USER_MODULENO FROM TB_USER  WHERE  %s",strValue);
			
			m_info = m_info + "\r\n\r\n参数不合格模块如下：\r\n";
			
			strValue.Format("%20.20s   %s   %s   %s    %s","变电站名","变电站号","母线编号","出线编号","模块号");
			m_info = m_info  +  strValue + "\r\n";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//读用户信息
			for( j = 0;j < fields; j++)
			{
				rs.GetFieldValue((short)0,strValue1);
				strValue1.TrimRight();
				rs.GetFieldValue((short)1,strValue2);
				strValue2.TrimRight();
				rs.GetFieldValue((short)2,strValue3);
				strValue3.TrimRight();
				rs.GetFieldValue((short)3,strValue4);
				strValue4.TrimRight();
				rs.GetFieldValue((short)4,strValue5);
				strValue5.TrimRight();  
				strValue.Format("%20.20s      %5.5s       %14.14s        %4.4s   %18.18s",strValue1,strValue2,strValue3,strValue4,strValue5);
				m_info = m_info  +  strValue + "\r\n";
				
				//库下滑一个记录
				rs.MoveNext();
			}
			
			//关闭数据库
			rs.Close( ); 
			
			db.Close( );
		 }
		 
	}

	UpdateData(FALSE);

}

BOOL CShowInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//检查数据
    CheckUseData();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
