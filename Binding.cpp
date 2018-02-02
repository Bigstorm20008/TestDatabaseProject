#include "Binding.h"


Binding::Binding()
{
	//init all pointers by not valid value
	pDescription = nullptr;     
	pNextBinding = nullptr;
}


Binding::~Binding()
{
	
	if (pDescription)
	{
		delete[]pDescription;
		pDescription = nullptr;
	}
	Binding* pTempBinding = this->pNextBinding;
	while (pTempBinding)
	{
		delete[](pTempBinding->pDescription);
		pTempBinding->pDescription = nullptr;
		pTempBinding = pTempBinding->pNextBinding;
	}
	while (pNextBinding)
	{
		delete pNextBinding;
		pNextBinding = nullptr;
	}
}


void Binding::AllocateBindings(SQLHANDLE hStmthandle)
{
	SQLRETURN retcode;     //return for ODBC API function   
	SQLSMALLINT numCols;   //here save count of columns in dataset
	retcode = SQLNumResultCols(hStmthandle, &numCols);    //get count of columns from dataset

	//binding variables for each columns
	for (int i = 1; i <= numCols; i++)
	{
		//========================================================================================================================
		if (i == 1)     //if first column
		{
			Binding* pThisBinding = this;       //create temp pointer and init by "this" value ("this" pointer initialazing in dynamyc memory in CSqlFramework.cpp)
			bindingVariables(hStmthandle, i, pThisBinding);  //binding varables
			if (pNextBinding)       //if pNextBinding is valid
			{
				delete pNextBinding;          //delete pNextBinding
				pNextBinding = nullptr;       //set value to no valid
			} 
			continue;    //go to the next iteration
		}

		//=========================================================================================================================
		if (i < numCols)  //if index < numCols
		{

			if (!pNextBinding)      //if pNextBinding is not valid
			{
				Binding* pThisBinding = new Binding;	            //Allocate memory for current column			
				bindingVariables(hStmthandle, i, pThisBinding);     //binding it
				pNextBinding = pThisBinding;                        //init pNextBinding by pThisBinding
			}
			else    //if pNextBinding is valid
			{
				//find last element in single linked list
				Binding* pTempBinding = pNextBinding;             //Create temp pointer and init by this->pNextBinding
				while (pTempBinding->pNextBinding)                //while pTempBindng->pNextBinding is valid
				{
					pTempBinding = pTempBinding->pNextBinding;    //set pTempBinding to pTempBinding->pNextBinding
				}
				Binding* pThisBinding = new Binding;              //Allocate memory for current column
				bindingVariables(hStmthandle, i, pThisBinding);   //binding it
				pTempBinding->pNextBinding = pThisBinding;        //set finded last element to pThisBinding
				continue;    //go to the next iteration
			}
		}
		//==============================================================================================================================
		if (i == numCols)        //if it last column in dataset
		{
			if (pNextBinding)   //if pNextBinding is valid
			{
				//find last element
				Binding* pTempBinding = pNextBinding;             //Create temp pointer and init by this->pNextBinding
				while (pTempBinding->pNextBinding)                //while pTempBindng->pNextBinding is valid
				{
					pTempBinding = pTempBinding->pNextBinding;    //set pTempBinding to pTempBinding->pNextBinding
				}

				Binding* pThisBinding = new Binding;              //Allocate memory for current column
				bindingVariables(hStmthandle, i, pThisBinding);   //binding it
				pThisBinding->pNextBinding = nullptr;             //its a last column, therefore set pNextBinding of current binding to not valid value
				pTempBinding->pNextBinding = pThisBinding;		  //set finded last element to pThisBinding	 
			}
			else
			{
				Binding* pThisBinding = new Binding;              //Allocate memory for current column
				bindingVariables(hStmthandle, i, pThisBinding);   //binding it
				pThisBinding->pNextBinding = nullptr;             //its a last column, therefore set pNextBinding of current binding to not valid value
				pNextBinding = pThisBinding;
			
			}

		}
		//=================================================================================================================================
	}
	//============================================================================================================================================
}

TCHAR* Binding::GetDescription(void)
{
	return pDescription;
}

TCHAR* Binding::GetColumnName(void)
{
	return columnName;
}

Binding* Binding::GetNextBinding(void)
{
	return pNextBinding;
}

SQLINTEGER Binding::getIntegerData()
{
	return itegerData;
}

void Binding::FreeBinding(void)
{
	Binding* pTempBinding = this;
	while (pTempBinding)
	{
		delete[] pTempBinding->pDescription;
		pTempBinding->pDescription = nullptr;
		pTempBinding->pDescLen = 0;
		pTempBinding->StrLen_or_Ind = 0;
		pTempBinding = pTempBinding->pNextBinding;
	}
}

void Binding::bindingVariables(SQLHANDLE statementHandle, int index, Binding* pThisBinding)
{
	

	//Get the column label or title
	SQLRETURN retcode = SQLColAttribute(statementHandle,                    //statetment handle
		                      index,                              //number of row in dataset
							  SQL_DESC_LABEL,                     //column label or title
							  &pThisBinding->columnName,          //here save column label or title
							  sizeof(pThisBinding->columnName),   //size of pThisBinding->columnName in bytes
							  NULL,                               //is not required if SQL_DESC_LABEL
							  NULL);                              //is not required if SQL_DESC_LABEL
	SQLLEN ssType;
	retcode = SQLColAttribute(statementHandle,                    //statetment handle
		                      index,                              //number of row in dataset
							  SQL_DESC_CONCISE_TYPE,              //column label or title
		                      NULL,                               //here save column label or title
		                      0,                                  //size of pThisBinding->columnName in bytes
		                      NULL,                               //is not required if SQL_DESC_LABEL
		                      &ssType);                           //is not required if SQL_DESC_LABEL

	//Binding 
	if ((ssType == SQL_INTEGER) || (ssType == SQL_TINYINT) || (ssType == SQL_SMALLINT))
	{
		pThisBinding->pDescription = nullptr;
		retcode = SQLBindCol(statementHandle,                   //statetment handle
			index,                             //number of row in dataset
			SQL_C_SLONG,                       //type from convert data
			&pThisBinding->itegerData,                      //here save data from dataset
			sizeof(itegerData),                 //size pThisBinding->pDescription in bytes
			&pThisBinding->StrLen_or_Ind);     //here save actual size in characters when called SQLFetch() function
	}
	else
	{
		pThisBinding->itegerData = 0;
		//Get maximum number of characters required to display data from the column
		retcode = SQLColAttribute(statementHandle,                //statetment handle
			index,                          //number of row in dataset
			SQL_DESC_DISPLAY_SIZE,          //maximum number of characters required to display data
			NULL,                           //is not required if SQL_DESC_DISPLAY_SIZE
			NULL,                           //is not required if SQL_DESC_DISPLAY_SIZE
			NULL,                           //is not required if SQL_DESC_DISPLAY_SIZE
			&pThisBinding->pDescLen);       //here save lenght in characters

		size_t len = (pThisBinding->pDescLen + 1);          //Compute lenght in characters for save data
		pThisBinding->pDescription = new TCHAR[len];        //Allocate memory for saving data

		retcode = SQLBindCol(statementHandle,                   //statetment handle
			index,                             //number of row in dataset
			SQL_C_TCHAR,                       //type from convert data
			pThisBinding->pDescription,        //here save data from dataset
			len*sizeof(TCHAR),                 //size pThisBinding->pDescription in bytes
			&pThisBinding->StrLen_or_Ind);     //here save actual size in characters when called SQLFetch() function
	}
}