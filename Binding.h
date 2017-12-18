#pragma once
#include <Windows.h>
#include <odbcinst.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>

//This class binding variables in class to result of dataset. It is single linked list
class Binding
{
private:

	TCHAR* pDescription;         //description for current binding
	SQLLEN pDescLen;             //maximum lenght for current column
	SQLLEN StrLen_or_Ind;        //actual lenght for current description(initializing when use SQLFetch())
	Binding* pNextBinding;       //pointer to next Binding
	SQLTCHAR columnName[250];    //column name for current binding
	
	void bindingVariables(SQLHANDLE statementHandle, int index, Binding* pThisBinding);
	
public:
	
	void AllocateBindings(SQLHANDLE hStmthandle);
	TCHAR* GetDescription(void);
	TCHAR* GetColumnName(void);
	Binding* GetNextBinding(void);
	void FreeBinding(void);
	Binding();
	~Binding();
};

