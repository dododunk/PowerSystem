// CHANGEAMMETERDLG.cpp : implementation file
//

#include "stdafx.h"
#include "CHANGEAMMETERset.h"
#include "CHANGEAMMETERDLG.h"
#include "SearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCHANGEAMMETERDLG dialog


CCHANGEAMMETERDlg::CCHANGEAMMETERDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCHANGEAMMETERDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCHANGEAMMETERDLG)
	m_times = 0;
	//}}AFX_DATA_INIT
	m_adding   = FALSE;
	m_modified = FALSE;
}

CCHANGEAMMETERDlg::CCHANGEAMMETERDlg(CCHANGEAMMETERSet* pSet,CWnd* pParent /*=NULL*/)
	: CDialog(CCHANGEAMMETERDlg::IDD, pParent)
{

	m_pSet  = pSet;

}

void CCHANGEAMMETERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCHANGEAMMETERDLG)
	DDX_DateTimeCtrl(pDX, IDC_INSTALLDATE, m_times);
	DDX_FieldText(pDX, IDC_FDL, m_pSet->m_CHANGEAMMETER_FDL, m_pSet);
	DDX_FieldText(pDX, IDC_FDLOLD, m_pSet->m_CHANGEAMMETER_FDLOLD, m_pSet);
	DDX_FieldText(pDX, IDC_GDL, m_pSet->m_CHANGEAMMETER_GDL, m_pSet);
	DDX_FieldText(pDX, IDC_GDLOLD, m_pSet->m_CHANGEAMMETER_GDLOLD, m_pSet);
	DDX_FieldText(pDX, IDC_JFDL, m_pSet->m_CHANGEAMMETER_JFDL, m_pSet);
	DDX_FieldText(pDX, IDC_JFDLOLD, m_pSet->m_CHANGEAMMETER_JFDLOLD, m_pSet);
	DDX_FieldText(pDX, IDC_PDL, m_pSet->m_CHANGEAMMETER_PDL, m_pSet);
	DDX_FieldText(pDX, IDC_PDLOLD, m_pSet->m_CHANGEAMMETER_PDLOLD, m_pSet);
	DDX_FieldText(pDX, IDC_YGDD, m_pSet->m_CHANGEAMMETER_WORKDEGREE, m_pSet);
	DDX_FieldText(pDX, IDC_YGDDOLD, m_pSet->m_CHANGEAMMETER_WORKDEGREEOLD, m_pSet);
	DDX_FieldText(pDX, IDC_HANDYGDD, m_pSet->m_CHANGEAMMETER_WORKDEGREETOTAL, m_pSet);
    DDX_FieldText(pDX, IDC_HANDYGDDOLD, m_pSet->m_CHANGEAMMETER_WORKDEGREETOTALOLD, m_pSet);
	DDX_FieldText(pDX, IDC_HANDWGDD, m_pSet->m_CHANGEAMMETER_LOSEDEGREETOTAL, m_pSet);
	DDX_FieldText(pDX, IDC_HANDWGDDOLD, m_pSet->m_CHANGEAMMETER_WORKDEGREETOTALOLD, m_pSet);
	DDX_FieldText(pDX, IDC_WGDD, m_pSet->m_CHANGEAMMETER_LOSEDEGREE, m_pSet);
	DDX_FieldText(pDX, IDC_WGDDOLD, m_pSet->m_CHANGEAMMETER_LOSEDEGREEOLD, m_pSet);
	DDX_FieldText(pDX, IDC_MODULENO, m_pSet->m_CHANGEAMMETER_MODULENO, m_pSet);
	DDX_FieldText(pDX, IDC_MODULENOOLD, m_pSet->m_CHANGEAMMETER_MODULENOOLD, m_pSet);
	DDX_FieldText(pDX, IDC_AMMETERNO, m_pSet->m_CHANGEAMMETER_NO, m_pSet);
	DDX_FieldText(pDX, IDC_AMMETERNOOLD, m_pSet->m_CHANGEAMMETER_NOOLD, m_pSet);
	DDX_FieldText(pDX, IDC_NAME, m_pSet->m_CHANGEAMMETER_NAME, m_pSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCHANGEAMMETERDlg, CDialog)
	//{{AFX_MSG_MAP(CCHANGEAMMETERDLG)
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
// CCHANGEAMMETERDLG message handlers

