// UserInfo.cpp : implementation file
//

#include "stdafx.h"

#include "UserInfoDlg.h"
#include "SearchDlg.h"
#include "ShowInfoDlg.h"


#include "IFRMView.h"
#include "AmetterDlg.h"
#include "TransformerDlg.h"
#include "WuGongSpaceDlg.h"
#include "DataBaseInstance.h"
#include "RuntimeAccount.h"
#include "AppInfo.h"

#include "AmetterRecordset.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserInfo dialog


CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserInfo)
	m_pSet           =  NULL;
	m_times          =     0;
	m_radios         =    -1;
	m_ammeterradio   =    -1;
	m_supplykinds    =    -1;
	m_runnings       =     0;
	//}}AFX_DATA_INIT
	m_adding         = FALSE;
	m_modified       = FALSE;
}

CUserInfoDlg::CUserInfoDlg(CUseInfoRecordSet* pSet,CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfoDlg::IDD, pParent)
{

	m_pSet  = pSet;

}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserInfo)
	DDX_Control(pDX, IDC_BAKLINECOMBO, m_baklinecombox);
	DDX_Control(pDX, IDC_BAKMOTHERCOMBO, m_bakmotherline);
	DDX_Control(pDX, IDC_AMMTERCOMBO, m_ammeter);
	DDX_Control(pDX, IDC_LINECOMBO, m_linecombox);
	DDX_Control(pDX, IDC_MOTHERCOMBO, m_motherline);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_SEACHBROWSE, m_searchbrowse);
	DDX_Control(pDX, IDC_SAVEDATA, m_savedata);
	DDX_Control(pDX, IDC_PREVIOUSRECORD, m_previousrecord);
	DDX_Control(pDX, IDC_NEXTRECORD, m_nextrecord);
	DDX_Control(pDX, IDC_MODIFY, m_modify);
	DDX_Control(pDX, IDC_LASTRECORD, m_lastrecord);
	DDX_Control(pDX, IDC_DELRECORD, m_delrecord);
	DDX_Control(pDX, IDC_ADDRECORD, m_addrecord);
	DDX_Control(pDX, IDC_FIRSTRECORD, m_first);
	DDX_Control(pDX, IDC_GIF, m_Picture);
	DDX_Control(pDX, IDC_MODULENO, m_moduleno);
	DDX_DateTimeCtrl(pDX, IDC_INSTALLDATE, m_times);
	DDX_Radio(pDX, IDC_RADIO2, m_radios);
	DDX_Radio(pDX, IDC_RADIO3, m_ammeterradio);
	DDX_Radio(pDX, IDC_RADIO14, m_supplykinds);
	DDX_FieldText(pDX, IDC_COMPANY, m_pSet->m_USER_COMPANY, m_pSet);
	DDX_FieldText(pDX, IDC_POWERSTATIONNO, m_pSet->m_USER_STATIONNO, m_pSet);
	DDX_FieldText(pDX, IDC_POWERSTATION, m_pSet->m_USER_STATIONNAME, m_pSet);
	DDX_FieldText(pDX, IDC_LINENO, m_pSet->m_USER_LINENO, m_pSet);
	DDX_FieldText(pDX, IDC_GENERATRIXNO, m_pSet->m_USER_MOTHERLINE, m_pSet);
	DDX_FieldText(pDX, IDC_LINE, m_pSet->m_USER_LINENAME, m_pSet);
	DDX_FieldText(pDX, IDC_TRANSFORMERNO, m_pSet->m_USER_TRANSFORMERNO, m_pSet);
	DDX_FieldText(pDX, IDC_MODULENO, m_pSet->m_USER_MODULENO, m_pSet);
	DDX_FieldText(pDX, IDC_NAME, m_pSet->m_USER_NAME, m_pSet);
	DDX_FieldText(pDX, IDC_USERNO, m_pSet->m_USER_NO, m_pSet);
	DDX_FieldText(pDX, IDC_OLDUSERNO, m_pSet->m_USER_OLDNO, m_pSet);
	DDX_FieldText(pDX, IDC_ADDRESS, m_pSet->m_USER_ADDRESS, m_pSet);
	DDX_FieldText(pDX, IDC_TELEPHONE, m_pSet->m_USER_PHONE, m_pSet);
	DDX_FieldText(pDX, IDC_AMMETTERNO, m_pSet->m_USER_AMMETERNO, m_pSet);
	DDX_FieldText(pDX, IDC_CTSCALE, m_pSet->m_USER_MULTIPLE, m_pSet);
	DDX_FieldText(pDX, IDC_USEDESCRIBE, m_pSet->m_USER_DESCRIBE, m_pSet);
	DDX_FieldText(pDX, IDC_TABLEBOTTOMDATA, m_pSet->m_USER_INITIALVALUE, m_pSet);
	DDX_FieldText(pDX, IDC_PROTOCOL, m_pSet->m_USER_PROTOCOL, m_pSet);
	DDX_FieldText(pDX, IDC_ELCTYPE, m_pSet->m_USER_AMMETERTYPE, m_pSet);
	DDX_FieldText(pDX, IDC_SENDANGLE, m_pSet->m_USER_SENDANGLE, m_pSet);
	DDX_FieldText(pDX, IDC_ELCKIND, m_pSet->m_USER_ELECTRICITYKIND, m_pSet);
	DDX_FieldText(pDX, IDC_UPVALUE, m_pSet->m_USER_UPVALUE, m_pSet);
	DDX_FieldText(pDX, IDC_DOWNVALUE, m_pSet->m_USER_DOWNVALUE, m_pSet);
	DDX_FieldText(pDX, IDC_BAKGENERATRIXNO, m_pSet->m_USER_BAKMOTHERLINE, m_pSet);
	DDX_FieldText(pDX, IDC_BAKLINENO, m_pSet->m_USER_BAKLINENO, m_pSet);
	DDX_Radio(pDX, IDC_RADIO1, m_runnings);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CUserInfo)
	ON_BN_CLICKED(IDC_FIRSTRECORD, OnFirstrecord)
	ON_BN_CLICKED(IDC_PREVIOUSRECORD, OnPreviousrecord)
	ON_BN_CLICKED(IDC_NEXTRECORD, OnNextrecord)
	ON_BN_CLICKED(IDC_LASTRECORD, OnLastrecord)
	ON_BN_CLICKED(IDC_ADDRECORD, OnAddrecord)
	ON_BN_CLICKED(IDC_DELRECORD, OnDelrecord)
	ON_BN_CLICKED(IDC_SEACHBROWSE, OnSeachbrowse)
	ON_BN_CLICKED(IDC_SAVEDATA, OnSavedata)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_EN_CHANGE(IDC_COMPANY, OnChangeCompany)
	ON_EN_CHANGE(IDC_POWERSTATION, OnChangePowerstation)
	ON_EN_CHANGE(IDC_LINE, OnChangeLine)
	ON_EN_CHANGE(IDC_TRANSFORMERNO, OnChangeTransformerno)
	ON_EN_CHANGE(IDC_MODULENO, OnChangeModuleno)
	ON_BN_CLICKED(IDC_RADIO14, OnRadio14)
	ON_BN_CLICKED(IDC_RADIO16, OnRadio16)
	ON_BN_CLICKED(IDC_RADIO15, OnRadio15)
	ON_BN_CLICKED(IDC_CHAAMMETER, OnChaammeter)
	ON_BN_CLICKED(IDC_BTSEARCH, OnBtsearch)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInfo message handlers
