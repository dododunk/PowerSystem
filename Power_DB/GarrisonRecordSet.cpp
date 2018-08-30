// GarrisonRecordSet.cpp : implementation file
//

#include "stdafx.h"

#include "GarrisonRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGarrisonRecordSet

IMPLEMENT_DYNAMIC(CGarrisonRecordSet, CRecordset)

CGarrisonRecordSet::CGarrisonRecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGarrisonRecordSet)
	m_GARRISON_ACURRENT = 0.0;
	m_GARRISON_AVOLTAGE = 0.0;
	m_GARRISON_BCURRENT = 0.0;
	m_GARRISON_BVOLTAGE = 0.0;
	m_GARRISON_CCURRENT = 0.0;
	m_GARRISON_CVOLTAGE = 0.0;
	m_GARRISON_HALTTIME = _T("");
	m_GARRISON_LOSEDEGREE = 0.0;
	m_GARRISON_LOSEDEGREETOTAL = 0.0;
	m_GARRISON_MODULENO = _T("");
	m_GARRISON_PROTOCOL = 0;
	m_GARRISON_TRANSCRIBETIME = _T("");
	m_GARRISON_WORKDEGREE = 0.0;
	m_GARRISON_WORKDEGREETOTAL = 0.0;
	m_GARRISON_FDL  = 0.0;
	m_GARRISON_GDL  = 0.0;
	m_GARRISON_JFDL = 0.0;
	m_GARRISON_PDL  = 0.0;
	m_GARRISON_GLYS = 0.0;
	m_nFields = 19;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CGarrisonRecordSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=IFRM");
}

CString CGarrisonRecordSet::GetDefaultSQL()
{
	return _T("[dbo].[TB_GARRISON]");
}

void CGarrisonRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGarrisonRecordSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Double(pFX, _T("[GARRISON_ACURRENT]"), m_GARRISON_ACURRENT);
	RFX_Double(pFX, _T("[GARRISON_AVOLTAGE]"), m_GARRISON_AVOLTAGE);
	RFX_Double(pFX, _T("[GARRISON_BCURRENT]"), m_GARRISON_BCURRENT);
	RFX_Double(pFX, _T("[GARRISON_BVOLTAGE]"), m_GARRISON_BVOLTAGE);
	RFX_Double(pFX, _T("[GARRISON_CCURRENT]"), m_GARRISON_CCURRENT);
	RFX_Double(pFX, _T("[GARRISON_CVOLTAGE]"), m_GARRISON_CVOLTAGE);
	RFX_Text(pFX, _T("[GARRISON_HALTTIME]"), m_GARRISON_HALTTIME);
	RFX_Double(pFX, _T("[GARRISON_LOSEDEGREE]"), m_GARRISON_LOSEDEGREE);
	RFX_Double(pFX, _T("[GARRISON_LOSEDEGREETOTAL]"), m_GARRISON_LOSEDEGREETOTAL);
	RFX_Text(pFX, _T("[GARRISON_MODULENO]"), m_GARRISON_MODULENO);
	RFX_Int(pFX, _T("[GARRISON_PROTOCOL]"), m_GARRISON_PROTOCOL);
	RFX_Text(pFX, _T("[GARRISON_TRANSCRIBETIME]"), m_GARRISON_TRANSCRIBETIME);
	RFX_Double(pFX, _T("[GARRISON_WORKDEGREE]"), m_GARRISON_WORKDEGREE);
	RFX_Double(pFX, _T("[GARRISON_WORKDEGREETOTAL]"), m_GARRISON_WORKDEGREETOTAL);
	RFX_Double(pFX, _T("[GARRISON_FDL]"), m_GARRISON_FDL);
	RFX_Double(pFX, _T("[GARRISON_GDL]"), m_GARRISON_GDL);
	RFX_Double(pFX, _T("[GARRISON_JFDL]"), m_GARRISON_JFDL);
	RFX_Double(pFX, _T("[GARRISON_PDL]"), m_GARRISON_PDL);
	RFX_Double(pFX, _T("[GARRISON_GLYS]"), m_GARRISON_GLYS);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGarrisonRecordSet diagnostics

#ifdef _DEBUG
void CGarrisonRecordSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGarrisonRecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
