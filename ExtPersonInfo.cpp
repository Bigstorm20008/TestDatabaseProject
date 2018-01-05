#include "ExtPersonInfo.h"


CExtPersonInfo::CExtPersonInfo(HWND parent, UINT imageIdentifier)
{
	parentWnd = parent;

	//Get client area of parent window and save it in RECT structure
	RECT rc;
	GetClientRect(parent, &rc);
	//Get window rect of image window and save it in RECT structure
	HWND imageWnd = GetDlgItem(parent, imageIdentifier);
	RECT imgRc;
	GetWindowRect(imageWnd, &imgRc);
	//Save coordinates x,y of top right coner in POINT structure
	POINT tmp;
	tmp.x = imgRc.left;
	tmp.y = imgRc.bottom;
	//Get coordinates of top right coner image window in client area of main window
	ScreenToClient(parent, &tmp);
	//Compute coordinates for placing window and initialize width and height 
	int xPos = tmp.x;    
	int yPos = tmp.y + offsetBetweenWindow;       
	int width = imgRc.right - imgRc.left;  
	int height = (rc.bottom - rc.top) - (imgRc.bottom - imgRc.top) - 3*offsetBetweenWindow;


	//Create control 
	extentedInfoWnd = CreateWindow(TEXT("STATIC"),
		NULL,
		WS_CHILD | WS_BORDER,
		xPos, yPos,
		width, height,
		parent,
		(HMENU)ID_EXT_INFO_WND,   //defined in Constants.h
		reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		NULL);

	
	HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		TEXT("Time New Romans"));
	RECT infoWndRc;
	GetClientRect(extentedInfoWnd, &infoWndRc);

	int titleWidth = infoWndRc.right - infoWndRc.left;
	int titleHeight = 20;
	int titleXPos = 0;
	int titleYPos = 5;
	HWND titleWnd = CreateWindow(TEXT("STATIC"),
		                         TEXT("Информация о клиенте"),
								 WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
								 titleXPos, titleYPos,
								 titleWidth, titleHeight,
								 extentedInfoWnd,
		                         NULL,   //defined in Constants.h
		                         reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                         NULL);

	int xPosStatic = offsetBetweenWindow;
	int yPosStatic = titleYPos + titleHeight;
	int widthStatic = 100;
	int heightStatic = 20;
	
	descForLastname = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Фамилия:"), NULL);

	yPosStatic += heightStatic;
	descForFirstname = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Имя:"), NULL);

	yPosStatic += heightStatic;
	descForPatronymic = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Отчество:"), NULL);

	yPosStatic += heightStatic;
	descForBirthday = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Дата рождения:"), NULL);

	yPosStatic += heightStatic;
	descForStatus = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Статус:"), NULL);

	yPosStatic += heightStatic;
	titleYPos = yPosStatic;
	titleWnd = CreateWindow(TEXT("STATIC"),
		                    TEXT("Активность клиента"),
		                    WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
		                    titleXPos, titleYPos,
		                    titleWidth, titleHeight,
		                    extentedInfoWnd,
		                    NULL,   
		                    reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                    NULL);

	yPosStatic = titleYPos + titleHeight;
	widthStatic = 160;
	descForLastVisit = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Последнее посещение:"), NULL);

	yPosStatic += heightStatic;
	descForVisitsInThisMounth = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Посещений за месяц:"), NULL);

	yPosStatic += heightStatic;
	descForAllVisits = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Всего посещений:"), NULL);

	yPosStatic += heightStatic;
	descForDropToday = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Drop(сегодня):"), NULL);

	yPosStatic += heightStatic;
	descForResultToday = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Result(сегодня):"), NULL);

	yPosStatic += heightStatic;
	descForDropMonth = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Drop(текущий месяц):"), NULL);

	yPosStatic += heightStatic;
	descForResultMounth = createStaticWithStaticDescription(xPosStatic, yPosStatic, widthStatic, heightStatic, TEXT("Result(текущий месяц):"), NULL);

	yPosStatic += heightStatic;
	titleYPos = yPosStatic;
	titleWnd = CreateWindow(TEXT("STATIC"),
						    TEXT("Контакты"),
							WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
							titleXPos, titleYPos,
							titleWidth, titleHeight,
							extentedInfoWnd,
							NULL,
							reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
							NULL);

	yPosStatic = titleYPos + titleHeight;	
	int listWidth = infoWndRc.right - infoWndRc.left;
	int listHeight = 100;
	int listXPos = 0;
	int listYPos = yPosStatic;
	phoneNumbersWnd = CreateWindow(TEXT("LISTBOX"), 
		                           NULL, 
								   WS_CHILD | WS_VISIBLE | LBS_STANDARD,
								   listXPos, listYPos,
								   listWidth, listHeight,
								   extentedInfoWnd,
								   NULL,
								   (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
								   NULL);
	SendMessage(phoneNumbersWnd, WM_SETFONT, (WPARAM)hFont, NULL);

	titleYPos = listYPos + listHeight;
	titleWnd = CreateWindow(TEXT("STATIC"),
		                    TEXT("Дополнительные сведения"),
		                    WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
		                    titleXPos, titleYPos,
		                    titleWidth, titleHeight,
		                    extentedInfoWnd,
		                    NULL,
		                    reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                    NULL);
	titleYPos += titleHeight;
	int extInfoWndXPos = 0;
	int extInfoWndYPos = titleYPos;
	int extInfoWndWidth = infoWndRc.right - infoWndRc.left;
	int extInfoWndHeight = infoWndRc.bottom - extInfoWndYPos;
	extInfoAboutPerson = CreateWindow(TEXT("EDIT"),
								      NULL,
									  WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_READONLY,
									  extInfoWndXPos, extInfoWndYPos,
									  extInfoWndWidth, extInfoWndHeight,
									  extentedInfoWnd,
									  NULL,
									  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
									  NULL);
	SendMessage(extInfoAboutPerson, WM_SETFONT, (WPARAM)hFont, NULL);
}

