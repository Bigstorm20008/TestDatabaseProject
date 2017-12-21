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

	void FillAllClientField(Binding*pBinding);    //function fill data about current client
	void LoadMainInfo();                          //load main info about client to Client View
	SQLTCHAR* GetDataFromEdit(HWND textFrom);
public:

	void FreeAllField();    //clear all field of Client class

	//Function send query with patameter to database and set field of Client class
	//After that call LoadMainInfo() function for update info about client
	void GetInfoForCurrentClient(std::vector<SQLTCHAR*>* selectedClient); 
	void addNewClientToDatabase(HWND infoFrom);
	Client();  //constructor
	~Client(); //destructor
};

