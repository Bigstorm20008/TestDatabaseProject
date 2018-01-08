#include "ButtonsForViews.h"


CButtonsForViews::CButtonsForViews(HWND parent, UINT listWndIdentifier)
{
	parentWindow = parent;
	HWND listWnd = GetDlgItem(parent, listWndIdentifier);
	getCurrentDate();
}


CButtonsForViews::~CButtonsForViews()
{

}

void CButtonsForViews::getCurrentDate()
{
	GetLocalTime(&dateTime);
}

void CButtonsForViews::createParentWindowForButtons(HWND listWnd)
{
	RECT rc;
	GetClientRect(parentWindow, &rc);
	RECT listRc;
	GetWindowRect(listWnd, &listRc);
	//Save coordinates x,y of top right coner in POINT structure
	POINT tmp;
	tmp.x = listRc.right;
	tmp.y = listRc.top;
	//Get coordinates of top right coner image window in client area of main window
	ScreenToClient(parentWindow, &tmp);
	//Compute coordinates for placing listview control and initialize width and height of 
	int xPos = tmp.x + offsetBetweenWindow;   //step break from the brink of image window by 5 
	int yPos = tmp.y;       //y poasition of listview control = y position of image window
	int width = rc.right - rc.left - xPos - offsetBetweenWindow;  //width of listview(listViewWidth defined in Constants.h)
	int height = rc.bottom - rc.top - 2 * offsetBetweenWindow;  //height of listview = height of main window - height of control panel(55)

	//Create control 
	parentForButtons = CreateWindow(TEXT("STATIC"),
		                            NULL,
		                            WS_CHILD | WS_BORDER,
		                            xPos, yPos,
		                            width, height,
		                            parentWindow,
		                            NULL,
		                            reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                            NULL);

	extern WNDPROC oldParentForButtonsProc;
	oldParentForButtonsProc = (WNDPROC)SetWindowLong(parentForButtons, GWL_WNDPROC, (LONG)ParentForButtonsProc);
}

void CButtonsForViews::createCashViewButtons()
{
	DestroyWindow(parentForButtons);
	HWND listWnd = GetDlgItem(parentWindow, ID_LISTVIEW_WND);
	createParentWindowForButtons(listWnd);
	int xPos = 10;
	int yPos = 0;
	createCaptionForGroupButton(yPos, TEXT("Операции с клиентами"));

	yPos += 25;
	int btnWidth = 140;
	int btnHeight = 25;
	cashInButton = CreateWindow(TEXT("BUTTON"),
		                            TEXT("Cash In"),
									WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_DISABLED,
		                            xPos, yPos,
									btnWidth, btnHeight,
									parentForButtons,
		                            (HMENU)ID_CASH_IN_BTN,
		                            reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                            NULL);


	yPos += btnHeight + offsetBetweenWindow;
	cashOutButton = CreateWindow(TEXT("BUTTON"),
		TEXT("Cash Out"),
		WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_DISABLED,
		xPos, yPos,
		btnWidth, btnHeight,
		parentForButtons,
		(HMENU)ID_CASH_OUT_BTN,
		reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		NULL);
	

	yPos += btnHeight + offsetBetweenWindow;
	clientOutButton = CreateWindow(TEXT("BUTTON"),
		TEXT("Выход из казино"),
		WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_DISABLED,
		xPos, yPos,
		btnWidth, btnHeight,
		parentForButtons,
		(HMENU)ID_EXIT_FROM_CASINO_BTN,
		reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		NULL);

	yPos += btnHeight + offsetBetweenWindow;
	createCaptionForGroupButton(yPos, TEXT("Операции по кассе"));

	yPos += btnHeight + offsetBetweenWindow;
	incomingBtn = CreateWindow(TEXT("BUTTON"),
							   TEXT("Приход"),
		                       WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE,
		                       xPos, yPos,
		                       btnWidth, btnHeight,
		                       parentForButtons,
		                       NULL,
		                       reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                       NULL);

	yPos += btnHeight + offsetBetweenWindow;
	incomingBtn = CreateWindow(TEXT("BUTTON"),
		                       TEXT("Расход"),
		                       WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE,
		                       xPos, yPos,
		                       btnWidth, btnHeight,
		                       parentForButtons,
		                       NULL,
		                       reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                       NULL);

	ShowWindow(parentForButtons, SW_NORMAL);
}

