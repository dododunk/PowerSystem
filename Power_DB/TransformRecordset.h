#if !defined(AFX_TRANSFORMRECORDSET_H__BB53AD56_9139_4920_AEDC_7349C50581D4__INCLUDED_)
#define AFX_TRANSFORMRECORDSET_H__BB53AD56_9139_4920_AEDC_7349C50581D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransformRecordset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransformRecordset recordset
#include "Power_DBDefinition.h"
class POWERDBAPI
CTransformRecordset : public CRecordset
{
public:
	CTransformRecordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTransformRecordset)

// Field/Param Data
	//{{AFX_FIELD(CTransformRecordset, CRecordset)
	CString	m_column1;
	CString	m_column2;
	long	m_column3;
	CTime	m_column5;
	CString	m_column6;
	CString	m_column7;
	BYTE	m_column8;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformRecordset)
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

#endif // !defined(AFX_TRANSFORMRECORDSET_H__BB53AD56_9139_4920_AEDC_7349C50581D4__INCLUDED_)
