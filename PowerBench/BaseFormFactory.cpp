#include "StdAfx.h"
#include "BaseFormFactory.h"
#include "BaseForm.h"
#include "CtrlholdDlg.h"
#include "CtrlMessageHostDlg.h"
#include "CtrlGridHoldDlg.h"
#include "CtrlHistoryHoldDlg.h"

CBaseForm* CBaseFormFactory::CreateForm( int CMD )
{
	CBaseForm *pForm = NULL;
	switch(CMD)
	{
	case 1:
		break;
	case 2:
		break;
	default:
		//CAboutDlg* dlg
		break;
	}
	pForm->ModifyStyle(0,WS_EX_CONTROLPARENT);
	pForm->ShowWindow(SW_SHOW);

	return NULL;
}

CBaseForm* CBaseFormFactory::CreateFrom( const char* CMD )
{

	return NULL;
}

CBaseFormFactory::CBaseFormFactory()
{

}

CBaseFormFactory& CBaseFormFactory::Instance()
{
	static CBaseFormFactory instance;
	return instance;
}

BOOL CBaseFormFactory::SetCurrentActionID(ActionEnum id)
{
	m_currentActionID = id;
	return FALSE;
}

CBaseForm* CBaseFormFactory::RunCurrentAction( CWnd* pParent )
{
	CBaseForm* pForm = NULL;
	switch(m_currentActionID)
	{
	case ActionEnum::_3761Test:
		{		
			pForm = new CCtrlholdDlg(pParent);
			pForm->Create(CCtrlholdDlg::IDD,pParent);
			break;
		}
	case  ActionEnum::_NetServerStartListen:
		{		
			pForm = new CCtrlMessageHostDlg(pParent);		
			pForm->Create(CCtrlMessageHostDlg::IDD,pParent);
			((CCtrlMessageHostDlg*)pForm)->GetHoldCtrl()->ClientMode = false;
			break;
		}
	case  ActionEnum::_NetConnected:
		{		
			pForm = new CCtrlMessageHostDlg(pParent);		
			pForm->Create(CCtrlMessageHostDlg::IDD,pParent);
			((CCtrlMessageHostDlg*)pForm)->GetHoldCtrl()->ClientMode = true;
			break;
		}
	case  ActionEnum::_SHOWSELECTED:
		{		
			pForm = new CCtrlGridHoldDlg(pParent);		
			pForm->Create(CCtrlGridHoldDlg::IDD,pParent);
			
			break;
		}
	case ActionEnum::_CALLTESTFORM:
		{
			break;
		}
	case  ActionEnum::_QUERYHISTORY:
		{
			pForm = new CCtrlHistoryHoldDlg(pParent);
			pForm->Create(CCtrlGridHoldDlg::IDD,pParent);
			break;
		}
			

		
	default:
		break;

	}
	if(pForm != NULL)
	{	
		pForm->ModifyStyle(0,WS_EX_CONTROLPARENT);
		pForm->ShowWindow(SW_SHOW);
	}

	return pForm;
}
