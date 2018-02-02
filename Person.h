#pragma once

#include <Windows.h>
#include <vector>
#include "SqlFramework.h"

class Person
{
public:
	Person(CSqlFramework* sqlConnection);
	virtual ~Person() = 0;

	virtual void getInfoForCurrentPerson(SQLTCHAR* currentDay) = 0;
	virtual void saveDataFromList(TCHAR* columnName, TCHAR* dataFromList) = 0;
	virtual void FreeAllField() = 0;
	int getPersonId();
	TCHAR* getLastname() const;
	TCHAR* getFirstname() const;
	TCHAR* getPatronymic() const;
	TCHAR* getBirthDay() const;
	TCHAR* getImageLocation() const;
	std::vector<TCHAR*>* getPhoneNumbers() const;
protected:
	CSqlFramework* m_sqlConnection;

	int m_personID;
	TCHAR* m_lastname;               
	TCHAR* m_firstname;              
	TCHAR* m_patronymicname;         
	TCHAR* m_imageLocation;          
	TCHAR* m_birthDay;

	std::vector<TCHAR*>* m_phoneNumbers;
	void deleteAllPhoneNumbers();
	void getPhoneNumbersFromDatabase(SQLTCHAR* sqlCommand);

	

	virtual void fillAllPersonField(Binding*pBinding) = 0;
	
private:
	
};

