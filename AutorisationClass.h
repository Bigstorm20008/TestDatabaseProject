#pragma once
#include <Windows.h>
#include "SqlFramework.h"
#include "MyUserInterface.h"
#include <tchar.h>

//This class define rights of current user in database and give control to MyUserInterface class for create GUI
class AutorisationClass
{
private:

	TCHAR* pUserName;            //here save current username
	TCHAR* pRoleMember;          //here save role of current user in database

	
	void GetDBUserName();        //Function get username of current user from database	
	void GetRoleOfCurrentUser(); //Function get role of current user from database

public:
	AutorisationClass();
	~AutorisationClass();
};

