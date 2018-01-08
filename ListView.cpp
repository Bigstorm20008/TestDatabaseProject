#include "ListView.h"


ListView::ListView(HWND parent, UINT imageIdentifier)
{
	listParent = parent;
	//Create and fill struct for initialize ListView control
	//INITCOMMONCONTROLSEX icex;
	//icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	//icex.dwICC = ICC_LISTVIEW_CLASSES;
	//Registered it and load all needed components from ComCtl32.Lib
	//InitCommonControlsEx(&icex);
	InitCommonControls();

	//Get client area of parent window and save it in RECT structure
	RECT rc;
	GetClientRect(parent, &rc);
	//Get window rect of image window and save it in RECT structure
	HWND imageWnd = GetDlgItem(parent, imageIdentifier);
	RECT imgRc;
	GetWindowRect(imageWnd, &imgRc);
	//Save coordinates x,y of top right coner in POINT structure
	POINT tmp;
	tmp.x = imgRc.right;
	tmp.y = imgRc.top;
	//Get coordinates of top right coner image window in client area of main window
	ScreenToClient(parent, &tmp);
	//Compute coordinates for placing listview control and initialize width and height of listview
	int xPos = tmp.x + offsetBetweenWindow;   //step break from the brink of image window by 5 
	int yPos = tmp.y;       //y poasition of listview control = y position of image window
	int width = listViewWidth;  //width of listview(listViewWidth defined in Constants.h)
	int height = rc.bottom - rc.top - 2*offsetBetweenWindow;  //height of listview = height of main window - height of control panel(55)


	//Create control ListView
	listWnd = CreateWindow(WC_LISTVIEW,
		                   NULL,
						   WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL,
		                   xPos, yPos,
		                   width, height,
		                   parent,
						   (HMENU)ID_LISTVIEW_WND,   //defined in Constants.h
		                   reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                   NULL);
	//Extended style for ListView
	ListView_SetExtendedListViewStyleEx(listWnd, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_DOUBLEBUFFER);
	//Fill listview from database
	//GetDataFromDatabase(sqlCommandForGetData);
	//ShowWindow(listWnd, SW_NORMAL);
	SendMessage(listWnd, CCM_SETVERSION, 6, 0);
}


ListView::~ListView()
{
	if (selectedClient)
	{
		delete selectedClient;
		selectedClient = nullptr;
	}
}


void ListView::deleteAllColumn()
{
	for (int i = numCols-1; i>=0; i--)
	{
		ListView_DeleteColumn(listWnd, i);
		//SendMessage(listWnd, LVM_DELETECOLUMN, i, 0);
	}
}

void ListView::DestroyListView(UINT listViewIdentifier)
{
	extern LPTSTR szClassName;      //window class of main window(init in main.cpp)             
	extern LPTSTR szWindowName;     //title of main window(init in main.cpp)
	HWND parent = FindWindow(szClassName, szWindowName);    //Get handler to main application window
	HWND list = GetDlgItem(parent,listViewIdentifier);
	DestroyWindow(list);  //destroy listview

}


void ListView::GetDataFromDatabase(SQLTCHAR* sqlCommandForGetData)
{
	
	ListView_DeleteAllItems(listWnd);
	deleteAllColumn();
	extern CSqlFramework* sqlODBC;   //allocating in main.cpp for working with database  
	//Send query to database  and save statement handle in hsTmt  
	SQLHANDLE hsTmt = sqlODBC->SendQueryToDatabase(sqlCommandForGetData);
	//get count of columns in dataset
	numCols = 0;
	SQLNumResultCols(hsTmt, &numCols);
	//Get pointer to binded data
	Binding* pBinding = sqlODBC->GetBinding();
	//create and fill struct for manage columns and data in columns
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH ;  //column contains text and defined width of column
	lvc.cx = listViewWidth / numCols;      //width of column = width of listview / count of columns
	lvc.cchTextMax = 30;	             //maximum characters in columnname
	//get columname from database and init listview columns
	int i = 0; //counter for columns(increase after add column)
	Binding* tempBinding = pBinding; //tempBinding for get columnname
	while (tempBinding)   //while tempBinding is valid
	{
		lvc.pszText = tempBinding->GetColumnName();   //save column name to lvc.pszText
		ListView_InsertColumn(this->listWnd, i++, &lvc);  //insert column in listview and increase counter of column
		tempBinding = tempBinding->GetNextBinding();  //set pointer to next element
	}
	//Now we get the values ​​for the columns
	//int index = ListView_GetItemCount(this->listWnd);        //this macros return index of last free row in listview control 

	//Create a structure for working with the contents of the columns and fill it
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = 30;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	lvi.pszText = TEXT("");

	//Fetching result to listview
	while (SQLFetch(hsTmt) != SQL_NO_DATA)
	{
		ListView_InsertItem(this->listWnd, &lvi);  //insert row
		Binding* tempBinding = pBinding;           //temporary pointer to pBinding
		while (tempBinding)    //while tempBnding is valid
		{
			lvi.pszText = tempBinding->GetDescription();   //save description to structure
			ListView_SetItemText(this->listWnd, lvi.iItem, lvi.iSubItem, lvi.pszText);  //set subitem in this item
			++lvi.iSubItem;  //increase subitem
			tempBinding = tempBinding->GetNextBinding(); //set pointer to next element
		}
        //after filling the item in while 
		++lvi.iItem; //increase item
		lvi.iSubItem = 0; //set subitem 0
	}

	//after end working with dataset free all resources
	sqlODBC->FreeBinding(hsTmt);
	if (!IsWindowVisible(listWnd))
	{
		ShowWindow(listWnd, SW_NORMAL);
	}
}

