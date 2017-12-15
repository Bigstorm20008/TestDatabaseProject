#include "AutorisationClass.h"


AutorisationClass::AutorisationClass()
{	
	GetDBUserName();
	GetRoleOfCurrentUser();
	MyUserInterface interfaceForUser(pRoleMember);
}


AutorisationClass::~AutorisationClass()
{
	//Удалим переменные, выделенные операцией new
	delete[]pUserName;
	pUserName = nullptr;
	delete pRoleMember;
	pRoleMember = nullptr;
	
}

void AutorisationClass::GetDBUserName()
{


	extern CSqlFramework* sqlODBC;                                //Переменная объявлена глобально в main.cpp
	TCHAR* sqlCommand = TEXT("SELECT CURRENT_USER");              //Запрос для SQL Server
	SQLHANDLE hStmt = sqlODBC->SendQueryToDatabase(sqlCommand);   //Отправим запрос на выполнение и получим дескриптор hsTmt
	//Результатом данного запроса будет 1 строка поэтому просто извлечем данные из источника
	SQLFetch(hStmt);
	//Получим наши данные
	Binding* pBinding = sqlODBC->GetBinding();
	//Получим длину, полученного имени пользователя
	size_t len = _tcslen(pBinding->GetDescription());
	//Выделим память для сохранения и обнулим ее
	pUserName = new TCHAR[len + sizeof(TCHAR)];
	memset(pUserName, 0, len*sizeof(TCHAR));
	//Скопируем данные в pUserName
	lstrcat(pUserName, pBinding->GetDescription());
	//Освободим ресурсы после использования
	sqlODBC->FreeBinding(hStmt);
	
	
	
	

	
}

void AutorisationClass::GetRoleOfCurrentUser()
{
	extern CSqlFramework* sqlODBC;                       //Переменная объявлена глобально в main.cpp
	TCHAR* partOfsqlCommand = TEXT("EXEC sp_helpuser");       //SQL запрос для получения информации о пользователе(без имени пользователя)

	//Составим SQL запрос для БД......
	//Получим длину запроса и выделим память для него
	size_t len = _tcslen(partOfsqlCommand) + _tcslen(pUserName) + _tcslen(TEXT(" '")) + _tcslen(TEXT("'"));
	TCHAR* sqlCommand = new TCHAR[len+1];
	//Обнулим, выделенную память
	memset(sqlCommand, 0, len);
	//Составим запрос путем конкатенации
	lstrcat(sqlCommand, partOfsqlCommand);
	lstrcat(sqlCommand, TEXT(" '"));
	lstrcat(sqlCommand, pUserName);
	lstrcat(sqlCommand, TEXT("'"));
	//Отправим запрос на выполнение и получим операторный дескриптор hstmt
	SQLHANDLE hStmt = sqlODBC->SendQueryToDatabase(sqlCommand);
	//Получим указатель на класс с полученными данными
	Binding* pBinding = sqlODBC->GetBinding();
	//Извлечем полученные данные, основываясь на имени столбца('RoleName')
	while (SQLFetch(hStmt) != SQL_NO_DATA)
	{
		Binding* thisBinding = pBinding;
		while (thisBinding)
		{
			if (lstrcmp(thisBinding->GetColumnName(),TEXT("RoleName")) == 0)
			{
				size_t len = lstrlen(thisBinding->GetDescription());
				pRoleMember = new TCHAR[len + 1];
				memset(pRoleMember, 0, len);
				lstrcat(pRoleMember, thisBinding->GetDescription());
				break;
			}
			else
			{
				thisBinding = thisBinding->GetNextBinding();
			}
		}
		
	}
	sqlODBC->FreeBinding(hStmt);
	delete sqlCommand;
	sqlCommand = nullptr;

}





