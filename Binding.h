#pragma once
#include <Windows.h>
#include <odbcinst.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>


class Binding
{
private:
	
	TCHAR* description;
	SQLLEN descLen;
	SQLLEN StrLen_or_Ind;
	Binding* nextBinding;

	

	
public:
	static int destructorCalled;
	static int construcorCalled;

	void AllocateBindings(SQLHANDLE hStmthandle);
	TCHAR* GetDescription(void);
	Binding();
	~Binding();
};

