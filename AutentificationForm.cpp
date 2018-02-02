#include "AutentificationForm.h"


AutentificationForm::AutentificationForm(HWND windowToDisable, HWND parent, CSqlFramework* sqlConnection)
	:AuxiliaryWindowTemplate(windowToDisable, parent, 300, 230, TEXT("Аутентификация"))
{
	m_UserName = nullptr;
	m_Password = nullptr;
	m_sqlConnection = sqlConnection;
	createControlsForWindow();
}


AutentificationForm::~AutentificationForm()
{
	if (m_UserName)
	{
		delete m_UserName;
		m_UserName = nullptr;
	}
	if (m_Password)
	{
		delete m_Password;
		m_Password = nullptr;
	}
}

void AutentificationForm::createControlsForWindow()
{
	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
		                     DEFAULT_CHARSET,
		                     0, 0, 0, VARIABLE_PITCH,
		                     L"Time New Romans");

	RECT parentRC;
	GetClientRect(m_auxiliaryWnd, &parentRC);
	int btnWidth = 90;
	int btnHeight = 22;
	int xPos = parentRC.right - btnWidth - 5;
	int yPos = parentRC.bottom - btnHeight - 5;

	HWND btn = CreateWindow(TEXT("BUTTON"),
		                    TEXT("Продолжить"),
		                    WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		                    xPos, yPos,
		                    btnWidth, btnHeight,
		                    m_auxiliaryWnd,
		                    (HMENU)ID_CONTINUE_AUTENTIFICATION_BTN,
		                    (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                    NULL);
	SendMessage(btn, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

	xPos -= btnWidth + 5;
	btn = CreateWindow(TEXT("BUTTON"),
		               TEXT("Отмена"),
		               WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		               xPos, yPos,
		               btnWidth, btnHeight,
		               m_auxiliaryWnd,
		               (HMENU)ID_CANCEL_AUXILIARY_BTN,
		               (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		               NULL);
	SendMessage(btn, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

	xPos = parentRC.left;
	yPos = parentRC.top + windowCaptionHeight + offsetsBetweenWindow;
	int staticTextWidth = parentRC.right - parentRC.left;
	int staticTextHeight = 40;
	HWND staticText = CreateWindow(TEXT("STATIC"),
		                           TEXT("Для продолжения необходимо ввести имя пользователя и пароль"),
		                           WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		                           xPos, yPos,
								   staticTextWidth, staticTextHeight,
		                           m_auxiliaryWnd,
		                           (HMENU)NULL,
		                           (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                           NULL);

	int editWidth = 200;
	int editHeight = 20;
	xPos = (parentRC.right - parentRC.left) / 2 - editWidth / 2;
	yPos += staticTextHeight + 6*offsetsBetweenWindow;
	m_UserName = new EditControlTemplate;
	m_UserName->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER);
	m_UserName->createDescriptionForEdit(TEXT("Имя пользователя"));
	m_UserName->setFontForEdit(hFont);
	m_UserName->setNewTextForEdit(TEXT("Zhmenka"));
	

	yPos += editHeight + descriptionForControlHeight + offsetsBetweenWindow;
	m_Password = new EditControlTemplate;
	m_Password->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD);
	m_Password->createDescriptionForEdit(TEXT("Пароль"));
	m_Password->setFontForEdit(hFont);
	m_Password->setNewTextForEdit(TEXT("47dim9175rty"));
	
	
}

BOOL AutentificationForm::connectToDatabase()
{
	TCHAR* userName = m_UserName->getTextFromEdit();
	if (_tcscmp(userName, TEXT("")) == 0)
	{
		MessageBox(m_auxiliaryWnd, TEXT("Введите имя пользователя"), TEXT("Ошибка при подключении"), MB_OK);
		return FALSE;
	}
	TCHAR* password = m_Password->getTextFromEdit();
	if (_tcscmp(password, TEXT("")) == 0)
	{
		MessageBox(m_auxiliaryWnd, TEXT("Введите пароль"), TEXT("Ошибка при подключении"), MB_OK);
		return FALSE;
	}
	if (m_sqlConnection->OpenConnection(TEXT("Malinka"), userName, password))
	{

		return TRUE;
	}
	else
	{
		MessageBox(m_auxiliaryWnd, TEXT("Неверное имя пользователя или пароль"), TEXT("Ошибка при подключении"), MB_OK);
		return FALSE;
	}
}
LRESULT AutentificationForm::RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
		switch (LOWORD(wParam))
		{
			case ID_CANCEL_AUXILIARY_BTN:
			{
				SendMessage(hWnd, WM_DESTROY, 0, 0);
				PostQuitMessage(0);
				break;
			}
			case ID_CONTINUE_AUTENTIFICATION_BTN:
			{
				if (connectToDatabase())
				{
					EnableWindow(m_WndToDisable, TRUE);
					SendMessage(m_auxiliaryParent, INF_DATABASE_CONNECTED, 0, 0);
					SendMessage(hWnd, WM_DESTROY, 0, 0);
				}
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