void CUserInfoDlg::OnFirstrecord() 
{ 
   SetReadOnly(TRUE);

   if(!(m_pSet->IsEOF() && m_pSet->IsBOF()))
   {
	   m_pSet->MoveFirst(); 
	   
	   //隐藏列表框
	   ShowCombox(FALSE);
	   
	   m_times         = m_pSet->m_USER_INSTALLTIME;
	   m_radios        = m_pSet->m_USER_PHASE;
	   m_runnings      = m_pSet->m_USER_RUNSTATUS;
	   m_ammeterradio  = m_pSet->m_USER_AMMETERKIND;
	   m_supplykinds   = m_pSet->m_USER_SUPPLYMODE;
	   m_adding        = FALSE;
	   m_modified      = FALSE;
	   UpdateData(FALSE);
   }
   
   //GIF 隐藏
   CWnd * pts = GetDlgItem(IDC_GIF);
   pts->ShowWindow(SW_HIDE);
}

void CUserInfoDlg::OnPreviousrecord() 
{   
	if (m_pSet->IsBOF() && m_pSet->IsEOF())
	{
	 	return;
	}

	if (!m_pSet->IsBOF())
	{
		m_pSet->MovePrev();
	}
	else
	{
		m_pSet->MoveFirst();

	}
	
	if (m_pSet->IsBOF())
	{
		m_pSet->MoveFirst();
	}

    //隐藏列表框
	ShowCombox(FALSE);

    m_times         = m_pSet->m_USER_INSTALLTIME;
    m_radios        = m_pSet->m_USER_PHASE;
	m_runnings      = m_pSet->m_USER_RUNSTATUS;
    m_ammeterradio  = m_pSet->m_USER_AMMETERKIND;
	m_supplykinds   = m_pSet->m_USER_SUPPLYMODE;
	
	m_adding        = FALSE;
	m_modified      = FALSE;
    SetReadOnly(TRUE);
	
	if(m_pSet->CanBookmark())
	{
		m_pSet->GetBookmark(varCurrentRecord);
	}

	UpdateData(FALSE);	

	//GIF 隐藏
	CWnd * pts = GetDlgItem(IDC_GIF);
	pts->ShowWindow(SW_HIDE);
}

void CUserInfoDlg::OnNextrecord() 
{
	if (m_pSet->IsBOF() && m_pSet->IsEOF())
	{
	 	return;
	}

	if (!m_pSet->IsEOF())
	{
        m_pSet->MoveNext();
	}
	else
	{
		m_pSet->MoveLast();
	}
	
	if (m_pSet->IsEOF())
	{
		m_pSet->MoveLast();
	}

	if (!m_pSet->CanScroll())
	{
		m_pSet->SetFieldNull(NULL);
	}

    //隐藏列表框
	ShowCombox(FALSE);

	m_adding   =             FALSE;
	m_modified =            FALSE;
    m_times    = m_pSet->m_USER_INSTALLTIME;
    m_radios   = m_pSet->m_USER_PHASE;
	m_runnings      = m_pSet->m_USER_RUNSTATUS;
    m_ammeterradio  = m_pSet->m_USER_AMMETERKIND;
	m_supplykinds   = m_pSet->m_USER_SUPPLYMODE;
	SetReadOnly(TRUE);

	if(m_pSet->CanBookmark())
	{
		m_pSet->GetBookmark(varCurrentRecord);
	}

	UpdateData(FALSE);

	//GIF 隐藏
	CWnd * pts = GetDlgItem(IDC_GIF);
	pts->ShowWindow(SW_HIDE);
}

void CUserInfoDlg::OnLastrecord() 
{
	 if (m_pSet->IsBOF() && m_pSet->IsEOF())
	 {
	 	return;
	 }
     m_pSet->MoveLast();

	 //隐藏列表框
	 ShowCombox(FALSE);

     m_times    = m_pSet->m_USER_INSTALLTIME;
     m_radios   = m_pSet->m_USER_PHASE;
	 m_runnings      = m_pSet->m_USER_RUNSTATUS;
     m_ammeterradio  = m_pSet->m_USER_AMMETERKIND;
	 m_supplykinds   = m_pSet->m_USER_SUPPLYMODE;
	 m_adding        = FALSE;
	 m_modified      = FALSE;

	 SetReadOnly(TRUE);

	 if(m_pSet->CanBookmark())
	 {
		m_pSet->GetBookmark(varCurrentRecord);
	 }

	 UpdateData(FALSE);
	
	 //GIF 隐藏
	 CWnd * pts = GetDlgItem(IDC_GIF);
	 pts->ShowWindow(SW_HIDE);
}


void CUserInfoDlg::OnAddrecord() 
{

	if(m_adding ==  TRUE)
	{
		if(m_pSet->CanBookmark())
		{
			m_pSet->GetBookmark(varCurrentRecord);
		}

		OnSavedata();

	}

	CWnd * pts = GetDlgItem(IDC_GIF);
	pts->ShowWindow(SW_SHOW);
	
	//显示列表框
	ShowCombox(TRUE);

	//公司名称
	CEdit* pt = (CEdit*)GetDlgItem(IDC_COMPANY);
	if(pt)
	{
	   pt->GetWindowText(str[0]);
	}

    //电站编号
	pt = (CEdit*)GetDlgItem(IDC_POWERSTATIONNO);
	if(pt)
	{
	   pt->GetWindowText(str[1]);
	}

    //变电站名
	pt = (CEdit*)GetDlgItem(IDC_POWERSTATION);
	if(pt)
	{
	   pt->GetWindowText(str[2]);
	}

  	//线路名称
	pt = (CEdit*)GetDlgItem(IDC_LINE);
	if(pt)
	{
	   pt->GetWindowText(str[3]);
	}
	
	//变台名称
	pt = (CEdit*)GetDlgItem(IDC_TRANSFORMERNO);
	if(pt)
	{
    	pt->GetWindowText(str[4]);
	}	
	
	//用电描述
	pt = (CEdit*)GetDlgItem(IDC_USEDESCRIBE);
	if(pt)
	{
    	pt->GetWindowText(str[5]);
	}

	//抄表协议
	pt = (CEdit*)GetDlgItem(IDC_PROTOCOL);
	if(pt)
	{
    	pt->GetWindowText(str[6]);
	}

	//用电编号
	pt = (CEdit*)GetDlgItem(IDC_ELCKIND);
	if(pt)
	{
    	pt->GetWindowText(str[7]);
	}

	//姓名
	pt = (CEdit*)GetDlgItem(IDC_NAME);
	if(pt)
	{
    	pt->GetWindowText(str[8]);
	}
	
	//地址
	pt = (CEdit*)GetDlgItem(IDC_ADDRESS);
	if(pt)
	{
    	pt->GetWindowText(str[9]);
	}

	m_adding    =  TRUE;
	m_modified  = FALSE;
	CTime time  = CTime::GetCurrentTime();
	m_times     =  time;    
	m_pSet->SetFieldNull(NULL);
	SetReadOnly(FALSE);

	//相
	m_radios       =   3;
	
	//表计种类
	m_ammeterradio =   0;
	m_supplykinds  =   0;
	m_runnings     =   0;
	
	UpdateData(FALSE);

	//公司名称
	pt = (CEdit*)GetDlgItem(IDC_COMPANY);
	if(pt)
	{
	   pt->SetWindowText(str[0]);
	}

    //电站编号
	pt = (CEdit*)GetDlgItem(IDC_POWERSTATIONNO);
	if(pt)
	{
	   pt->SetWindowText(str[1]);
	}

    //变电站名
	pt = (CEdit*)GetDlgItem(IDC_POWERSTATION);
	if(pt)
	{
	   pt->SetWindowText(str[2]);
	}

    //线路名称
	pt = (CEdit*)GetDlgItem(IDC_LINE);
	if(pt)
	{
	   pt->SetWindowText(str[3]);
	}
	
	//变台号码
	pt = (CEdit*)GetDlgItem(IDC_TRANSFORMERNO);
	if(pt)
	{
    	pt->SetWindowText(str[4]);
	}

	//电表初值
	pt = (CEdit*)GetDlgItem(IDC_TABLEBOTTOMDATA);
	if(pt)
	{
    	pt->SetWindowText("0");//str[6]);
	}

	//倍率
	pt = (CEdit*)GetDlgItem(IDC_CTSCALE);
	if(pt)
	{
    	pt->SetWindowText("1");//str[7]);
	}
	
	//用电描述
	pt = (CEdit*)GetDlgItem(IDC_USEDESCRIBE);
	if(pt)
	{
    	pt->SetWindowText(str[5]);
	}
	
	//抄表协议
	pt = (CEdit*)GetDlgItem(IDC_PROTOCOL);
	if(pt)
	{
    	pt->SetWindowText(str[6]);
	}
	
	//发射角度
	pt = (CEdit*)GetDlgItem(IDC_SENDANGLE);
	if(pt)
	{
    	pt->SetWindowText("0");
	}	
	
	//用电编号
	pt = (CEdit*)GetDlgItem(IDC_ELCKIND);
	if(pt)
	{
    	pt->SetWindowText(str[7]);
	}

	//姓名
	pt = (CEdit*)GetDlgItem(IDC_NAME);
	if(pt)
	{
    	pt->SetWindowText(str[8]);
	}
	
	//地址
	pt = (CEdit*)GetDlgItem(IDC_ADDRESS);
	if(pt)
	{
    	pt->SetWindowText(str[9]);
	}

	m_moduleno.SetFocus();

}

