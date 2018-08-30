#pragma once

#include "BaseForm.h"
#include "resource.h"
// CCtrlMessageHostDlg dialog

class CCtrlMessageHostDlg : public CBaseForm
{
	DECLARE_DYNAMIC(CCtrlMessageHostDlg)

public:
	CCtrlMessageHostDlg(CWnd* pParent = NULL);
	virtual ~CCtrlMessageHostDlg()
	{

	}
	static CCtrlMessageHostDlg* Instance();

	virtual CString GetTitle() const
	{
		return "网络消息服务";
	}


	
public:
	bool SendData();

	// Dialog Data
	enum { IDD = IDD_DIALOG_CTL_HOLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX)    // DDX/DDV support
	{
		CBaseForm::DoDataExchange(pDX);
		DDX_ManagedControl(pDX,IDC_CTRL_HOLD,m_ctrl);
	}


	virtual BOOL OnInitDialog()	
	{
		CBaseForm::OnInitDialog();
		//TO DO 界面元素初始化在此:主要是Combox数据添加
		CString title ;
		
		m_ctrl.GetWindowText(title);
		this->SetWindowText(title);

		return TRUE;
	}

	DECLARE_MESSAGE_MAP()
public: 
	CWinFormsControl<Tigera::LibNetworkWrap::UCMessageHost>& GetHoldCtrl();
		 
private:
	CWinFormsControl<Tigera::LibNetworkWrap::UCMessageHost> m_ctrl;
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
