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
	//binding variables to all column in dataset. This function called after SQLExecute or SQLExecDirect
	void AllocateBindings(SQLHANDLE hStmthandle);
	//get description for current column in dataset. Value in pDescription is valid after called SQLFetch()
	TCHAR* GetDescription(void);
	//get column name for current column in dataset. Value in columnName is valid after called SQLFetch()
	TCHAR* GetColumnName(void);
	//get pointer to pNextBinding
	Binding* GetNextBinding(void);
	//this function free all binding after using data. its called from CSqlFramework class.Other class must not call this function.
	void FreeBinding(void);
	Binding();
	~Binding();
};