void CUserInfoDlg::OnDelrecord() 
{
    CString   StrSql;

	if (m_pSet->IsBOF() && m_pSet->IsEOF())
	{
	 	return;
	}

	if(MessageBox("你想删除这条记录吗？警告：删除后数据不能恢复！！","询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		//修改或增加了记录
	    m_IfAdding = TRUE;

		CRecordsetStatus status;
		try
		{
			m_pSet->Delete();
		}
		catch(CDBException* e) 
		{
			MessageBox(e->m_strError,"警告",MB_OK|MB_ICONWARNING);
			e->Delete();
			m_pSet->MoveFirst(); // lost our place!
			UpdateData(FALSE);
			return;
		}

		m_pSet->GetStatus(status);
		if (status.m_lCurrentRecord == 0)
		{
			// We deleted last of 2 records
			m_pSet->MoveFirst();
		}
		else 
		{
			m_pSet->MoveNext();
		}
	
		m_pSet->Requery(); // for sorted sets
	
		m_times         =  m_pSet->m_USER_INSTALLTIME;
        m_radios        = m_pSet->m_USER_PHASE;
		m_runnings      = m_pSet->m_USER_RUNSTATUS;
		m_supplykinds   = m_pSet->m_USER_SUPPLYMODE;
		m_adding        =              FALSE; 
		m_modified      =              FALSE;
		
		SetReadOnly(TRUE);
		UpdateData(FALSE);
	}

}

void CUserInfoDlg::OnSeachbrowse() 
{

    CSearchDlg        dlg;
	m_adding   = FALSE; 
	m_modified = FALSE;

	dlg.SetDataBaseName("TB_USER");
	
	
	long m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL");

	dlg.m_FieldPositionm = m_FieldPosition;//字段名称位置
	dlg.m_symbol         =        m_symbol;//符号
    dlg.m_FieldName      =     m_FieldName;//值    

	if(dlg.DoModal() == IDOK)
	{
		m_pSet->m_strFilter = dlg.m_totalsql;
	
		m_FieldPosition = dlg.m_FieldPositionm;//字段名称位置
        m_symbol        = dlg.m_symbol;        //符号
        m_FieldName     = dlg.m_FieldName ;    //值
		
		m_pSet->Requery();
		OnNextrecord();

	}
	else
	{
		m_pSet->m_strFilter = "";
	    m_pSet->Requery();
	}
	
	//记录有变化
	if(dlg.m_modified || CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") != m_records)
	{	
		//修改或增加了记录
	    m_IfAdding = TRUE;
	}

}

BOOL CUserInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CWnd * pts = GetDlgItem(IDC_GIF);
	pts->ShowWindow(SW_HIDE);

	//母线编号,线路编号
	m_motherline.SetCurSel(0);
	m_linecombox.SetCurSel(0);
	
	//备用母线编号,线路号
	m_bakmotherline.SetCurSel(0);
	m_baklinecombox.SetCurSel(0);
   
	//初始化电表列表列表
    InitializeAmmeterCombo();

	//电表型号
	m_ammeter.SetCurSel(0);

	//母线编号,线路编号
	m_motherline.ShowWindow(SW_HIDE);
	m_linecombox.ShowWindow(SW_HIDE);
	
	//备用母线编号,线路号
	m_bakmotherline.ShowWindow(SW_HIDE);
	m_baklinecombox.ShowWindow(SW_HIDE);
	m_ammeter.ShowWindow(SW_HIDE);

	//GIF图片
	if (m_Picture.Load(MAKEINTRESOURCE(IDR_TYPE),_T("GIF")))
		m_Picture.Draw();

	m_pSet->m_strFilter =   m_filtercondtion;
	m_pSet->m_strSort   =   "USER_MODULENO ASC";
	m_pSet->Requery();
		
//	m_first.SetBitmaps(IDB_DOWNBUTTON,NULL,NULL,NULL);
//	m_first.DrawBorder(FALSE);
//	m_first.SetAlign(CButtonST::ST_ALIGN_OVERLAP);

	//设置窗口的图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_MODULES);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	m_radios        =  0;
	m_runnings      =  0;

	m_FieldPosition =  0;//字段名称位置
	m_symbol        =  0;//符号
	m_FieldName     = "";//值 

	OnFirstrecord();

	UpdateData(FALSE);	

	//修改或增加了记录
	m_IfAdding = FALSE;
    CWnd*          ptt; 
	
	//包头专用，封 2004.10.8 胡高明	
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
   	CIFRMApp*   pt = (CIFRMApp*)AfxGetApp();



	if(!m_filtercondtion.IsEmpty())
	{
		//增加修改模块数据
		ptt = GetDlgItem(IDC_SEACHBROWSE);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_DELRECORD);
		ptt->EnableWindow(FALSE);
		
		//母线赋值,线路赋值
		if(m_pSet->m_USER_MOTHERLINE > 0)
		{
			m_motherline.SetCurSel(m_pSet->m_USER_MOTHERLINE - 1);
		}
				
		if(m_pSet->m_USER_LINENO > 0)
		{
			m_linecombox.SetCurSel(m_pSet->m_USER_LINENO - 1);
		}
		
		//备用母线赋值,线路赋值
		if(m_pSet->m_USER_BAKMOTHERLINE > 0)
		{
			m_bakmotherline.SetCurSel(m_pSet->m_USER_BAKMOTHERLINE);
		}
		else
		{
			m_bakmotherline.SetCurSel(0);
		}
				
		if(m_pSet->m_USER_BAKLINENO > 0)
		{
			m_baklinecombox.SetCurSel(m_pSet->m_USER_BAKLINENO);
		}
		else
		{
			m_baklinecombox.SetCurSel(0);
		}

		//电表型号
		if(m_ammeter.FindString(-1, m_pSet->m_USER_AMMETERTYPE) != CB_ERR)
		{
			m_ammeter.SetCurSel(m_ammeter.FindString(-1, m_pSet->m_USER_AMMETERTYPE));
		}
		
	}

	//用户权限
	//CIFRMApp* Apppt = (CIFRMApp*)AfxGetApp();

	if(CRuntimeAccount::GetCurrentPrivilege() > 1)
	{
	    ptt = GetDlgItem(IDC_DELRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_ADDRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_MODIFY);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SAVEDATA);
		ptt->EnableWindow(FALSE);
	}
	
	return TRUE;  
}

