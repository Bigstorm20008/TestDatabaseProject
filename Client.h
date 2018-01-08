#pragma once
#include <Windowsx.h>
#include <tchar.h>
#include "SqlFramework.h"
#include <vector>
#include "Constants.h"


class Client
{
private:
	int clientID;                     //here save clientID from database
	SQLTCHAR* nickname;               //client nickname
	SQLTCHAR* lastname;               //client lastname
	SQLTCHAR* firstname;              //client firstname
	SQLTCHAR* patronymicname;         //client patronymicname
	SQLTCHAR* imageLocation;          //image location on HD for current client
	SQLTCHAR* birthDay;               
	SQLTCHAR* status;
	BOOL clientState;
	int cashInSum;
	int cashOutSum;
	int result;
	int drop;
	std::vector<SQLTCHAR*>* phoneNumbers;

	void deleteAllPhoneNumbers();
	void FillAllClientField(Binding*pBinding);    //function fill data about current client
	SQLTCHAR* GetDataFromEdit(HWND textFrom);
	void getPhoneNumbersFromDatabase();
	void getCustomerFinancialStatistics();
	Client& Client::operator=(const Client& client);
public:
	SQLTCHAR* getNickname() const;
	SQLTCHAR* getLastname() const;
	SQLTCHAR* getFirstname() const;
	SQLTCHAR* getPatronymic() const;
	SQLTCHAR* getBirthDay() const;
	SQLTCHAR* getStatus() const;
	int getDrop() const;
	int getResult() const;
	std::vector<SQLTCHAR*>* getPhoneNumbers() const;
	void changeClientState(UINT exitOrEntranceBtnIdentifier);
	void FreeAllField();    //clear all field of Client class
	SQLTCHAR* getImageLocation();
	//Function send query with patameter to database and set field of Client class
	//After that call LoadMainInfo() function for update info about client
	void GetInfoForCurrentClient();
	void saveDataFromList(TCHAR* columnName, TCHAR* dataFromList);
	BOOL addNewClientToDatabase(HWND infoFrom);
	Client();  //constructor
	~Client(); //destructor
};

