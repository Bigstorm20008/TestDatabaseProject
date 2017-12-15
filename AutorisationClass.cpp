#include "AutorisationClass.h"


AutorisationClass::AutorisationClass()
{
	GetDBUserName();
}


AutorisationClass::~AutorisationClass()
{
}

void AutorisationClass::GetDBUserName()
{
	extern CSqlFramework* sqlODBC;
	TCHAR* sqlCommand = L"SELECT CURRENT_USER";           //Запрос для SQL Server
	SQLHANDLE hStmt = sqlODBC->SendQueryToDatabase(sqlCommand);
	Binding* pBinding = sqlODBC->GetBinding();
	size_t len = lstrlen(pBinding->GetDescription());
	pUserName = new TCHAR[len + 1];
	FetchingResult(hStmt, pUserName);

	
}

void AutorisationClass::FetchingResult(SQLHANDLE hsTmtHandle, TCHAR* classVariable)
{
	
	SQLRETURN retcode = SQL_SUCCESS;
	while (SQLFetch(hsTmtHandle) != SQL_NO_DATA)
	{
		extern CSqlFramework* sqlODBC;
		Binding* pBinding = sqlODBC->GetBinding();
		classVariable = pBinding->GetDescription();
		/*if (nextBinding)
		{
			Binding* tempBinding = nextBinding;
			while (tempBinding)
			{
				tempBinding = tempBinding->nextBinding;
			}
		}*/
	}
}