void CUserInfoDlg::OnSavedata() 
{
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CString      StrSql;
	
	//抄表协议
	CIFRMApp* Apppt = (CIFRMApp*)AfxGetApp();
			
	//用户最多为2000户
	if(AppInfo::Instance().m_2000Users)
	{

		if(CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL") > 2000)
		{
			MessageBox("对不起，你的用户数据已超出2000户，请先升级软件再管理更多的用户！"," ",MB_OK|MB_ICONWARNING);
			return;
		}

	}
  
	if(m_adding == TRUE)
	{
	
		if(!m_pSet->IsEOF())
		{
		  m_pSet->MoveLast();
		}
		
		m_modified = FALSE;
		m_pSet->AddNew();

        //母线编号,线路编号
		m_motherline.GetLBText(m_motherline.GetCurSel(),StrSql);
		StrSql.TrimLeft();
        StrSql.TrimRight();
		CEdit* editpt = (CEdit*)GetDlgItem(IDC_GENERATRIXNO);
		editpt->SetWindowText(StrSql);
			
		m_linecombox.GetLBText(m_linecombox.GetCurSel(),StrSql);
		StrSql.TrimLeft();
        StrSql.TrimRight();
		editpt = (CEdit*)GetDlgItem(IDC_LINENO);
		editpt->SetWindowText(StrSql); 
		
		//备用母线编号,线路编号
		if(m_bakmotherline.GetCurSel() > 0)
		{
			m_bakmotherline.GetLBText(m_bakmotherline.GetCurSel(),StrSql);
			StrSql.TrimLeft();
			StrSql.TrimRight();
			editpt = (CEdit*)GetDlgItem(IDC_BAKGENERATRIXNO);
			editpt->SetWindowText(StrSql);
		}
		else
		{	
			editpt = (CEdit*)GetDlgItem(IDC_BAKGENERATRIXNO);
			editpt->SetWindowText("0");
		}

        if(m_baklinecombox.GetCurSel() > 0)
		{	
			m_baklinecombox.GetLBText(m_baklinecombox.GetCurSel(),StrSql);
			StrSql.TrimLeft();
			StrSql.TrimRight();
			editpt = (CEdit*)GetDlgItem(IDC_BAKLINENO);
			editpt->SetWindowText(StrSql);
		}
		else
		{
			editpt = (CEdit*)GetDlgItem(IDC_BAKLINENO);
			editpt->SetWindowText("0");
		}

		//电表型号
		if(m_ammeter.GetCurSel() > 0)
		{
			m_ammeter.GetLBText(m_ammeter.GetCurSel(),StrSql);
			StrSql.TrimLeft();
			StrSql.TrimRight();
			editpt = (CEdit*)GetDlgItem(IDC_ELCTYPE);
			editpt->SetWindowText(StrSql);
		}
		else
		{
			editpt = (CEdit*)GetDlgItem(IDC_ELCTYPE);
			editpt->SetWindowText("");
		}

		UpdateData(TRUE);

		//公司名称
		editpt = (CEdit*)GetDlgItem(IDC_COMPANY);
		editpt->GetWindowText(StrSql);
        
		StrSql.TrimLeft();
        StrSql.TrimRight();

		if(StrSql.IsEmpty())
		{	
			editpt->SetFocus();
			MessageBox("公司名称不能为空！","警告",MB_OK|MB_ICONWARNING);
			return;
		}

		//变电站名称
	    editpt = (CEdit*)GetDlgItem(IDC_POWERSTATION);
		editpt->GetWindowText(StrSql);
        
		StrSql.TrimLeft();
        StrSql.TrimRight();

		if(StrSql.IsEmpty())
		{	
			editpt->SetFocus();
			MessageBox("变电站名称不能为空！","警告",MB_OK|MB_ICONWARNING);
			return;
		}	
		
		//线路名称
	    editpt = (CEdit*)GetDlgItem(IDC_LINE);
		editpt->GetWindowText(StrSql);
        
		//
		StrSql.TrimLeft();
        StrSql.TrimRight();

		//
		if(StrSql.IsEmpty())
		{	
			editpt->SetFocus();
			MessageBox("线路名称不能为空！","警告",MB_OK|MB_ICONWARNING);
			return;
		}	
		
		//变台名称
	    editpt = (CEdit*)GetDlgItem(IDC_TRANSFORMERNO);
		editpt->GetWindowText(StrSql);
        
		StrSql.TrimLeft();
        StrSql.TrimRight();

		//
		if(StrSql.IsEmpty())
		{	
			editpt->SetFocus();
			MessageBox("变台名称不能为空！","警告",MB_OK|MB_ICONWARNING);
			return;
		}
	    
		//线手拉手
		if(m_supplykinds ==2 ) 
		{
			
			if(m_pSet->m_USER_BAKMOTHERLINE < 1 ||  m_pSet->m_USER_BAKLINENO < 1)
			{
				MessageBox("模块在线路手拉手时备用母线\r\n或备用出线号不能为空！","警告",MB_OK|MB_ICONWARNING);
				return;
			}
			
			if((m_pSet->m_USER_MOTHERLINE ==  m_pSet->m_USER_BAKMOTHERLINE) && (m_pSet->m_USER_LINENO==m_pSet->m_USER_BAKLINENO))
			{
				MessageBox("母线、出线号和备用母线、备用出线号不能全相同！","警告",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}
		else
		{	
			
			if(m_pSet->m_USER_BAKMOTHERLINE > 0 ||  m_pSet->m_USER_BAKLINENO > 0)
			{
				MessageBox("模块在非线路手拉手时备用母线\r\n或备用出线号应为空！","警告",MB_OK|MB_ICONWARNING);
				return;
			}

		}


		//居民表、大用户表、台变总表的模块地址不能大于13107115且最后两位不能大于15
		if(((atol(m_pSet->m_USER_MODULENO) > 13107115 || atol(m_pSet->m_USER_MODULENO)%100 > 15 || atol(m_pSet->m_USER_MODULENO)/100 < 1) && m_ammeterradio <= 5 && (m_pSet->m_USER_PROTOCOL == 71 || m_pSet->m_USER_PROTOCOL == 72 || m_pSet->m_USER_PROTOCOL == 31 || m_pSet->m_USER_PROTOCOL == 32)))
		{
			editpt = (CEdit*)GetDlgItem(IDC_MODULENO);
            editpt->SetFocus();
			MessageBox("31、32、71、72协议居民表、大用户表、台变总表、无功补偿表的模块地址范围为\r\n[101-13107115],且后两位子表地址不能大于15！！","警告",MB_OK|MB_ICONWARNING);
			return;
		}

		//居民表、大用户表、台变总表的模块地址不能大于13107115且最后两位不能大于15
		if(((atol(m_pSet->m_USER_MODULENO) > 1638315 || atol(m_pSet->m_USER_MODULENO)%100 > 15 || atol(m_pSet->m_USER_MODULENO)/100 < 1) && m_ammeterradio <= 5 && (m_pSet->m_USER_PROTOCOL == 61 || m_pSet->m_USER_PROTOCOL == 62)))
		{
			editpt = (CEdit*)GetDlgItem(IDC_MODULENO);
            editpt->SetFocus();
			MessageBox("61、62协议居民表、大用户表、台变总表、无功补偿表的模块地址范围为\r\n[101-1638315],且后两位子表地址不能大于15！！","警告",MB_OK|MB_ICONWARNING);
			return;
		}

		//线表、站表最后两位为16
		if(m_ammeterradio > 5 && atol(m_pSet->m_USER_MODULENO)%100 != 16)
		{	
			editpt = (CEdit*)GetDlgItem(IDC_MODULENO);
            editpt->SetFocus();
			MessageBox("线表、站表最后两位为16！","警告",MB_OK|MB_ICONWARNING);
			return;
		}	
	
		if(!(m_pSet->m_USER_PROTOCOL == 22 || m_pSet->m_USER_PROTOCOL == 31 || m_pSet->m_USER_PROTOCOL == 32 || m_pSet->m_USER_PROTOCOL == 61 || m_pSet->m_USER_PROTOCOL == 62 || m_pSet->m_USER_PROTOCOL == 71 || m_pSet->m_USER_PROTOCOL == 72  || m_pSet->m_USER_PROTOCOL == 73))		
		{
			editpt = (CEdit*)GetDlgItem(IDC_PROTOCOL);
			editpt->SetFocus();
			MessageBox("抄表协议编号范围应为[22,31,32,61,62,71,72,73]，请修改抄表协议值！","警告",MB_OK|MB_ICONWARNING);
			return;
		}
		
		//把原来的模块号存
	//	StrSql.Format("USER_MODULENO='%d' AND USER_STATIONNO='%s'",atol(m_pSet->m_column11),m_pSet->m_column9);
		StrSql.Format("USER_MODULENO='%d'",atol(m_pSet->m_USER_MODULENO));
		
		if(CDataBaseInstance::GetAllRecordsCount("TB_USER",StrSql) > 0)
		{	
			editpt = (CEdit*)GetDlgItem(IDC_MODULENO);
            editpt->SetFocus();
			MessageBox("变电站用户信息中已存在此模块号！\r\n模块号重复，请重输！","警告",MB_OK|MB_ICONWARNING);
			return;
		}


		m_pSet->m_USER_INSTALLTIME   =  m_times;
		m_pSet->m_USER_PHASE  =  m_radios;
		m_pSet->m_USER_RUNSTATUS  =  m_runnings ;
        m_pSet->m_USER_AMMETERKIND   =  m_ammeterradio ;
		m_pSet->m_USER_SUPPLYMODE  =  m_supplykinds ;
	
		//无功补偿表
		if(m_pSet->m_USER_AMMETERKIND == 5)
		{
			CWuGongSpaceDlg                    dlg;
			dlg.m_Module  =  m_pSet->m_USER_MODULENO;
			
			if(dlg.DoModal() != IDOK)
			{
				
				return;
			}

		}

		if (m_pSet->CanUpdate())
		{
			m_pSet->Update();
		}

		m_pSet->Requery(); // for sorted sets

		//隐藏列表框
		ShowCombox(FALSE);
	
		if (!m_pSet->IsEOF())
		{
			m_pSet->MoveLast();
		}
	
		m_adding   = FALSE; 
		m_modified = FALSE;

		//修改或增加了记录
	    m_IfAdding = TRUE;
        
		if (!m_pSet->IsEOF())
		{
			
			if(m_pSet->CanBookmark() && varCurrentRecord.m_dwType!=DBVT_NULL)
			{
				m_pSet->SetBookmark(varCurrentRecord);
			}
			
			UpdateData(FALSE);
		}

		SetReadOnly(TRUE);

	}

	//如果修改了
	if(m_modified == TRUE)
	{

		//母线编号,线路编号
		m_motherline.GetLBText(m_motherline.GetCurSel(),StrSql);
		StrSql.TrimLeft();
        StrSql.TrimRight();
		CEdit* editpt = (CEdit*)GetDlgItem(IDC_GENERATRIXNO);
		editpt->SetWindowText(StrSql);
			
		m_linecombox.GetLBText(m_linecombox.GetCurSel(),StrSql);
		StrSql.TrimLeft();
        StrSql.TrimRight();
		editpt = (CEdit*)GetDlgItem(IDC_LINENO);
		editpt->SetWindowText(StrSql);

	    //备用母线编号,线路编号
		if(m_bakmotherline.GetCurSel() > 0)
		{
			m_bakmotherline.GetLBText(m_bakmotherline.GetCurSel(),StrSql);
			StrSql.TrimLeft();
			StrSql.TrimRight();
			editpt = (CEdit*)GetDlgItem(IDC_BAKGENERATRIXNO);
			editpt->SetWindowText(StrSql);
		}
		else
		{	
			editpt = (CEdit*)GetDlgItem(IDC_BAKGENERATRIXNO);
			editpt->SetWindowText("0");
		}
		
		if(m_baklinecombox.GetCurSel() > 0)
		{
			
			m_baklinecombox.GetLBText(m_baklinecombox.GetCurSel(),StrSql);
			StrSql.TrimLeft();
			StrSql.TrimRight();
			editpt = (CEdit*)GetDlgItem(IDC_BAKLINENO);
			editpt->SetWindowText(StrSql);
		}
		else
		{
			editpt = (CEdit*)GetDlgItem(IDC_BAKLINENO);
			editpt->SetWindowText("0");
		}
		
		//电表型号
		if(m_ammeter.GetCurSel() > 0)
		{
			m_ammeter.GetLBText(m_ammeter.GetCurSel(),StrSql);
			StrSql.TrimLeft();
			StrSql.TrimRight();
			editpt = (CEdit*)GetDlgItem(IDC_ELCTYPE);
			editpt->SetWindowText(StrSql);
		}
		else
		{
			editpt = (CEdit*)GetDlgItem(IDC_ELCTYPE);
			editpt->SetWindowText("");
		}

		UpdateData(TRUE);

		m_pSet->m_USER_INSTALLTIME   =  m_times;
		m_pSet->m_USER_PHASE  =  m_radios;
		m_pSet->m_USER_RUNSTATUS  =  m_runnings;
        m_pSet->m_USER_AMMETERKIND   =  m_ammeterradio;
		m_pSet->m_USER_SUPPLYMODE  =  m_supplykinds;
		
		//公司名称
		editpt = (CEdit*)GetDlgItem(IDC_COMPANY);
		editpt->GetWindowText(StrSql);
        
		StrSql.TrimLeft();
        StrSql.TrimRight();

		if(StrSql.IsEmpty())
		{	  
			editpt->SetFocus();
			MessageBox("公司名称不能为空！","警告",MB_OK|MB_ICONWARNING);
			return;
		}

		//变电站名称
	    editpt = (CEdit*)GetDlgItem(IDC_POWERSTATION);
		editpt->GetWindowText(StrSql);
        
		StrSql.TrimLeft();
        StrSql.TrimRight();

		if(StrSql.IsEmpty())
		{	
			editpt->SetFocus();
			MessageBox("变电站名称不能为空！","警告",MB_OK|MB_ICONWARNING);
			return;
		}	
		
		//线路名称
	    editpt = (CEdit*)GetDlgItem(IDC_LINE);
		editpt->GetWindowText(StrSql);
        
		StrSql.TrimLeft();
        StrSql.TrimRight();

		if(StrSql.IsEmpty())
		{	
			editpt->SetFocus();
			MessageBox("线路名称不能为空！","警告",MB_OK|MB_ICONWARNING);
			return;
		}	
		
		//变台名称
	    editpt = (CEdit*)GetDlgItem(IDC_TRANSFORMERNO);
		editpt->GetWindowText(StrSql);
        
		StrSql.TrimLeft();
        StrSql.TrimRight();

		if(StrSql.IsEmpty())
		{	
			editpt->SetFocus();
			MessageBox("变台名称不能为空！","警告",MB_OK|MB_ICONWARNING);
			return;
		}

		//居民表、大用户表、台变总表的模块地址不能大于13107115且最后两位不能大于15
		if(((atol(m_pSet->m_USER_MODULENO) > 13107115 || atol(m_pSet->m_USER_MODULENO)%100 > 15 || atol(m_pSet->m_USER_MODULENO)/100 < 1) && m_ammeterradio <= 5 && (m_pSet->m_USER_PROTOCOL == 71 || m_pSet->m_USER_PROTOCOL == 72 || m_pSet->m_USER_PROTOCOL == 73)) || ((atol(m_pSet->m_USER_MODULENO) > 1638315 || (atol(m_pSet->m_USER_MODULENO)%100 != 15 && atol(m_pSet->m_USER_MODULENO)%100 > 8) || atol(m_pSet->m_USER_MODULENO)/100 < 1) && m_ammeterradio <= 3 && (m_pSet->m_USER_PROTOCOL == 22)))
		{
			editpt = (CEdit*)GetDlgItem(IDC_MODULENO);
            editpt->SetFocus();
			MessageBox("71、72、73协议居民表、大用户表、台变总表、无功补偿表的模块地址范围为\r\n[101-13107115],22协议的模块地址范围为[101-1638415],71、72、73协议模块最\r\n后两位不能大于15,22协议模块最后两位应为1－8或15！","警告",MB_OK|MB_ICONWARNING);
			return;
		}	
		
		//居民表、大用户表、台变总表的模块地址不能大于13107115且最后两位不能大于15
		if(((atol(m_pSet->m_USER_MODULENO) > 1638315 || atol(m_pSet->m_USER_MODULENO)%100 > 15 || atol(m_pSet->m_USER_MODULENO)/100 < 1) && m_ammeterradio <= 5 && (m_pSet->m_USER_PROTOCOL == 61 || m_pSet->m_USER_PROTOCOL == 62)))
		{
			editpt = (CEdit*)GetDlgItem(IDC_MODULENO);
            editpt->SetFocus();
			MessageBox("61、62协议居民表、大用户表、台变总表、无功补偿表的模块地址范围为\r\n[101-1638315],且后两位子表地址不能大于15！！","警告",MB_OK|MB_ICONWARNING);
			return;
		}
	
		//线总表、站总表最后两位为16
		if(m_ammeterradio > 5 && atol(m_pSet->m_USER_MODULENO)%100 != 16)
		{	
			editpt = (CEdit*)GetDlgItem(IDC_MODULENO);
            editpt->SetFocus();
			MessageBox("线表、站表最后两位为16！","警告",MB_OK|MB_ICONWARNING);
			return;
		}
		
		//线手拉手
		if(m_supplykinds== 2) 
		{
			
			if(m_pSet->m_USER_BAKMOTHERLINE < 1 ||  m_pSet->m_USER_BAKLINENO < 1)
			{
				MessageBox("模块在线路手拉手时备用母线\r\n或备用出线号不能为空！","警告",MB_OK|MB_ICONWARNING);
				return;
			}
			
			if((m_pSet->m_USER_MOTHERLINE ==  m_pSet->m_USER_BAKMOTHERLINE) && (m_pSet->m_USER_LINENO==m_pSet->m_USER_BAKLINENO))
			{
				MessageBox("母线、出线号和备用母线、备用出线号不能全相同！","警告",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}
		else
		{	
			
			if(m_pSet->m_USER_BAKMOTHERLINE > 0 ||  m_pSet->m_USER_BAKLINENO > 0)
			{
				MessageBox("模块在非线路手拉手时备用母线\r\n或备用出线号应为空！","警告",MB_OK|MB_ICONWARNING);
				return;
			}

		}
		
	   	if(!(m_pSet->m_USER_PROTOCOL == 22 || m_pSet->m_USER_PROTOCOL == 31 || m_pSet->m_USER_PROTOCOL == 32	|| m_pSet->m_USER_PROTOCOL == 61 || m_pSet->m_USER_PROTOCOL == 62 || m_pSet->m_USER_PROTOCOL == 71 || m_pSet->m_USER_PROTOCOL == 72  || m_pSet->m_USER_PROTOCOL == 73))		
		{
			editpt = (CEdit*)GetDlgItem(IDC_PROTOCOL);
			editpt->SetFocus();
			MessageBox("抄表协议编号范围应为[22,31,32,61,62,71,72,73]，请修改抄表协议值！","警告",MB_OK|MB_ICONWARNING);
			return;
		}
	
		//把原来的模块号存
		StrSql.Format("USER_MODULENO='%d' AND USER_STATIONNO='%s'",atol(m_pSet->m_USER_MODULENO),m_pSet->m_USER_STATIONNO);
		
	    //把原来的模块号存
		if(atol(m_pSet->m_USER_MODULENO) != m_OldModule)
		{
		   //StrSql.Format("USER_MODULENO='%d' AND USER_STATIONNO='%s'",atol(m_pSet->m_column11),m_pSet->m_column9);
		    StrSql.Format("USER_MODULENO='%d'",atol(m_pSet->m_USER_MODULENO));

			if(CDataBaseInstance::GetAllRecordsCount("TB_USER",StrSql) > 0)
			{	
				MessageBox("变电站用户信息中已存在此模块号！\r\n模块号重复，请重输！","警告",MB_OK|MB_ICONWARNING);
				return;
			}

		}

		//无功补偿表
		if(m_pSet->m_USER_AMMETERKIND == 5)
		{
			CWuGongSpaceDlg                    dlg;
			dlg.m_Module  =  m_pSet->m_USER_MODULENO;
			
			if(dlg.DoModal() != IDOK)
			{
				
				return;
			}

		}
		
	  	if (m_pSet->CanUpdate())
		{
			m_pSet->Update();
		}

		m_pSet->Requery(); 

		//隐藏列表框
		ShowCombox(FALSE);

		m_adding      = FALSE;
		m_modified    = FALSE;

		SetReadOnly(TRUE);
		
		if (!m_pSet->IsEOF())
		{

			if(m_pSet->CanBookmark())
			{
				m_pSet->SetBookmark(varCurrentRecord);
			}
			
			UpdateData(FALSE);
		
		}
	
	}

	//GIF 隐藏
	CWnd * pts = GetDlgItem(IDC_GIF);
	pts->ShowWindow(SW_HIDE);

}

void CUserInfoDlg::OnModify() 
{	

	if (m_pSet->IsBOF() && m_pSet->IsEOF())
	{
	 	return;
	}
	
	if(m_pSet->CanBookmark())
	{
		m_pSet->GetBookmark(varCurrentRecord);
	}
	
	m_pSet->Edit();

	//把原来的模块号存
	if(!m_modified)
	{
		m_OldModule = atol(m_pSet->m_USER_MODULENO);
	}

    m_modified = TRUE;

	//GIF 显示
	CWnd * pts = GetDlgItem(IDC_GIF);
	pts->ShowWindow(SW_SHOW);

	//母线赋值,线路赋值
	if(m_pSet->m_USER_MOTHERLINE > 0)
	{
	  m_motherline.SetCurSel(m_pSet->m_USER_MOTHERLINE - 1);
	}
    
	if(m_pSet->m_USER_LINENO > 0)
	{
		m_linecombox.SetCurSel(m_pSet->m_USER_LINENO - 1);
	}
	
	//电表型号
	if(m_ammeter.FindString(-1, m_pSet->m_USER_AMMETERTYPE) != CB_ERR)
	{
		m_ammeter.SetCurSel(m_ammeter.FindString(-1, m_pSet->m_USER_AMMETERTYPE));
	}

	//显示列表框
	ShowCombox(TRUE);
  
	SetReadOnly(FALSE);

	//供电模式
	switch(m_pSet->m_USER_SUPPLYMODE)
	{
	case 0:
		{
			OnRadio14();
			break;
		}
	case 1:
		{
			OnRadio16();
			break;
		}
	case 2:
		{
			OnRadio15();
			
			//备用母线赋值,线路赋值
			if(m_pSet->m_USER_BAKMOTHERLINE > 0)
			{
				m_bakmotherline.SetCurSel(m_pSet->m_USER_BAKMOTHERLINE);
			}
			else
			{
				m_bakmotherline.SetCurSel(0);
			}
			
			if(m_pSet->m_USER_BAKLINENO > 0)
			{
				m_baklinecombox.SetCurSel(m_pSet->m_USER_BAKLINENO);
			}
			else
			{
				m_baklinecombox.SetCurSel(0);
			}
			
			break;

		}
		
	}
	
	/*
	//包头专用 2004.10.13
	CEdit* pt = (CEdit*)GetDlgItem(IDC_COMPANY);
	if(pt)
	{
	  pt->SetReadOnly(TRUE);
	}
	pt = (CEdit*)GetDlgItem(IDC_POWERSTATIONNO);
	if(pt)
	{
	  pt->SetReadOnly(TRUE);
	}
	pt = (CEdit*)GetDlgItem(IDC_POWERSTATION);
	if(pt)
	{
	  pt->SetReadOnly(TRUE);
	}
	pt = (CEdit*)GetDlgItem(IDC_TRANSFORMERNO);
	if(pt)
	{
	  pt->SetReadOnly(TRUE);
	}
	pt = (CEdit*)GetDlgItem(IDC_CTSCALE);
	if(pt)
	{
	  pt->SetReadOnly(TRUE);
	}	
	*/
}

void CUserInfoDlg::SetReadOnly(BOOL ISReading)
{

	CEdit* pt = (CEdit*)GetDlgItem(IDC_POWERSTATION);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_LINENO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_BAKLINENO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_LINE);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}	
	pt = (CEdit*)GetDlgItem(IDC_TRANSFORMERNO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_MODULENO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_NAME);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_ADDRESS);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_TELEPHONE);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_ELECTRICITYKIND);
    if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}

	pt = (CEdit*)GetDlgItem(IDC_AMMETTERNO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}	
	pt = (CEdit*)GetDlgItem(IDC_TABLEBOTTOMDATA);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}	
	pt = (CEdit*)GetDlgItem(IDC_CTSCALE);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_INTENSION);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_USEDESCRIBE);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_COMPANY);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_POWERSTATIONNO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_USERNO);
    if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	pt = (CEdit*)GetDlgItem(IDC_OLDUSERNO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}

	pt = (CEdit*)GetDlgItem(IDC_ELCNO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	
	pt = (CEdit*)GetDlgItem(IDC_GENERATRIXNO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	
	pt = (CEdit*)GetDlgItem(IDC_BAKGENERATRIXNO);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}

    pt = (CEdit*)GetDlgItem(IDC_ELCTYPE);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}

	pt = (CEdit*)GetDlgItem(IDC_SENDANGLE);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	
	pt = (CEdit*)GetDlgItem(IDC_UPVALUE);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	
	pt = (CEdit*)GetDlgItem(IDC_DOWNVALUE);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}
	
	CWnd* p = GetDlgItem(IDC_INSTALLDATE);
	if(p)
	{
		p->EnableWindow(!ISReading);
	}

	pt = (CEdit*)GetDlgItem(IDC_ELCKIND);
	if(pt)
	{
	   pt->SetReadOnly(ISReading);
	}

	p = GetDlgItem(IDC_RADIO2);
	if(p)
	{
	  p->EnableWindow(!ISReading);
	}
    
	pt = (CEdit*)GetDlgItem(IDC_PROTOCOL);
	if(pt)
	{
	  pt->SetReadOnly(ISReading);
	}

	p = GetDlgItem(IDC_RADIO4);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO5);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO10);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO3);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO47);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO48);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO36);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO6);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO9);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO12);
	p->EnableWindow(!ISReading);

	p = GetDlgItem(IDC_RADIO44);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO1);
	p->EnableWindow(!ISReading);	
	p = GetDlgItem(IDC_RADIO43);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO7);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO45);
	p->EnableWindow(!ISReading);

	p = GetDlgItem(IDC_RADIO13);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO14);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO15);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO16);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO46);
	p->EnableWindow(!ISReading);
}


void CUserInfoDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

void CUserInfoDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CUserInfoDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->wParam == ';' || pMsg->wParam == ':' || pMsg->wParam == '*')
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}



void CUserInfoDlg::OnDatacheck() 
{
	CString   StrSql,Str;
	long       m_records;
	StrSql = "USER_MODULENO<101 OR USER_MODULENO>13107115 OR USER_MODULENO%100 > 15 OR USER_LINENO> 16 OR USER_LINENO<1";
	
	m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",StrSql);
	
	if(m_records > 0)
	{
		CShowInfoDlg    dlg;
		dlg.DoModal();
		m_pSet->m_strFilter = StrSql;
		m_pSet->Requery();
		OnNextrecord();
	}
	else
	{
		if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") > 0)
		{
			MessageBox("恭喜你，经检验所有数据符合要求！","  ",MB_OK);
		}
		else
		{
			MessageBox("无用户信息记录！","  ",MB_OK);
		}
	}
	
}


void CUserInfoDlg::OnChangeCompany() 
{
	//修改标记
    m_IfAdding = TRUE;
}

void CUserInfoDlg::ShowCombox(BOOL m_IfShow)
{

	if(m_IfShow)
	{
	 	m_motherline.ShowWindow(SW_SHOW);
		m_linecombox.ShowWindow(SW_SHOW);
		m_bakmotherline.ShowWindow(SW_SHOW);
		m_baklinecombox.ShowWindow(SW_SHOW);
		m_ammeter.ShowWindow(SW_SHOW);    
		CWnd* pt = GetDlgItem(IDC_GENERATRIXNO);
		pt->ShowWindow(SW_HIDE);
		pt =GetDlgItem(IDC_LINENO);
		pt->ShowWindow(SW_HIDE);
		pt = GetDlgItem(IDC_BAKGENERATRIXNO);
		pt->ShowWindow(SW_HIDE);
		pt =GetDlgItem(IDC_BAKLINENO);
		pt->ShowWindow(SW_HIDE);
		pt =GetDlgItem(IDC_ELCTYPE);
		pt->ShowWindow(SW_HIDE);
	}
	else
	{
		m_motherline.ShowWindow(SW_HIDE);
		m_linecombox.ShowWindow(SW_HIDE); 
		m_bakmotherline.ShowWindow(SW_HIDE);
		m_baklinecombox.ShowWindow(SW_HIDE); 
		m_ammeter.ShowWindow(SW_HIDE);    
		CWnd* pt = GetDlgItem(IDC_GENERATRIXNO);
		pt->ShowWindow(SW_SHOW);
		pt =GetDlgItem(IDC_LINENO);
		pt->ShowWindow(SW_SHOW);
		pt = GetDlgItem(IDC_BAKGENERATRIXNO);
		pt->ShowWindow(SW_SHOW);
		pt =GetDlgItem(IDC_BAKLINENO);
		pt->ShowWindow(SW_SHOW);
		pt =GetDlgItem(IDC_ELCTYPE);
		pt->ShowWindow(SW_SHOW);
	}

}


