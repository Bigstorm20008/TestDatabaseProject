#include "Binding.h"

int Binding::destructorCalled = 0;
int Binding::construcorCalled = 0;


Binding::Binding()
{
	construcorCalled++;
}


Binding::~Binding()
{
	destructorCalled++;
	if (description)
	{
		delete[]description;
		description = nullptr;
	}
	if (nextBinding)
	{
		delete nextBinding;
		nextBinding = nullptr;
	}
	
}


void Binding::AllocateBindings(SQLHANDLE hStmthandle)
{
	SQLRETURN retcode; 
	SQLSMALLINT numCols;
	SQLTCHAR typeName[250];
	retcode = SQLNumResultCols(hStmthandle, &numCols);
	retcode = SQLColAttribute(hStmthandle, 1, SQL_DESC_TABLE_NAME, &typeName, sizeof(typeName), NULL, NULL);
	for (int i = 1; i <= numCols; i++)
	{
		//========================================================================================================================
		if (i == 1) 
		{
			retcode = SQLColAttribute(hStmthandle, i, SQL_DESC_LENGTH, NULL, NULL, NULL, &descLen);
			size_t len = (descLen + 1)*sizeof(TCHAR);
			description = new TCHAR[len];
			SQLBindCol(hStmthandle, i, SQL_C_TCHAR, description, len, &StrLen_or_Ind);
			nextBinding = nullptr;
			continue;
		}

		//=========================================================================================================================
		if (i < numCols)
		{

			if (!nextBinding)
			{
				Binding* lastBinding = new Binding;
				nextBinding = lastBinding;
				SQLColAttribute(hStmthandle, i, SQL_DESC_LENGTH, NULL, NULL, NULL, &lastBinding->descLen);
				size_t len = (lastBinding->descLen + 1)*sizeof(TCHAR);
				lastBinding->description = new TCHAR[len];
				SQLBindCol(hStmthandle, i, SQL_C_TCHAR, lastBinding->description, len, &nextBinding->StrLen_or_Ind);
			}
			else
			{
				Binding* tempBinding = nextBinding;
				while (tempBinding->nextBinding)
				{
					tempBinding = tempBinding->nextBinding;
				}
				Binding* lastBinding = new Binding;
				SQLColAttribute(hStmthandle, i, SQL_DESC_LENGTH, NULL, NULL, NULL, &lastBinding->descLen);
				size_t len = (lastBinding->descLen + 1)*sizeof(TCHAR);
				lastBinding->description = new TCHAR[len];
				SQLBindCol(hStmthandle, i, SQL_C_TCHAR, lastBinding->description, len, &nextBinding->StrLen_or_Ind);
				tempBinding->nextBinding = lastBinding;
				continue;
			}
		}
		//==============================================================================================================================
		if (i == numCols)
		{
			if (nextBinding)
			{
				Binding* tempBinding = nextBinding;
				while (tempBinding->nextBinding)
				{
					tempBinding = tempBinding->nextBinding;
				}
				Binding* lastBinding = new Binding;
				SQLColAttribute(hStmthandle, i, SQL_DESC_LENGTH, NULL, NULL, NULL, &lastBinding->descLen);
				size_t len = (lastBinding->descLen + 1)*sizeof(TCHAR);
				lastBinding->description = new TCHAR[len];
				SQLBindCol(hStmthandle, i, SQL_C_TCHAR, lastBinding->description, len, &nextBinding->StrLen_or_Ind);
				lastBinding->nextBinding = nullptr;
				tempBinding->nextBinding = lastBinding;
			}
			else
			{
				Binding* lastBinding = new Binding;
				retcode = SQLColAttribute(hStmthandle, i, SQL_DESC_LENGTH, NULL, NULL, NULL, &lastBinding->descLen);
				size_t len = (lastBinding->descLen + 1)*sizeof(TCHAR);
				lastBinding->description = new TCHAR[len];
				retcode = SQLBindCol(hStmthandle, i, SQL_C_TCHAR, lastBinding->description, len, &lastBinding->StrLen_or_Ind);
				nextBinding = lastBinding;
				lastBinding->nextBinding = nullptr;
			}
		}
		//=================================================================================================================================
	}
	//============================================================================================================================================
}

TCHAR* Binding::GetDescription(void)
{
	return description;
}

