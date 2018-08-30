#if !defined(AFX_USEINFORECORDSET_H__920D9921_066A_4E19_8161_8780C7AC85D8__INCLUDED_)
#define AFX_USEINFORECORDSET_H__920D9921_066A_4E19_8161_8780C7AC85D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UseInfoRecordSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUseInfoRecordSet recordset
#include "Power_DBDefinition.h"
class POWERDBAPI CUseInfoRecordSet : public CRecordset
{
public:
	CUseInfoRecordSet(CDatabase* pDatabase = NULL);

	DECLARE_DYNAMIC(CUseInfoRecordSet)

// Field/Param Data
	//{{AFX_FIELD(CUseInfoRecordSet, CRecordset)
	CTime	m_USER_INSTALLTIME;
	double	m_USER_MULTIPLE;
	CString	m_USER_STATIONNAME;
	CString	m_USER_TRANSFORMERNO;
	BYTE	m_USER_AMMETERKIND;
	CString	m_USER_AMMETERNO;
	double	m_USER_INITIALVALUE;
	CString	m_USER_PHONE;
	CString	m_USER_STATIONNO;
	CString	m_USER_COMPANY;
	CString	m_USER_MODULENO;
	long	m_USER_LINENO;
	CString	m_USER_LINENAME;
	BYTE	m_USER_PHASE;
	CString	m_USER_NAME;
	CString	m_USER_DESCRIBE;
	BYTE	m_USER_ELECTRICITYKIND;
	CString	m_USER_NO;
	CString	m_USER_OLDNO;
	CString	m_USER_ADDRESS;
	BYTE	m_USER_SUPPLYMODE;
	BYTE	m_USER_MOTHERLINE;
	BYTE	m_USER_PROTOCOL;
	CString	m_USER_AMMETERTYPE;
	BYTE	m_USER_SENDANGLE;
	long	m_USER_DOWNVALUE;
	long	m_USER_UPVALUE;	
	BYTE	m_USER_BAKMOTHERLINE;	
	BYTE	m_USER_BAKLINENO;	
	BYTE	m_USER_RUNSTATUS;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseInfoRecordSet)
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

#endif // !defined(AFX_USEINFORECORDSET_H__920D9921_066A_4E19_8161_8780C7AC85D8__INCLUDED_)
