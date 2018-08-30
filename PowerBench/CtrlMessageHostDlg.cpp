#include "StdAfx.h"
#include "CtrlMessageHostDlg.h"
#include "afxdialogex.h"


// CCtrlMessageHostDlg dialog

IMPLEMENT_DYNAMIC(CCtrlMessageHostDlg, CBaseForm)

CWinFormsControl<Tigera::LibNetworkWrap::UCMessageHost>& CCtrlMessageHostDlg::GetHoldCtrl()
{
	return m_ctrl;
}

static CCtrlMessageHostDlg* pinstance = NULL;
CCtrlMessageHostDlg* CCtrlMessageHostDlg::Instance()
{
	return pinstance;
}

CCtrlMessageHostDlg::CCtrlMessageHostDlg( CWnd* pParent /*= NULL*/ ) : CBaseForm(CCtrlMessageHostDlg::IDD, pParent)
{
	pinstance = this;
}

bool CCtrlMessageHostDlg::SendData()
{
	Tigera::T_Definition::P_AmmeterInfo info;
	auto data =  Tigera::T_Definition::ESHelper::Pack(info);
	this->GetHoldCtrl().GetControl()->SendMessage(data);
	return true;
}




	BEGIN_MESSAGE_MAP(CCtrlMessageHostDlg, CBaseForm)	
		ON_WM_SIZE()
	END_MESSAGE_MAP()


	// CCtrlMessageHostDlg message handlers



