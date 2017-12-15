#include "ClientList.h"


ClientList::ClientList()
{
	//Create and fill struct for initialize ListView control
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	//Registered it and load all needed components from ComCtl32.Lib
	InitCommonControlsEx(&icex);
	//Получим клиентскую область родительского окна и сохраним ее в структуре RECT
	extern LPTSTR szClassName;               
	extern LPTSTR szWindowName;
	HWND parent = FindWindow(szClassName, szWindowName);
	RECT rc;
	GetClientRect(parent, &rc);
	HWND imgWnd = GetDlgItem(parent, ID_IMAGE_WND);
	RECT imgRc;
	GetWindowRect(imgWnd, &imgRc);
	POINT tmp;
	tmp.x = imgRc.right;
	tmp.y = imgRc.top;
	ScreenToClient(parent, &tmp);
	//Вычислим координаты для расположения  элемента ListView и установим длину и ширину
	int xPos = tmp.x + 5;
	int yPos = tmp.y;
	width = listViewWidth;
	height = rc.bottom - rc.top - 55;

	
	//Создадим элемент ListView
	listWnd = CreateWindow(WC_LISTVIEW,
		L"",
		WS_CHILD | LVS_REPORT | WS_VISIBLE | LVS_SHOWSELALWAYS,
		xPos, yPos,
		width, height,
		parent,
		(HMENU)ID_LIST_FOR_CLIENTVIEW,
		reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		NULL);
	//Укажем дополнительные стили для созданного ListView
	ListView_SetExtendedListViewStyleEx(listWnd, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_DOUBLEBUFFER );

	GetDataFromDatabase();
}


ClientList::~ClientList()
{
	if (selectedItem)
	{
		FreeVector();
		delete selectedItem;
		selectedItem = nullptr;
	}
}

void ClientList::DestroyListView()
{
	if (selectedItem)
	{
		FreeVector();
		delete selectedItem;
		selectedItem = nullptr;
	}
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND parent = FindWindow(szClassName, szWindowName);
	HWND listWnd = GetDlgItem(parent, ID_LIST_FOR_CLIENTVIEW);
	DestroyWindow(listWnd);
}


void ClientList::GetDataFromDatabase()
{
	extern CSqlFramework* sqlODBC;   //Переменная указаель на класс работы с БД(объявлена в main.cpp)   
	SQLHANDLE hsTmt = sqlODBC->SendQueryToDatabase(TEXT("SELECT Nickname,Фамилия,Имя,Отчество FROM dbo.Clients"));    //Выполним запрос и получим дескриптор
	//Получим количество столбцов в источнике данных и сохраним его в numCols
	numCols = 0;
	SQLNumResultCols(hsTmt, &numCols);
	selectedItem = new std::vector<SQLTCHAR*>;
	selectedItem->reserve(numCols);
	//Получим указатель на класс, в который сохраняются результаты запроса
	Binding* pBinding = sqlODBC->GetBinding();
	//Создадим структуру для упраления столбцами и содержимым и частично заполним ее(остальные поля будем использовать в процессе выполнения программы)
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH ;
	lvc.cx = this->width / numCols;
	lvc.cchTextMax = 30;	
	//Получим  имена столбцов и назовем соответственно столбцы ListView
	int i = 0; //Счетчик для столбцов(увеличиваем после добавления столбца)
	Binding* tempBinding = pBinding;
	while (i<numCols)
	{
		lvc.pszText = tempBinding->GetColumnName();
		ListView_InsertColumn(this->listWnd, i++, &lvc);
		tempBinding = tempBinding->GetNextBinding();
	}
	//Теперь получим значения для столбцов
	int index = ListView_GetItemCount(this->listWnd);        //получим текущее кол-во срок в ListView

	//Создадим структуру для работы с содержимым столбцов и  заполним ее
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = 30;
	lvi.iItem = index;
	lvi.iSubItem = 0;
	lvi.pszText = TEXT("re-re");


	while (SQLFetch(hsTmt) != SQL_NO_DATA)
	{
		ListView_InsertItem(this->listWnd, &lvi);
		Binding* tempBinding = pBinding;
		while (tempBinding)
		{
			lvi.pszText = tempBinding->GetDescription();
			ListView_SetItemText(this->listWnd, lvi.iItem, lvi.iSubItem, lvi.pszText);
			lvi.iSubItem++;
			tempBinding = tempBinding->GetNextBinding();
		}
		lvi.iItem++;
		lvi.iSubItem = 0;
	}
	sqlODBC->FreeBinding(hsTmt);

}


std::vector<SQLTCHAR*>* ClientList::getSelectedClient(void)
{
	FreeVector();
	int numSelection = ListView_GetNextItem(this->listWnd, -1, LVNI_ALL | LVNI_SELECTED);
	if (numSelection < 0)
	{
		return selectedItem;
	}
	else
	{
		SQLTCHAR str[MAX_PATH];
		memset(str, 0, sizeof(str));
		LVITEM* lvi = new LVITEM;
		lvi->mask = LVIF_TEXT;
		lvi->cchTextMax = 30;
		lvi->iItem = numSelection;
		lvi->iSubItem = 0;
		lvi->pszText = str;
		for (lvi->iSubItem; lvi->iSubItem < this->numCols; lvi->iSubItem++)
		{
			memset(str, 0, sizeof(str));
			SendMessage(this->listWnd, LVM_GETITEMTEXT, lvi->iItem, (LPARAM)lvi);
			size_t len = _tcslen(lvi->pszText);
			SQLTCHAR* str = new SQLTCHAR[len + 1];
			memset(str, 0, (len + 1)*sizeof(SQLTCHAR));
			_tcscpy_s(str, len + 1, (SQLTCHAR*)lvi->pszText);
			selectedItem->push_back(str);
		}
		delete lvi;
		lvi = nullptr;
	}
	return selectedItem;
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