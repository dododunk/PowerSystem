#if !defined(AFX_DATABASESET_H__F5465D79_7182_4D23_8A23_80F3FB0E9984__INCLUDED_)
#define AFX_DATABASESET_H__F5465D79_7182_4D23_8A23_80F3FB0E9984__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataBaseSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataBaseSet recordset
#include "Power_DBDefinition.h"
class POWERDBAPI CDataBaseSet : public CRecordset
{
public:
	CDataBaseSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDataBaseSet)

// Field/Param Data
	//{{AFX_FIELD(CDataBaseSet, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataBaseSet)
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

#endif // !defined(AFX_DATABASESET_H__F5465D79_7182_4D23_8A23_80F3FB0E9984__INCLUDED_)
