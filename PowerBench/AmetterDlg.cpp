// Ametter.cpp : implementation file
//

#include "stdafx.h"
//#include "IFRM.h"
#include "AmetterDlg.h"
#include "SearchDlg.h"
#include "RumtimeAccount.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmetter dialog


CAmetterDlg::CAmetterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAmetterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAmetter)
	m_pSet     = NULL;
	//}}AFX_DATA_INIT
	m_adding   = FALSE;
	m_modified = FALSE;
}

CAmetterDlg::CAmetterDlg(CAmetterRecordset* pSet,CWnd* pParent /*=NULL*/)
	: CDialog(CAmetterDlg::IDD, pParent)
{
	m_pSet              = pSet;

}

void CAmetterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAmetter)
	DDX_FieldText(pDX, IDC_AMMETTERTYPE, m_pSet->m_Ammeter_Type, m_pSet);
	DDX_FieldText(pDX, IDC_MANUFACTURER, m_pSet->m_AmmeterMenufature, m_pSet);
	DDX_FieldText(pDX, IDC_IMPLUSE, m_pSet->m_ammeterImpulse, m_pSet);
	DDX_FieldText(pDX, IDC_AMMETTERREMARK, m_pSet->m_Ammeter_remark, m_pSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAmetterDlg, CDialog)
	//{{AFX_MSG_MAP(CAmetter)
	ON_BN_CLICKED(IDC_FIRSTRECORD, OnFirstrecord)
	ON_BN_CLICKED(IDC_PREVIOUSRECORD, OnPreviousrecord)
	ON_BN_CLICKED(IDC_NEXTRECORD, OnNextrecord)
	ON_BN_CLICKED(IDC_LASTRECORD, OnLastrecord)
	ON_BN_CLICKED(IDC_ADDRECORD, OnAddrecord)
	ON_BN_CLICKED(IDC_SAVEDATA, OnSavedata)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_DELRECORD, OnDelrecord)
	ON_BN_CLICKED(IDC_SEACHBROWSE, OnSeachbrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmetter message handlers

void CAmetterDlg::OnFirstrecord() 
{
	SetReadOnly(TRUE);
	if(!(m_pSet->IsEOF() && m_pSet->IsBOF()))
	{
		m_pSet->MoveFirst();
		
		if(m_pSet->CanBookmark())
		{
		   m_pSet->GetBookmark(varCurrentRecord);
		}

		m_adding = FALSE;
		SetReadOnly(TRUE);
		UpdateData(FALSE);
	}
}

void CAmetterDlg::OnPreviousrecord() 
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

void CAmetterDlg::OnNextrecord() 
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

void CAmetterDlg::OnLastrecord() 
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


void CAmetterDlg::OnAddrecord() 
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
	
	GetDlgItem(IDC_AMMETTERTYPE)->SetFocus();
}

void CAmetterDlg::OnDelrecord() 
{
	if (m_pSet->IsBOF() && m_pSet->IsEOF())
	{
	 	return;
	}

	if(MessageBox("你想删除这条记录吗？警告：删除后数据不能恢复！！","询问：",MB_YESNO|MB_ICONQUESTION) == IDYES)
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


void CAmetterDlg::OnSavedata() 
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
		if (!m_pSet->IsEOF())
		{
			m_pSet->MoveLast();
		}	
		
		m_pSet->Requery(); // for sorted sets	
		
		if(m_pSet->CanBookmark() && varCurrentRecord.m_dwType!=DBVT_NULL)
		{
		   m_pSet->SetBookmark(varCurrentRecord);
		}
		m_adding = FALSE;
		UpdateData(FALSE);
		SetReadOnly(TRUE);
		m_modified = FALSE;
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

void CAmetterDlg::OnModify() 
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

void CAmetterDlg::SetReadOnly(BOOL ISReading)
{
	CEdit* pt = (CEdit*)GetDlgItem(IDC_AMMETTERTYPE);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_MANUFACTURER);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_IMPLUSE);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_AMMETTERREMARK);
	pt->SetReadOnly(ISReading);
}

void CAmetterDlg::OnSeachbrowse() 
{
    CSearchDlg dlg;
	dlg.SetDataBaseName("TB_AMMETER");
	
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

BOOL CAmetterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//设置按钮风格
//	m_pSet->m_strFilter =   "";
	m_pSet->Requery();
	
	m_FieldPosition =  0;//字段名称位置
	m_symbol        =  0;//符号
	m_FieldName     = "";//值 

	//窗口居中
	CenterWindow();

	//设置窗口的图标
//	HICON hIcon=AfxGetApp()->LoadIcon(IDI_AMMETTER);
//	ASSERT(hIcon);
//	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	OnFirstrecord();
	
	//用户权限
	//CIFRMApp* Apppt = (CIFRMApp*)AfxGetApp();

	if(CRumtimeAccount::GetCurrentPrivilege() > 1)
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

BOOL CAmetterDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->wParam == ';' || pMsg->wParam == ':' || pMsg->wParam == '*')
	{
		return TRUE;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
