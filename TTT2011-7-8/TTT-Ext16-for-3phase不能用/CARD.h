#if !defined(AFX_CARD_H__D53844EC_3533_4F07_80FF_E8275DAC124A__INCLUDED_)
#define AFX_CARD_H__D53844EC_3533_4F07_80FF_E8275DAC124A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CARD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCARD dialog

class CCARD : public CDialog
{
// Construction
public:
	CCARD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCARD)
	enum { IDD = IDD_CARDDIALOG };
	CComboBox	m_cardcombox;
	int		m_cardvalue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCARD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCARD)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARD_H__D53844EC_3533_4F07_80FF_E8275DAC124A__INCLUDED_)
