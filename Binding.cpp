#include "Binding.h"

int Binding::destructorCalled = 0;
int Binding::construcorCalled = 0;

Binding::Binding()
{
	description = nullptr;
	nextBinding = nullptr;
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
	Binding* tempBinding = this->nextBinding;
	while (tempBinding)
	{
		delete[](tempBinding->description);
		tempBinding->description = nullptr;
		tempBinding = tempBinding->nextBinding;
	}
	while (nextBinding)
	{
		delete nextBinding;
		nextBinding = nullptr;
	}
}


void Binding::AllocateBindings(SQLHANDLE hStmthandle)
{
	SQLRETURN retcode; 
	SQLSMALLINT numCols;
	retcode = SQLNumResultCols(hStmthandle, &numCols);
	for (int i = 1; i <= numCols; i++)
	{
		//========================================================================================================================
		if (i == 1) 
		{
			retcode = SQLColAttribute(hStmthandle, i, SQL_DESC_DISPLAY_SIZE, NULL, NULL, NULL, &descLen);
			size_t len = (descLen + 1);
			SQLColAttribute(hStmthandle, i, SQL_DESC_LABEL, &columnName, sizeof(columnName), NULL, NULL);
			description = new TCHAR[len];
			SQLBindCol(hStmthandle, i, SQL_C_TCHAR, description, len*sizeof(TCHAR), &StrLen_or_Ind);
			if (nextBinding)
			{
				delete nextBinding;
				nextBinding = nullptr;
			}
			continue;
		}

		//=========================================================================================================================
		if (i < numCols)
		{

			if (!nextBinding)
			{
				Binding* lastBinding = new Binding;
				nextBinding = lastBinding;
				SQLColAttribute(hStmthandle, i, SQL_DESC_DISPLAY_SIZE, NULL, NULL, NULL, &lastBinding->descLen);
				size_t len = (lastBinding->descLen + 1);
				SQLColAttribute(hStmthandle, i, SQL_DESC_LABEL, &lastBinding->columnName, sizeof(columnName), NULL, NULL);
				lastBinding->description = new TCHAR[len];
				SQLBindCol(hStmthandle, i, SQL_C_TCHAR, lastBinding->description, len*sizeof(TCHAR), &nextBinding->StrLen_or_Ind);
			}
			else
			{
				Binding* tempBinding = nextBinding;
				while (tempBinding->nextBinding)
				{
					tempBinding = tempBinding->nextBinding;
				}
				Binding* lastBinding = new Binding;
				SQLColAttribute(hStmthandle, i, SQL_DESC_DISPLAY_SIZE, NULL, NULL, NULL, &lastBinding->descLen);
				size_t len = (lastBinding->descLen + 1);
				SQLColAttribute(hStmthandle, i, SQL_DESC_LABEL, &lastBinding->columnName, sizeof(columnName), NULL, NULL);
				lastBinding->description = new TCHAR[len];
				SQLBindCol(hStmthandle, i, SQL_C_TCHAR, lastBinding->description, len*sizeof(TCHAR), &nextBinding->StrLen_or_Ind);
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
				SQLColAttribute(hStmthandle, i, SQL_DESC_DISPLAY_SIZE, NULL, NULL, NULL, &lastBinding->descLen);
				size_t len = (lastBinding->descLen + 1);
				lastBinding->description = new TCHAR[len];
				SQLColAttribute(hStmthandle, i, SQL_DESC_LABEL, &lastBinding->columnName, sizeof(columnName), NULL, NULL);
				SQLBindCol(hStmthandle, i, SQL_C_TCHAR, lastBinding->description, len*sizeof(TCHAR), &nextBinding->StrLen_or_Ind);
				lastBinding->nextBinding = nullptr;
				tempBinding->nextBinding = lastBinding;
			}
			else
			{
				Binding* lastBinding = new Binding;
				retcode = SQLColAttribute(hStmthandle, i, SQL_DESC_DISPLAY_SIZE, NULL, NULL, NULL, &lastBinding->descLen);
				size_t len = (lastBinding->descLen + 1);
				lastBinding->description = new TCHAR[len];
				SQLColAttribute(hStmthandle, i, SQL_DESC_LABEL, &lastBinding->columnName, sizeof(columnName), NULL, NULL);
				retcode = SQLBindCol(hStmthandle, i, SQL_C_TCHAR, lastBinding->description, len*sizeof(TCHAR), &lastBinding->StrLen_or_Ind);
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

TCHAR* Binding::GetColumnName(void)
{
	return columnName;
}

Binding* Binding::GetNextBinding(void)
{
	return nextBinding;
}

void Binding::FreeBinding(void)
{
	Binding* tempBinding = this;
	while (tempBinding)
	{
		delete[] tempBinding->description;
		tempBinding->description = nullptr;
		tempBinding->descLen = 0;
		tempBinding->StrLen_or_Ind = 0;
		tempBinding = tempBinding->nextBinding;
	}
}