void ListView::setFocusOnItem()
{
	//int numSelection = ListView_GetNextItem(this->listWnd, -1, LVNI_ALL | LVNI_SELECTED);   //get index of selection item
	//ListView_SetItemState(listWnd, numSelection, LVNI_SELECTED | LVNI_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	//ListView_SetSelectionMark(listWnd, numSelection);
	//ListView_EnsureVisible(listWnd, numSelection, false);
	SetFocus(listWnd);
}

void ListView::deleteSelectedPerson()
{
	int numSelection = ListView_GetNextItem(this->listWnd, -1, LVNI_ALL | LVNI_SELECTED);   //get index of selection item
	ListView_DeleteItem(listWnd, numSelection);
}
Client* ListView::getSelectedClient(void)
{
	
	int numSelection = ListView_GetNextItem(this->listWnd, -1, LVNI_ALL | LVNI_SELECTED);   //get index of selection item
	if (numSelection < 0) //if no selection item
	{
		
		return nullptr;  //return no valid pointer
	}
	else  //if item selected
	{
		if (selectedClient)
		{
			delete selectedClient;
			selectedClient = nullptr;
		}
		selectedClient = new Client;
		size_t maxTextLenght = 30;
		TCHAR strInList[30];  //for saving data from listview
		//Allocating pointer to structure for working with the contents of the columns and fill it
		LVITEM lvi;      
		lvi.mask = LVIF_TEXT;
		lvi.cchTextMax = maxTextLenght;
		lvi.iItem = numSelection;   //number of selected row
		lvi.iSubItem = 0;           //number of column
		lvi.pszText = strInList;    //here save text from subitem in selected row
		for (lvi.iSubItem; lvi.iSubItem < this->numCols; lvi.iSubItem++)
		{
			size_t len = _tcslen(getColumnName(lvi.iSubItem));
			TCHAR* currentColumnName = new TCHAR[len+1];
			memset(currentColumnName, 0, (len + 1)*sizeof(TCHAR));
			_tcscat_s(currentColumnName, len+1, getColumnName(lvi.iSubItem));
			SendMessage(this->listWnd, LVM_GETITEMTEXT, lvi.iItem, (LPARAM)&lvi);     //get text from subitem
			selectedClient->saveDataFromList(currentColumnName, lvi.pszText);
			delete[]currentColumnName;
			currentColumnName = nullptr;
		}
		//after working delete pointer and set value to not valid
	}
	return selectedClient;      //return pointer to selected client
}

/*void ClientList::hideListView()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND parent = FindWindow(szClassName, szWindowName);
	HWND listWnd = GetDlgItem(parent, ID_LIST_FOR_CLIENTVIEW);
	ShowWindow(listWnd, SW_HIDE);
}

void ClientList::showListView(void)
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND parent = FindWindow(szClassName, szWindowName);
	HWND listWnd = GetDlgItem(parent, ID_LIST_FOR_CLIENTVIEW);
	ShowWindow(listWnd, SW_NORMAL);
}*/

TCHAR* ListView::getColumnName(int subItem)
{	
	const size_t columnTextLenght = 30;
	TCHAR szText[columnTextLenght];
	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_TEXT;                //column contains text and defined width of column	    
	lvcolumn.cchTextMax = columnTextLenght;
	lvcolumn.pszText = szText;
	//maximum characters in columnname
	ListView_GetColumn(listWnd, subItem, &lvcolumn);
	return lvcolumn.pszText;
}