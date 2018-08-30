// WuGongSpace.cpp : implementation file
//

#include "stdafx.h"

#include "WuGongSpaceDlg.h"


#include "IFRMView.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWuGongSpace dialog


CWuGongSpaceDlg::CWuGongSpaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWuGongSpaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWuGongSpace)
	m_wgspace = 20;
	//}}AFX_DATA_INIT
}


void CWuGongSpaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWuGongSpace)
	DDX_Text(pDX, IDC_WGSPACE, m_wgspace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWuGongSpaceDlg, CDialog)
	//{{AFX_MSG_MAP(CWuGongSpace)
	ON_EN_CHANGE(IDC_WGSPACE, OnChangeWgspace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWuGongSpace message handlers

BOOL CWuGongSpaceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString             str;

	str.Format("无功补偿表模块号【%s】",m_Module);
	SetWindowText(str);
	
	//对应模块的电容器容量
    m_wgspace = GetWuGongSpace(atol(m_Module));
	UpdateData(FALSE);

	return TRUE;  
}


//对应模块的电容器容量
int CWuGongSpaceDlg::GetWuGongSpace(long m_doule)
{
	CString strValue,StrSql;
	CDatabase           db;	

	m_Module.TrimLeft();
	m_Module.TrimRight();

	strValue.Format("WUGONG_MODULE='%s'",m_Module);

    //打开数据库
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//和CRecordset连上
		CRecordset    rs(&db );
		StrSql.Format("SELECT WUGONG_SPACE FROM TB_WUGONG  WHERE %s",strValue);
		rs.Open(CRecordset::dynaset,StrSql);	
		
		if(rs.IsEOF())
		{
			rs.Close( );
			db.Close( );
			return    0;
		}
		
		rs.GetFieldValue((short)0,strValue);
    	rs.Close( );
		db.Close( );

		return atoi(strValue);

	}

	return 0;
}

void CWuGongSpaceDlg::OnOK() 
{
    UpdateData(TRUE);
	CString   SqlStr;
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	SqlStr.Format("DELETE FROM TB_WUGONG WHERE WUGONG_MODULE='%s'",m_Module);
    CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

	SqlStr.Format("INSERT INTO TB_WUGONG(WUGONG_MODULE,WUGONG_SPACE) VALUES ('%s',%d)",m_Module,m_wgspace);
    CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

	CDialog::OnOK();
}

void CWuGongSpaceDlg::OnChangeWgspace() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
