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
	SQLTCHAR columnName[250];
	

	
public:
	static int destructorCalled;
	static int construcorCalled;

	void AllocateBindings(SQLHANDLE hStmthandle);
	TCHAR* GetDescription(void);
	TCHAR* GetColumnName(void);
	Binding* GetNextBinding(void);
	void FreeBinding(void);
	Binding();
	~Binding();
};

