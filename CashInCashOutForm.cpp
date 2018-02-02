#include "CashInCashOutForm.h"


CashInCashOutForm::CashInCashOutForm(HWND windowToDisable, HWND parentForWindow, UINT pressedBtnIdentifier, Person* selectedPerson, CSqlFramework* sqlConnection,TCHAR* dateInCasino)
	: AuxiliaryWindowTemplate(windowToDisable,parentForWindow, 640, 300, NULL)
{
	m_sqlConnection = sqlConnection;
	m_dateInCasino = dateInCasino;
	m_pressedBtnIdentifier = pressedBtnIdentifier;
	m_selectedPerson = selectedPerson;
	m_editForEnterValueOfCashInCashOut = nullptr;
	m_dateInCasino = dateInCasino;
	createControlsForWindow();
}


CashInCashOutForm::~CashInCashOutForm()
{
	if (m_clientPhoto)
	{
		delete m_clientPhoto;
		m_clientPhoto = nullptr;
	}
	if (m_editForEnterValueOfCashInCashOut)
	{
		delete m_editForEnterValueOfCashInCashOut;
		m_editForEnterValueOfCashInCashOut = nullptr;
	}
	if (m_dateInCasino)
	{
		m_dateInCasino = nullptr;
	}
}


void CashInCashOutForm::createControlsForWindow()
{
	TCHAR* windowCaption = nullptr;
	UINT identifierBtnForForm = NULL;
	switch (m_pressedBtnIdentifier)
	{
		case ID_CASH_IN_BUTTON:
		{
			windowCaption = TEXT("Cash In");
			identifierBtnForForm = ID_SAVE_CASHIN_IN_DATABASE_BUTTON;
			break;
		}
		case ID_CASH_OUT_BUTTON:
		{
			windowCaption = TEXT("Cash Out");
			identifierBtnForForm = ID_SAVE_CASHOUT_IN_DATABASE_BUTTON;
			break;
		}
		default:
		{
			break;
		}
	}
    SetWindowText(m_captionWnd, windowCaption);

	RECT parentRC;
	GetClientRect(m_auxiliaryWnd, &parentRC);
	int btnWidth = 130;
	int btnHeight = 25;
	int xPos = parentRC.right - btnWidth - offsetsBetweenWindow;
	int yPos = parentRC.bottom - btnHeight - offsetsBetweenWindow;

	HWND btn = CreateWindow(TEXT("BUTTON"),
							windowCaption,
							WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
							xPos, yPos,
							btnWidth, btnHeight,
							m_auxiliaryWnd,
							(HMENU)identifierBtnForForm,
							(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
							NULL);

	xPos -= btnWidth + offsetsBetweenWindow;
	btn = CreateWindow(TEXT("BUTTON"),
					   TEXT("ќтмена"),
					   WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
					   xPos, yPos,
					   btnWidth, btnHeight,
					   m_auxiliaryWnd,
					   (HMENU)ID_CANCEL_AUXILIARY_BTN,
					   (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
					   NULL);

	xPos = 0;
	yPos = windowCaptionHeight;
	int imageWidth = imageWidthForApplication;
	int imageHeight = imageHeightForApplication;
	m_clientPhoto = new ImageTemplate(xPos, yPos, imageWidth, imageHeight, m_auxiliaryWnd, m_selectedPerson->getImageLocation());

	xPos += imageWidth + offsetsBetweenWindow;
	yPos += offsetsBetweenWindow;
	int staticWidth = (parentRC.right - parentRC.left) - imageWidth - 2*offsetsBetweenWindow;
	int staticHeight = 25;

	CreateWindow(TEXT("STATIC"),
		         ((Client*)m_selectedPerson)->getNickname(),
		         WS_CHILD | WS_VISIBLE | SS_LEFT,
		         xPos, yPos,
				 staticWidth, staticHeight,
		         m_auxiliaryWnd,
		         (HMENU)NULL,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);

	yPos += staticHeight;
	CreateWindow(TEXT("STATIC"),
		         m_selectedPerson->getLastname(),
				 WS_CHILD | WS_VISIBLE | SS_LEFT,
		         xPos, yPos,
		         staticWidth, staticHeight,
		         m_auxiliaryWnd,
		         (HMENU)NULL,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);

	yPos += staticHeight;
	CreateWindow(TEXT("STATIC"),
		         m_selectedPerson->getFirstname(),
				 WS_CHILD | WS_VISIBLE | SS_LEFT,
		         xPos, yPos,
		         staticWidth, staticHeight,
		         m_auxiliaryWnd,
		         (HMENU)NULL,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);

	yPos += staticHeight;
	CreateWindow(TEXT("STATIC"),
		         m_selectedPerson->getPatronymic(),
				 WS_CHILD | WS_VISIBLE | SS_LEFT,
		         xPos, yPos,
		         staticWidth, staticHeight,
		         m_auxiliaryWnd,
		         (HMENU)NULL,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);

	yPos += 10 * offsetsBetweenWindow;
	CreateWindow(TEXT("STATIC"),
		         TEXT("¬ведите сумму в долларах"),
		         WS_CHILD | WS_VISIBLE | SS_CENTER,
		         xPos, yPos,
		         staticWidth, staticHeight,
		         m_auxiliaryWnd,
		         (HMENU)NULL,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);

	int editWidth = 60;
	int editHeight = 20;
	xPos = ((parentRC.right - imageWidth) / 2 - editWidth / 2) + imageWidth;
	yPos += staticHeight;
	m_editForEnterValueOfCashInCashOut = new EditControlTemplate();
	m_editForEnterValueOfCashInCashOut->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER);
	m_editForEnterValueOfCashInCashOut->setFocusOnEdit();
}

BOOL CashInCashOutForm::checkData(UINT pressedBtnIdentifier)
{
	TCHAR* stringValue = m_editForEnterValueOfCashInCashOut->getTextFromEdit();
	if (_tcscmp(stringValue, TEXT("")) == 0)
	{
		MessageBox(m_auxiliaryWnd, TEXT("”кажите значение"), TEXT("ќшибка сохранени€ в базе"), MB_OK);
		return FALSE;
	}
	else
	{
		saveCashInCashOutInDatabase(pressedBtnIdentifier, stringValue);
		return TRUE;
	}
}

void CashInCashOutForm::saveCashInCashOutInDatabase(UINT pressedBtnIdentifier, TCHAR* value)
{
	TCHAR* sqlCommand = nullptr;
	TCHAR stringClientID[4];
	_itot_s(m_selectedPerson->getPersonId(), stringClientID, 4, 10);
	SQLTCHAR* parameterArray[] = { stringClientID, m_dateInCasino, value };
	SQLHANDLE statementHandle = SQL_NULL_HANDLE;

	switch (pressedBtnIdentifier)
	{
		case ID_SAVE_CASHIN_IN_DATABASE_BUTTON:
		{
			sqlCommand = TEXT("INSERT INTO [dbo].[AllCashIn] ([ClientID],[CashInDate],[CashInValue]) VALUES (?,?,?)");
			statementHandle = m_sqlConnection->ExecutePrepearedQuery(sqlCommand, parameterArray);
			break;
		}
		case ID_SAVE_CASHOUT_IN_DATABASE_BUTTON:
		{
			sqlCommand = TEXT("INSERT INTO [dbo].[AllCashOut] ([ClientID],[CashOutDate],[CashOutValue]) VALUES (?,?,?)");
			statementHandle = m_sqlConnection->ExecutePrepearedQuery(sqlCommand, parameterArray);
			break;
		}
		default:
			break;
	}

	if (statementHandle)
	{
		m_sqlConnection->FreeBinding(statementHandle);
	}
	EnableWindow(m_WndToDisable, TRUE);
	SendMessage(m_auxiliaryParent, INF_OPERATION_COMPLETE, INF_CASHIN_CASHOUT_COMPLETE, 0);
}


LRESULT CashInCashOutForm::RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
				EnableWindow(m_WndToDisable, TRUE);
				SendMessage(m_auxiliaryParent, INF_OPERATION_COMPLETE, INF_CASHIN_CASHOUT_COMPLETE, 0);
				SendMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
			case ID_SAVE_CASHOUT_IN_DATABASE_BUTTON:
			{
				if (checkData(ID_SAVE_CASHOUT_IN_DATABASE_BUTTON))
				{
					DestroyWindow(hWnd);
				}
				break;
			}
			case ID_SAVE_CASHIN_IN_DATABASE_BUTTON:
			{
				if (checkData(ID_SAVE_CASHIN_IN_DATABASE_BUTTON))
				{
					DestroyWindow(hWnd);
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
		EnableWindow(m_WndToDisable, TRUE);
		DestroyWindow(hWnd);

		break;
	}

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
