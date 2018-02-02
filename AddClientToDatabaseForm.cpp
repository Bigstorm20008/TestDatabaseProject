#include "AddClientToDatabaseForm.h"


AddClientToDatabaseForm::AddClientToDatabaseForm(HWND windowToDisable, HWND parent, TCHAR* captionText) 
	: AuxiliaryWindowTemplate(windowToDisable,parent,600,500,captionText)
{
	m_addClientToDatabaseBtn = nullptr;
	m_cancelBtn = nullptr;
	m_nicknameEdit = nullptr;
	m_lastnameEdit = nullptr;
	m_firstnameEdit = nullptr;
	m_patronymicEdit = nullptr;
	m_clientStatus = nullptr;
	m_windowForClientImage = nullptr;
	m_editForAddPhoneNumber = nullptr;
	createControlsForWindow();
}


AddClientToDatabaseForm::~AddClientToDatabaseForm()
{
	if (m_addClientToDatabaseBtn)
	{
		delete m_addClientToDatabaseBtn;
		m_addClientToDatabaseBtn = nullptr;
	}
	if (m_cancelBtn)
	{
		delete m_cancelBtn;
		m_cancelBtn = nullptr;
	}
	if (m_nicknameEdit)
	{
		delete m_nicknameEdit;
		m_nicknameEdit = nullptr;
	}
	if (m_lastnameEdit)
	{
		delete m_lastnameEdit;
		m_lastnameEdit = nullptr;
	}
	if (m_firstnameEdit)
	{
		delete m_firstnameEdit;
		m_firstnameEdit = nullptr;
	}
	if (m_patronymicEdit)
	{
		delete m_patronymicEdit;
		m_patronymicEdit = nullptr;
	}
	if (m_clientStatus)
	{
		delete m_clientStatus;
		m_clientStatus = nullptr;
	}
	if (m_windowForClientImage)
	{
		delete m_windowForClientImage;
		m_windowForClientImage = nullptr;
	}
	if (m_editForAddPhoneNumber)
	{
		delete m_editForAddPhoneNumber;
		m_editForAddPhoneNumber = nullptr;
	}
	if (m_additionalInfoAboutClient)
	{
		delete m_additionalInfoAboutClient;
		m_additionalInfoAboutClient = nullptr;
	}

}

void AddClientToDatabaseForm::createControlsForWindow()
{
	
	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
		                     DEFAULT_CHARSET,
		                     0, 0, 0, VARIABLE_PITCH,
		                     L"Time New Romans");
	RECT parentRC;
	GetClientRect(m_auxiliaryWnd, &parentRC);
	int btnWidth = 130;
	int btnHeight = 25;
	int xPos = parentRC.right - btnWidth - offsetsBetweenWindow;
	int yPos = parentRC.bottom - btnHeight - offsetsBetweenWindow;

	HWND btn = CreateWindow(TEXT("BUTTON"),
							TEXT("Добавить в базу"),
							WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
							xPos, yPos,
							btnWidth, btnHeight,
							m_auxiliaryWnd,
							(HMENU)ID_ADD_CLIENT_TO_BASE_BTN,
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

	xPos = offsetsBetweenWindow;
	yPos = 35;
	int editWidth = 200;
	int editHeight = 20;
	m_nicknameEdit = new EditControlTemplate;
	m_nicknameEdit->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER);
	m_nicknameEdit->setFontForEdit(hFont);
	m_nicknameEdit->createDescriptionForEdit(TEXT("Nickname"));
	m_nicknameEdit->setFocusOnEdit();

	yPos += editHeight + descriptionForControlHeight + offsetsBetweenWindow;
	m_lastnameEdit = new EditControlTemplate;
	m_lastnameEdit->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER);
	m_lastnameEdit->setFontForEdit(hFont);
	m_lastnameEdit->createDescriptionForEdit(TEXT("Фамилия"));

	yPos += editHeight + descriptionForControlHeight + offsetsBetweenWindow;
	m_firstnameEdit = new EditControlTemplate;
	m_firstnameEdit->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER);
	m_firstnameEdit->setFontForEdit(hFont);
	m_firstnameEdit->createDescriptionForEdit(TEXT("Имя"));

	yPos += editHeight + descriptionForControlHeight + offsetsBetweenWindow;
	m_patronymicEdit = new EditControlTemplate;
	m_patronymicEdit->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER);
	m_patronymicEdit->setFontForEdit(hFont);
	m_patronymicEdit->createDescriptionForEdit(TEXT("Отчество"));

	yPos += editHeight + descriptionForControlHeight + offsetsBetweenWindow;
	int dropDownListWidth = editWidth;
	int dropDownListHeight = 20;
	m_clientStatus = new DropDownListTemplate(m_auxiliaryWnd, xPos, yPos, dropDownListWidth, dropDownListHeight, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE);
	m_clientStatus->createDescriptionForDropDownList(TEXT("Статус клиента"));
	m_clientStatus->addNewItemToDropBox(TEXT("VIP"));

	yPos += dropDownListHeight + descriptionForControlHeight + offsetsBetweenWindow;
	createGroupForAddPhoneNumbers(xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER);

	int clientImageWidth = imageWidthForApplication;
	int clientImageHeight = imageHeightForApplication;
	xPos = parentRC.right - clientImageWidth - offsetsBetweenWindow;
	yPos = parentRC.top + windowCaptionHeight + offsetsBetweenWindow;
	TCHAR* defaultImageLocation = TEXT("D:\\Clients\\defaultImage.bmp");
	m_windowForClientImage = new ImageTemplate(xPos,yPos,clientImageWidth,clientImageHeight,m_auxiliaryWnd,defaultImageLocation);
	m_windowForClientImage->createButtonForImage(TEXT("Указать расположение"), ID_OPEN_WINDOW_EXPLORER);

	editWidth = clientImageWidth;
	editHeight = 100;
	yPos += clientImageHeight + 40;
	m_additionalInfoAboutClient = new EditControlTemplate;
	m_additionalInfoAboutClient->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE);
	m_additionalInfoAboutClient->createDescriptionForEdit(TEXT("Дополнительная информация о клиенте"));
	m_additionalInfoAboutClient->setFontForEdit(hFont);

}

