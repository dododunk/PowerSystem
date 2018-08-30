#if !defined(AFX_GARRISONRECORDSET_H__E392CEBA_483C_4862_93A3_256743E3DBE5__INCLUDED_)
#define AFX_GARRISONRECORDSET_H__E392CEBA_483C_4862_93A3_256743E3DBE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GarrisonRecordSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGarrisonRecordSet recordset
#include "Power_DBDefinition.h"
class POWERDBAPI CGarrisonRecordSet : public CRecordset
{
public:
	CGarrisonRecordSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGarrisonRecordSet)

// Field/Param Data
	//{{AFX_FIELD(CGarrisonRecordSet, CRecordset)
	double	m_GARRISON_ACURRENT;
	double	m_GARRISON_AVOLTAGE;
	double	m_GARRISON_BCURRENT;
	double	m_GARRISON_BVOLTAGE;
	double	m_GARRISON_CCURRENT;
	double	m_GARRISON_CVOLTAGE;
	CString	m_GARRISON_HALTTIME;
	double	m_GARRISON_LOSEDEGREE;
	double	m_GARRISON_LOSEDEGREETOTAL;
	CString	m_GARRISON_MODULENO;
	int		m_GARRISON_PROTOCOL;
	CString	m_GARRISON_TRANSCRIBETIME;
	double	m_GARRISON_WORKDEGREE;
	double	m_GARRISON_WORKDEGREETOTAL;
	double	m_GARRISON_FDL;
	double	m_GARRISON_GDL;
	double	m_GARRISON_JFDL;
	double	m_GARRISON_PDL;
    double	m_GARRISON_GLYS;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGarrisonRecordSet)
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

#endif // !defined(AFX_GARRISONRECORDSET_H__E392CEBA_483C_4862_93A3_256743E3DBE5__INCLUDED_)
