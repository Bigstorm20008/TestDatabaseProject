#include "ExtendedInfoAboutPerson.h"


ExtendedInfoAboutPerson::ExtendedInfoAboutPerson(HWND parent,int xPos, int yPos, int width, int height)
{
	m_parentOfExtInfoWindow = parent;
	m_extendedInfoWindow = CreateWindow(TEXT("STATIC"),
		                                NULL,
		                                WS_CHILD | WS_VISIBLE | SS_WHITERECT,
		                                xPos, yPos,
		                                width, height,
				                        m_parentOfExtInfoWindow,
		                                NULL,
		                                (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                                NULL);
	SetWindowLongPtr(m_extendedInfoWindow, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	m_ExtInfoWindowProc = (LONG_PTR)SetWindowLongPtr(m_extendedInfoWindow, GWLP_WNDPROC, (LONG_PTR)(ExtInfoWindowProc));

	m_windowForNickname = NULL;
	m_windowForLastname = NULL;
	m_windowForFirstname = NULL;
	m_windowForPatronymic = NULL;
	m_windowForStatus = NULL;
	m_windowForLastVisitDate = NULL;
	m_windowForThisMounthVisitsCount = NULL;
	m_windowForDropToday = NULL;
	m_windowForResultToday = NULL;
	m_windowForDropInCurrentMounth = NULL;
	m_windowForResultInCurrentMounth = NULL;
}


ExtendedInfoAboutPerson::~ExtendedInfoAboutPerson()
{
	DestroyWindow(m_extendedInfoWindow);
}

void ExtendedInfoAboutPerson::createInfoWindowWithDescription(int descriptionXPos, int descriptionYPos, int descriptionWidth, int descriptionHeight, TCHAR* descriptionText, HWND& windowWithInfo)
{
	CreateWindow(TEXT("STATIC"),
		         descriptionText,
		         WS_CHILD | WS_VISIBLE | SS_LEFT,
				 descriptionXPos, descriptionYPos,
		         descriptionWidth, descriptionHeight,
		         m_extendedInfoWindow,
		         NULL,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);
	descriptionXPos += descriptionWidth;
	RECT extInfoRC;
	GetClientRect(m_extendedInfoWindow, &extInfoRC);
	int infoWindowWidth = extInfoRC.right - descriptionWidth - 2 * offsetsBetweenWindow;
	int infoWindowHeight = descriptionHeight;
	windowWithInfo = CreateWindow(TEXT("STATIC"),
		                          NULL,
		                          WS_CHILD | WS_VISIBLE | SS_LEFT ,
								  descriptionXPos, descriptionYPos,
		                          infoWindowWidth, infoWindowHeight,
		                          m_extendedInfoWindow,
		                          NULL,
		                          (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                          NULL);
}


void ExtendedInfoAboutPerson::destroyAllControls()
{
	HWND childWnd = NULL;
	while (childWnd = GetTopWindow(m_extendedInfoWindow))
	{
		DestroyWindow(childWnd);
	}
}


void ExtendedInfoAboutPerson::createClientExtendedInfoControls()
{
	destroyAllControls();
	RECT extInfoRC;
	GetClientRect(m_extendedInfoWindow, &extInfoRC);

	int xPos = extInfoRC.left;
	int yPos = extInfoRC.top;
	int captionForGroupWidth = extInfoRC.right - extInfoRC.left;
	int captionForGroupHeight = 20;
	CreateWindow(TEXT("STATIC"),
		         TEXT("Общая информация о клиенте"),
				 WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
		         xPos, yPos,
				 captionForGroupWidth, captionForGroupHeight,
		         m_extendedInfoWindow,
		         NULL,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);

	xPos += offsetsBetweenWindow;
	yPos += captionForGroupHeight + offsetsBetweenWindow;
	int descriptionWidth = 70;
	int descriptionHeight = 20;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Nickname:"), m_windowForNickname);

	yPos += descriptionHeight;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Фамилия:"), m_windowForLastname);

	yPos += descriptionHeight;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Имя:"), m_windowForFirstname);

	yPos += descriptionHeight;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Отчество:"), m_windowForPatronymic);

	yPos += descriptionHeight;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Статус:"), m_windowForStatus);

	xPos = extInfoRC.left;
	yPos += descriptionHeight;
	CreateWindow(TEXT("STATIC"),
		         TEXT("Информация об активности клиента"),
		         WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
		         xPos, yPos,
		         captionForGroupWidth, captionForGroupHeight,
		         m_extendedInfoWindow,
		         NULL,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);

	yPos += captionForGroupHeight + offsetsBetweenWindow;
	descriptionWidth = 160;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Последнее посещение:"), m_windowForLastVisitDate);

	yPos += descriptionHeight;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Посещений за этот месяц:"), m_windowForThisMounthVisitsCount);

	yPos += descriptionHeight;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Drop за сегодня:"), m_windowForDropToday);

	yPos += descriptionHeight;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Result за сегодня:"), m_windowForResultToday);

	yPos += descriptionHeight;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Drop за этот месяц:"), m_windowForDropInCurrentMounth);

	yPos += descriptionHeight;
	createInfoWindowWithDescription(xPos, yPos, descriptionWidth, descriptionHeight, TEXT("Result за этот месяц:"), m_windowForResultInCurrentMounth);
	
}


void ExtendedInfoAboutPerson::createEmployeeExtendedInfoControls()
{
	destroyAllControls();
}


void ExtendedInfoAboutPerson::setExtendedInfoAboutPerson(Person* selectedPerson)
{
	if (m_windowForNickname)
	{
		SetWindowText(m_windowForNickname, ((Client*)selectedPerson)->getNickname());
	}
	if (m_windowForStatus)
	{
		SetWindowText(m_windowForStatus, ((Client*)selectedPerson)->getStatus());
	}
	if (m_windowForLastVisitDate)
	{
		if (((Client*)selectedPerson)->getClientState())
		{
			SetWindowText(m_windowForLastVisitDate, TEXT("Клиент сейчас в казино"));
		}
		else
		{
			SetWindowText(m_windowForLastVisitDate, ((Client*)selectedPerson)->getLastVisit());
		}
	}
	SetWindowText(m_windowForLastname, selectedPerson->getLastname());
	SetWindowText(m_windowForFirstname, selectedPerson->getFirstname());
	SetWindowText(m_windowForPatronymic, selectedPerson->getPatronymic());
}


void ExtendedInfoAboutPerson::clearExtendedInfoWindow()
{
	if (m_windowForNickname)
	{
		SetWindowText(m_windowForNickname, TEXT(""));
	}
	if (m_windowForStatus)
	{
		SetWindowText(m_windowForStatus, TEXT(""));
	}
	if (m_windowForLastVisitDate)
	{
	    SetWindowText(m_windowForLastVisitDate, TEXT(""));
	}
	SetWindowText(m_windowForLastname, TEXT(""));
	SetWindowText(m_windowForFirstname, TEXT(""));
	SetWindowText(m_windowForPatronymic, TEXT(""));

}



LRESULT CALLBACK ExtendedInfoAboutPerson::ExtInfoWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ExtendedInfoAboutPerson* extInfo = NULL;
	extInfo = (ExtendedInfoAboutPerson*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (extInfo != NULL)
	{
		return extInfo->RealExtInfoWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

LRESULT ExtendedInfoAboutPerson::RealExtInfoWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
									DEFAULT_CHARSET,
									0, 0, 0, VARIABLE_PITCH,
									L"Time New Romans");
			SelectObject(hdcStatic, hFont);
			SetBkMode(hdcStatic, TRANSPARENT);
			return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
		}
		default:
		{
			return CallWindowProc((WNDPROC)m_ExtInfoWindowProc, m_extendedInfoWindow, msg, wParam, lParam);
		}

	}
	return 0;
}
