#include "StdAfx.h"
#include "CtrlGridHoldDlg.h"
#include "afxdialogex.h"
#include "CtrlMessageHostDlg.h"

// CCtrlGridHoldDlg dialog

IMPLEMENT_DYNAMIC(CCtrlGridHoldDlg, CBaseForm)

CWinFormsControl<PowerBenchSharpLib::UCAmmetersOpe>& CCtrlGridHoldDlg::GetHoldCtrl()
{
	return m_ctrl;
}

static CCtrlGridHoldDlg* pinstance = NULL;
CCtrlGridHoldDlg* CCtrlGridHoldDlg::Instance()
{
	return pinstance;
}

CCtrlGridHoldDlg::CCtrlGridHoldDlg( CWnd* pParent /*= NULL*/ ) : CBaseForm(CCtrlGridHoldDlg::IDD, pParent)
{
	pinstance = this;
}

void CCtrlGridHoldDlg::OnSelected( System::Object^ Sender,System::EventArgs^ eventargs )
{
	
	CCtrlMessageHostDlg* pinstance = CCtrlMessageHostDlg::Instance();
	if(pinstance != NULL)
	{
		Tigera::LibCommon::BytesBuilder^ bb = gcnew Tigera::LibCommon::BytesBuilder();
		Tigera::T_Definition::P_CMD_Request cmd;// = gcnew Tigera::TransportData::Definition::P_CMD_Request();
		cmd.ChildCount =m_ctrl->Datas->Count;
		cmd.Request = Tigera::T_Definition::P_CMD_Request::CMD::SendUserInfo;
		bb->Append(Tigera::T_Definition::ESHelper::Pack(cmd, m_ctrl->Datas->Count) );
		for(int i =0; i<m_ctrl->Datas->Count; ++i)
		{		
			bb->Append(Tigera::T_Definition::ESHelper::Pack(m_ctrl->Datas[i]));
		}
		pinstance->GetHoldCtrl()->SendMessage(bb->ToBytes());
	}
}

BOOL CCtrlGridHoldDlg::OnInitDialog()
{
	CBaseForm::OnInitDialog();
	//TO DO 界面元素初始化在此:主要是Combox数据添加
	CString title ;

	m_ctrl.GetWindowText(title);
	this->SetWindowText(title);

	m_ctrl->ONbutton_SendAmmDatasClick += MAKE_DELEGATE(System::EventHandler ,OnSelected);

	return TRUE;
}




BEGIN_MESSAGE_MAP(CCtrlGridHoldDlg, CBaseForm)	
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCtrlGridHoldDlg message handlers



