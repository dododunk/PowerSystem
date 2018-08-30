// Phone.cpp : implementation file
//

#include "stdafx.h"

#include "PhoneDlg.h"


#include "IFRMView.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhone dialog


CPhoneDlg::CPhoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhoneDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPhone)
	m_address = _T("");
	m_phone = _T("");
	//}}AFX_DATA_INIT
}


void CPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhone)
	DDX_Text(pDX, IDC_ADDRESS, m_address);
	DDX_Text(pDX, IDC_PHONENO, m_phone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPhoneDlg, CDialog)
	//{{AFX_MSG_MAP(CPhone)
	ON_BN_CLICKED(ID_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhone message handlers

void CPhoneDlg::OnAdd() 
{
    UpdateData(TRUE);
	CString   StrSql;

	m_address.TrimLeft();
	m_address.TrimRight();
	m_phone.TrimLeft();
	m_phone.TrimRight();

	if(m_address.IsEmpty() ||  m_phone.IsEmpty())
	{   
		
		if(m_phone.IsEmpty())
		{
			MessageBox("电话号码不能为空!"," ",MB_OK|MB_ICONWARNING);
			return;
		}
		
		if(m_address.IsEmpty())
		{
			MessageBox("地点名称不能为空!"," ",MB_OK|MB_ICONWARNING);
		}

       
	}
	else
	{	
		
		//CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
        
		StrSql.Format("RTRIM(PHONE_NO)='%s'",m_phone);

		if(CDataBaseInstance::GetAllRecordsCount("TB_PHONE",StrSql) < 1)
		{
			//没有此电话号码,则保存此电话
	    	StrSql.Format("INSERT INTO TB_PHONE(PHONE_NO,PHONE_NAME) VALUES ('%s','%s')",m_phone,m_address);
			CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
			m_address = m_phone = "";
			UpdateData(FALSE);

		}
		else
		{
	     	MessageBox("此电话已经已经存在！"," ",MB_OK|MB_ICONWARNING);
		}

	}
	
}

BOOL CPhoneDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    CWnd* pt = GetDlgItem(IDC_PHONENO);
	pt->SetFocus();

	return TRUE;  
}

