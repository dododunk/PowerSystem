#pragma once

#include "BaseForm.h"
#include "resource.h"
// CCtrlHistoryHoldDlg dialog

class CCtrlHistoryHoldDlg : public CBaseForm
{
	DECLARE_DYNAMIC(CCtrlHistoryHoldDlg)

public:
	CCtrlHistoryHoldDlg(CWnd* pParent = NULL);
	virtual ~CCtrlHistoryHoldDlg()
	{

	}
	static CCtrlHistoryHoldDlg* Instance();

	virtual CString GetTitle() const
	{
		return "历史数据";
	}


public:
	

	// Dialog Data
	enum { IDD = IDD_DIALOG_CTL_HOLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX)    // DDX/DDV support
	{
		CBaseForm::DoDataExchange(pDX);
		DDX_ManagedControl(pDX,IDC_CTRL_HOLD,m_ctrl);
	}


	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public: 
	CWinFormsControl<PowerBenchSharpLib::UCAmmeterUsage>& GetHoldCtrl();

private:
	CWinFormsControl<PowerBenchSharpLib::UCAmmeterUsage> m_ctrl;
public:

	afx_msg void OnSize(UINT nType, int cx, int cy)
	{
		CBaseForm::OnSize(nType, cx, cy);

		RECT rect;
		this->GetClientRect(&rect);
		if ( ::IsWindow(this->m_ctrl.GetSafeHwnd()) )
		{	
			this->m_ctrl.MoveWindow(&rect,FALSE);
		}

		// TODO: Add your message handler code here
	}
};
