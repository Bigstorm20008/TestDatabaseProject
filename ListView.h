#pragma once

#include <Windows.h>
#include <commctrl.h>

#include "Constatnts.h"
#include "SqlFramework.h"
#include "Client.h"


#pragma comment(lib, "ComCtl32.Lib")


//This class create ListView for ClientView and show main information about all client in database
class ListView
{
private:
	HWND m_listParent;
	CSqlFramework* m_sqlConnection;
	SQLSMALLINT m_numCols;                                                  //count of columns in dataset and listview
	
	HWND m_listWnd;                                                         //handle to listview
	TCHAR* getColumnName(int subItem);
	void deleteAllColumn();
public:	
	void GetDataFromDatabase(SQLTCHAR* sqlCommandForGetData);   //load to listview data from database
	BOOL getSelectedClient(Person& currentPerson);                            
	void InitListView();                                        //initialize listview window
	void DestroyListView(UINT listViewIdentifier);              //destroy listview window
	void setFocusOnItem();
	void deleteSelectedPerson();
	HWND getHandleOfList() const;

	ListView(HWND parent, int xPos, int yPos, int listWidth, int listHeight, CSqlFramework* sqlConnection);
	~ListView();
};

