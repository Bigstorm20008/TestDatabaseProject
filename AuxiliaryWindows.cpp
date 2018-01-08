#include "AuxiliaryWindows.h"


AuxiliaryWindows::AuxiliaryWindows()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	mainWnd = FindWindow(szClassName, szWindowName);
	
}


AuxiliaryWindows::~AuxiliaryWindows()
{
}

void AuxiliaryWindows::createAuxiliaryWindow(int width, int height, TCHAR* captionText)
{
	RECT mainRC;
	GetClientRect(mainWnd, &mainRC);
	int xPos = mainRC.right / 2 - width / 2;
	int yPos = mainRC.bottom / 2 - height / 2;

	WNDCLASSEX wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);
	wc.lpfnWndProc = AuxiliaryWndProc;
	wc.lpszClassName = TEXT("AuxiliaryWindow");
	wc.lpszMenuName = NULL;
	wc.style =  CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);

	auxiliaryWnd = CreateWindow(wc.lpszClassName,
		                       NULL,
		                       WS_CHILD | WS_VISIBLE | WS_BORDER | WS_OVERLAPPED,
		                       xPos, yPos,
		                       width, height,
		                       mainWnd,
		                       NULL,
		                       (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                       NULL);

	HWND staticCaption = CreateWindow(TEXT("STATIC"),
								      captionText,
		                              WS_CHILD | WS_VISIBLE | SS_CENTER | SS_EDITCONTROL,
		                              0, 0,
		                              width, 20,
									  auxiliaryWnd,
		                              (HMENU)ID_STATIC_CAPTION,
		                              (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                              NULL);
}
void AuxiliaryWindows::createAddNewClientWnd()
{
	RECT mainRC;
	GetClientRect(mainWnd, &mainRC);
	int auxiliaryWndWidth = mainRC.right / 2;
	int auxiliaryWndHeight = static_cast<int>(mainRC.bottom / 1.5);

	createAuxiliaryWindow(auxiliaryWndWidth, auxiliaryWndHeight, TEXT("Добавление нового клиента в базу данных"));
	
	RECT hwndRC;
	GetClientRect(auxiliaryWnd, &hwndRC);
	int btnWidth = 150;
	int btnHeight = 25;
	int xPos = hwndRC.right - btnWidth - 10;
	int yPos = hwndRC.bottom - btnHeight - 10;
	HWND okBtn = CreateWindow(TEXT("BUTTON"),
		                      TEXT("Добавить в базу"),
							  WS_CHILD | WS_VISIBLE |BS_DEFPUSHBUTTON,
							  xPos,yPos,
							  btnWidth, btnHeight,
							  auxiliaryWnd,
							  (HMENU)ID_ADD_TO_BASE_BTN,
							  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), 
							  NULL);
	xPos -= btnWidth + 10;

	HWND cancelBtn = CreateWindow(TEXT("BUTTON"),
		                          TEXT("Отмена"),
		                          WS_CHILD  | WS_VISIBLE | BS_DEFPUSHBUTTON,
		                          xPos, yPos,
		                          btnWidth, btnHeight,
								  auxiliaryWnd,
								  (HMENU)ID_CANCEL_AUXILIARY_BTN,
		                          (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                          NULL);
	int xPosForEdit = 10;
	int yPosForEdit = 40;
	int widthForEdit = 200;
	int heightForEdit = 20;
	int offsetBetweenWnd = 10;
	int descriptionHeight = 15;
	createEditBoxWithDescription(auxiliaryWnd, TEXT("Nickname*"), ID_EDITBOX_FOR_NICKNAME, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit += heightForEdit + offsetBetweenWnd + descriptionHeight;
	createEditBoxWithDescription(auxiliaryWnd, TEXT("Фамилия"), ID_EDITBOX_FOR_LASTNAME, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit += heightForEdit + offsetBetweenWnd + descriptionHeight;
	createEditBoxWithDescription(auxiliaryWnd, TEXT("Имя"), ID_EDITBOX_FOR_FIRSTNAME, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit += heightForEdit + offsetBetweenWnd + descriptionHeight;
	createEditBoxWithDescription(auxiliaryWnd, TEXT("Отчество"), ID_EDITBOX_FOR_PATRONYMIC, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit += heightForEdit + offsetBetweenWnd + descriptionHeight;
	createEditBoxWithDescription(auxiliaryWnd, TEXT("Дата рождения (чч/мм/гггг)"), ID_EDITBOX_FOR_BIRTHDAY, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit += heightForEdit + offsetBetweenWnd + descriptionHeight;
	createComboBoxForClientStatusSelect(auxiliaryWnd, ID_CB_STATUS_SELECT, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);

	yPosForEdit += heightForEdit + offsetBetweenWnd + descriptionHeight;
	createEditBoxWithDescription(auxiliaryWnd, TEXT("Введите номер телефона"), ID_EDITBOX_FOR_PHONE, xPosForEdit, yPosForEdit, widthForEdit, heightForEdit);
	HWND editForPhone = GetDlgItem(auxiliaryWnd, ID_EDITBOX_FOR_PHONE);
	SetWindowLong(editForPhone, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER |ES_NUMBER);
	RECT rcEdit;
	GetWindowRect(editForPhone, &rcEdit);
	POINT tmp;
	tmp.x = rcEdit.right;
	tmp.y = rcEdit.bottom;
	ScreenToClient(auxiliaryWnd, &tmp);
	int btnPhoneWidth = 105;
	int btnPhoneHeight = 22;
	int btnPhoneXPos = tmp.x - btnPhoneWidth;
	int btnPhoneYPos = tmp.y;
	HWND addPhoneBtn = CreateWindow(TEXT("BUTTON"), TEXT("Добавить номер"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		btnPhoneXPos, btnPhoneYPos, btnPhoneWidth, btnPhoneHeight, auxiliaryWnd, (HMENU)ID_BTN_ADD_PHONE, (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), NULL);
	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		L"Time New Romans");
	SendMessage(addPhoneBtn, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
	
	yPosForEdit += heightForEdit + offsetBetweenWnd + descriptionHeight + btnPhoneHeight;
	HWND hList = CreateWindow(TEXT("LISTBOX"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD,
		xPosForEdit, yPosForEdit, 200, heightForEdit + 10 + 20, auxiliaryWnd, (HMENU)ID_LB_FOR_PHONENUMBER, (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), NULL);
	createDescriptionForControl(auxiliaryWnd, hList, TEXT("Известные номера телефонов"));

	createGroupForImgWindow(auxiliaryWnd, ID_IMAGE_WND_FOR_NEW_CLIENT, ID_BTN_ADD_PHOTO, ID_EDITBOX_FOR_IMAGE);

}


void AuxiliaryWindows::createCashInCashOutWindow(Client* currentClient,UINT btnIdentifier)
{
	TCHAR* btnTitle = nullptr;
	UINT cashInCashOutIdentifier;
	if (btnIdentifier == ID_CASH_IN_BTN)
	{
		TCHAR* text = TEXT("Cash In");
		size_t len = _tcslen(text) + 1;
		btnTitle = new TCHAR[len];
		memset(btnTitle, 0, len*sizeof(TCHAR));
		_tcscpy_s(btnTitle, len, text);
		cashInCashOutIdentifier = ID_CASH_IN__AUXILIARY_BTN;

	}
	if (btnIdentifier == ID_CASH_OUT_BTN)
	{
		TCHAR* text = TEXT("Cash Out");
		size_t len = _tcslen(text) + 1;
		btnTitle = new TCHAR[len];
		memset(btnTitle, 0, len*sizeof(TCHAR));
		_tcscpy_s(btnTitle, len, text);
		cashInCashOutIdentifier = ID_CASH_OUT_AUXILIARY_BTN;

	}
	RECT mainRC;
	GetClientRect(mainWnd, &mainRC);
	int auxiliaryWndWidth = mainRC.right / 2;
	int auxiliaryWndHeight = static_cast<int>(mainRC.bottom / 3);

	createAuxiliaryWindow(auxiliaryWndWidth, auxiliaryWndHeight, btnTitle);

	RECT parentRC;
	GetClientRect(auxiliaryWnd, &parentRC);
	int btnWidth = 100;
	int btnHeight = 25;
	int btnXPos = parentRC.right - btnWidth - offsetBetweenWindow;
	int btnYPos = parentRC.bottom - btnHeight - offsetBetweenWindow;
	CreateWindow(TEXT("BUTTON"),
		         btnTitle,
		         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		         btnXPos, btnYPos,
		         btnWidth, btnHeight,
		         auxiliaryWnd,
				 (HMENU)cashInCashOutIdentifier,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);
	delete[]btnTitle;
	btnTitle = nullptr;

	btnXPos -= btnWidth + offsetBetweenWindow;
	CreateWindow(TEXT("BUTTON"),
		         TEXT("Отмена"),
		         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		         btnXPos, btnYPos,
		         btnWidth, btnHeight,
		         auxiliaryWnd,
		         (HMENU)ID_CANCEL_AUXILIARY_BTN,
		         (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		         NULL);

	int descriptionHeight = 15;
	int editBox_width = 150;
	int editBox_height = 20;
	int editBox_xPos = parentRC.right - editBox_width - offsetBetweenWindow;
	int editBox_yPos = parentRC.bottom/2 - offsetBetweenWindow;
	createEditBoxWithDescription(auxiliaryWnd, TEXT("Доллары"), ID_EDITBOX_FOR_DOLLARS_VALUE, editBox_xPos, editBox_yPos, editBox_width, editBox_height);
	HWND editControl = GetDlgItem(auxiliaryWnd, ID_EDITBOX_FOR_DOLLARS_VALUE);
	SetWindowLong(editControl, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER);

	editBox_yPos += editBox_height + offsetBetweenWindow + descriptionHeight;
	createEditBoxWithDescription(auxiliaryWnd, TEXT("Гривны"), ID_EDITBOX_FOR_GRIVNA_VALUE, editBox_xPos, editBox_yPos, editBox_width, editBox_height);
	editControl = GetDlgItem(auxiliaryWnd, ID_EDITBOX_FOR_GRIVNA_VALUE);
	SetWindowLong(editControl, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER);

	int captionHeight = 20;
	int imageXPos = 0;
	int imageYPos = captionHeight;
	int imageWidthForWnd = imageWidth / 1.5;
	int imageHeightforWnd = imageHeight / 1.5;
	HWND imgWindow = CreateWindow(TEXT("STATIC"),
		                          NULL,
								  WS_CHILD | WS_BORDER | SS_BITMAP,
		                          imageXPos,
		                          imageYPos,
								  imageWidthForWnd,    //is not required if SS_BITMAP(width set by BITMAP)
								  imageHeightforWnd,    //is not required if SS_BITMAP(height set by BITMAP)
								  auxiliaryWnd,
								  (HMENU)ID_IMAGE_CASHIN_CASHOUT_WND,
		                          (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                          NULL);
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, currentClient->getImageLocation(), IMAGE_BITMAP, imageWidthForWnd, imageHeightforWnd, LR_LOADFROMFILE);
	SendMessage(imgWindow, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	ShowWindow(imgWindow, SW_NORMAL);

	int descForPersonXPos = imageXPos + imageWidthForWnd + offsetBetweenWindow;
	int descForPersonYPos = imageYPos;
	int descForPersonWidth = 150;
	int descForPersonHeight = 25;
	HWND nickNameWnd = CreateWindow(TEXT("STATIC"),
		                            currentClient->getNickname(),
		                            WS_CHILD | WS_VISIBLE,
									descForPersonXPos,
									descForPersonYPos,
									descForPersonWidth,
									descForPersonHeight,
		                            auxiliaryWnd,
		                            NULL,
		                            (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                            NULL);
	
	
	descForPersonYPos += descForPersonHeight;
	HWND lastNameWnd = CreateWindow(TEXT("STATIC"),
		                            currentClient->getLastname(),
		                            WS_CHILD | WS_VISIBLE,
		                            descForPersonXPos,
		                            descForPersonYPos,
		                            descForPersonWidth,
		                            descForPersonHeight,
		                            auxiliaryWnd,
		                            NULL,
		                            (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                            NULL);

	descForPersonYPos += descForPersonHeight;
	HWND firstNameWnd = CreateWindow(TEXT("STATIC"),
		                             currentClient->getFirstname(),
		                             WS_CHILD | WS_VISIBLE,
		                             descForPersonXPos,
		                             descForPersonYPos,
		                             descForPersonWidth,
		                             descForPersonHeight,
		                             auxiliaryWnd,
		                             NULL,
		                             (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                             NULL);

	descForPersonYPos += descForPersonHeight;
	HWND patronymicNameWnd = CreateWindow(TEXT("STATIC"),
		                                  currentClient->getPatronymic(),
		                                  WS_CHILD | WS_VISIBLE,
		                                  descForPersonXPos,
		                                  descForPersonYPos,
		                                  descForPersonWidth,
		                                  descForPersonHeight,
		                                  auxiliaryWnd,
		                                  NULL,
		                                  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                                  NULL);
}
void AuxiliaryWindows::createComboBoxForClientStatusSelect(HWND parent, UINT comboBoxIdentifier, int xPos, int yPos, int width, int height)
{
	HWND hWndStatusComboBox = CreateWindow(TEXT("COMBOBOX"),
		                                   TEXT(""),
		                                   CBS_DROPDOWNLIST | WS_CHILD  | WS_VISIBLE,
		                                   xPos, yPos, 
										   width, height,
										   parent,
										   (HMENU)comboBoxIdentifier,
										   (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
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
	createDescriptionForControl(parent, hWndStatusComboBox, TEXT("Статус в казино*"));
}

void AuxiliaryWindows::createDescriptionForControl(HWND parentOfControl, HWND controlWnd, LPTSTR description)
{
	RECT controlRc;
	GetWindowRect(controlWnd, &controlRc);
	POINT tmp;
	tmp.x = controlRc.left;
	tmp.y = controlRc.top;
	ScreenToClient(parentOfControl, &tmp);
	int desc_width = controlRc.right - controlRc.left;
	int desc_height = 15;
	int desc_xPos = tmp.x;
	int desc_yPos = tmp.y - desc_height;

	HWND descWnd = CreateWindow(TEXT("STATIC"),
		                        description,
		                        WS_CHILD | WS_VISIBLE | SS_LEFT | SS_EDITCONTROL,
		                        desc_xPos, desc_yPos,
		                        desc_width, desc_height,
								parentOfControl,
		                        NULL,
		                        (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                        NULL);

	HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		L"Time New Romans");
	SendMessage(descWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)FALSE);
}

void AuxiliaryWindows::createGroupForImgWindow(HWND parent, UINT imgWndIdentifier, UINT btnIdentifier, UINT editIdentifier)
{
	RECT mainRC;
	GetClientRect(parent, &mainRC);

	int imageHeightforWnd = imageHeight;
	int imageWidthForWnd = imageWidth;
	int imageXPos = mainRC.right - imageWidth - 5;
	int imageYPos = mainRC.top + 25;
	HWND imgWnd = CreateWindow(TEXT("STATIC"),
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP | SS_CENTERIMAGE,
		imageXPos,
		imageYPos,
		imageWidthForWnd,    //is not required if SS_BITMAP(width set by BITMAP)
		imageHeightforWnd,    //is not required if SS_BITMAP(height set by BITMAP)
		parent,
		(HMENU)imgWndIdentifier, 
		(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		NULL);

	RECT rcImgWnd;
	GetWindowRect(imgWnd, &rcImgWnd);

	POINT tmp;
	tmp.x = rcImgWnd.right;
	tmp.y = rcImgWnd.bottom;
	ScreenToClient(parent, &tmp);
	int btnPhotoWidth = 150;
	int btnPhotoHeight = 22;
	int btnPhotoXPos = tmp.x - btnPhotoWidth;
	int btnPhotoYPos = tmp.y;
	HWND addPhotoBtn = CreateWindow(TEXT("BUTTON"), TEXT("Указать расположение"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		btnPhotoXPos, btnPhotoYPos, btnPhotoWidth, btnPhotoHeight, parent, (HMENU)ID_BTN_ADD_PHOTO, (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), NULL);
	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH,
		L"Time New Romans");
	SendMessage(addPhotoBtn, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

	tmp.x = rcImgWnd.left;
	tmp.y = rcImgWnd.bottom;
	ScreenToClient(parent, &tmp);
	int editXPos = tmp.x;
	int editYPos = tmp.y;
	RECT btnRect;
	GetWindowRect(addPhotoBtn, &btnRect);
	tmp.x = btnRect.left;
	tmp.y = btnRect.top;
	ScreenToClient(parent, &tmp);
	int editWidth = tmp.x - editXPos;
	int editHeight = btnPhotoHeight;

	HWND editLocationForImg = CreateWindow(TEXT("EDIT"),
		                                   NULL,
										   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE |ES_AUTOVSCROLL,
										   editXPos, editYPos,
										   editWidth, editHeight,
		                                   parent,
										   (HMENU)editIdentifier,
		                                   (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                                   NULL);
	SendMessage(editLocationForImg, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
}

void AuxiliaryWindows::destroyAuxiliaryWindow()
{
	HWND hwndToDestroy = GetDlgItem(mainWnd, ID_ADD_NEW_CLIENT_WND);
	if (hwndToDestroy)
	{
		DestroyWindow(hwndToDestroy);
	}
}

void AuxiliaryWindows::createEditBoxWithDescription(HWND parent, LPTSTR description, UINT editBoxIdentifier, int editBox_xPos, int  editBox_yPos, int editBox_width, int editBox_height)
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
	
	createDescriptionForControl(parent, editWnd, description);
}


LRESULT CALLBACK AuxiliaryWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)

{
	static HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\Безымянный1.bmp"), IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
	switch (msg)
	{
	case WM_CREATE:
	{
		
		extern LPTSTR szClassName;
		extern LPTSTR szWindowName;
		HWND mainWnd = FindWindow(szClassName, szWindowName);
		HWND controlPanelWnd = GetDlgItem(mainWnd, ID_CONTROL_PANEL_WND);
		EnableWindow(controlPanelWnd, FALSE);
		HWND clientAreaWnd = GetDlgItem(mainWnd, ID_CLIENT_AREA);
		EnableWindow(clientAreaWnd, FALSE);
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		//=======================================================================
		HWND staticWnd = GetDlgItem(hwnd, ID_STATIC_CAPTION);
		HWND imageWnd = GetDlgItem(hwnd, ID_IMAGE_WND_FOR_NEW_CLIENT);
		HWND cashImageWnd = GetDlgItem(hwnd, ID_IMAGE_CASHIN_CASHOUT_WND);
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
		if ((HWND)lParam == imageWnd)
		{
			return (INT_PTR)CreateSolidBrush(RGB(217, 236, 249));
		}
		/*if ((HWND)lParam == cashImageWnd)
		{
			return (INT_PTR)FALSE;
		}*/
		else
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
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case ID_CANCEL_AUXILIARY_BTN:
			{
				extern LPTSTR szClassName;
				extern LPTSTR szWindowName;
				HWND mainWnd = FindWindow(szClassName, szWindowName);
				HWND controlPanelWnd = GetDlgItem(mainWnd, ID_CONTROL_PANEL_WND);
				EnableWindow(controlPanelWnd, TRUE);
				HWND clientAreaWnd = GetDlgItem(mainWnd, ID_CLIENT_AREA);
				EnableWindow(clientAreaWnd, TRUE);
				DestroyWindow(hwnd);
				UpdateWindow(clientAreaWnd);
				SendMessage(mainWnd, INF_OPERATION_COMPLETE, 0, 0);
				break;
			}
			case ID_BTN_ADD_PHONE:
			{
				HWND editForPhone = GetDlgItem(hwnd, ID_EDITBOX_FOR_PHONE);
				size_t len = Edit_LineLength(editForPhone, 0);
				if (len)
				{
					TCHAR* buf = new TCHAR[len + 1];
					memset(buf, 0, len*sizeof(TCHAR));
					Edit_GetText(editForPhone, buf, len + 1);
					HWND hList = GetDlgItem(hwnd, ID_LB_FOR_PHONENUMBER);
					int pos = (int)SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buf);
					delete[]buf;
					buf = nullptr;
					Edit_SetText(editForPhone, TEXT(""));
					SetFocus(editForPhone);
				}
				break;
			}
			case ID_ADD_TO_BASE_BTN:
			{
				extern LPTSTR szClassName;
				extern LPTSTR szWindowName;
				HWND mainWnd = FindWindow(szClassName, szWindowName);
				Client* newClient = new Client;
				if(newClient->addNewClientToDatabase(hwnd))
				{	
					delete newClient;
					newClient = nullptr;
					HWND controlPanelWnd = GetDlgItem(mainWnd, ID_CONTROL_PANEL_WND);
					EnableWindow(controlPanelWnd, TRUE);
					HWND clientAreaWnd = GetDlgItem(mainWnd, ID_CLIENT_AREA);
					EnableWindow(clientAreaWnd, TRUE);
					DestroyWindow(hwnd);
					UpdateWindow(clientAreaWnd);
					SendMessage(mainWnd, INF_OPERATION_COMPLETE, 0, 0);					
				}				
				break;
			}
			case ID_BTN_ADD_PHOTO:
			{
				OPENFILENAME ofn;
				TCHAR szFile[MAX_PATH];
				TCHAR szFileName[MAX_PATH];
				ZeroMemory(&ofn, sizeof(OPENFILENAME));			
				ZeroMemory(szFile, MAX_PATH);			
				ZeroMemory(szFileName, MAX_PATH);
				//initialise OPENFILENAME
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = hwnd;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = MAX_PATH;
				ofn.lpstrFilter = NULL;
				ofn.nFilterIndex = 1;
				ofn.lpstrInitialDir = NULL;
				ofn.lpstrDefExt = L"";
				ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
				GetOpenFileName(&ofn);
				hBitmap = (HBITMAP)LoadImage(NULL, ofn.lpstrFile, IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
				if (hBitmap)
				{
					HWND imgWnd = GetDlgItem(hwnd, ID_IMAGE_WND_FOR_NEW_CLIENT);
					HWND editForImg = GetDlgItem(hwnd, ID_EDITBOX_FOR_IMAGE);
					SendMessage(imgWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
					SendMessage(editForImg, WM_SETTEXT, 0, (LPARAM)ofn.lpstrFile);
					SendMessage(editForImg, EM_SETREADONLY, (WPARAM)TRUE, 0);
					ShowWindow(imgWnd, SW_NORMAL);
					UpdateWindow(imgWnd);
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