// MyDialogDataBar.cpp : implementation file
//

#include "stdafx.h"

#include "MyDialogDataBar.h"


#include "IFRMView.h"
#include "ShowDataDlg.h"
#include "DataBaseInstance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialogDataBar dialog


CMyDialogDataBar::CMyDialogDataBar()
{
	//{{AFX_DATA_INIT(CMyDialogDataBar)

	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar message handlers
BOOL CMyDialogDataBar::OnInitDialogBar()
{
	// Support for DDX mechanism
	// If you do not want DDX then
	// do not call base class
	CInitDialogBar::OnInitDialogBar();
	m_MaxPosition.vt   =   VT_I4;
    m_MaxPosition.lVal =      0;
 	return TRUE;
}

void CMyDialogDataBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDialogDataBar)
	DDX_Control(pDX, IDC_DBGRID, m_dbgrid);
	DDX_Control(pDX, IDC_REMOTEDATACTL, m_remotedatactrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDialogDataBar, CInitDialogBar)
	//{{AFX_MSG_MAP(CMyDialogDataBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialogDataBar message handlers

void CMyDialogDataBar::ChangeSize()
{
	CRect rect;
    GetClientRect(rect);
    m_dbgrid.SetWindowPos(NULL,20,3,rect.right-rect.left-20,rect.bottom-rect.top-8,SWP_SHOWWINDOW);
}


//显示数据
void CMyDialogDataBar::initializeFieldInfo(CString m_title,CString m_totalsql,int columns,VARIANT  position)
{
	CString        Sqlstr;
    m_remotedatactrl.SetDataSourceName(_T("ifrm"));
    m_totalsql.TrimLeft();
	m_totalsql.TrimRight();
	long    m_records =  0;
	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	if(m_totalsql == "ALL")
	{
		//公司名称,电站编号,变电站名称,线路编号,线路名称,变台名称,模块号,相,姓名,用户编号,原用户号,住址,电话,用电种类,电表编号,表计种类,安装时间,电表初值,倍率,用电描述
		Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNAME AS 变电站名称,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_MOTHERLINE  AS 母线编号,USER_LINENO AS 线路编号,USER_BAKMOTHERLINE  AS 备用母线,USER_BAKLINENO AS 备用出线,USER_PHASE AS 相,USER_PROTOCOL AS 抄表协议,USER_MODULENO AS 模块号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_DOWNVALUE AS 月报警量下限,USER_UPVALUE AS 月报警量上限,USER_DESCRIBE AS 用电描述 FROM %s ORDER BY USER_MODULENO","TB_USER");
	}
	else
	{  
		Sqlstr.Format("SELECT USER_COMPANY AS 公司名称,USER_STATIONNAME AS 变电站名称,USER_LINENAME AS 线路名称,USER_TRANSFORMERNO AS 变台名称,USER_NAME AS 姓名,USER_NO AS 用户编号,USER_MOTHERLINE  AS 母线编号,USER_LINENO AS 线路编号,USER_BAKMOTHERLINE  AS 备用母线,USER_BAKLINENO AS 备用出线,USER_PHASE AS 相,USER_PROTOCOL AS 抄表协议,USER_MODULENO AS 模块号,USER_OLDNO AS 原用户号,USER_ADDRESS AS 住址,USER_PHONE AS 电话,USER_ELECTRICITYKIND AS 用电种类,USER_AMMETERNO AS 电表编号,USER_AMMETERKIND AS 表计种类,USER_INSTALLTIME AS 安装时间,USER_INITIALVALUE  AS 电表初值,USER_MULTIPLE AS 倍率,USER_DOWNVALUE AS 月报警量下限,USER_UPVALUE AS 月报警量上限,USER_DESCRIBE AS 用电描述 FROM %s WHERE %s ORDER BY USER_MODULENO","TB_USER",m_totalsql);
	}
	
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
	m_dbgrid.Scroll(columns, 0);
	m_dbgrid.SetBackColor(RGB(255,255,255));
	m_dbgrid.SetEditActive(FALSE);
	
	VARIANT  VAR = m_dbgrid.GetFirstRow();
    m_dbgrid.SetFirstRow(VAR);
	m_dbgrid.SetBookmark(position);	/**/
	m_dbgrid.Refresh(); 

	m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", m_totalsql);

    m_MaxPosition.vt   =           VT_I4;
    m_MaxPosition.lVal =       m_records;

	Sqlstr.Format("%s：记录个数［%d］，模块个数［%d］",m_title,m_records,CDataBaseInstance::Getmoduls(m_totalsql));
    m_dbgrid.SetCaption(Sqlstr);
	
}

//下翻数据记录
void CMyDialogDataBar::ScrollRecord(VARIANT  position)
{
	VARIANT  VAR = m_dbgrid.GetFirstRow();
    m_dbgrid.SetFirstRow(VAR);
	
	if(position.lVal <= m_MaxPosition.lVal)
	{
		m_dbgrid.SetBookmark(position);	
		m_dbgrid.Refresh(); 
	}

}


