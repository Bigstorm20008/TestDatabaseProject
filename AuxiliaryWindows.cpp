#include "AuxiliaryWindows.h"


AuxiliaryWindows::AuxiliaryWindows()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	mainWnd = FindWindow(szClassName, szWindowName);
	RECT mainRC;
	GetClientRect(mainWnd, &mainRC);
	auxiliaryWndWidth = mainRC.right / 2;
	auxiliaryWndHeight = mainRC.bottom / 1.5;
	xPosCentred = mainRC.right / 2 - auxiliaryWndWidth / 2;
	yPosCentred = mainRC.bottom / 2 - auxiliaryWndHeight / 2;
}


AuxiliaryWindows::~AuxiliaryWindows()
{
}

void AuxiliaryWindows::createAddNewClientWnd()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);
	wc.lpfnWndProc = addNewClientWndProc;
	wc.lpszClassName = TEXT("NewClientWnd");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);
	
	HWND hwnd = CreateWindow(TEXT("NewClientWnd"),
		         TEXT("Добавление нового клиента"),
				 WS_CHILD|WS_VISIBLE|WS_BORDER,
				 xPosCentred,yPosCentred,
				 auxiliaryWndWidth,auxiliaryWndHeight,
				 mainWnd,
				 (HMENU)ID_ADD_NEW_CLIENT_WND,
				 (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
				 NULL);

	HWND staticCaption = CreateWindow(TEXT("STATIC"),
		                              TEXT("Добавление нового клиента в базу данных"),
									  WS_CHILD | WS_VISIBLE | SS_CENTER | SS_EDITCONTROL,
									  0,0,
									  auxiliaryWndWidth,20,
									  hwnd,
									  (HMENU)ID_STATIC_CAPTION,
									  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), 
									  NULL);
	RECT hwndRC;
	GetClientRect(hwnd, &hwndRC);
	int btnWidth = 150;
	int btnHeight = 25;
	int xPos = hwndRC.right - btnWidth - 10;
	int yPos = hwndRC.bottom - btnHeight - 10;
	HWND okBtn = CreateWindow(TEXT("BUTTON"),
		                      TEXT("Добавить в базу"),
							  WS_CHILD | WS_VISIBLE |BS_DEFPUSHBUTTON,
							  xPos,yPos,
							  btnWidth, btnHeight,
							  hwnd,
							  (HMENU)ID_ADD_TO_BASE_BTN,
							  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), 
							  NULL);
	xPos -= btnWidth + 10;

	HWND cancelBtn = CreateWindow(TEXT("BUTTON"),
		                          TEXT("Отмена"),
		                          WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		                          xPos, yPos,
		                          btnWidth, btnHeight,
		                          hwnd,
								  (HMENU)ID_CANCEL_ADD_TO_BASE_BTN,
		                          (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                          NULL);
	int xPosForEdit = 10;
	int yPosForEdit = 40;
	int widthForEdit = 200;
	int heightForEdit = 20;
	createEditBoxWithDescription(hwnd, TEXT("Nickname*"), ID_EDITBOX_FOR_NICKNAME, ID_DESCRIPTION_NICKNAME, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit = yPosForEdit + heightForEdit + 10 + 25;
	createEditBoxWithDescription(hwnd, TEXT("Фамилия"), ID_EDITBOX_FOR_LASTNAME, ID_DESCRIPTION_LASTNAME, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit = yPosForEdit + heightForEdit + 10 + 25;
	createEditBoxWithDescription(hwnd, TEXT("Имя"), ID_EDITBOX_FOR_FIRSTNAME, ID_DESCRIPTION_FIRSTNAME, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit = yPosForEdit + heightForEdit + 10 + 25;
	createEditBoxWithDescription(hwnd, TEXT("Отчество"), ID_EDITBOX_FOR_PATRONYMIC, ID_DESCRIPTION_PATRONYMIC, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit = yPosForEdit + heightForEdit + 10 + 25;
	createEditBoxWithDescription(hwnd, TEXT("Дата рождения (чч/мм/гггг)"), ID_EDITBOX_FOR_BIRTHDAY, ID_DESCRIPTION_BIRTHDAY, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit = yPosForEdit + heightForEdit + 10 + 25;
	HWND hWndStatusComboBox = CreateWindow(TEXT("COMBOBOX"), TEXT(""),
		CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		xPosForEdit, yPosForEdit, widthForEdit, heightForEdit, hwnd, NULL, (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		NULL);
	extern CSqlFramework* sqlODBC;
	SQLHANDLE statementHandle = sqlODBC->SendQueryToDatabase(TEXT("SELECT Статус FROM dbo.Status"));
	Binding* pBinding = sqlODBC->GetBinding();
	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		Binding* pTempBinding = pBinding;
		while (pTempBinding)
		{
			SendMessage(hWndStatusComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)pTempBinding->GetDescription());
			pTempBinding = pTempBinding->GetNextBinding();
		}
	}
	sqlODBC->FreeBinding(statementHandle);

	yPosForEdit = yPosForEdit + heightForEdit + 10 + 25;

	HWND hList = CreateWindow(TEXT("LISTBOX"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD,
		xPosForEdit, yPosForEdit, 200, heightForEdit + 10 + 25, hwnd, NULL, (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), NULL);
	RECT rcList;
	GetWindowRect(hList, &rcList);
	POINT tmp;
	tmp.x = rcList.right;
	tmp.y = rcList.bottom;
	ScreenToClient(hwnd, &tmp);
	int btnPhoneWidth = 105;
	int btnPhoneHeight = 20;
	int btnPhoneXPos = tmp.x - btnPhoneWidth;
	int btnPhoneYPos = tmp.y;
	
	HWND addPhoneBtn = CreateWindow(TEXT("BUTTON"), TEXT("Добавить номер"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		btnPhoneXPos, btnPhoneYPos, btnPhoneWidth, btnPhoneHeight, hwnd, NULL, (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), NULL);
	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		L"Time New Romans");
	SendMessage(addPhoneBtn, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
	//int pos = (int)SendMessage(hList, LB_ADDSTRING, 0,
		//(LPARAM)TEXT("hi worldghghghghghghghghg"));
	//pos = (int)SendMessage(hList, LB_ADDSTRING, pos,
		//(LPARAM)TEXT("hi world!!!"));



}

void AuxiliaryWindows::destroyAuxiliaryWindow()
{
	HWND hwndToDestroy = GetDlgItem(mainWnd, ID_ADD_NEW_CLIENT_WND);
	if (hwndToDestroy)
	{
		DestroyWindow(hwndToDestroy);
	}
}

void AuxiliaryWindows::createEditBoxWithDescription(HWND parent, LPTSTR description, UINT editBoxIdentifier, UINT staticControlIdentifier, int editBox_xPos, int  editBox_yPos, int editBox_width, int editBox_height)
{
	HWND editWnd = CreateWindow(TEXT("EDIT"),
		                        NULL,
				                WS_CHILD | WS_VISIBLE | WS_BORDER |WS_TABSTOP,
				                editBox_xPos,editBox_yPos,
				                editBox_width,editBox_height,
				                parent,
				                (HMENU)editBoxIdentifier,
				                (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
				                NULL);
	HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		L"Time New Romans");
	SendMessage(editWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
	RECT editRc;
	GetWindowRect(editWnd, &editRc);
	POINT tmp;
	tmp.x = editRc.left;
	tmp.y = editRc.top;
	ScreenToClient(parent, &tmp);
	int static_width = editBox_width;
	int static_height = 15;
	int static_xPos = tmp.x;
	int static_yPos = tmp.y - static_height;

	HWND descWnd = CreateWindow(TEXT("STATIC"),
		                        description,
								WS_CHILD | WS_VISIBLE | SS_LEFT | SS_EDITCONTROL,
								static_xPos, static_yPos,
								static_width, static_height,
		                        parent,
								(HMENU)staticControlIdentifier,
		                        (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                        NULL);

}


LRESULT CALLBACK addNewClientWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)

{
	switch (msg)
	{
	case WM_CTLCOLORSTATIC:
	{
		//=======================================================================
		HWND staticWnd = GetDlgItem(hwnd, ID_STATIC_CAPTION);
		if ((HWND)lParam == staticWnd)
		{
			HDC hdcStatic = (HDC)wParam;			
			HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
				DEFAULT_CHARSET,
				0, 0, 0, VARIABLE_PITCH,
				L"Time New Romans");
			SelectObject(hdcStatic, hFont);		
			SetBkMode(hdcStatic, TRANSPARENT);
			return (INT_PTR)CreateSolidBrush(RGB(217, 236, 249));
		}
		//========================================================================
		HWND staticNickname = GetDlgItem(hwnd, ID_DESCRIPTION_NICKNAME);
		HWND staticLastname = GetDlgItem(hwnd, ID_DESCRIPTION_LASTNAME);
		HWND staticFirstname = GetDlgItem(hwnd, ID_DESCRIPTION_FIRSTNAME);
		HWND staticPatronymic = GetDlgItem(hwnd, ID_DESCRIPTION_PATRONYMIC);
		HWND staticBirthday = GetDlgItem(hwnd, ID_DESCRIPTION_BIRTHDAY);
		if ((HWND)lParam == staticNickname || (HWND)lParam == staticLastname || (HWND)lParam == staticFirstname || (HWND)lParam == staticPatronymic ||(HWND)lParam == staticBirthday)
		{
			HDC hdcStatic = (HDC)wParam;
			HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
					                 DEFAULT_CHARSET,
					                 0, 0, 0, VARIABLE_PITCH,
					                 L"Time New Romans");
			SelectObject(hdcStatic, hFont);
			SetBkMode(hdcStatic, TRANSPARENT);
			return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
		}
		//=========================================================================
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case ID_CANCEL_ADD_TO_BASE_BTN:
			{
				extern LPTSTR szClassName;
				extern LPTSTR szWindowName;
				HWND mainWnd = FindWindow(szClassName, szWindowName);
				HWND controlPanel = GetDlgItem(mainWnd, ID_CASHIER_PANEL);
				SendMessage(controlPanel, WM_COMMAND, ID_CLIENT_BTN, 0);
				UpdateWindow(mainWnd);
				break;
			}
			default:
			{
				break;
			}
		}
		break;
	}
	// реакция на сообщение о прекращении работы программы
	case WM_DESTROY:
	{
		DestroyWindow(hwnd);
		break;
	}
		//Обработка всех остальных сообщений производится ОС по умолчанию
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam); //Просто вернем системе сообщение, которого нет в нашем обработчике
	}
	return 0;
}