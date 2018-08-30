// TransformRecordset.cpp : implementation file
//

#include "stdafx.h"

#include "TransformRecordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformRecordset

IMPLEMENT_DYNAMIC(CTransformRecordset, CRecordset)

CTransformRecordset::CTransformRecordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTransformRecordset)
	m_column1 = _T("");
	m_column2 = _T("");
	m_column3 = 0;
	m_column6 = _T("");
	m_column7 = _T("");
	m_column8 = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTransformRecordset::GetDefaultConnect()
{
	return _T("ODBC;DSN=IFRM");
}

CString CTransformRecordset::GetDefaultSQL()
{
	return _T("[dbo].[TB_TRANSFORMER]");
}

void CTransformRecordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTransformRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[TRANSFORMER_NO]"), m_column1);
	RFX_Text(pFX, _T("[TRANSFORMER_TYPE]"), m_column2);
	RFX_Long(pFX, _T("[TRANSFORMER_CAPACITY]"), m_column3);
	RFX_Date(pFX, _T("[TRANSFORMER_INSTALLTIME]"), m_column5);
	RFX_Text(pFX, _T("[TRANSFORMER_POSITION]"), m_column6);
	RFX_Text(pFX, _T("[TRANSFORMER_OWNERSHIP]"), m_column7);
	RFX_Byte(pFX, _T("[TRANSFORMER_CONNECTFORM]"), m_column8);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTransformRecordset diagnostics

#ifdef _DEBUG
void CTransformRecordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTransformRecordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
