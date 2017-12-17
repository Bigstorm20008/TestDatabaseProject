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

	createEditBoxWithDescription(hwnd, L"Nickname*", ID_EDITBOX_FOR_NICKNAME, ID_STATIC_DESCRIPTION, 10, 40, 200, 20);
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
				                WS_CHILD | WS_VISIBLE | WS_BORDER,
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
		staticWnd = GetDlgItem(hwnd, ID_STATIC_DESCRIPTION);
		if ((HWND)lParam == staticWnd)
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