//初始化电表列表列表
void CUserInfoDlg::InitializeAmmeterCombo()
{   
	//打开数据库
	CDatabase     db;
	CString   strSql;
	m_ammeter.ResetContent();
    m_ammeter.AddString("无型号");

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//公司级开始
		CDaoRecordset m_CompanySet(m_pDatabase);
		m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT AMMETER_TYPE from TB_AMMETER order by AMMETER_TYPE"));
	
		//寻找满足条件的记录
		while (!m_CompanySet.IsEOF())
		{
			strSql = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
			m_ammeter.AddString(strSql);
			m_CompanySet.MoveNext();
		}
		m_CompanySet.Close();	
		//公司级完
		
		delete m_pDatabase;
		m_pDatabase = NULL; 
		m_ammeter.SetCurSel(0);
	
	}
  
}

void CUserInfoDlg::OnChangePowerstation() 
{
	//修改标记
    m_IfAdding = TRUE;
	
}

void CUserInfoDlg::OnChangeLine() 
{
	//修改标记
    m_IfAdding = TRUE;
	
}

void CUserInfoDlg::OnChangeTransformerno() 
{
	//修改标记
    m_IfAdding = TRUE;
	
}

void CUserInfoDlg::OnChangeModuleno() 
{
	//修改标记
    m_IfAdding = TRUE;
}

