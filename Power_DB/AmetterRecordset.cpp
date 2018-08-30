// AmetterRecordset.cpp : implementation file
//

#include "stdafx.h"

#include "AmetterRecordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmetterRecordset

IMPLEMENT_DYNAMIC(CAmetterRecordset, CRecordset)

CAmetterRecordset::CAmetterRecordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAmetterRecordset)
	m_Ammeter_Type = _T("");
	m_AmmeterMenufature = _T("");
	m_ammeterImpulse = 0;
	m_Ammeter_remark = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CAmetterRecordset::GetDefaultConnect()
{
	return _T("ODBC;DSN=IFRM");
}

CString CAmetterRecordset::GetDefaultSQL()
{
	return _T("[dbo].[TB_AMMETER]");
}

void CAmetterRecordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAmetterRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[AMMETER_TYPE]"), m_Ammeter_Type);//电表类型
	RFX_Text(pFX, _T("[AMMETER_MANUFACTURER]"), m_AmmeterMenufature);
	RFX_Long(pFX, _T("[AMMETER_IMPULSE]"), m_ammeterImpulse);
	RFX_Text(pFX, _T("[AMMETER_REMARK]"), m_Ammeter_remark);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAmetterRecordset diagnostics

#ifdef _DEBUG
void CAmetterRecordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAmetterRecordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
