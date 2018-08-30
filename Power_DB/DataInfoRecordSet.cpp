// DataInfoRecordSet.cpp : implementation file
//

#include "stdafx.h"

#include "DataInfoRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataInfoRecordSet

IMPLEMENT_DYNAMIC(CDataInfoRecordSet, CRecordset)

CDataInfoRecordSet::CDataInfoRecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDataInfoRecordSet)
	m_REALTIME_ACURRENT = 0.0;
	m_REALTIME_AVOLTAGE = 0.0;
	m_REALTIME_BCURRENT = 0.0;
	m_REALTIME_BVOLTAGE = 0.0;
	m_REALTIME_CCURRENT = 0.0;
	m_REALTIME_CVOLTAGE = 0.0;
	m_REALTIME_LOSEDEGREE = 0.0;
	m_REALTIME_MODULENO = _T("");
	m_REALTIME_PROTOCOL = 0;
	m_REALTIME_TRANSCRIBETIME = _T("");
	m_REALTIME_WORKDEGREE = 0.0;
	m_REALTIME_LOSEDEGREETOTAL = 0.0;
	m_REALTIME_WORKDEGREETOTAL = 0.0;
	m_REALTIME_FDL  = 0.0;
	m_REALTIME_GDL  = 0.0;
	m_REALTIME_JFDL = 0.0;
	m_REALTIME_PDL  = 0.0;
	m_REALTIME_GLYS = 0.0;
	m_nFields       =  18;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CDataInfoRecordSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=IFRM");
}

CString CDataInfoRecordSet::GetDefaultSQL()
{
	return _T("[dbo].[TB_REALTIME]");
}

void CDataInfoRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDataInfoRecordSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Double(pFX, _T("[REALTIME_ACURRENT]"), m_REALTIME_ACURRENT);
	RFX_Double(pFX, _T("[REALTIME_AVOLTAGE]"), m_REALTIME_AVOLTAGE);
	RFX_Double(pFX, _T("[REALTIME_BCURRENT]"), m_REALTIME_BCURRENT);
	RFX_Double(pFX, _T("[REALTIME_BVOLTAGE]"), m_REALTIME_BVOLTAGE);
	RFX_Double(pFX, _T("[REALTIME_CCURRENT]"), m_REALTIME_CCURRENT);
	RFX_Double(pFX, _T("[REALTIME_CVOLTAGE]"), m_REALTIME_CVOLTAGE);
	RFX_Double(pFX, _T("[REALTIME_LOSEDEGREE]"), m_REALTIME_LOSEDEGREE);
	RFX_Text(pFX, _T("[REALTIME_MODULENO]"), m_REALTIME_MODULENO);
	RFX_Int(pFX, _T("[REALTIME_PROTOCOL]"), m_REALTIME_PROTOCOL);
	RFX_Text(pFX, _T("[REALTIME_TRANSCRIBETIME]"), m_REALTIME_TRANSCRIBETIME);
	RFX_Double(pFX, _T("[REALTIME_WORKDEGREE]"), m_REALTIME_WORKDEGREE);
	RFX_Double(pFX, _T("[REALTIME_LOSEDEGREETOTAL]"), m_REALTIME_LOSEDEGREETOTAL);
	RFX_Double(pFX, _T("[REALTIME_WORKDEGREETOTAL]"), m_REALTIME_WORKDEGREETOTAL);
	RFX_Double(pFX, _T("[REALTIME_FDL]"), m_REALTIME_FDL);
	RFX_Double(pFX, _T("[REALTIME_GDL]"), m_REALTIME_GDL);
	RFX_Double(pFX, _T("[REALTIME_JFDL]"), m_REALTIME_JFDL);
	RFX_Double(pFX, _T("[REALTIME_PDL]"), m_REALTIME_PDL);
	RFX_Double(pFX, _T("[REALTIME_GLYS]"), m_REALTIME_GLYS);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDataInfoRecordSet diagnostics

#ifdef _DEBUG
void CDataInfoRecordSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDataInfoRecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
