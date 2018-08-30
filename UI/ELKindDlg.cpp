// ELKind.cpp : implementation file
//

#include "stdafx.h"

#include "ELKindDlg.h"
#include "SearchDlg.h"
#include "RuntimeAccount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CELKind dialog


CELKindDlg::CELKindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CELKindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CELKind)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
}

CELKindDlg::CELKindDlg(CPriceSet* pSet,CWnd* pParent /*=NULL*/)
	: CDialog(CELKindDlg::IDD, pParent)
{

	m_pSet  = pSet;
	
}



void CELKindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CELKind)
	DDX_Control(pDX, IDC_SEACHBROWSE, m_search);
	DDX_Control(pDX, IDC_SAVEDATA, m_save);
	DDX_Control(pDX, IDC_MODIFY, m_modify);
	DDX_Control(pDX, IDC_LASTRECORD, m_last);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_PREVIOUSRECORD, m_previous);
	DDX_Control(pDX, IDC_NEXTRECORD, m_next);
	DDX_Control(pDX, IDC_DELRECORD, m_delete);
	DDX_Control(pDX, IDC_ADDRECORD, m_add);
	DDX_Control(pDX, IDC_FIRSTRECORD, m_first);
	DDX_FieldText(pDX, IDC_ELCKIND, m_pSet->m_column1, m_pSet);
	DDX_FieldText(pDX, IDC_ELCPRICE, m_pSet->m_column2, m_pSet);
	DDX_FieldText(pDX, IDC_ELCNO, m_pSet->m_column3, m_pSet);
	DDX_FieldText(pDX, IDC_REMARK, m_pSet->m_column4, m_pSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CELKindDlg, CDialog)
	//{{AFX_MSG_MAP(CELKind)
	ON_BN_CLICKED(IDC_ADDRECORD, OnAddrecord)
	ON_BN_CLICKED(IDC_FIRSTRECORD, OnFirstrecord)
	ON_BN_CLICKED(IDC_PREVIOUSRECORD, OnPreviousrecord)
	ON_BN_CLICKED(IDC_NEXTRECORD, OnNextrecord)
	ON_BN_CLICKED(IDC_LASTRECORD, OnLastrecord)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_DELRECORD, OnDelrecord)
	ON_BN_CLICKED(IDC_SEACHBROWSE, OnSeachbrowse)
	ON_BN_CLICKED(IDC_SAVEDATA, OnSavedata)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CELKind message handlers

BOOL CELKindDlg::OnInitDialog() 
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
	
	m_adding   = FALSE;
	m_modified = FALSE;
	
	OnFirstrecord(); 
	
	//用户权限
	

	if(CRuntimeAccount::GetCurrentPrivilege() > 1)
	{
	    CWnd* ptt =  GetDlgItem(IDC_DELRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_ADDRECORD);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_MODIFY);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SAVEDATA);
		ptt->EnableWindow(FALSE);
	}

	//HICON hIcon=AfxGetApp()->LoadIcon(IDI_POWER);
	//ASSERT(hIcon);
	//SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CELKindDlg::OnFirstrecord() 
{
	SetReadOnly(TRUE);

	if(!(m_pSet->IsEOF() && m_pSet->IsBOF()))
	{
		
		m_pSet->MoveFirst();
		m_adding = FALSE;
		UpdateData(FALSE);

	}
	
}

//向前移动数据
void CELKindDlg::OnPreviousrecord() 
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

 	m_adding = FALSE;
    SetReadOnly(TRUE);
	UpdateData(FALSE);

}

//向后移动数据
void CELKindDlg::OnNextrecord() 
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

//最后一个数据
void CELKindDlg::OnLastrecord() 
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

  	 m_adding = FALSE;
	 SetReadOnly(TRUE);
	 UpdateData(FALSE);

}

//增加数据
void CELKindDlg::OnAddrecord() 
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
	m_pSet->SetFieldNull(NULL);
	SetReadOnly(FALSE);
	UpdateData(FALSE);

	GetDlgItem(IDC_ELCNO)->SetFocus();

}

//删除数据
void CELKindDlg::OnDelrecord() 
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
	  	m_adding = FALSE;
	    SetReadOnly(TRUE);
		UpdateData(FALSE);	
	}
}

//保存数据
void CELKindDlg::OnSavedata() 
{
	if(m_adding == TRUE)
	{
		m_pSet->AddNew();
		UpdateData(TRUE);
        m_modified = FALSE;
		if (m_pSet->CanUpdate())
		{
			m_pSet->Update();
		}
		if (!m_pSet->IsEOF())
		{
			m_pSet->MoveLast();
		}
		m_pSet->Requery(); // for sorted sets
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

//修改数据
void CELKindDlg::OnModify() 
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

//设置只读属性
void CELKindDlg::SetReadOnly(BOOL ISReading)
{	
	CEdit* pt = (CEdit*)GetDlgItem(IDC_ELCNO);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_ELCKIND);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_ELCPRICE);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_REMARK);
	pt->SetReadOnly(ISReading);

}

//查询浏览
void CELKindDlg::OnSeachbrowse() 
{
    
	CSearchDlg   dlg;
	dlg.SetDataBaseName("TB_ELECTRICITY");
		
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



BOOL CELKindDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->wParam == ';' || pMsg->wParam == ':' || pMsg->wParam == '*')
	{
		return TRUE;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
