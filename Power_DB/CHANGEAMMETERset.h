#if !defined(AFX_CHANGEAMMETER_H__52D99A34_453D_4FC4_A167_6D1936E484BD__INCLUDED_)
#define AFX_CHANGEAMMETER_H__52D99A34_453D_4FC4_A167_6D1936E484BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHANGEAMMETER.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCHANGEAMMETER recordset
#include "Power_DBDefinition.h"

class POWERDBAPI CCHANGEAMMETERSet : public CRecordset
{
public:
	CCHANGEAMMETERSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCHANGEAMMETERSet)

// Field/Param Data
	//{{AFX_FIELD(CCHANGEAMMETER, CRecordset)
	double	m_CHANGEAMMETER_FDL;
	double	m_CHANGEAMMETER_FDLOLD;
	double	m_CHANGEAMMETER_GDL;
	double	m_CHANGEAMMETER_GDLOLD;
	double	m_CHANGEAMMETER_JFDL;
	double	m_CHANGEAMMETER_JFDLOLD;
	double	m_CHANGEAMMETER_LOSEDEGREE;
	double	m_CHANGEAMMETER_LOSEDEGREEOLD;
	double	m_CHANGEAMMETER_LOSEDEGREETOTAL;
	double	m_CHANGEAMMETER_LOSEDEGREETOTALOLD;
	CString	m_CHANGEAMMETER_MODULENO;
	CString	m_CHANGEAMMETER_MODULENOOLD;
	CString	m_CHANGEAMMETER_NAME;
	CString	m_CHANGEAMMETER_NO;
	CString	m_CHANGEAMMETER_NOOLD;
	double	m_CHANGEAMMETER_PDL;
	double	m_CHANGEAMMETER_PDLOLD;
	CTime	m_CHANGEAMMETER_UPDATETIME;
	double	m_CHANGEAMMETER_WORKDEGREE;
	CString	m_CHANGEAMMETER_WORKDEGREEOLD;
	double	m_CHANGEAMMETER_WORKDEGREETOTAL;
	double	m_CHANGEAMMETER_WORKDEGREETOTALOLD;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHANGEAMMETER)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEAMMETER_H__52D99A34_453D_4FC4_A167_6D1936E484BD__INCLUDED_)