void CUserInfoDlg::OnRadio14() 
{
	CWnd* pt = GetDlgItem(IDC_BAKMOTHERCOMBO);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_BAKLINECOMBO);
	pt->EnableWindow(FALSE);
	m_bakmotherline.SetCurSel(0);
	m_baklinecombox.SetCurSel(0);
}

void CUserInfoDlg::OnRadio16() 
{
	CWnd* pt = GetDlgItem(IDC_BAKMOTHERCOMBO);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_BAKLINECOMBO);
	pt->EnableWindow(FALSE);
	m_bakmotherline.SetCurSel(0);
	m_baklinecombox.SetCurSel(0);
}

void CUserInfoDlg::OnRadio15() 
{
	CWnd* pt = GetDlgItem(IDC_BAKMOTHERCOMBO);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_BAKLINECOMBO);
	pt->EnableWindow(TRUE);	
}

//查对应的电表型号
void CUserInfoDlg::OnChaammeter() 
{
	CString     Str,m_Str;
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	if(!m_adding)
	{
		CWnd*  pt  =   GetDlgItem(IDC_ELCTYPE);
		pt->GetWindowText(Str);
	}
	else
	{
		m_ammeter.GetLBText(m_ammeter.GetCurSel(),Str);
	}

	Str.TrimLeft();
	Str.TrimRight();
	
	if(Str.IsEmpty() || Str.Find("无型号") != -1)
	{
		return;
	}	
	
	if(pview->m_AmetterSet->IsOpen())
	{
		pview->m_AmetterSet->Close();
	}

	//电表型号
	m_Str.Format("LTRIM(RTRIM(AMMETER_TYPE))='%s'",Str);

	//数据库表是否打开
	if(pview->m_AmetterSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		
		CAmetterDlg  dlg(pview->m_AmetterSet.get(),0);
		dlg.m_Enalbed   =  FALSE;
		
		//取对应的字段值
		pview->m_AmetterSet->m_strFilter = m_Str;
		dlg.DoModal();
	
		pview->m_AmetterSet->m_strFilter = "";
		
		if(pview->m_AmetterSet->IsOpen())
		{
			pview->m_AmetterSet->Close();
		}		
		
	}
	
}

