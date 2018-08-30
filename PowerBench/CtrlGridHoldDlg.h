#pragma once

#include "BaseForm.h"
#include "resource.h"
// CCtrlGridHoldDlg dialog

class CCtrlGridHoldDlg : public CBaseForm
{
	DECLARE_DYNAMIC(CCtrlGridHoldDlg)

public:
	CCtrlGridHoldDlg(CWnd* pParent = NULL);
	virtual ~CCtrlGridHoldDlg()
	{

	}
	static CCtrlGridHoldDlg* Instance();

	virtual CString GetTitle() const
	{
		return "Ñ¡Ôñ";
	}

public:
	BEGIN_DELEGATE_MAP(CCtrlGridHoldDlg)
		EVENT_DELEGATE_ENTRY(OnSelected,System::Object^ ,System::EventArgs^ )
	END_DELEGATE_MAP()

	void OnSelected(System::Object^ Sender,System::EventArgs^ eventargs);


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
	CWinFormsControl<PowerBenchSharpLib::UCAmmetersOpe>& GetHoldCtrl();

private:
	CWinFormsControl<PowerBenchSharpLib::UCAmmetersOpe> m_ctrl;
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
