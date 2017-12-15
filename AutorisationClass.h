#pragma once
#include <Windows.h>
#include "SqlFramework.h"



class AutorisationClass
{
private:
	TCHAR* pUserName;
	TCHAR* pRoleMember;
	void GetDBUserName();
	void GetRoleOfCurrentUser();
	void FetchingResult(SQLHANDLE hsTmtHandle,TCHAR* classVariable);
public:
	AutorisationClass();
	~AutorisationClass();
};

