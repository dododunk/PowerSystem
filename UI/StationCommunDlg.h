//{{AFX_INCLUDES()
#include "sstabctl.h"
//}}AFX_INCLUDES
#if !defined(AFX_STATIONCOMMUN_H__14248D84_7A00_4BC7_9512_F7FFC0DCCADE__INCLUDED_)
#define AFX_STATIONCOMMUN_H__14248D84_7A00_4BC7_9512_F7FFC0DCCADE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationCommun.h : header file
//
#include "Resource.h"
#include "winnetwk.h"

/////////////////////////////////////////////////////////////////////////////
// CStationCommun dialog

class CStationCommunDlg : public CDialog
{
// Construction
public:
	BOOL m_WhichKind;
	CStationCommunDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStationCommun)
	enum { IDD = IDD_STATIONCOMM };
	CComboBox	m_PhoneSelect;
	CButton	m_ok;
	CButton	m_cancel;
	CComboBox	m_comstop;
	CComboBox	m_comdata;
	CComboBox	m_comcheck;
	CComboBox	m_comboport;
	CComboBox	m_combobit;
	int	     	m_Port;
	CSSTabCtl	m_maintab;
	CString	m_telephone;
	BOOL	m_AutoAnswer;
	BOOL	m_IfVoice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStationCommun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStationCommun)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkComputers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickSstab(short PreviousTab);
	afx_msg void OnNetsearch();
	afx_msg void OnRefreshs();
	afx_msg void OnNetdelete();
	afx_msg void OnDeletephone();
	afx_msg void OnAddphone();
	afx_msg void OnAutodial();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddAddressToTable();
	void ShowButton(short kinds);
	void GetAllPhoneInfo();
	void GetAllIpAddress();
	void SaveComInfoParameter();
	void GetLocalAddress();
	CImageList m_imageList;
	void InitializeNet();
	void GetComInfoParameter();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONCOMMUN_H__14248D84_7A00_4BC7_9512_F7FFC0DCCADE__INCLUDED_)