void AddClientToDatabaseForm::createGroupForAddPhoneNumbers(int xPos, int yPos, int editWidth, int editHeight,UINT editStyle)
{
	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		L"Time New Romans");
	m_editForAddPhoneNumber = new EditControlTemplate;
	m_editForAddPhoneNumber->createEditControl(m_auxiliaryWnd, xPos, yPos, editWidth, editHeight, editStyle);
	m_editForAddPhoneNumber->createDescriptionForEdit(TEXT("Введите номер телефона"));
	m_editForAddPhoneNumber->setFontForEdit(hFont);

	HWND edit = m_editForAddPhoneNumber->getEditHandle();
	RECT editRc;
	GetWindowRect(edit, &editRc);
	POINT tmp;
	tmp.x = editRc.right;
	tmp.y = editRc.bottom;
	ScreenToClient(m_auxiliaryWnd, &tmp);

	int btnWidth = 110;
	int btnHeight = 22;
	POINT buttonPosition;
	buttonPosition.x = tmp.x - btnWidth;
	buttonPosition.y = tmp.y;

	HWND btn = CreateWindow(TEXT("BUTTON"),
		                    TEXT("Добавить номер"),
				            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				            buttonPosition.x,buttonPosition.y,
				            btnWidth,btnHeight,
				            m_auxiliaryWnd,
				            (HMENU)ID_ADD_PHONE_NUMBER_TO_LIST,
				            (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
				            NULL);
	
	SendMessage(btn, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

	tmp.x = editRc.left;
	tmp.y = editRc.bottom;
	ScreenToClient(m_auxiliaryWnd, &tmp);

	int listWidth = editWidth;
	int listHeight = 70;
	int listXPos = tmp.x;
	int listYPos = tmp.y + btnHeight;
	m_listForPhoneNumbers = CreateWindow(TEXT("LISTBOX"),
		                                 NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD,
										 listXPos, listYPos,
										 listWidth, listHeight,
										 m_auxiliaryWnd,
										 (HMENU)NULL,
										 (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
										 NULL);
	SendMessage(m_listForPhoneNumbers, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

	RECT listRC;
	GetWindowRect(m_listForPhoneNumbers, &listRC);
	tmp.x = listRC.right;
	tmp.y = listRC.bottom;
	ScreenToClient(m_auxiliaryWnd, &tmp);
	
	buttonPosition.x = tmp.x - btnWidth;
	buttonPosition.y = tmp.y;
	btn = CreateWindow(TEXT("BUTTON"),
		               TEXT("Удалить номер"),
		               WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		               buttonPosition.x, buttonPosition.y,
		               btnWidth, btnHeight,
		               m_auxiliaryWnd,
		               (HMENU)ID_REMOVE_PHONE_NUMBER_FROM_LIST,
		               (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		               NULL);
	SendMessage(btn, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

}

BOOL AddClientToDatabaseForm::checkData()
{
	TCHAR* nickname = m_nicknameEdit->getTextFromEdit();
	if (_tcscmp(nickname, TEXT("")) == 0)
	{
		MessageBox(m_auxiliaryWnd, TEXT("Поле Nickname обязательно для заполнения"), TEXT("Ошибка при добавлении в базу данных"), MB_OK);
		return FALSE;
	}
	TCHAR* imageLocation = m_windowForClientImage->getImageLocation();
	if (_tcscmp(imageLocation, TEXT("")) == 0)
	{
		MessageBox(m_auxiliaryWnd, TEXT("Выберите фотографию для клиента"), TEXT("Ошибка при добавлении в базу данных"), MB_OK);
		return FALSE;
	}
	TCHAR* clientStatus = m_clientStatus->getSelectedItemFromDropDownList();
	if (_tcscmp(clientStatus, TEXT("")) == 0)
	{
		MessageBox(m_auxiliaryWnd, TEXT("Укажите статус для нового клиента"), TEXT("Ошибка при добавлении в базу данных"), MB_OK);
		return FALSE;
	}
	TCHAR* lastname = m_lastnameEdit->getTextFromEdit();
	TCHAR* firstname = m_firstnameEdit->getTextFromEdit();
	TCHAR* patronymic = m_patronymicEdit->getTextFromEdit();
	TCHAR* additionalInfoAboutClient = m_additionalInfoAboutClient->getTextFromEdit();
	saveNewClientInDatabase();
	return TRUE;
}

void AddClientToDatabaseForm::saveNewClientInDatabase()
{
	

	
}
void AddClientToDatabaseForm::addPhoneNumberToList()
{
	TCHAR* phoneNumber = m_editForAddPhoneNumber->getTextFromEdit();
	size_t len = _tcslen(phoneNumber);
	if (len != 10)
	{
		MessageBox(m_auxiliaryWnd, TEXT("Введите корректный номер телефона (0ХХХХХХХХХ всего 10 цифр)"), TEXT("Ошибка при добавлении номера телефона"), MB_OK);
	}
	else
	{
		SendMessage(m_listForPhoneNumbers, LB_ADDSTRING, 0, (LPARAM)phoneNumber);
		m_editForAddPhoneNumber->setNewTextForEdit(TEXT(""));
		m_editForAddPhoneNumber->setFocusOnEdit();
	}
}

void AddClientToDatabaseForm::removePhoneNumberFromList()
{
	int index = SendMessage(m_listForPhoneNumbers, LB_GETCURSEL, 0, 0);
	SendMessage(m_listForPhoneNumbers, LB_DELETESTRING, index, 0);
}

void AddClientToDatabaseForm::openExplorerForImageSelect()
{
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];
	TCHAR szFileName[MAX_PATH];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ZeroMemory(szFile, MAX_PATH);
	ZeroMemory(szFileName, MAX_PATH);
	//initialise OPENFILENAME
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_auxiliaryWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = NULL;
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrDefExt = L"";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	GetOpenFileName(&ofn);

	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, ofn.lpstrFile, IMAGE_BITMAP, imageWidthForApplication, imageHeightForApplication, LR_LOADFROMFILE);
	if (hBitmap)
	{
		m_windowForClientImage->setNewImageLocationAndLoadIt(ofn.lpstrFile);
	}
}

LRESULT AddClientToDatabaseForm::RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
			break;
		}
		case ID_OPEN_WINDOW_EXPLORER:
		{
			openExplorerForImageSelect();
			break;
		}
		case ID_ADD_PHONE_NUMBER_TO_LIST:
		{
			addPhoneNumberToList();
			break;
		}
		case ID_REMOVE_PHONE_NUMBER_FROM_LIST:
		{
			removePhoneNumberFromList();
			break;
		}
		case ID_ADD_CLIENT_TO_BASE_BTN:
		{
			if (checkData())
			{
				EnableWindow(m_WndToDisable, TRUE);
				SendMessage(m_WndToDisable, INF_DATABASE_CONNECTED, 0, 0);
				SendMessage(hWnd, WM_DESTROY, 0, 0);
			}
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
