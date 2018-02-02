#include "Employee.h"


Employee::Employee(CSqlFramework* sqlConnection) 
	: Person(sqlConnection)
{
	//set all pointers to not valid value
	m_lastname = nullptr;
	m_firstname = nullptr;
	m_patronymicname = nullptr;
	m_imageLocation = nullptr;
	m_birthDay = nullptr;
	m_phoneNumbers = nullptr;
}


Employee::~Employee()
{
	FreeAllField();
}

void Employee::FreeAllField()
{
	if (m_lastname)
	{
		delete[]m_lastname;
		m_lastname = nullptr;
	}
	if (m_firstname)
	{
		delete[]m_firstname;
		m_firstname = nullptr;
	}
	if (m_patronymicname)
	{
		delete[]m_patronymicname;
		m_patronymicname = nullptr;
	}
	if (m_imageLocation)
	{
		delete[]m_imageLocation;
		m_imageLocation = nullptr;
	}
	if (m_birthDay)
	{
		delete[]m_birthDay;
		m_birthDay = nullptr;
	}
	if (m_phoneNumbers)
	{
		deleteAllPhoneNumbers();
		delete m_phoneNumbers;
		m_phoneNumbers = nullptr;
	}
}

void Employee::getInfoForCurrentPerson(SQLTCHAR* currentDay)
{
	//init parameter array for query with parametr((index of parameter+1) in parameterArray = number of parameter in query)
	SQLTCHAR* parametrArray[] = { m_lastname, m_firstname, m_patronymicname };
	//query with parameter, where parameter is ?
	SQLTCHAR* sqlCommand = TEXT("SELECT [EmployeeID] ,[ImageLocation],[Posts].Должность FROM [dbo].[Employees] JOIN [Posts] on Employees.PostID = Posts.PostID WHERE (Lastname = ? AND Firstname = ? AND Patronymicname = ?)");
	//allocating in main.cpp for working with database
	SQLHANDLE statementHandle = m_sqlConnection->ExecutePrepearedQuery(sqlCommand, parametrArray);  //send query with parameter and parameter array to database
	Binding* pBinding = m_sqlConnection->GetBinding();                                              //get bindig with data after execute query

	//Fetching result to pBinding
	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		fillAllPersonField(pBinding);   //fill all field of Client class
	}
	m_sqlConnection->FreeBinding(statementHandle);  //free all resource after working

	//getPhoneNumbersFromDatabase(TEXT("SELECT PhoneNumber FROM ClientsPhoneNumbers WHERE ClientID = ?"));
	//getCustomerFinancialStatistics(currentDay);
}

void saveDataFromList(TCHAR* columnName, TCHAR* dataFromList)
{

}

void Employee::fillAllPersonField(Binding*pBinding)
{
	Binding* tempBinding = pBinding;
	while (tempBinding)
	{
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("ImageLocation")) == 0)   
		{
			//save description to imageLocation 
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;                  
			m_imageLocation = new SQLTCHAR[len];                                        
			memset(m_imageLocation, 0, len*sizeof(SQLTCHAR));                           
			_tcscat_s(m_imageLocation, len, tempBinding->GetDescription());             
			tempBinding = tempBinding->GetNextBinding();                              
			continue;
		}
		
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("EmployeeID")) == 0)
		{

			m_personID = tempBinding->getIntegerData();
			tempBinding = tempBinding->GetNextBinding();                              
			continue;
		}
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("Дата рождения")) == 0)   
		{
			//save description to birthday
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;                  
			if (len == 0)
			{
				m_birthDay = TEXT("");
				tempBinding = tempBinding->GetNextBinding();                             
				continue;
			}
			else
			{
				m_birthDay = new SQLTCHAR[len];                                        
				memset(m_birthDay, 0, len*sizeof(SQLTCHAR));                           
				_tcscat_s(m_birthDay, len, tempBinding->GetDescription());             
				tempBinding = tempBinding->GetNextBinding();                              
				continue;
			}
		}
		tempBinding = tempBinding->GetNextBinding();  
	}
}

void Employee::saveDataFromList(TCHAR* columnName, TCHAR* dataFromList)
{
	
	if ((_tcscmp(columnName, TEXT("Фамилия")) == 0) || (_tcscmp(columnName, TEXT("Lastname")) == 0))
	{
		size_t len = _tcslen(dataFromList);
		m_lastname = new TCHAR[len + 1];
		memset(m_lastname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(m_lastname, len + 1, dataFromList);
	}

	if ((_tcscmp(columnName, TEXT("Имя")) == 0) || (_tcscmp(columnName, TEXT("Firstname")) == 0))
	{
		size_t len = _tcslen(dataFromList);
		m_firstname = new TCHAR[len + 1];
		memset(m_firstname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(m_firstname, len + 1, dataFromList);
	}

	if ((_tcscmp(columnName, TEXT("Отчество")) == 0) || (_tcscmp(columnName, TEXT("Patronymicname")) == 0))
	{
		size_t len = _tcslen(dataFromList);
		m_patronymicname = new TCHAR[len + 1];
		memset(m_patronymicname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(m_patronymicname, len + 1, dataFromList);
	}
	else
	{
		return;
	}
}