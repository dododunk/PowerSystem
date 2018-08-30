#if !defined(AFX_DATAINFORECORDSET_H__1C285BFD_8838_4995_8565_A776439D4859__INCLUDED_)
#define AFX_DATAINFORECORDSET_H__1C285BFD_8838_4995_8565_A776439D4859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataInfoRecordSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataInfoRecordSet recordset
#include "Power_DBDefinition.h"
class POWERDBAPI CDataInfoRecordSet : public CRecordset
{
public:
	CDataInfoRecordSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDataInfoRecordSet)

// Field/Param Data
	//{{AFX_FIELD(CDataInfoRecordSet, CRecordset)
	double	m_REALTIME_ACURRENT;
	double	m_REALTIME_AVOLTAGE;
	double	m_REALTIME_BCURRENT;
	double	m_REALTIME_BVOLTAGE;
	double	m_REALTIME_CCURRENT;
	double	m_REALTIME_CVOLTAGE;
	double	m_REALTIME_LOSEDEGREE;
	CString	m_REALTIME_MODULENO;
	int		m_REALTIME_PROTOCOL;
	CString	m_REALTIME_TRANSCRIBETIME;
	double	m_REALTIME_WORKDEGREE;
	double	m_REALTIME_LOSEDEGREETOTAL;
	double	m_REALTIME_WORKDEGREETOTAL;
	double	m_REALTIME_FDL;
	double	m_REALTIME_GDL;
	double	m_REALTIME_JFDL;
	double	m_REALTIME_PDL;
	double	m_REALTIME_GLYS;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataInfoRecordSet)
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

#endif // !defined(AFX_DATAINFORECORDSET_H__1C285BFD_8838_4995_8565_A776439D4859__INCLUDED_)
