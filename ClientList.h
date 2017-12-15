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
	SQLSMALLINT numCols;
	void GetDataFromDatabase();
	int width;
	int height;
	HWND listWnd;
	std::vector<SQLTCHAR*>* selectedItem;

	void FreeVector();
public:
	std::vector<SQLTCHAR*>* getSelectedClient(void);
	void InitListView();
	void DestroyListView();
	void hideListView();
	void showListView(void);
	ClientList();
	~ClientList();
};

