#pragma once
#include <map>

#include "ActionEnum.h"
class CBaseForm;
class CBaseFormFactory
{
public:
	static CBaseFormFactory& Instance();
	BOOL SetCurrentActionID(ActionEnum actionID);
	CBaseForm* RunCurrentAction(CWnd* pParent);
	
	static CBaseForm* CreateForm(int CMD);
	static CBaseForm* CreateFrom(const char* CMD);
private:
	std::map<CString,CBaseForm*> m_Map;
	ActionEnum m_currentActionID;
	
private:
	CBaseFormFactory();


private:
	CBaseFormFactory(const CBaseFormFactory& objectSrc);              // no implementation
	void operator=(const CBaseFormFactory& objectSrc);       // no implementation


};
