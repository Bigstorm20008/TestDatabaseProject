#include "SqlFramework.h"

//Constructor
CSqlFramework::CSqlFramework()
{
	//Initialize  variables

	
}

void CSqlFramework::InitHandles(void)
{
	//Allocate an enviroment handle
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	//ODBC 3 support
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)(SQL_OV_ODBC3), SQL_IS_INTEGER);
	//Allocate a connection handle
	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
	
}
//Connection to database
BOOL CSqlFramework::OpenConnection(SQLTCHAR* dataSourceName, SQLTCHAR* username, SQLTCHAR* pass) 
{
	InitHandles();
	//При попытке подключения к базе данных изменим вид курсора
	HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
	SetCursor(hCursor);

	//Подключимся к базе данных
	SQLRETURN retCode;
	retCode = SQLConnect(hDbc, dataSourceName, SQL_NTS, username, SQL_NTS, pass, SQL_NTS);
	switch (retCode)
	{
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:
	{
		return TRUE;
		break;
	}
	case SQL_ERROR:
	{
		return FALSE;
		break;
	}
	default:
		break;
	}
	return 0;
}

void CSqlFramework::CloseConnection(void)
{
	if (hStmt)
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLDisconnect(hDbc);
	if (hDbc)
	    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv)
	    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	hStmt = hDbc = hEnv = nullptr;
}

//Destructor
CSqlFramework::~CSqlFramework()
{
	delete pBinding;
}



BOOL CSqlFramework::CreateConsole(void)
{
	FreeConsole(); //на всякий случай
	if (AllocConsole())
	{
		int hCrt = _open_osfhandle((long)
			GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		*stdout = *(::_fdopen(hCrt, "w"));
		::setvbuf(stdout, NULL, _IONBF, 0);
		*stderr = *(::_fdopen(hCrt, "w"));
		::setvbuf(stderr, NULL, _IONBF, 0);
		return TRUE;
	}
	return FALSE;
}

 
SQLHANDLE CSqlFramework::SendQueryToDatabase(SQLWCHAR* sqlCommand)
{
	SQLRETURN retCode;
	retCode = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	if (retCode == SQL_ERROR)
		extract_error(TEXT("AllocHandle error(hstmt)"), hDbc, SQL_HANDLE_DBC);
	size_t len = _tcslen(sqlCommand) + 1;
	retCode = SQLExecDirect(hStmt, sqlCommand, len);
	if (retCode == SQL_ERROR)
		extract_error(TEXT("ExecDirect error"), hStmt, SQL_HANDLE_STMT);
	pBinding = new Binding;
	pBinding->AllocateBindings(hStmt);
	return hStmt;
}


void CSqlFramework::extract_error(TCHAR *fn, SQLHANDLE handle, SQLSMALLINT type)
{
	CreateConsole();
	SQLSMALLINT  i = 0;
	SQLINTEGER   native;
	SQLTCHAR     state[7];
	SQLTCHAR     text[256];
	SQLSMALLINT  len;
	SQLRETURN    ret;

	do
	{
		ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
			sizeof(text), &len);
		if (SQL_SUCCEEDED(ret))
			std::wcout << state << "||" << i << "||" << native << "||" << text;
		    std::cout << std::endl;
	} while (ret == SQL_SUCCESS);
	system("pause");
}

Binding* CSqlFramework::GetBinding(void)
{
	return pBinding;
}

void CSqlFramework::FreeBinding(SQLHANDLE hsTmtHandle)
{
	SQLRETURN retCode;
	retCode = SQLFreeStmt(hsTmtHandle, SQL_CLOSE);
	retCode = SQLFreeStmt(hsTmtHandle, SQL_UNBIND);
	retCode = SQLFreeStmt(hsTmtHandle, SQL_RESET_PARAMS);

	retCode = SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	pBinding->FreeBinding();
	delete pBinding;
	pBinding = nullptr;
}

SQLHANDLE CSqlFramework::ExecutePrepearedQuery(SQLTCHAR* sqlCommand, SQLTCHAR** parametrArray)
{
	SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	SQLRETURN retcode = SQLPrepare(hStmt, sqlCommand, SQL_NTS);
	if (retcode == SQL_ERROR)
		extract_error(L"Ошибка подготовки запроса", hStmt, SQL_HANDLE_STMT);
	SQLSMALLINT   DataType, DecimalDigits, Nullable;
	SQLUINTEGER   ParamSize;
	SQLINTEGER iNts = SQL_NTS;
	SQLSMALLINT numParams;
	SQLNumParams(hStmt, &numParams);

	if (numParams)
	{
		for (int i = 0; i < numParams; i++)
		{
			SQLDescribeParam(hStmt, i + 1, &DataType, &ParamSize, &DecimalDigits, &Nullable);
			SQLBindParameter(hStmt, i + 1, SQL_PARAM_INPUT, SQL_C_TCHAR, DataType, ParamSize,
				DecimalDigits, parametrArray[i], (ParamSize)*sizeof(SQLTCHAR),
				&iNts);
		}

	}
	retcode = SQLExecute(hStmt);
	if (retcode == SQL_ERROR)
		extract_error(L"Ошибка выполнения запроса", hStmt, SQL_HANDLE_STMT);


	pBinding = new Binding;
	pBinding->AllocateBindings(hStmt);
	return hStmt;
	
}


SQLHANDLE CSqlFramework::GetStatementHandle(void)
{
	return &hStmt;
}