// UseInfoRecordSet.cpp : implementation file
//

#include "stdafx.h"

#include "UseInfoRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseInfoRecordSet

IMPLEMENT_DYNAMIC(CUseInfoRecordSet, CRecordset)

CUseInfoRecordSet::CUseInfoRecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CUseInfoRecordSet)
	m_USER_MULTIPLE = 0.0;
	m_USER_STATIONNAME = _T("");
	m_USER_TRANSFORMERNO = _T("");
	m_USER_AMMETERKIND = 0;
	m_USER_AMMETERNO = _T("");
	m_USER_INITIALVALUE = 0.0;
	m_USER_PHONE = _T("");
	m_USER_STATIONNO = _T("");
	m_USER_COMPANY = _T("");
	m_USER_MODULENO = _T("");
	m_USER_LINENO = 0;
	m_USER_LINENAME = _T("");
	m_USER_PHASE = 0;
	m_USER_NAME = _T("");
	m_USER_DESCRIBE = _T("");
	m_USER_ELECTRICITYKIND = 0;
	m_USER_NO = _T("");
	m_USER_OLDNO = _T("");
	m_USER_ADDRESS = _T("");
	m_USER_SUPPLYMODE = 0;	
	m_USER_MOTHERLINE = 0;
	m_USER_PROTOCOL = 0;
	m_USER_AMMETERTYPE = _T("");
	m_USER_SENDANGLE = 0;	
	m_USER_DOWNVALUE = 0;
	m_USER_UPVALUE = 0;
	m_USER_BAKMOTHERLINE = 0;	
	m_USER_BAKLINENO = 0;
	m_USER_RUNSTATUS = 0;
	m_nFields = 30;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CUseInfoRecordSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=IFRM");
}

CString CUseInfoRecordSet::GetDefaultSQL()
{
	return _T("[dbo].[TB_USER]");
}

void CUseInfoRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CUseInfoRecordSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Date(pFX, _T("[USER_INSTALLTIME]"), m_USER_INSTALLTIME);
	RFX_Double(pFX, _T("[USER_MULTIPLE]"), m_USER_MULTIPLE);
	RFX_Text(pFX, _T("[USER_STATIONNAME]"), m_USER_STATIONNAME);
	RFX_Text(pFX, _T("[USER_TRANSFORMERNO]"), m_USER_TRANSFORMERNO);
	RFX_Byte(pFX, _T("[USER_AMMETERKIND]"), m_USER_AMMETERKIND);
	RFX_Text(pFX, _T("[USER_AMMETERNO]"), m_USER_AMMETERNO);
	RFX_Double(pFX, _T("[USER_INITIALVALUE]"), m_USER_INITIALVALUE);
	RFX_Text(pFX, _T("[USER_PHONE]"), m_USER_PHONE);
	RFX_Text(pFX, _T("[USER_STATIONNO]"), m_USER_STATIONNO);
	RFX_Text(pFX, _T("[USER_COMPANY]"), m_USER_COMPANY);
	RFX_Text(pFX, _T("[USER_MODULENO]"), m_USER_MODULENO);
	RFX_Long(pFX, _T("[USER_LINENO]"), m_USER_LINENO);
	RFX_Text(pFX, _T("[USER_LINENAME]"), m_USER_LINENAME);
	RFX_Byte(pFX, _T("[USER_PHASE]"), m_USER_PHASE);
	RFX_Text(pFX, _T("[USER_NAME]"), m_USER_NAME);
	RFX_Text(pFX, _T("[USER_DESCRIBE]"), m_USER_DESCRIBE);
	RFX_Byte(pFX, _T("[USER_ELECTRICITYKIND]"), m_USER_ELECTRICITYKIND);
	RFX_Text(pFX, _T("[USER_NO]"), m_USER_NO);
	RFX_Text(pFX, _T("[USER_OLDNO]"), m_USER_OLDNO);
	RFX_Text(pFX, _T("[USER_ADDRESS]"), m_USER_ADDRESS);
	RFX_Byte(pFX, _T("[USER_SUPPLYMODE]"), m_USER_SUPPLYMODE);	
	RFX_Byte(pFX, _T("[USER_MOTHERLINE]"), m_USER_MOTHERLINE);
	RFX_Byte(pFX, _T("[USER_PROTOCOL]"), m_USER_PROTOCOL);
	RFX_Text(pFX, _T("[USER_AMMETERTYPE]"), m_USER_AMMETERTYPE);
	RFX_Byte(pFX, _T("[USER_SENDANGLE]"), m_USER_SENDANGLE);
	RFX_Long(pFX, _T("[USER_DOWNVALUE]"), m_USER_DOWNVALUE);
	RFX_Long(pFX, _T("[USER_UPVALUE]"), m_USER_UPVALUE);
	RFX_Byte(pFX, _T("[USER_BAKMOTHERLINE]"), m_USER_BAKMOTHERLINE);
	RFX_Byte(pFX, _T("[USER_BAKLINENO]"), m_USER_BAKLINENO);
	RFX_Byte(pFX, _T("[USER_RUNSTATUS]"), m_USER_RUNSTATUS);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CUseInfoRecordSet diagnostics

#ifdef _DEBUG
void CUseInfoRecordSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUseInfoRecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
