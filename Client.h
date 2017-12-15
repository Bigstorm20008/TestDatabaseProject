#pragma once

#include <tchar.h>
#include "SqlFramework.h"
#include <vector>
#include "Constants.h"

class Client
{
private:
	int clientID;
	SQLTCHAR* nickname;
	SQLTCHAR* lastname;
	SQLTCHAR* firstname;
	SQLTCHAR* patronymicname;
	SQLTCHAR* imageLocation;

	void FillAllClientField(Binding*pBinding);
	void LoadMainInfo();
public:
	void FreeAllField();
	void GetInfoForCurrentClient(std::vector<SQLTCHAR*>* selectedClient);
	Client();
	~Client();
};

