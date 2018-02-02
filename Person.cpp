#include "Person.h"


Person::Person(CSqlFramework* sqlConnection)
{
	m_sqlConnection = sqlConnection;
}


Person::~Person()
{
}

void Person::getPhoneNumbersFromDatabase(SQLTCHAR* sqlCommand)
{
	int parameterArray[] = { m_personID };

	SQLHANDLE statementHandle = m_sqlConnection->ExecutePrepearedQuery(sqlCommand, parameterArray);  //send query with parameter and parameter array to database
	Binding* pBinding = m_sqlConnection->GetBinding();                                               //get bindig with data after execute query

	//Fetching result to pBinding
	if (m_phoneNumbers)
	{
		deleteAllPhoneNumbers();
		delete m_phoneNumbers;
		m_phoneNumbers = nullptr;
	}
	m_phoneNumbers = new std::vector<SQLTCHAR*>;
	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		Binding* tempBinding = pBinding;
		while (tempBinding)
		{
			size_t phoneLen = _tcslen(tempBinding->GetDescription()) + 1;
			SQLTCHAR* phoneNumber = new SQLTCHAR[phoneLen];
			memset(phoneNumber, 0, phoneLen*sizeof(SQLTCHAR));                           //fill pointer by /0
			_tcscat_s(phoneNumber, phoneLen, tempBinding->GetDescription());             //copy data from binding to imageLocation
			m_phoneNumbers->push_back(phoneNumber);
			tempBinding = tempBinding->GetNextBinding();
		}
	}
	m_sqlConnection->FreeBinding(statementHandle);  //free all resource after working
	if (m_phoneNumbers->empty())
	{
		delete m_phoneNumbers;
		m_phoneNumbers = nullptr;
	}
}

void Person::deleteAllPhoneNumbers()
{
	auto iter = m_phoneNumbers->begin();
	for (iter; iter < m_phoneNumbers->end(); iter++)
	{
		delete [] *iter;
		*iter = nullptr;
	}
}


int Person::getPersonId()
{
	return m_personID;
}


SQLTCHAR* Person::getLastname() const
{
	return m_lastname;
}

SQLTCHAR* Person::getFirstname() const
{
	return m_firstname;
}

SQLTCHAR* Person::getPatronymic() const
{
	return m_patronymicname;
}

SQLTCHAR* Person::getBirthDay() const
{
	return m_birthDay;
}


std::vector<SQLTCHAR*>* Person::getPhoneNumbers() const
{
	return m_phoneNumbers;
}

TCHAR* Person::getImageLocation() const
{
	return m_imageLocation;
}
