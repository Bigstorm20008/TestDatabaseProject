#pragma once

#include <Windows.h>
#include <odbcinst.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "Binding.h"
#include "AutorisationClass.h"

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
	void extract_error(char *fn, SQLHANDLE handle, SQLSMALLINT type);

	Binding* pBinding;
public:
	
	CSqlFramework(); //constructor
    ~CSqlFramework();//destructor

	
	BOOL OpenConnection(SQLTCHAR* dataSourceName, SQLTCHAR* username, SQLTCHAR* pass);       //Connecting to database
	void CloseConnection(void);                                                              //disconnect from database
	SQLHANDLE SendQueryToDatabase(SQLTCHAR* sqlCommand);
	Binding* GetBinding(void);
};

