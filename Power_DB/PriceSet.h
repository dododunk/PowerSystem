#if !defined(AFX_PRICESET_H__5AA183EB_6911_42CD_B74F_A1A22E078D51__INCLUDED_)
#define AFX_PRICESET_H__5AA183EB_6911_42CD_B74F_A1A22E078D51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PriceSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPriceSet recordset
#include "Power_DBDefinition.h"
class POWERDBAPI CPriceSet : public CRecordset
{
public:
	CPriceSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPriceSet)

// Field/Param Data
	//{{AFX_FIELD(CPriceSet, CRecordset)
	CString	m_column1;
	double	m_column2;
	BYTE	m_column3;
	CString	m_column4;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPriceSet)
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

#endif // !defined(AFX_PRICESET_H__5AA183EB_6911_42CD_B74F_A1A22E078D51__INCLUDED_)
