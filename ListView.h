#pragma once

#include <Windows.h>
#include <commctrl.h>
#include "Constants.h"
#include "SqlFramework.h"
#include "Client.h"


#pragma comment(lib, "ComCtl32.Lib")


//This class create ListView for ClientView and show main information about all client in database
class ListView
{
private:
	HWND listParent;
	SQLSMALLINT numCols;                                                  //count of columns in dataset and listview
	
	HWND listWnd;                                                         //handle to listview
	Client* selectedClient;
	TCHAR* getColumnName(int subItem);
	void deleteAllColumn();
public:	
	void GetDataFromDatabase(SQLTCHAR* sqlCommandForGetData);             //load to listview data from database
	Client* getSelectedClient(void);   //get data from selected item in listview 
	void InitListView();                                 //initialize listview window
	void DestroyListView(UINT listViewIdentifier);         //destroy listview window
	void setFocusOnItem();
	//void hideListView();                                 //hide listview window
	//void showListView(void);                             //show listview window
	ListView(HWND parent, UINT imageIdentifier);
	~ListView();
};

