// Transformer.cpp : implementation file
//

#include "stdafx.h"

#include "TransformerDlg.h"
#include "SearchDlg.h"


#include "IFRMView.h"
#include "DataBaseInstance.h"
#include "RuntimeAccount.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformer dialog
CTransformerDlg::CTransformerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransformerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransformer)
	m_pSet   = NULL;
	m_times  = 0;
	m_radios = -1;
	//}}AFX_DATA_INIT
	m_adding   = FALSE;
	m_modified = FALSE;
}


CTransformerDlg::CTransformerDlg(CTransformRecordset* pSet,CWnd* pParent /*=NULL*/)
	: CDialog(CTransformerDlg::IDD, pParent)
{

	m_pSet  = pSet;
	
}

void CTransformerDlg::DoDataExchange(CDataExchange* pDX)
{
  	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransformer)
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER, m_times);
	DDX_Radio(pDX, IDC_RADIO1, m_radios);
	DDX_FieldText(pDX, IDC_CAPABILOITY, m_pSet->m_column3, m_pSet);
	DDX_FieldText(pDX, IDC_OWNERSHIP, m_pSet->m_column7, m_pSet);
	DDX_FieldText(pDX, IDC_POSITION, m_pSet->m_column6, m_pSet);
	DDX_FieldText(pDX, IDC_TRANSFORMERMODEL, m_pSet->m_column2, m_pSet);
	DDX_FieldText(pDX, IDC_TRANSFORMERNO, m_pSet->m_column1, m_pSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransformerDlg, CDialog)
	//{{AFX_MSG_MAP(CTransformer)
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
// CTransformer message handlers

BOOL CTransformerDlg::OnInitDialog() 
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
	m_FieldPosition =  0;//字段名称位置
	m_symbol        =  0;//符号
	m_FieldName     = "";//值 

	m_pSet->m_strFilter =   "";
	m_pSet->Requery();
	
	//窗口居中
	CenterWindow();

	//设置窗口的图标
//	HICON hIcon=AfxGetApp()->LoadIcon(IDI_TRANSFORMER);
//	ASSERT(hIcon);
//	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	m_radios    = 0;
	OnFirstrecord();
	UpdateData(FALSE);

    //用户权限
	//CIFRMApp* Apppt = (CIFRMApp*)AfxGetApp();

	if(CRuntimeAccount::GetCurrentPrivilege()> 1)
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

	if(!m_Enalbed)
	{		
		CWnd* ptt = GetDlgItem(IDC_DELRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_ADDRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_MODIFY);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SAVEDATA);
		ptt->EnableWindow(FALSE);
	    ptt = GetDlgItem(IDC_FIRSTRECORD);
		ptt->EnableWindow(FALSE);
	    ptt = GetDlgItem(IDC_PREVIOUSRECORD);
		ptt->EnableWindow(FALSE); 
		ptt = GetDlgItem(IDC_NEXTRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_LASTRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SEACHBROWSE);
		ptt->EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransformerDlg::OnFirstrecord() 
{
	SetReadOnly(TRUE);
	if(!(m_pSet->IsEOF() && m_pSet->IsBOF()))
	{
		m_pSet->MoveFirst();
		m_times  = m_pSet->m_column5;
		m_radios = m_pSet->m_column8;
		m_adding = FALSE;
		UpdateData(FALSE);
	}

}

void CTransformerDlg::OnPreviousrecord() 
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
    m_times  = m_pSet->m_column5;
    m_radios = m_pSet->m_column8;
	m_adding = FALSE;
    SetReadOnly(TRUE);

	if(m_pSet->CanBookmark())
	{
		m_pSet->GetBookmark(varCurrentRecord);
	}
	UpdateData(FALSE);
}

void CTransformerDlg::OnNextrecord() 
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
	m_adding = FALSE;
    m_times  = m_pSet->m_column5;
    m_radios = m_pSet->m_column8;
	SetReadOnly(TRUE);
	
	if(m_pSet->CanBookmark())
	{
		m_pSet->GetBookmark(varCurrentRecord);
	}

	UpdateData(FALSE);
}

