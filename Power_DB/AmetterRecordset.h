#if !defined(AFX_AMETTERRECORDSET_H__58B70A70_860C_4853_8219_07E1CD7E7A99__INCLUDED_)
#define AFX_AMETTERRECORDSET_H__58B70A70_860C_4853_8219_07E1CD7E7A99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AmetterRecordset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAmetterRecordset recordset
#include "Power_DBDefinition.h"
class POWERDBAPI CAmetterRecordset : public CRecordset
{
public:
	CAmetterRecordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAmetterRecordset)

// Field/Param Data
	//{{AFX_FIELD(CAmetterRecordset, CRecordset)
	CString	m_Ammeter_Type;
	CString	m_AmmeterMenufature;
	long	m_ammeterImpulse;
	CString	m_Ammeter_remark;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAmetterRecordset)
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

#endif // !defined(AFX_AMETTERRECORDSET_H__58B70A70_860C_4853_8219_07E1CD7E7A99__INCLUDED_)
