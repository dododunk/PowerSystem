// DataBaseSet.cpp : implementation file
//

#include "stdafx.h"

#include "DataBaseSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataBaseSet

IMPLEMENT_DYNAMIC(CDataBaseSet, CRecordset)

CDataBaseSet::CDataBaseSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDataBaseSet)
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CDataBaseSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=IFRM");
}

CString CDataBaseSet::GetDefaultSQL()
{
	return _T("");
}

void CDataBaseSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDataBaseSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDataBaseSet diagnostics

#ifdef _DEBUG
void CDataBaseSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDataBaseSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
