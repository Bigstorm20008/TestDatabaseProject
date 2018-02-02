#pragma once

#include "Person.h"

class Employee 
	: public Person
{
public:
	Employee(CSqlFramework* sqlConnection);
	~Employee();

	virtual void getInfoForCurrentPerson(SQLTCHAR* currentDay);
	virtual void saveDataFromList(TCHAR* columnName, TCHAR* dataFromList);
	virtual void FreeAllField();
private:
	
	virtual void fillAllPersonField(Binding*pBinding);
};

