#include "ClientViewButtons.h"

int ClientViewButtons::xPos = 0;
int ClientViewButtons::yPos = 0;
int ClientViewButtons::btnWidth = 0;
int ClientViewButtons::btnHeight = 0;
ClientViewButtons::ClientViewButtons()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	parentWndForBtns = FindWindow(szClassName, szWindowName);
	RECT rc;
	GetClientRect(parentWndForBtns, &rc);
	HWND listWnd = GetDlgItem(parentWndForBtns, ID_LIST_FOR_CLIENTVIEW);
	RECT listRc;
	GetWindowRect(listWnd, &listRc);
	POINT tmp;
	tmp.x = listRc.right;
	tmp.y = listRc.top;
	ScreenToClient(parentWndForBtns, &tmp);
	xPos = tmp.x + 5;
	yPos = tmp.y;
	btnWidth = 200;
	btnHeight = 30;

}


ClientViewButtons::~ClientViewButtons()
{
}

void ClientViewButtons::createAddClientToDatabaseBtn(void)
{
	CreateWindow(TEXT("BUTTON"),
		         TEXT("Добавить нового клиента"),
				 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				 xPos,yPos,
				 btnWidth,btnHeight,
				 parentWndForBtns,
				 (HMENU)ID_ADD_NEW_CLIENT_BTN,
				 (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
				 NULL);
	xPos -= btnWidth + 10;
	yPos += btnHeight + 10;
}
void ClientViewButtons::createButtons()
{
	createEntranceCasinoBtn();
	createAddClientToDatabaseBtn();
	createEditClientBtn();
}

void ClientViewButtons::destroyAllClientViewButtons()
{
	HWND hWndToDestroy = GetDlgItem(parentWndForBtns, ID_ADD_NEW_CLIENT_BTN);
	DestroyWindow(hWndToDestroy);
	hWndToDestroy = GetDlgItem(parentWndForBtns, ID_ENTRANCE_CASINO_BTN);
	DestroyWindow(hWndToDestroy);
	hWndToDestroy = GetDlgItem(parentWndForBtns, ID_EDIT_CLIENT_BTN);
	DestroyWindow(hWndToDestroy);
}

void ClientViewButtons::createEntranceCasinoBtn(void)
{
	HWND hwnd = CreateWindow(TEXT("BUTTON"),
		                     TEXT("Вход в казино"),
		                     WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		                     xPos, yPos,
		                     btnWidth, btnHeight,
		                     parentWndForBtns,
		                     (HMENU)ID_ENTRANCE_CASINO_BTN,
		                     (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                     NULL);
	EnableWindow(hwnd, FALSE);
	xPos += btnWidth + 10;
}

void ClientViewButtons::createEditClientBtn(void)
{
	HWND hwnd = CreateWindow(TEXT("BUTTON"),
		TEXT("Редактировать данные"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		xPos, yPos,
		btnWidth, btnHeight,
		parentWndForBtns,
		(HMENU)ID_EDIT_CLIENT_BTN,
		(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		NULL);
	EnableWindow(hwnd, FALSE);
	xPos += btnWidth + 10;
}

void ClientViewButtons::hideAllButtons(void)
{
	HWND hWndToHide = GetDlgItem(parentWndForBtns, ID_ADD_NEW_CLIENT_BTN);
	ShowWindow(hWndToHide,SW_HIDE);
	hWndToHide = GetDlgItem(parentWndForBtns, ID_ENTRANCE_CASINO_BTN);
	ShowWindow(hWndToHide, SW_HIDE);
	hWndToHide = GetDlgItem(parentWndForBtns, ID_EDIT_CLIENT_BTN);
	ShowWindow(hWndToHide, SW_HIDE);
}

void ClientViewButtons::showAllButtons(void)
{
	HWND hWndToShow = GetDlgItem(parentWndForBtns, ID_ADD_NEW_CLIENT_BTN);
	ShowWindow(hWndToShow, SW_NORMAL);
	hWndToShow = GetDlgItem(parentWndForBtns, ID_ENTRANCE_CASINO_BTN);
	ShowWindow(hWndToShow, SW_NORMAL);
	hWndToShow = GetDlgItem(parentWndForBtns, ID_EDIT_CLIENT_BTN);
	ShowWindow(hWndToShow, SW_NORMAL);
}

void ClientViewButtons::showButtonsForSelectedClient(void)
{	
	HWND hWndToShow = GetDlgItem(parentWndForBtns, ID_ENTRANCE_CASINO_BTN);
	EnableWindow(hWndToShow, TRUE);
	hWndToShow = GetDlgItem(parentWndForBtns, ID_EDIT_CLIENT_BTN);
	EnableWindow(hWndToShow, TRUE);
}

void ClientViewButtons::disableBtnIfNotSelectedClient(void)
{
	HWND hWndToDisable = GetDlgItem(parentWndForBtns, ID_ENTRANCE_CASINO_BTN);
	EnableWindow(hWndToDisable, FALSE);
	hWndToDisable = GetDlgItem(parentWndForBtns, ID_EDIT_CLIENT_BTN);
	EnableWindow(hWndToDisable, FALSE);
}