void CUserInfoDlg::OnBtsearch() 
{
	CString     Str,m_Str;
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	CWnd*  pt  =   GetDlgItem(IDC_TRANSFORMERNO);
	pt->GetWindowText(Str);

	Str.TrimLeft();
	Str.TrimRight();
	
	if(Str.IsEmpty())
	{
		return;
	}	
	
	if(pview->m_TransformpSet->IsOpen())
	{
		pview->m_TransformpSet->Close();
	}

	//电表型号
	m_Str.Format("LTRIM(RTRIM(TRANSFORMER_NO))='%s'",Str);

	//数据库表是否打开
	if(pview->m_TransformpSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		
		CTransformerDlg  dlg(pview->m_TransformpSet.get(),0);
		dlg.m_Enalbed  = FALSE;
		
		//取对应的字段值
		pview->m_TransformpSet->m_strFilter = m_Str;
		dlg.DoModal();
	
		pview->m_TransformpSet->m_strFilter = "";
		
		if(pview->m_TransformpSet->IsOpen())
		{
			pview->m_TransformpSet->Close();
		}		
		
	}	

}

void CUserInfoDlg::OnCancel() 
{

	//删除无功补偿表
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CString       StrSql;
	StrSql.Format("DELETE FROM TB_WUGONG WHERE WUGONG_MODULE NOT IN (SELECT DISTINCT USER_MODULENO FROM TB_USER)");
	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

	CDialog::OnCancel();
}