void CButtonsForViews::createClientViewButtons()
{
	DestroyWindow(parentForButtons);
	HWND listWnd = GetDlgItem(parentWindow, ID_LISTVIEW_WND);
	createParentWindowForButtons(listWnd);
	addClientButton = CreateWindow(TEXT("BUTTON"),
		                           TEXT("Добавить клиента"),
		                           WS_CHILD | WS_BORDER | BS_DEFPUSHBUTTON | WS_VISIBLE,
		                           10, 10,
		                           200, 25,
		                           parentForButtons,
		                           (HMENU)ID_ADD_CLIENT_TO_DATABASE,
		                           reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                           NULL);

	clientInButton =  CreateWindow(TEXT("BUTTON"),
		                           TEXT("Вход в казино"),
		                           WS_CHILD | WS_BORDER | BS_DEFPUSHBUTTON | WS_VISIBLE | WS_DISABLED,
		                           10, 40,
		                           200, 25,
		                           parentForButtons,
								   (HMENU)ID_ENTRANCE_IN_CASINO_BTN,
		                           reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                           NULL);
	
	ShowWindow(parentForButtons, SW_NORMAL);
}

void CButtonsForViews::createEmployeesViewButtons()
{
	DestroyWindow(parentForButtons);
}

void CButtonsForViews::createCaptionForGroupButton(int yPos, TCHAR* caption)
{
	
	RECT parentRC;
	GetClientRect(parentForButtons, &parentRC);
	int xPos = parentRC.left;
	int captionWidth = parentRC.right - parentRC.left;
	int captionHeight = 20;
	HWND staticCaption = CreateWindow(TEXT("STATIC"),
								      caption,
									  WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
									  xPos, yPos,
									  captionWidth, captionHeight,
									  parentForButtons,
									  NULL,
									  reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
									  NULL);
	/*HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		TEXT("Time New Romans"));
	SendMessage(staticCaption, WM_SETFONT, (WPARAM)hFont, NULL);*/
}

void CButtonsForViews::enableButtonsIfPersonSelected()
{
	if (cashInButton)
	{
		EnableWindow(cashInButton, TRUE);
	}
	if (cashOutButton)
	{
		EnableWindow(cashOutButton, TRUE);
	}
	if (clientOutButton)
	{
		EnableWindow(clientOutButton, TRUE);
	}
	if (clientInButton)
	{
		EnableWindow(clientInButton, TRUE);
	}
}

void CButtonsForViews::disableButtonsIfNoSelected()
{
	if (cashInButton)
	{
		EnableWindow(cashInButton, FALSE);
	}
	if (cashOutButton)
	{
		EnableWindow(cashOutButton, FALSE);
	}
	if (clientOutButton)
	{
		EnableWindow(clientOutButton, FALSE);
	}
	if (clientInButton)
	{
		EnableWindow(clientInButton, FALSE);
	}
}


LRESULT CALLBACK ParentForButtonsProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	extern LPTSTR szClassName;      //window class of main window(init in main.cpp)             
	extern LPTSTR szWindowName;     //title of main window(init in main.cpp)
	HWND mainAppWindow = FindWindow(szClassName, szWindowName);    //Get handler to main application window
	switch (msg)
	{
		case WM_COMMAND:
		{
			switch (wp)
			{
				case ID_CASH_IN_BTN:
				{
					SendMessage(mainAppWindow, WM_COMMAND, ID_CASH_IN_BTN, 0);
					break;
				}
				case ID_CASH_OUT_BTN:
				{
					SendMessage(mainAppWindow, WM_COMMAND, ID_CASH_OUT_BTN, 0);
					break;
				}
				case ID_EXIT_FROM_CASINO_BTN:
				{
					SendMessage(mainAppWindow, WM_COMMAND, ID_EXIT_FROM_CASINO_BTN, 0);
					break;
				}
				case ID_ENTRANCE_IN_CASINO_BTN:
				{
					SendMessage(mainAppWindow, WM_COMMAND, ID_ENTRANCE_IN_CASINO_BTN, 0);
					break;
				}
				case ID_ADD_CLIENT_TO_DATABASE:
				{
					SendMessage(mainAppWindow, WM_COMMAND, ID_ADD_CLIENT_TO_DATABASE, 0);
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}

	}
	extern WNDPROC oldParentForButtonsProc;
	return CallWindowProc(oldParentForButtonsProc, hWnd, msg, wp, lp);
}