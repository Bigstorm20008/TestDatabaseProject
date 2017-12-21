#include "ClientList.h"


ClientList::ClientList()
{
	//Create and fill struct for initialize ListView control
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	//Registered it and load all needed components from ComCtl32.Lib
	InitCommonControlsEx(&icex);
	
	
	//Find main window app
	extern LPTSTR szClassName;      //window class of main window(init in main.cpp)             
	extern LPTSTR szWindowName;     //title of main window(init in main.cpp)
	HWND parent = FindWindow(szClassName, szWindowName);    //Get handler to main application window
	//Get client area of parent window and save it in RECT structure
	RECT rc;
	GetClientRect(parent, &rc);
	//Get handler of image window in client view
	HWND imgWnd = GetDlgItem(parent, ID_IMAGE_WND);
	//Get window rect of image window and save it in RECT structure
	RECT imgRc;
	GetWindowRect(imgWnd, &imgRc);
	//Save coordinates x,y of top right coner in POINT structure
	POINT tmp;
	tmp.x = imgRc.right;
	tmp.y = imgRc.top;
	//Get coordinates of top right coner image window in client area of main window
	ScreenToClient(parent, &tmp);
	//Compute coordinates for placing listview control and initialize width and height of listview
	int xPos = tmp.x + 5;   //step break from the brink of image window by 5 
	int yPos = tmp.y;       //y poasition of listview control = y position of image window
	width = listViewWidth;  //width of listview(listViewWidth defined in Constants.h)
	height = rc.bottom - rc.top - 55;  //height of listview = height of main window - height of control panel(55)

	
	//Create control ListView
	listWnd = CreateWindow(WC_LISTVIEW,
		                   NULL,
		                   WS_CHILD | LVS_REPORT | WS_VISIBLE | LVS_SHOWSELALWAYS,
		                   xPos, yPos,
		                   width, height,
		                   parent,
		                   (HMENU)ID_LIST_FOR_CLIENTVIEW,   //defined in Constants.h
		                   reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                   NULL);
	//Extended style for ListView
	ListView_SetExtendedListViewStyleEx(listWnd, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_DOUBLEBUFFER );
	//Fill listview from database
	GetDataFromDatabase();
}


ClientList::~ClientList()
{
	if (selectedItem)//if pointer to vector is valid
	{
		FreeVector();            //free vector
		delete selectedItem;     //delete pointer
		selectedItem = nullptr;  //set pointer to not valid value
	}
}

void ClientList::DestroyListView()
{
	if (selectedItem)//if pointer to vector is valid
	{
		FreeVector();             //free vector
		delete selectedItem;      //delete pointer
		selectedItem = nullptr;   //set pointer to not valid value
	}
	//find main app window
	extern LPTSTR szClassName;    //window class of main window(init in main.cpp)   
	extern LPTSTR szWindowName;   //title of main window(init in main.cpp)
	HWND parent = FindWindow(szClassName, szWindowName);        //Get handler to main application window
	HWND listWnd = GetDlgItem(parent, ID_LIST_FOR_CLIENTVIEW);  //Get handler to listview(ID_LIST_FOR_CLIENTVIEW defined in Constants.h)
	DestroyWindow(listWnd);  //destroy listview
}


void ClientList::GetDataFromDatabase()
{
	extern CSqlFramework* sqlODBC;   //allocating in main.cpp for working with database  
	//Send query to database for get Nickname,Lastname,Firstname,Patronymic all clients and save statement handle in hsTmt  
	SQLHANDLE hsTmt = sqlODBC->SendQueryToDatabase(TEXT("SELECT Nickname, Фамилия, Имя, Отчество FROM dbo.Clients"));    
	//get count of columns in dataset
	numCols = 0;
	SQLNumResultCols(hsTmt, &numCols);
	//init pointer to vector and reserve space in vector by numCols
	selectedItem = new std::vector<SQLTCHAR*>;
	selectedItem->reserve(numCols);
	//Get pointer to binded data
	Binding* pBinding = sqlODBC->GetBinding();
	//create and fill struct for manage columns and data in columns
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH ;  //column contains text and defined width of column
	lvc.cx = this->width / numCols;      //width of column = width of listview / count of columns
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
	int index = ListView_GetItemCount(this->listWnd);        //this macros return index of last free row in listview control 

	//Create a structure for working with the contents of the columns and fill it
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = 30;
	lvi.iItem = index;
	lvi.iSubItem = 0;
	lvi.pszText = TEXT("re-re");

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

}


std::vector<SQLTCHAR*>* ClientList::getSelectedClient(void)
{
	FreeVector();    //be on the safe side free vector
	int numSelection = ListView_GetNextItem(this->listWnd, -1, LVNI_ALL | LVNI_SELECTED);   //get index of selection item
	if (numSelection < 0) //if no selection item
	{
		return selectedItem;  //return empty vector
	}
	else  //if item selected
	{
		SQLTCHAR strInList[MAX_PATH];  //for saving data from listview

		//Allocating pointer to structure for working with the contents of the columns and fill it
		LVITEM* lvi = new LVITEM;      
		lvi->mask = LVIF_TEXT;
		lvi->cchTextMax = 30;
		lvi->iItem = numSelection;   //number of selected row
		lvi->iSubItem = 0;           //number of column
		lvi->pszText = strInList;    //here save text from subitem in selected row
		for (lvi->iSubItem; lvi->iSubItem < this->numCols; lvi->iSubItem++)
		{
			SendMessage(this->listWnd, LVM_GETITEMTEXT, lvi->iItem, (LPARAM)lvi);     //get text from subitem
			size_t len = _tcslen(lvi->pszText);   //compute lenght of this text
			SQLTCHAR* str = new SQLTCHAR[len + 1]; //alocate memory for save it
			memset(str, 0, (len + 1)*sizeof(SQLTCHAR)); //fill memory by /0
			_tcscpy_s(str, len + 1, (SQLTCHAR*)lvi->pszText);  //copy text in alocated memory
			selectedItem->push_back(str);  //save pointer in vector
		}
		//after working delete pointer and set value to not valid
		delete lvi;
		lvi = nullptr;
	}
	return selectedItem;      //return pointer to vector
}


void ClientList::FreeVector()
{
	if (selectedItem)
	{
		auto it = selectedItem->begin();
		while (it != selectedItem->end())
		{
			delete *(it++);
		}
		selectedItem->clear();
	}
}

void ClientList::hideListView()
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
}