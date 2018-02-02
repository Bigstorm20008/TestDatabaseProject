#include "ChangeCurrencyRateForm.h"


ChangeCurrencyRateForm::ChangeCurrencyRateForm(HWND windowToDisable, HWND parent, HWND windowWithInfoAboutRate, UINT btnIdentifer, CSqlFramework* sqlConnection)
	:AuxiliaryWindowTemplate(windowToDisable, parent, 300, 150, NULL)
{
	m_pressedBtnIdentifier = btnIdentifer;
	m_windowWithInfoAboutRate = windowWithInfoAboutRate;
	switch (btnIdentifer)
	{
		case ID_CHANGE_DOLLAR_RATE:
		{
			m_captionForWindow = TEXT("Изменить курс доллара");
			m_descriptionForEdit = TEXT("Укажите новый курс доллара");
			break;
		}
		case ID_CHANGE_EURO_RATE:
		{
			m_captionForWindow = TEXT("Изменить курс евро");
			m_descriptionForEdit = TEXT("Укажите новый курс евро");
			break;
		}
		default:
		{
			break;
		}
	}
	m_sqlConnection = sqlConnection;
	m_editForNewCurrencyRate = nullptr;
	createControlsForWindow();
	SetWindowText(m_captionWnd, m_captionForWindow);
}


ChangeCurrencyRateForm::~ChangeCurrencyRateForm()
{
	if (m_editForNewCurrencyRate)
	{
		delete m_editForNewCurrencyRate;
		m_editForNewCurrencyRate = nullptr;
	}
}

void ChangeCurrencyRateForm::createControlsForWindow()
{
	RECT parentRC;
	GetClientRect(m_auxiliaryWnd, &parentRC);
	int btnWidth = 130;
	int btnHeight = 25;
	int xPos = parentRC.right - btnWidth - offsetsBetweenWindow;
	int yPos = parentRC.bottom - btnHeight - offsetsBetweenWindow;

	HWND btn = CreateWindow(TEXT("BUTTON"),
		TEXT("Изменить курс"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		xPos, yPos,
		btnWidth, btnHeight,
		m_auxiliaryWnd,
		(HMENU)ID_CHANGE_CURRENCY_RATE,
		(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		NULL);

	xPos -= btnWidth + 10;
	btn = CreateWindow(TEXT("BUTTON"),
		               TEXT("Отмена"),
		               WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		               xPos, yPos,
		               btnWidth, btnHeight,
		               m_auxiliaryWnd,
		               (HMENU)ID_CANCEL_AUXILIARY_BTN,
		               (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		               NULL);

	RECT auxiliaryRC;
	GetClientRect(m_auxiliaryWnd, &auxiliaryRC);
	int editWidth = 200;
	int editHeight = 20;
	xPos = (auxiliaryRC.right - auxiliaryRC.left) / 2 - editWidth / 2;
	yPos = (auxiliaryRC.bottom - auxiliaryRC.top) / 2 - editHeight / 2;
	m_editForNewCurrencyRate = new EditControlTemplate;
	m_editForNewCurrencyRate->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER);
	m_editForNewCurrencyRate->createDescriptionForEdit(m_descriptionForEdit);
	m_editForNewCurrencyRate->setFocusOnEdit();
}

BOOL ChangeCurrencyRateForm::changeCurrencyRate()
{
	TCHAR* newCurrencyValue = m_editForNewCurrencyRate->getTextFromEdit();
	if (_tcscmp(newCurrencyValue, TEXT("")) == 0)
	{
		MessageBox(m_auxiliaryWnd, TEXT("Укажите новый курс валюты!"), TEXT("Ошибка изменения курса"), MB_OK);
		return FALSE;
	}
	else
	{
		CurrencyOperation currencyOperation(m_sqlConnection);
		if (m_pressedBtnIdentifier == ID_CHANGE_DOLLAR_RATE)
		{
			currencyOperation.setNewDollarRate(newCurrencyValue);
			TCHAR* dollarRate = currencyOperation.getDollarRate();
			SetWindowText(m_windowWithInfoAboutRate, dollarRate);
			return TRUE;
		}
		else if (m_pressedBtnIdentifier == ID_CHANGE_EURO_RATE)
		{
			currencyOperation.setNewEuroRate(newCurrencyValue);
			TCHAR* euroRate = currencyOperation.getEuroRate();
			SetWindowText(m_windowWithInfoAboutRate, euroRate);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

LRESULT ChangeCurrencyRateForm::RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
	case WM_COMMAND:
	{
		switch (HIWORD(wParam))
		{
		case EN_UPDATE:
		{
			if ((HWND)lParam == m_editForNewCurrencyRate->getEditHandle())
			{
				size_t len = SendMessage((HWND)lParam, WM_GETTEXTLENGTH, 0, 0);
				TCHAR* pText = m_editForNewCurrencyRate->getTextFromEdit();
				switch (pText[len - 1])
				{
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case '0':
				case '.':
				{
					break;
				}
				default:
				{
					MessageBox(NULL, L"Можно вводить только цифры и десятичную точку", L"Ошибка!!!", MB_OK);
					SendMessage((HWND)lParam, EM_SETSEL, len - 1, len);
					SendMessage((HWND)lParam, WM_KEYDOWN, VK_DELETE, 0);
					SetFocus((HWND)lParam);
					break;
				}
				}
			}
			
			break;
		}
		default:
		{
			break;
		}
		}
		switch (LOWORD(wParam))
		{
			case ID_CANCEL_AUXILIARY_BTN:
			{
				EnableWindow(m_WndToDisable, TRUE);
				SendMessage(m_auxiliaryParent, INF_OPERATION_COMPLETE, ID_CHANGE_CURRENCY_RATE, 0);
				SendMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
			case ID_CHANGE_CURRENCY_RATE:
			{
				if (changeCurrencyRate())
				{
					EnableWindow(m_WndToDisable, TRUE);
					SendMessage(m_auxiliaryParent, INF_OPERATION_COMPLETE, ID_CHANGE_CURRENCY_RATE, 0);
					SendMessage(hWnd, WM_DESTROY, 0, 0);
				}
				break;
			}
			default:
			{
				break;
			}
		}
		break;
	}
	case WM_DESTROY:
	{
		
		DestroyWindow(hWnd);

		break;
	}

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
