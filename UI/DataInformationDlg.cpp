// DataInformation.cpp : implementation file
//

#include "stdafx.h"
//
#include "DataInformationDlg.h"
#include "SearchDlg.h"
#include "RuntimeAccount.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataInformation dialog
#include "Resource.h"

CDataInformationDlg::CDataInformationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataInformationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataInformation)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	m_adding   = FALSE;
	m_modified = FALSE;
}
 
CDataInformationDlg::CDataInformationDlg(CDataInfoRecordSet* pSet,CWnd* pParent /*=NULL*/)
	: CDialog(CDataInformationDlg::IDD, pParent)
{
	
	m_pSet              = pSet;
	
}

void CDataInformationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataInformation)
	DDX_FieldText(pDX, IDC_IA, m_pSet->m_REALTIME_ACURRENT, m_pSet);
	DDX_FieldText(pDX, IDC_IB, m_pSet->m_REALTIME_BCURRENT, m_pSet);
	DDX_FieldText(pDX, IDC_IC, m_pSet->m_REALTIME_CCURRENT, m_pSet);
	DDX_FieldText(pDX, IDC_PROTOCOL, m_pSet->m_REALTIME_PROTOCOL, m_pSet);
	DDX_FieldText(pDX, IDC_READTABLETIME, m_pSet->m_REALTIME_TRANSCRIBETIME, m_pSet);
	DDX_FieldText(pDX, IDC_UA, m_pSet->m_REALTIME_AVOLTAGE, m_pSet);
	DDX_FieldText(pDX, IDC_UB, m_pSet->m_REALTIME_BVOLTAGE, m_pSet);
	DDX_FieldText(pDX, IDC_UC, m_pSet->m_REALTIME_CVOLTAGE, m_pSet);
	DDX_FieldText(pDX, IDC_WGDD, m_pSet->m_REALTIME_LOSEDEGREE, m_pSet);
	DDX_FieldText(pDX, IDC_YGDD, m_pSet->m_REALTIME_WORKDEGREE, m_pSet);
	DDX_FieldText(pDX, IDC_MODULENO, m_pSet->m_REALTIME_MODULENO, m_pSet);
	DDX_FieldText(pDX, IDC_HANDWGDD, m_pSet->m_REALTIME_LOSEDEGREETOTAL, m_pSet);
	DDX_FieldText(pDX, IDC_HANDYGDD, m_pSet->m_REALTIME_WORKDEGREETOTAL, m_pSet);
	DDX_FieldText(pDX, IDC_JFDL, m_pSet->m_REALTIME_JFDL, m_pSet);
	DDX_FieldText(pDX, IDC_PDL, m_pSet->m_REALTIME_PDL, m_pSet);
	DDX_FieldText(pDX, IDC_GDL, m_pSet->m_REALTIME_GDL, m_pSet);
	DDX_FieldText(pDX, IDC_FDL, m_pSet->m_REALTIME_FDL, m_pSet);
	DDX_FieldText(pDX, IDC_GLYS, m_pSet->m_REALTIME_GLYS, m_pSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataInformationDlg, CDialog)
	//{{AFX_MSG_MAP(CDataInformation)
	ON_BN_CLICKED(IDC_FIRSTRECORD, OnFirstrecord)
	ON_BN_CLICKED(IDC_PREVIOUSRECORD, OnPreviousrecord)
	ON_BN_CLICKED(IDC_NEXTRECORD, OnNextrecord)
	ON_BN_CLICKED(IDC_LASTRECORD, OnLastrecord)
	ON_BN_CLICKED(IDC_ADDRECORD, OnAddrecord)
	ON_BN_CLICKED(IDC_DELRECORD, OnDelrecord)
	ON_BN_CLICKED(IDC_SAVEDATA, OnSavedata)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_SEACHBROWSE, OnSeachbrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataInformation message handlers
BOOL CDataInformationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//设置按钮风格
	/*
	m_search.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//
	m_save.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_modify.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_last.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_cancel.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_previous.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_next.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_delete.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_add.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_first.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
    */

	m_pSet->m_strFilter =   "";
	m_pSet->Requery();
	
	m_FieldPosition =  0;//字段名称位置
	m_symbol        =  0;//符号
	m_FieldName     = "";//值 

	//窗口居中
	CenterWindow();

	//设置窗口的图标
//	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	ASSERT(hIcon);
//	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
	
	OnFirstrecord();	
	
	//用户权限
	

	if(CRuntimeAccount::GetCurrentPrivilege() > 1)
	{
	    CWnd* ptt = GetDlgItem(IDC_DELRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_ADDRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_MODIFY);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SAVEDATA);
		ptt->EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataInformationDlg::OnFirstrecord() 
{
	SetReadOnly(TRUE);

	if(!(m_pSet->IsEOF() && m_pSet->IsBOF()))
	{
		m_pSet->MoveFirst();
		m_adding = FALSE;
		SetReadOnly(TRUE);
		UpdateData(FALSE);
	}

}

