#pragma once

#include <Windows.h>
#include <odbcinst.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>

#include "Binding.h"
//#include "AutorisationClass.h"

using std::cout;
using std::endl;
using std::wcout;


class CSqlFramework
{
private:
	SQLHENV hEnv;   //enviroment handle
	SQLHDBC hDbc;   //connection handle
	SQLHSTMT hStmt; //statement handle
	SQLHDESC hDesc; //descriptor handle
		
	void InitHandles(void);   //Initialize handles
	BOOL CreateConsole(void); //Init console in win32 app
	void extract_error(TCHAR* fn, SQLHANDLE handle, SQLSMALLINT type);

	Binding* pBinding;
public:
	
	CSqlFramework(); //constructor
    ~CSqlFramework();//destructor

	//Connecting to database
	BOOL OpenConnection(TCHAR* dataSourceName, TCHAR* username, TCHAR* pass); 
	//disconnect from database
	void CloseConnection(void);                                                    
	SQLHANDLE SendQueryToDatabase(TCHAR* sqlCommand);
	Binding* GetBinding(void);
	void FreeBinding(SQLHANDLE hsTmtHandle);
	SQLHANDLE ExecutePrepearedQuery(SQLTCHAR* sqlCommand, SQLTCHAR** parametrArray);
	SQLHANDLE GetStatementHandle(void);
};

