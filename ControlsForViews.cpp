#include "ControlsForViews.h"


ControlsForViews::ControlsForViews(HWND parentForControls, int xPos, int yPos, int width, int height, CSqlFramework* sqlConnection)
{
	m_parentOfParentOfControl = parentForControls;
	m_sqlConnection = sqlConnection;

	m_parentOfControl = CreateWindow(TEXT("STATIC"),
									 NULL,
									 WS_CHILD | WS_VISIBLE | SS_WHITERECT,
									 xPos,yPos,
									 width,height,
									 m_parentOfParentOfControl,
									 NULL,
									 (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
									 NULL);
	SetWindowLongPtr(m_parentOfControl, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	m_oldParentForButtonProc = (LONG_PTR)SetWindowLongPtr(m_parentOfControl, GWLP_WNDPROC, (LONG_PTR)(this->ParentForButtonProc));
}


ControlsForViews::~ControlsForViews()
{
	DestroyWindow(m_parentOfControl);
}

HWND ControlsForViews::getInfoWindowForRate(UINT pressedBtnIdentifier)
{
	switch (pressedBtnIdentifier)
	{
		case ID_CHANGE_DOLLAR_RATE:
		{
			return m_dollarRate;
		}
		case ID_CHANGE_EURO_RATE:
		{
			return m_euroRate;
		}
		default:
		{
			return NULL;
		}
	}
}
void ControlsForViews::createControlsForCashView()
{
	destroyAllControls();

	int xPos = offsetsBetweenWindow;
	int yPos = 0;
	createCaptionForGroupButton(yPos, TEXT("Общая информация"));

	yPos += captionHeightForGroupButton;
	int rateInfoWidth = 100;
	int rateInfoHeight = 20;
	m_dollarRate = createInfoWindowAboutRate(xPos, yPos, rateInfoWidth, rateInfoHeight, TEXT("Курс доллара"),ID_CHANGE_DOLLAR_RATE);

	xPos += rateInfoWidth + offsetsBetweenWindow;
	m_euroRate = createInfoWindowAboutRate(xPos, yPos, rateInfoWidth, rateInfoHeight, TEXT("Курс евро"), ID_CHANGE_EURO_RATE);

	xPos = offsetsBetweenWindow;
	yPos = 90;
	createCaptionForGroupButton(yPos, TEXT("Операции с клиентами"));

	yPos += captionHeightForGroupButton + offsetsBetweenWindow;
	int btnWidth = 125;
	int btnHeight = 25;
    m_cashInButton = CreateWindow(TEXT("BUTTON"),
		                          TEXT("Cash In"),
		                          WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_DISABLED,
		                          xPos, yPos,
		                          btnWidth, btnHeight,
		                          m_parentOfControl,
		                          (HMENU)ID_CASH_IN_BUTTON,
		                          reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                          NULL);

	yPos += btnHeight + offsetsBetweenWindow;
	m_cashOutButton = CreateWindow(TEXT("BUTTON"),
		                           TEXT("Cash Out"),
		                           WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_DISABLED,
		                           xPos, yPos,
		                           btnWidth, btnHeight,
		                           m_parentOfControl,
								   (HMENU)ID_CASH_OUT_BUTTON,
		                           reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                           NULL);

	yPos += btnHeight + offsetsBetweenWindow;
	m_exitFromCasinoButton = CreateWindow(TEXT("BUTTON"),
		                                  TEXT("Выход из казино"),
		                                  WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_DISABLED,
		                                  xPos, yPos,
		                                  btnWidth, btnHeight,
		                                  m_parentOfControl,
										  (HMENU)ID_EXIT_FROM_CASINO_BUTTON,
		                                  reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                                  NULL);
}

void ControlsForViews::createControlsForClientsView()
{
	destroyAllControls();
	int xPos = offsetsBetweenWindow;
	int yPos = offsetsBetweenWindow;
	int btnWidth = 135;
	int btnHeight = 25;

	m_entranceToCasinoButton = CreateWindow(TEXT("BUTTON"),
		                                    TEXT("Вход в казино"),
		                                    WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_DISABLED,
		                                    xPos, yPos,
		                                    btnWidth, btnHeight,
		                                    m_parentOfControl,
		                                    (HMENU)ID_ENTRANCE_TO_CASINO_BUTTON,
		                                    reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                                    NULL);

	yPos += btnHeight + offsetsBetweenWindow;
	CreateWindow(TEXT("BUTTON"),
		         TEXT("Добавить клиента"),
		         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		         xPos, yPos,
		         btnWidth, btnHeight,
		         m_parentOfControl,
		         (HMENU)ID_ADD_CLIENT_TO_DATABASE_BTN,
		         reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		         NULL);
}

void ControlsForViews::enableButtonsIfSelectedPerson()
{
	EnableWindow(m_cashInButton, TRUE);
	EnableWindow(m_cashOutButton, TRUE);
	EnableWindow(m_exitFromCasinoButton, TRUE);
	EnableWindow(m_entranceToCasinoButton, TRUE);
}


void ControlsForViews::disableButtonsIfNoSelectedPerson()
{
	EnableWindow(m_cashInButton, FALSE);
	EnableWindow(m_cashOutButton, FALSE);
	EnableWindow(m_exitFromCasinoButton, FALSE);
	EnableWindow(m_entranceToCasinoButton, FALSE);
}


void ControlsForViews::createControlsForEmployeesView()
{
	destroyAllControls();
}


void ControlsForViews::destroyAllControls()
{
	HWND childWnd = NULL;
	while (childWnd = GetTopWindow(m_parentOfControl))
	{
		DestroyWindow(childWnd);
	}
}


HWND ControlsForViews::createInfoWindowAboutRate(int xPos, int yPos, int width, int height, TCHAR* currencyName,UINT identifierForChangeRateBtn)
{
	TCHAR* currentRate = nullptr;
	CurrencyOperation currencyOperation(m_sqlConnection);
	switch (identifierForChangeRateBtn)
	{
		case ID_CHANGE_DOLLAR_RATE:
		{
			currentRate = currencyOperation.getDollarRate();
			break;
		}
		case ID_CHANGE_EURO_RATE:
		{
			currentRate = currencyOperation.getEuroRate();
			break;
		}
		default:
		{
			break;
		}
	}
	int staticHeight = 20;
	int staticWidth = 100;
	HWND currencyNameWnd = CreateWindow(TEXT("STATIC"),
		                                currencyName,
		                                WS_CHILD | WS_VISIBLE | SS_CENTER,
		                                xPos, yPos,
		                                staticWidth, staticHeight,
		                                m_parentOfControl,
		                                NULL,
		                                (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                                NULL);

	yPos += height;
	HWND currencyValue = CreateWindow(TEXT("STATIC"),
		                              currentRate,
		                              WS_CHILD | WS_VISIBLE | SS_CENTER,
		                              xPos, yPos,
		                              staticWidth, staticHeight,
		                              m_parentOfControl,
		                              NULL,
		                              (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                              NULL);


	HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		TEXT("Time New Romans"));
	yPos += height;
	HWND btn = CreateWindow(TEXT("BUTTON"),
		                    TEXT("Изменить курс"),
		                    WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE,
		                    xPos, yPos,
		                    staticWidth, staticHeight,
		                    m_parentOfControl,
		                    (HMENU)identifierForChangeRateBtn,
		                    reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                    NULL);
	SendMessage(btn, WM_SETFONT, (WPARAM)hFont, NULL);

	return currencyValue;
}


void ControlsForViews::createCaptionForGroupButton(int yPos, TCHAR* captionForGroup)
{
	RECT parentRC;
	GetClientRect(m_parentOfControl, &parentRC);
	int xPos = parentRC.left;
	int captionWidth = parentRC.right - parentRC.left;
	int captionHeight = captionHeightForGroupButton;
	HWND staticCaption = CreateWindow(TEXT("STATIC"),
		                              captionForGroup,
		                              WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
		                              xPos, yPos,
		                              captionWidth, captionHeight,
		                              m_parentOfControl,
		                              NULL,
		                              reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
		                              NULL);
}



LRESULT CALLBACK ControlsForViews::ParentForButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ControlsForViews* controlsForViews = NULL;
	controlsForViews = (ControlsForViews*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (controlsForViews != NULL)
	{
		return controlsForViews->RealParentForButtonProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}


LRESULT ControlsForViews::RealParentForButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CTLCOLORSTATIC:
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
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case ID_CHANGE_DOLLAR_RATE:
				{
					SendMessage(m_parentOfParentOfControl, WM_COMMAND, ID_CHANGE_DOLLAR_RATE, 0);
					//m_changeCurrencyForm = new ChangeCurrencyRateForm(m_parentOfParentOfControl, m_parentOfControl, m_dollarRate, ID_CHANGE_DOLLAR_RATE, m_sqlConnection);
					break;
				}
				case ID_CHANGE_EURO_RATE:
				{
					SendMessage(m_parentOfParentOfControl, WM_COMMAND, ID_CHANGE_EURO_RATE, 0);
					break;
				}
				case ID_CASH_IN_BUTTON:
				{
					SendMessage(m_parentOfParentOfControl, WM_COMMAND, ID_CASH_IN_BUTTON, 0);
					break;
				}
				case ID_CASH_OUT_BUTTON:
				{
					SendMessage(m_parentOfParentOfControl, WM_COMMAND, ID_CASH_OUT_BUTTON, 0);
					break;
				}
				case ID_EXIT_FROM_CASINO_BUTTON:
				{
					SendMessage(m_parentOfParentOfControl, WM_COMMAND, ID_EXIT_FROM_CASINO_BUTTON, 0);
					break;
				}
				case ID_ENTRANCE_TO_CASINO_BUTTON:
				{
					SendMessage(m_parentOfParentOfControl, WM_COMMAND, ID_ENTRANCE_TO_CASINO_BUTTON, 0);
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
			return CallWindowProc((WNDPROC)m_oldParentForButtonProc, m_parentOfControl, msg, wParam, lParam);
		}
	}
	return 0;
}

