#pragma once
#include <Windows.h>
#include "SqlFramework.h"
#include "MyUserInterface.h"
#include <tchar.h>


class AutorisationClass
{
private:

	TCHAR* pUserName;            //���� �������� ��� �������� ������������
	TCHAR* pRoleMember;          //���� �������� ������������
	void GetDBUserName();        //������� �������� ��� �������� ������������ �� � ��������� ��� � pUserName
	void GetRoleOfCurrentUser(); //������� �������� ���� �������� ������������ � �� � ��������� �� � pRoleMember

public:
	AutorisationClass();
	~AutorisationClass();
};