void CDataInformationDlg::OnPreviousrecord() 
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
    
	if(m_pSet->CanBookmark())
	{
		m_pSet->GetBookmark(varCurrentRecord);
	}

  	m_adding =  FALSE;
    SetReadOnly(TRUE);
	UpdateData(FALSE);
}

void CDataInformationDlg::OnNextrecord() 
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
	
	if(m_pSet->CanBookmark())
	{
		m_pSet->GetBookmark(varCurrentRecord);
	}

	if (!m_pSet->CanScroll())
	{
		m_pSet->SetFieldNull(NULL);
	}

	m_adding = FALSE;
  	SetReadOnly(TRUE);
	UpdateData(FALSE);
}

void CDataInformationDlg::OnLastrecord() 
{
	 if (m_pSet->IsBOF() && m_pSet->IsEOF())
	 {
	 	return;
	 }

     m_pSet->MoveLast();
	 
	 if(m_pSet->CanBookmark())
	 {
		m_pSet->GetBookmark(varCurrentRecord);
	 }

  	 m_adding =  FALSE;
	 SetReadOnly(TRUE);
	 UpdateData(FALSE);
}


void CDataInformationDlg::OnAddrecord() 
{
	if(m_adding ==  TRUE)
	{
		if(m_pSet->CanBookmark())
		{
			m_pSet->GetBookmark(varCurrentRecord);
		}

		OnSavedata();
	}

	m_adding     =        TRUE;
	m_pSet->SetFieldNull(NULL);
	SetReadOnly(FALSE);
	UpdateData(FALSE);
	
	GetDlgItem(IDC_MODULENO)->SetFocus();

}

void CDataInformationDlg::OnDelrecord() 
{
	
	if (m_pSet->IsBOF() && m_pSet->IsEOF())
	{
	 	return;
	}

	if(MessageBox("你想删除这条记录吗？警告：删除后数据不能恢复！！","询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
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
	 	m_adding = FALSE;
	    SetReadOnly(TRUE);
		UpdateData(FALSE);	
	}
}


void CDataInformationDlg::OnSavedata() 
{
	if(m_adding == TRUE)
	{
		if(!m_pSet->IsEOF())
		{
		  m_pSet->MoveLast();
		}

		m_pSet->AddNew();
		UpdateData(TRUE);
	
		if (m_pSet->CanUpdate())
		{
			m_pSet->Update();
		}
		
		m_pSet->Requery(); // for sorted sets

		if (!m_pSet->IsEOF())
		{
			m_pSet->MoveLast();
		}
	
		m_adding   = FALSE;
		m_modified = FALSE;
		
		if(m_pSet->CanBookmark() && varCurrentRecord.m_dwType!=DBVT_NULL)
		{
		   m_pSet->SetBookmark(varCurrentRecord);
		}

		UpdateData(FALSE);
		SetReadOnly(TRUE);
	}

	//如果修改了
	if(m_modified == TRUE)
	{
		UpdateData(TRUE);
		m_modified = FALSE;

		if (m_pSet->CanUpdate())
		{
			m_pSet->Update();
		}

		m_pSet->Requery(); 

		m_adding = FALSE;
		SetReadOnly(TRUE);
		
		if(m_pSet->CanBookmark())
		{
		   m_pSet->SetBookmark(varCurrentRecord);
		}

		UpdateData(FALSE);	
	}
}

void CDataInformationDlg::OnModify() 
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
    m_modified = TRUE;
	SetReadOnly(FALSE);
}

void CDataInformationDlg::SetReadOnly(BOOL ISReading)
{
	CEdit* pt = (CEdit*)GetDlgItem(IDC_MODULENO);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_YGDD);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_WGDD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_IA);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_IB);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_IC);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_UA);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_UB);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_UC);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_PROTOCOL);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_READTABLETIME);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_HANDYGDD);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_HANDWGDD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_JFDL);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_FDL);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_GDL);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_PDL);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_GLYS);
	pt->SetReadOnly(ISReading);	

}

void CDataInformationDlg::OnSeachbrowse() 
{
    CSearchDlg dlg;
	dlg.SetDataBaseName("TB_REALTIME");
	
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
}


BOOL CDataInformationDlg::PreTranslateMessage(MSG* pMsg) 
{

	if(pMsg->wParam == ';' || pMsg->wParam == ':' || pMsg->wParam == '*')
	{
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