HWND CExtPersonInfo::createStaticWithStaticDescription(int staticXPos, int staticYPos, int staticWidth, int staticHeight, TCHAR* staticText, UINT descriptionIdentifier)
{
	HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		TEXT("Time New Romans"));

	HWND currentStatic = CreateWindow(TEXT("STATIC"),
									  staticText,
		                              WS_CHILD | WS_VISIBLE,
		                              staticXPos, staticYPos,
		                              staticWidth, staticHeight,
		                              extentedInfoWnd,
		                              NULL,   
		                              reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                              NULL);
	SendMessage(currentStatic, WM_SETFONT, (WPARAM)hFont, NULL);

	int descriptionXPos = staticXPos + staticWidth + offsetBetweenWindow;
	int descriptionYpos = staticYPos;

	RECT parentRc;
	GetClientRect(extentedInfoWnd, &parentRc);
	int descriptionWidth = (parentRc.right - parentRc.left) - staticWidth - offsetBetweenWindow;
	int descriptionHeight = staticHeight;
	HWND descriptionStatic = CreateWindow(TEXT("STATIC"),
		                                  NULL,
		                                  WS_CHILD | WS_VISIBLE | SS_LEFT,
										  descriptionXPos, descriptionYpos,
										  descriptionWidth, descriptionHeight,
		                                  extentedInfoWnd,
		                                  (HMENU)descriptionIdentifier,
		                                  reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                                  NULL);
	SendMessage(descriptionStatic, WM_SETFONT, (WPARAM)hFont, NULL);

	return descriptionStatic;
}
CExtPersonInfo::~CExtPersonInfo()
{
}


void CExtPersonInfo::showExtInfoWnd()
{
	ShowWindow(extentedInfoWnd, SW_NORMAL);
}

void CExtPersonInfo::setExtInfoAboutPerson(Client* currentPerson)
{
	SendMessage(descForLastname, WM_SETTEXT, 0, LPARAM(currentPerson->getLastname()));
	SendMessage(descForFirstname, WM_SETTEXT, 0, LPARAM(currentPerson->getFirstname()));
	SendMessage(descForPatronymic, WM_SETTEXT, 0, LPARAM(currentPerson->getPatronymic()));
	SendMessage(descForStatus, WM_SETTEXT, 0, LPARAM(currentPerson->getStatus()));
	SendMessage(descForBirthday, WM_SETTEXT, 0, LPARAM(currentPerson->getBirthDay()));
	std::vector<SQLTCHAR*>* phoneNumbers = currentPerson->getPhoneNumbers();
	if (phoneNumbers)
	{
		auto iter = phoneNumbers->begin();
		for (iter; iter < phoneNumbers->end(); iter++)
		{
			SendMessage(phoneNumbersWnd, LB_ADDSTRING, 0, LPARAM(*iter));
		}
	}
	TCHAR dropToday[20];
	_itot_s(currentPerson->getDrop(), dropToday, 20, 10);
	SendMessage(descForDropToday, WM_SETTEXT, 0, LPARAM(dropToday));
	TCHAR resultToday[20];
	_itot_s(currentPerson->getResult(), resultToday, 20, 10);
	SendMessage(descForResultToday, WM_SETTEXT, 0, LPARAM(resultToday));
}

void CExtPersonInfo::clearExtInfoWnd()
{
	SendMessage(descForLastname, WM_SETTEXT, 0, LPARAM(TEXT("")));
	SendMessage(descForFirstname, WM_SETTEXT, 0, LPARAM(TEXT("")));
	SendMessage(descForPatronymic, WM_SETTEXT, 0, LPARAM(TEXT("")));
	SendMessage(descForStatus, WM_SETTEXT, 0, LPARAM(TEXT("")));
	SendMessage(descForBirthday, WM_SETTEXT, 0, LPARAM(TEXT("")));
	SendMessage(descForDropToday, WM_SETTEXT, 0, LPARAM(TEXT("")));
	SendMessage(descForResultToday, WM_SETTEXT, 0, LPARAM(TEXT("")));

	size_t itemCountinListBox = SendMessage(phoneNumbersWnd, LB_GETCOUNT, 0, 0);
	while (itemCountinListBox)
	{
		SendMessage(phoneNumbersWnd, LB_DELETESTRING, (itemCountinListBox - 1), 0);
		itemCountinListBox = SendMessage(phoneNumbersWnd, LB_GETCOUNT, 0, 0);
	}
	
}