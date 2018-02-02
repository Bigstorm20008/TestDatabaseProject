#include "ListView.h"


ListView::ListView(HWND parent, int xPos, int yPos, int listWidth, int listHeight, CSqlFramework* sqlConnection)
{
	m_listParent = parent;
	m_sqlConnection = sqlConnection;
	InitCommonControls();

	//Create control ListView
	m_listWnd = CreateWindow(WC_LISTVIEW,
		                     NULL,
						     WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL,
		                     xPos, yPos,
							 listWidth, listHeight,
		                     parent,
						     (HMENU)NULL,   //defined in Constants.h
		                     reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                     NULL);
	//Extended style for ListView
	ListView_SetExtendedListViewStyleEx(m_listWnd, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_DOUBLEBUFFER);
	//Fill listview from database
	//GetDataFromDatabase(sqlCommandForGetData);
	//ShowWindow(listWnd, SW_NORMAL);
	SendMessage(m_listWnd, CCM_SETVERSION, 6, 0);
}


ListView::~ListView()
{

}

HWND ListView::getHandleOfList() const
{
	return m_listWnd;
}
void ListView::deleteAllColumn()
{
	for (int i = m_numCols-1; i>=0; i--)
	{
		ListView_DeleteColumn(m_listWnd, i);
	}
}

void ListView::DestroyListView(UINT listViewIdentifier)
{
	DestroyWindow(m_listWnd);  //destroy listview

}


void ListView::GetDataFromDatabase(SQLTCHAR* sqlCommandForGetData)
{
	
	ListView_DeleteAllItems(m_listWnd);
	deleteAllColumn();
	//Send query to database  and save statement handle in hsTmt  
	SQLHANDLE hsTmt = m_sqlConnection->SendQueryToDatabase(sqlCommandForGetData);
	//get count of columns in dataset
	m_numCols = 0;
	SQLNumResultCols(hsTmt, &m_numCols);
	//Get pointer to binded data
	Binding* pBinding = m_sqlConnection->GetBinding();
	//create and fill struct for manage columns and data in columns
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH ;  //column contains text and defined width of column
	lvc.cx = listViewWidth / m_numCols;      //width of column = width of listview / count of columns
	lvc.cchTextMax = 30;	             //maximum characters in columnname
	//get columname from database and init listview columns
	int i = 0; //counter for columns(increase after add column)
	Binding* tempBinding = pBinding; //tempBinding for get columnname
	while (tempBinding)   //while tempBinding is valid
	{
		lvc.pszText = tempBinding->GetColumnName();   //save column name to lvc.pszText
		ListView_InsertColumn(m_listWnd, i++, &lvc);  //insert column in listview and increase counter of column
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
		ListView_InsertItem(m_listWnd, &lvi);  //insert row
		Binding* tempBinding = pBinding;           //temporary pointer to pBinding
		while (tempBinding)    //while tempBnding is valid
		{
			lvi.pszText = tempBinding->GetDescription();   //save description to structure
			ListView_SetItemText(m_listWnd, lvi.iItem, lvi.iSubItem, lvi.pszText);  //set subitem in this item
			++lvi.iSubItem;  //increase subitem
			tempBinding = tempBinding->GetNextBinding(); //set pointer to next element
		}
        //after filling the item in while 
		++lvi.iItem; //increase item
		lvi.iSubItem = 0; //set subitem 0
	}

	//after end working with dataset free all resources
	m_sqlConnection->FreeBinding(hsTmt);
	if (!IsWindowVisible(m_listWnd))
	{
		ShowWindow(m_listWnd, SW_NORMAL);
	}
}

void ListView::setFocusOnItem()
{
	//int numSelection = ListView_GetNextItem(this->listWnd, -1, LVNI_ALL | LVNI_SELECTED);   //get index of selection item
	//ListView_SetItemState(listWnd, numSelection, LVNI_SELECTED | LVNI_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	//ListView_SetSelectionMark(listWnd, numSelection);
	//ListView_EnsureVisible(listWnd, numSelection, false);
	SetFocus(m_listWnd);
}

void ListView::deleteSelectedPerson()
{
	int numSelection = ListView_GetNextItem(m_listWnd, -1, LVNI_ALL | LVNI_SELECTED);   //get index of selection item
	ListView_DeleteItem(m_listWnd, numSelection);
}
BOOL ListView::getSelectedClient(Person& currentPerson)
{
	
	int numSelection = ListView_GetNextItem(m_listWnd, -1, LVNI_ALL | LVNI_SELECTED);   //get index of selection item
	if (numSelection < 0) //if no selection item
	{
		
		return FALSE;  //return no valid pointer
	}
	else  //if item selected
	{
		currentPerson.FreeAllField();
		size_t maxTextLenght = 30;
		TCHAR strInList[30];  //for saving data from listview
		//Allocating pointer to structure for working with the contents of the columns and fill it
		LVITEM lvi;      
		lvi.mask = LVIF_TEXT;
		lvi.cchTextMax = maxTextLenght;
		lvi.iItem = numSelection;   //number of selected row
		lvi.iSubItem = 0;           //number of column
		lvi.pszText = strInList;    //here save text from subitem in selected row
		for (lvi.iSubItem; lvi.iSubItem < m_numCols; lvi.iSubItem++)
		{
			size_t len = _tcslen(getColumnName(lvi.iSubItem));
			TCHAR* currentColumnName = new TCHAR[len+1];
			memset(currentColumnName, 0, (len + 1)*sizeof(TCHAR));
			_tcscpy_s(currentColumnName, len+1, getColumnName(lvi.iSubItem));
			SendMessage(m_listWnd, LVM_GETITEMTEXT, lvi.iItem, (LPARAM)&lvi);     //get text from subitem
			currentPerson.saveDataFromList(currentColumnName, lvi.pszText);
			delete[]currentColumnName;
			currentColumnName = nullptr;
		}
		
	}
	return TRUE;      
}

TCHAR* ListView::getColumnName(int subItem)
{	
	const size_t columnTextLenght = 30;
	TCHAR szText[columnTextLenght];
	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_TEXT;                //column contains text and defined width of column	    
	lvcolumn.cchTextMax = columnTextLenght;
	lvcolumn.pszText = szText;
	//maximum characters in columnname
	ListView_GetColumn(m_listWnd, subItem, &lvcolumn);
	return lvcolumn.pszText;
}