void CTransformerDlg::OnLastrecord() 
{    
	 if (m_pSet->IsBOF() && m_pSet->IsEOF())
	 {
	 	return;
	 }
     m_pSet->MoveLast();
     m_times  = m_pSet->m_column5;
     m_radios = m_pSet->m_column8;
	 m_adding = FALSE;
	 SetReadOnly(TRUE);
	 
	 if(m_pSet->CanBookmark())
	 {
		m_pSet->GetBookmark(varCurrentRecord);
	 }
	 UpdateData(FALSE);
}


void CTransformerDlg::OnAddrecord() 
{   

	if(m_adding ==  TRUE)
	{	
		if(m_pSet->CanBookmark())
		{
			m_pSet->GetBookmark(varCurrentRecord);
		}

		OnSavedata();
	}

	m_adding =  TRUE;
	CTime time = CTime::GetCurrentTime();
	m_times = time;    
	m_pSet->SetFieldNull(NULL);
	SetReadOnly(FALSE);
	//接线形式
	m_radios  =      0;
	UpdateData(FALSE);
    
	GetDlgItem(IDC_TRANSFORMERNO)->SetFocus();
}

void CTransformerDlg::OnDelrecord() 
{
	
	if (m_pSet->IsBOF() && m_pSet->IsEOF())
	{
	 	return;
	}

	if(MessageBox("你想删除这条记录吗？警告：删除后数据不能恢复！！","询问",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
		CRecordsetStatus status;
		try {
			m_pSet->Delete();
		}
		catch(CDBException* e) {
			MessageBox(e->m_strError,"警告",MB_OK|MB_ICONWARNING);
			e->Delete();
			m_pSet->MoveFirst(); // lost our place!
			UpdateData(FALSE);
			return;
		}
		m_pSet->GetStatus(status);
		if (status.m_lCurrentRecord == 0) {
			// We deleted last of 2 records
			m_pSet->MoveFirst();
		}
		else {
			m_pSet->MoveNext();
		}
		m_pSet->Requery(); // for sorted sets
	    m_times  = m_pSet->m_column5;
        m_radios = m_pSet->m_column8;
		m_adding = FALSE;
	    SetReadOnly(TRUE);
		UpdateData(FALSE);
	
	}

}


void CTransformerDlg::OnSavedata() 
{

	if(m_adding == TRUE)
	{

		if(!m_pSet->IsEOF())
		{
		  m_pSet->MoveLast();
		}

		m_modified = FALSE;
		m_pSet->AddNew();
		UpdateData(TRUE);
		m_pSet->m_column5   = m_times;
		m_pSet->m_column8   = m_radios;
		//TransCOleDateTimeToCtime();
		if (m_pSet->CanUpdate())
		{
			m_pSet->Update();
		}
		
		m_pSet->Requery(); // for sorted sets
		
		if (!m_pSet->IsEOF())
		{
			m_pSet->MoveLast();
		}
	
		m_adding = FALSE;
		
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
		m_pSet->m_column5   = m_times;
		m_pSet->m_column8   = m_radios;
		if (m_pSet->CanUpdate())
		{
			m_pSet->Update();
		}
		m_pSet->Requery(); 
		m_adding   = FALSE;
		m_modified = FALSE;
		SetReadOnly(TRUE);
		if(m_pSet->CanBookmark())
		{
		   m_pSet->SetBookmark(varCurrentRecord);
		}
		UpdateData(FALSE);

	}
}

void CTransformerDlg::OnModify() 
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

void CTransformerDlg::SetReadOnly(BOOL ISReading)
{
	CEdit* pt = (CEdit*)GetDlgItem(IDC_TRANSFORMERNO);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_TRANSFORMERMODEL);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_CAPABILOITY);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_POSITION);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_OWNERSHIP);
	pt->SetReadOnly(ISReading);
	CWnd* p = GetDlgItem(IDC_DATETIMEPICKER);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO1);
	p->EnableWindow(!ISReading);
	p = GetDlgItem(IDC_RADIO3);
	p->EnableWindow(!ISReading);
}

void CTransformerDlg::OnSeachbrowse() 
{
	
	
	//变台记录个数
	long m_records = CDataBaseInstance::GetAllRecordsCount("TB_TRANSFORMER","ALL");

    CSearchDlg    dlg;
	dlg.SetDataBaseName("TB_TRANSFORMER");

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

BOOL CTransformerDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->wParam == ';' || pMsg->wParam == ':' || pMsg->wParam == '*')
	{
		return TRUE;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
