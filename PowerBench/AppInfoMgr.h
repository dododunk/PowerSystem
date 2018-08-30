#pragma once
class CAppInfoMgr
{
public:
	CAppInfoMgr(void);
	~CAppInfoMgr(void);
	BOOL LoadConfig(const  char* filepath);
};

