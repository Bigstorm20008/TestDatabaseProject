
#pragma once            //exclude repeat inclusion

//include librarys
#include <Windows.h>   

//include classes

#include "SqlFramework.h"
#include "AutorisationClass.h"


#include "Constants.h"    //global variables for this project(include identifiers for windows and some constants)

//This class create autentification window in main application window and open connection to database(using entered login and pass and datasource created in ODBC manegment) 
//User enter login and password 
//After that using CSqlFramework class and check login and pass in MS SQL Server
//if log and pass is valid - open connection and give control to AutorizationClass
class AutentificationClass
{
private:
	TCHAR* username;    //here save username
	TCHAR* password;    //here save password

public:
	//constructor of class receiving handle of parent window and identifier for create and control child autentification window
	AutentificationClass(HWND hWnd, UINT identifier);   
	//Destructor
	~AutentificationClass();
};


//Processing message from autentification window
LRESULT CALLBACK AutentificationProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);