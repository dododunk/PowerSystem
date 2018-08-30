// PriceSet.cpp : implementation file
//

#include "stdafx.h"

#include "PriceSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPriceSet

IMPLEMENT_DYNAMIC(CPriceSet, CRecordset)

CPriceSet::CPriceSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPriceSet)
	m_column1 = _T("");
	m_column2 = 0.0;
	m_column3 =   0;
	m_column4 = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CPriceSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=IFRM");
}

CString CPriceSet::GetDefaultSQL()
{
	return _T("[dbo].[TB_ELECTRICITY]");
}

void CPriceSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPriceSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ELECTRICITY_KIND]"), m_column1);
	RFX_Double(pFX, _T("[ELECTRICITY_PRICE]"), m_column2);
	RFX_Byte(pFX, _T("[ELECTRICITY_NO]"), m_column3);
	RFX_Text(pFX, _T("[ELECTRICITY_REMARK]"), m_column4);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPriceSet diagnostics

#ifdef _DEBUG
void CPriceSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPriceSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
