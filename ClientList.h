#pragma once

#include <Windows.h>
#include <commctrl.h>
#include "Constants.h"
#include "SqlFramework.h"
#include <vector>

#pragma comment(lib, "ComCtl32.Lib")


//This class create ListView for ClientView and show main information about all client in database
class ClientList
{
private:
	SQLSMALLINT numCols;                    //count of columns in dataset and listview
	void GetDataFromDatabase();             //load to listview data from database
	int width;                              //width of listview
	int height;                             //height of listview
	HWND listWnd;                           //handle to listview
	std::vector<SQLTCHAR*>* selectedItem;   //pointer to vector of pointer to SQLTCHAR. Here save data from seected item in listview     

	void FreeVector();                      //free vector before and after using
public:
	std::vector<SQLTCHAR*>* getSelectedClient(void);   //get data from selected item in listview 
	void InitListView();                               //initialize listview window
	void DestroyListView();                            //destroy listview window
	void hideListView();                               //hide listview window
	void showListView(void);                           //show listview window
	ClientList();
	~ClientList();
};

