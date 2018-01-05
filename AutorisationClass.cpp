#include "AutorisationClass.h"


AutorisationClass::AutorisationClass()
{	
	pUserName = nullptr;
	pRoleMember = nullptr;
}


AutorisationClass::~AutorisationClass()
{
	//if destructor called delete all variable and set it to not valid
	delete [] pUserName;
	pUserName = nullptr;
	delete [] pRoleMember;
	pRoleMember = nullptr;
	
}

void AutorisationClass::GetDBUserName()
{

	extern CSqlFramework* sqlODBC;                                //allocating in main.cpp for working with database
	TCHAR* sqlCommand = TEXT("SELECT CURRENT_USER");              //query to database for get current user
	SQLHANDLE hStmt = sqlODBC->SendQueryToDatabase(sqlCommand);   //send query to database and save statement handle fo fetching data
	
	//Result of this query is 1 row, get it
	SQLFetch(hStmt);
	//Get class where saved data from dataset(result of query)
	Binding* pBinding = sqlODBC->GetBinding();
	//Get lenght of username 
	size_t len = _tcslen(pBinding->GetDescription());
	//Allocate memory for save it and fill it by /0
	pUserName = new TCHAR[len + sizeof(TCHAR)];
	memset(pUserName, 0, len*sizeof(TCHAR));
	//copy current username to pUserName
	_tcscat_s(pUserName, len+1, pBinding->GetDescription());
	//Free resource after using
	sqlODBC->FreeBinding(hStmt);
	
}

TCHAR* AutorisationClass::GetRoleOfCurrentUser()
{
	GetDBUserName();
	extern CSqlFramework* sqlODBC;                            //allocating in main.cpp for working with database
	SQLTCHAR* sqlCommand = TEXT("EXEC sp_helpuser ?");        //SQL query with parameter
	SQLTCHAR* parametrArray[1] = { pUserName };               //parameter for query (pUsername)

	SQLHANDLE hStmt = sqlODBC->ExecutePrepearedQuery(sqlCommand, parametrArray);  //send query with parameter and parameter to execute
	Binding* pBinding = sqlODBC->GetBinding();               //Get class where saved data from dataset(result of query)

	//Fetching result to pBinding
	while (SQLFetch(hStmt) != SQL_NO_DATA)                  
	{
		Binding* thisBinding = pBinding;     //temp binding
		while (thisBinding)
		{
			if (_tcscmp(thisBinding->GetColumnName(), TEXT("RoleName")) == 0)    //if value in ColumnName = "RoleName"
			{
				size_t len = _tcslen(thisBinding->GetDescription());   //get len of description(role name)
				pRoleMember = new TCHAR[len + 1];                      //allocate memory for saving it
				memset(pRoleMember, 0, len*sizeof(TCHAR));             //fill it by /0
				_tcscat_s(pRoleMember,len+1, thisBinding->GetDescription());   //copy description to pRoleMember
				break;
			}
			else   //if ColumName != "RoleName"
			{
				thisBinding = thisBinding->GetNextBinding();     //set pointer to nextBinding
			}
		}
		
	}
	sqlODBC->FreeBinding(hStmt);    //Free all resource after working
	return pRoleMember;
}





