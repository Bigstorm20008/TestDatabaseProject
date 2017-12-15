#include "ClientView.h"


ClientView::ClientView()
{
	photoForCurrentClient = nullptr;
	allClient = nullptr;
	currentClient = nullptr;
	buttons = nullptr;
	auxiliaryWindows = nullptr;
}


ClientView::~ClientView()
{
	if (currentClient)
	{
		delete currentClient;
		currentClient = nullptr;
	}
	if (photoForCurrentClient)
	{
		delete photoForCurrentClient;
		photoForCurrentClient = nullptr;
	}
	if (allClient)
	{
		delete allClient;
		allClient = nullptr;
	}
	if (buttons)
	{
		delete buttons;
		buttons = nullptr;
	}
}


void ClientView::CreateClientViewWindows()
{
	photoForCurrentClient = new ClientImageWnd;
	allClient = new ClientList;
	buttons = new ClientViewButtons;
	buttons->createButtons();
	auxiliaryWindows = new AuxiliaryWindows;
}

void ClientView::DestroyAllClientViewWindow()
{
	if (currentClient)
	{
		delete currentClient;
		currentClient = nullptr;
	}
	if (photoForCurrentClient)
	{
		photoForCurrentClient->DestroyImageWindow();
		delete photoForCurrentClient;
		photoForCurrentClient = nullptr;
	}
	if (allClient)
	{
		allClient->DestroyListView();
		delete allClient;
		allClient = nullptr;
	}
	if (buttons)
	{
		buttons->destroyAllClientViewButtons();
		delete buttons;
		buttons = nullptr;
	}
	if (auxiliaryWindows)
	{
		delete auxiliaryWindows;
		auxiliaryWindows = nullptr;
	}
}

BOOL ClientView::getInfoAboutSelectedClient()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND parent = FindWindow(szClassName, szWindowName);
	HWND btnToEnable = GetDlgItem(parent, ID_ENTRANCE_CASINO_BTN);
	std::vector<SQLTCHAR*>* selectedClient = allClient->getSelectedClient();
	if (selectedClient->empty())
	{
		EnableWindow(btnToEnable, FALSE);
		btnToEnable = GetDlgItem(parent, ID_EDIT_CLIENT_BTN);
		EnableWindow(btnToEnable, FALSE);
		return FALSE;
	}
	else
	{		
		EnableWindow(btnToEnable, TRUE);
		btnToEnable = GetDlgItem(parent, ID_EDIT_CLIENT_BTN);
		EnableWindow(btnToEnable, TRUE);
		if (currentClient)
		{
			currentClient->FreeAllField();
			currentClient->GetInfoForCurrentClient(selectedClient);
		}
		else
		{
			currentClient = new Client;
			currentClient->GetInfoForCurrentClient(selectedClient);
			return TRUE;
		}
	}
	return FALSE;
}

void ClientView::InitAddClientWnd(void)
{
	if (!auxiliaryWindows)
	{
		auxiliaryWindows = new AuxiliaryWindows;
	}
	auxiliaryWindows->createAddNewClientWnd();
}

void ClientView::hideWndForClientView()
{
	if (photoForCurrentClient)
	{
		photoForCurrentClient->hideImageWindow();
	}
	if (allClient)
	{
		allClient->hideListView();
		
	}
	if (buttons)
	{
		buttons->hideAllButtons();
	}
}
void ClientView::showAllWndForClientView(void)
{
	if (photoForCurrentClient)
	{
		photoForCurrentClient->showImageWindow();
	}
	if (allClient)
	{
		allClient->showListView();

	}
	if (buttons)
	{
		buttons->showAllButtons();
	}
	/*extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND parent = FindWindow(szClassName, szWindowName);
	HWND listWnd = GetDlgItem(parent, ID_LIST_FOR_CLIENTVIEW);
	int index = ListView_GetNextItem(listWnd, -1, LVNI_ALL | LVNI_SELECTED|LVNI_FOCUSED);
	ListView_SetItemState(listWnd, index, 0x0, LVIS_SELECTED|LVNI_FOCUSED);*/
}

void ClientView::destroyAuxiliaryWindows(void)
{
	if (auxiliaryWindows)
	{
		auxiliaryWindows->destroyAuxiliaryWindow();
		delete auxiliaryWindows;
		auxiliaryWindows = nullptr;
	}
}