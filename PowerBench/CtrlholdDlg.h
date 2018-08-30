#pragma once

#include "BaseForm.h"
#include "resource.h"
// CCtrlholdDlg dialog

class CCtrlholdDlg : public CBaseForm
{
	DECLARE_DYNAMIC(CCtrlholdDlg)

public:
	CCtrlholdDlg(CWnd* pParent = NULL): CBaseForm(CCtrlholdDlg::IDD, pParent)
	{

	}
	virtual ~CCtrlholdDlg()
	{

	}

	virtual CString GetTitle() const
	{
		return "帧解析";
	}

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
private:
	CWinFormsControl<GB698Ctl::UCFrameParse> m_ctrl;
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
