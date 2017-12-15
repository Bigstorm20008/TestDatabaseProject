#pragma once
#include <Windows.h>
#include "SqlFramework.h"
#include "MyUserInterface.h"
#include <tchar.h>


class AutorisationClass
{
private:

	TCHAR* pUserName;            //Сюда сохраним имя текущего пользователя
	TCHAR* pRoleMember;          //Роль текущего пользователя
	void GetDBUserName();        //Функция получает имя текущего пользователя БД и сохраняет его в pUserName
	void GetRoleOfCurrentUser(); //Функция получает роль текущего пользователя в БД и сохраняет ее в pRoleMember

public:
	AutorisationClass();
	~AutorisationClass();
};

