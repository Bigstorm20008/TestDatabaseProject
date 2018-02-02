#pragma once

#include "Person.h"

class Client : public Person
{
private:
	SQLTCHAR* m_nickname;               
	SQLTCHAR* m_status;
	TCHAR* m_lastVisit;
	BOOL m_clientState;
	long long m_cashInSum;
	long long m_cashOutSum;
	long long m_result;
	long long m_drop;

	virtual void fillAllPersonField(Binding*pBinding);
	
	void getCustomerFinancialStatistics(SQLTCHAR* currentDay);
	
public:
	BOOL getClientState() const;
	SQLTCHAR* getNickname() const;
	SQLTCHAR* getLastname() const;
	SQLTCHAR* getFirstname() const;
	SQLTCHAR* getPatronymic() const;
	SQLTCHAR* getBirthDay() const;
	SQLTCHAR* getStatus() const;
	TCHAR* getLastVisit() const;
	int getDrop() const;
	int getResult() const;
	std::vector<SQLTCHAR*>* getPhoneNumbers() const;

	void setClientState(BOOL clientState);
	void setLastVisit(TCHAR* date);
	void changeClientState(UINT exitOrEntranceBtnIdentifier);
	virtual void FreeAllField();   
	
	virtual void getInfoForCurrentPerson(SQLTCHAR* currentDay);
	void saveDataFromList(TCHAR* columnName, TCHAR* dataFromList);
	Client(CSqlFramework* sqlConnection);  //constructor
	virtual ~Client(); //destructor
};

