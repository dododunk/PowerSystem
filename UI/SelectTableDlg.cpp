// SelectTable.cpp : implementation file
//

#include "stdafx.h"

#include "SelectTableDlg.h"
#include "SearchDlg.h"
#include "TimeSelectDlg.h"


#include "AppInfo.h"
#include "IFRMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectTable dialog
CSelectTableDlg::CSelectTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectTable)
	m_radio1 = 0;
	m_radio2 = 0;
	//}}AFX_DATA_INIT
}



void CSelectTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectTable)
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Radio(pDX, IDC_RADIO3, m_radio2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectTableDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectTable)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(ID_PASSOUT, OnPassout)
	ON_BN_CLICKED(ID_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectTable message handlers

BOOL CSelectTableDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//设置窗口的图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_PASS);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
    
	//设置缺省按钮
	SetDefID(IDCANCEL);

	StrTable = "TB_ELECTRICITY";
	Sqlstr   = "ALL";

	UpdateData(FALSE);
	
	//是从远程要数据
	m_selects  =  0;

	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//读数据种类
    if(AppInfo::Instance().m_WhichKind)
	{
		CWnd* pt = GetDlgItem(ID_CLEAR);
		pt->ShowWindow(SW_HIDE);
		pt = GetDlgItem(ID_PASSOUT);
		pt->ShowWindow(SW_HIDE);

	}
	
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectTableDlg::OnRadio2() 
{
	UpdateData(TRUE);


	Sqlstr   = "ALL";
	
	switch(m_radio2)
	{
	case 0:
		{
			StrTable = "TB_ELECTRICITY";
			break;
		}
	case 1:
		{
			StrTable = "TB_TRANSFORMER";
			break;
		}
	case 2:
		{
			StrTable = "TB_AMMETER";
			break;
		}
	case 3:
		{
			StrTable = "TB_USER";
			break;
		}
	case 4:
		{
			StrTable = "TB_REALTIME";
			break;
		}
	case 5:
		{
			StrTable = "TB_GARRISON";
			break;
		}

	}


	if(m_radio2  <  4)
	{
		//如果是前四个表
		CSearchDlg                   dlg;
		dlg.SetDataBaseName(StrTable);
		
		if(dlg.DoModal() == IDOK)
		{
			Sqlstr = dlg.m_totalsql;
		}

	}
	else
	{  
		//如果是后四个表
		CTimeSelectDlg             dlg;
		CString m_BeginStr,m_EndStr;

		if(dlg.DoModal() == IDOK)
		{
	        m_BeginStr.Format("%4d-%02d-%02d %02d:%02d:%02d",dlg.m_Begin.GetYear(),dlg.m_Begin.GetMonth(),dlg.m_Begin.GetDay(),0,0,0);
	        m_EndStr.Format("%4d-%02d-%02d %02d:%02d:%02d",dlg.m_End.GetYear(),dlg.m_End.GetMonth(),dlg.m_End.GetDay(),0,0,0);

			switch(m_radio2)
			{
			case 4:
				{
				
					Sqlstr.Format("REALTIME_TRANSCRIBETIME>='%s' AND REALTIME_TRANSCRIBETIME<='%s'",m_BeginStr,m_EndStr);
					break;
				}
			case 5:
				{
					Sqlstr.Format("GARRISON_HALTTIME>='%s' AND GARRISON_HALTTIME<='%s'",m_BeginStr,m_EndStr);
					break;
				}
			case 6:
				{
					Sqlstr.Format("读表时间>='%s' AND 读表时间<='%s'",m_BeginStr,m_EndStr);
					break;
				}
			}
	
		}

	}

}

void CSelectTableDlg::OnOK() 
{
	UpdateData(TRUE);
	
	switch(m_radio2)
	{
	case 0:
		{
			StrTable = "TB_ELECTRICITY";
			break;
		}
	case 1:
		{
			StrTable = "TB_TRANSFORMER";
			break;
		}
	case 2:
		{
			StrTable = "TB_AMMETER";
			break;
		}
	case 3:
		{
			StrTable = "TB_USER";
			break;
		}
	case 4:
		{
			StrTable = "TB_REALTIME";
			break;
		}
	case 5:
		{
			StrTable = "TB_GARRISON";
			break;
		}
	}

	

	if(MessageBox("你想导入远程数据表的数据到本地数据表中吗？"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
	   
	   m_selects = 0;
	   CDialog::OnOK();

	}

}



void CSelectTableDlg::OnPassout() 
{   
	UpdateData(TRUE);
	
	//条件选择
	switch(m_radio2)
	{
	case 0:
		{
			StrTable = "TB_ELECTRICITY";
			break;
		}
	case 1:
		{
			StrTable = "TB_TRANSFORMER";
			break;
		}
	case 2:
		{
			StrTable = "TB_AMMETER";
			break;
		}
	case 3:
		{
			StrTable = "TB_USER";
			break;
		}
	case 4:
		{
			StrTable = "TB_REALTIME";
			break;
		}
	case 5:
		{
			StrTable = "TB_GARRISON";
			break;
		}
	}

	

	if(MessageBox("你想把本地数据表数据传送到远程数据表中吗？"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
	   m_selects = 1;
	   CDialog::OnOK();
	}	
}


void CSelectTableDlg::OnClear() 
{
	
	CString      str;
    UpdateData(TRUE);

   	switch(m_radio2)
	{
	case 0:
		{ 
			str      = "你想删除远程机器上的电类电价数据表";
			StrTable = "TB_ELECTRICITY";
			break;
		}
	case 1:
		{   
			str      = "你想删除远程机器上的变台信息数据表";
			StrTable = "TB_TRANSFORMER";
			break;
		}
	case 2:
		{
			str      = "你想删除远程机器上的电表信息数据表";
			StrTable = "TB_AMMETER";
			break;
		}
	case 3:
		{
			str      = "你想删除远程机器上的用户信息数据表";
			StrTable = "TB_USER";
			break;
		}
	case 4:
		{
			str      = "你想删除远程机器上的正式读表数据表";
			StrTable = "TB_REALTIME";
			break;
		}
	case 5:
		{
			str      = "你想删除远程机器上的驻留数据数据表";
			StrTable = "TB_GARRISON";
			break;
		}
	}

	if(Sqlstr == "ALL")
	{
        str = str + "，范围［全部］的表数据吗？\r\n警告：删除后数据不能恢复！";
	}
	else
	{
        str = str + "，范围［" + Sqlstr + "］的表数据吗？\r\n警告：删除后数据不能恢复！";
	}

	if(MessageBox(str," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
		if(MessageBox("你真的确认想删除远程机器上的数据表数据吗？？！！\r\n警告：删除后数据不能恢复！后果可能是灾难性的！"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			m_selects =   2;
			CDialog::OnOK();
		}
		
	}	

}

void CSelectTableDlg::OnCancel() 
{
	CDialog::OnCancel();
}