void CCHANGEAMMETERDlg::OnFirstrecord() 
{
	SetReadOnly(TRUE);

	if(!(m_pSet->IsEOF() && m_pSet->IsBOF()))
	{
		m_pSet->MoveFirst();
		m_adding = FALSE;
		SetReadOnly(TRUE);
		m_times = m_pSet->m_CHANGEAMMETER_UPDATETIME;
		UpdateData(FALSE);
	}
	
}

void CCHANGEAMMETERDlg::OnPreviousrecord() 
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

	m_times = m_pSet->m_CHANGEAMMETER_UPDATETIME;
	UpdateData(FALSE);
	
}

void CCHANGEAMMETERDlg::OnNextrecord() 
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

	m_times = m_pSet->m_CHANGEAMMETER_UPDATETIME;
	UpdateData(FALSE);	
}

void CCHANGEAMMETERDlg::OnLastrecord() 
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
	m_times = m_pSet->m_CHANGEAMMETER_UPDATETIME;
	UpdateData(FALSE);	
}

void CCHANGEAMMETERDlg::OnAddrecord() 
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
	CTime time  = CTime::GetCurrentTime();
	m_times     =  time;   
	m_pSet->SetFieldNull(NULL);
	SetReadOnly(FALSE);
	UpdateData(FALSE);
	
	GetDlgItem(IDC_MODULENOOLD)->SetFocus();
	
}

void CCHANGEAMMETERDlg::OnSavedata() 
{	
	CString    m_str;

	if(m_adding == TRUE)
	{

		if(!m_pSet->IsEOF())
		{
		  m_pSet->MoveLast();
		}
		
		m_pSet->AddNew();
		UpdateData(TRUE);

		CEdit*	editpt = (CEdit*)GetDlgItem(IDC_MODULENO);
		editpt->GetWindowText(m_str);

		if(atol(m_str)%100 < 12)
		{
			MessageBox("只有485表才有更换信息输入！\r\n脉冲表请在用户信息中修改表底值即可！"," ",MB_OK|MB_ICONWARNING);
			return;
		}

		m_pSet->m_CHANGEAMMETER_UPDATETIME   =  m_times;
		
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
		
		CEdit*	editpt = (CEdit*)GetDlgItem(IDC_MODULENO);
		editpt->GetWindowText(m_str);

		if(atol(m_str)%100 < 12)
		{
			MessageBox("只有485表才有更换信息输入！"," ",MB_OK|MB_ICONWARNING);
			return;
		}

		m_pSet->m_CHANGEAMMETER_UPDATETIME   =  m_times;
		
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

void CCHANGEAMMETERDlg::OnModify() 
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

void CCHANGEAMMETERDlg::OnDelrecord() 
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
		
		m_times    = m_pSet->m_CHANGEAMMETER_UPDATETIME;

	 	m_adding = FALSE;
	    SetReadOnly(TRUE);
		UpdateData(FALSE);	
	}	
}

void CCHANGEAMMETERDlg::OnSeachbrowse() 
{
	CSearchDlg                dlg;
	dlg.SetDataBaseName("TB_CHANGEAMMETER");
		
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


void CCHANGEAMMETERDlg::SetReadOnly(BOOL ISReading)
{

	CEdit* pt = (CEdit*)GetDlgItem(IDC_MODULENO);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_AMMETERNO);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_YGDD);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_WGDD);
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
	pt = (CEdit*)GetDlgItem(IDC_NAME);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_MODULENOOLD);
	pt->SetReadOnly(ISReading);	
	pt = (CEdit*)GetDlgItem(IDC_AMMETERNOOLD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_YGDDOLD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_HANDYGDDOLD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_WGDDOLD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_HANDWGDDOLD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_FDLOLD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_JFDLOLD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_GDLOLD);
	pt->SetReadOnly(ISReading);
	pt = (CEdit*)GetDlgItem(IDC_PDLOLD);
	pt->SetReadOnly(ISReading);
	CWnd* ptt = GetDlgItem(IDC_INSTALLDATE);
	ptt->EnableWindow(!ISReading);	
}

BOOL CCHANGEAMMETERDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_FieldPosition =  0;//字段名称位置
	m_symbol        =  0;//符号
	m_FieldName     = "";//值 
	OnFirstrecord();
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
