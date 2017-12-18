#include "AutentificationClass.h"


AutentificationClass::AutentificationClass(HWND hWnd, UINT identifier)
{
	//Create and fill structure for window class
	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = NULL;
	wcex.hInstance = reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE));
	wcex.lpfnWndProc = AutentificationProc;
	wcex.lpszClassName = TEXT("AutentificationWindowClass");
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	
	//register class in system
	RegisterClassEx(&wcex);

	//Create structure RECT and get client area coordinates of main aplication window
	RECT rc;
	GetClientRect(hWnd, &rc);

	int width = 300;      //width of autentification window
	int height = 150;     //height of autentification window

	//compute coordinates (x,y) in client area of main window for autentification window(window in center of parent)
	int xPos = rc.right/2 -  width / 2;
	int yPos = rc.bottom/2 - height / 2;

	//Create and show autentification window
	CreateWindow(TEXT("AutentificationWindowClass"),
		         TEXT("Аутентификация"),
				 WS_CHILD | WS_BORDER | WS_VISIBLE |WS_TABSTOP,
				 xPos,
				 yPos,
				 width,
				 height,
				 hWnd,
				 reinterpret_cast<HMENU>(identifier),
				 reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)),
				 NULL);
}


AutentificationClass::~AutentificationClass()
{
}

LRESULT CALLBACK AutentificationProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
    //process window create message
	case WM_CREATE:
	{
		//if autentification window is create - create interface of window 

		HWND hUserName, hPass;                  //handlers for "EDIT" windows 
		LPTSTR strUser = TEXT("Zhmenka");       //username by default is "Zhmenka"
		LPTSTR strPass = TEXT("47dim9175rty");  //pass by default is "47dim9175rty"

		//Create "EDIT" window for username
		hUserName = CreateWindow(TEXT("EDIT"),
			                     strUser,
								 WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
								 10,
								 60,
								 280,
								 20,
								 hWnd,
								 (HMENU)ID_USER_NAME,  //defined in "COnstants.h"
								 (HINSTANCE)GetWindowLong(NULL,GWLP_HINSTANCE),
								 NULL);
		//Create font for "EDIT"
		HFONT hFont;
		hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
			DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH,
			TEXT("Time New Romans"));
		//Set font in username window
		SendMessage(hUserName, WM_SETFONT, (WPARAM)hFont, NULL);
		//select all in username window
		SendMessage(hUserName, EM_SETSEL, 0, wcslen(strUser));
		//set focus on username window
		SetFocus(hUserName);

		//Create "EDIT" for password window
		hPass = CreateWindow(TEXT("EDIT"),
			                 strPass,
							 WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD | WS_TABSTOP,
			                 10,
			                 90,
			                 280,
			                 20,
			                 hWnd,
			                 (HMENU)ID_PASS,  //defined in "COnstants.h"
			                 (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
			                 NULL);
		//set font in password window
		SendMessage(hPass, WM_SETFONT, (WPARAM)hFont, NULL);

		//Create buttons(using class MyButton)
		MyButton okBtn;
		okBtn.CreateButton(hWnd, ID_OKBTN, TEXT("Продолжить"), 200, 125, 90, 20);
		MyButton cancelBtn;
		cancelBtn.CreateButton(hWnd, ID_CANCELBTN, TEXT("Отмена"), 100, 125, 90, 20);
		break;
	}

	//process message from controls of autentification window
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_OKBTN:    //if control is ID_OKBTN (defined in "COnstants.h")
		{
			//Get data for connect to database
			//========================================================================================================
			HWND hWndUserName = GetDlgItem(hWnd, ID_USER_NAME);               //Get handle of username EDIT window
			size_t len = GetWindowTextLength(hWndUserName) ;                  //Get lenght of text in EDIT
			TCHAR* userName = new TCHAR[len + sizeof(TCHAR)];                 //Allocate memory for save it
			GetWindowText(hWndUserName, userName, len + sizeof(TCHAR));       //Save data to userName
			//=========================================================================================================
			HWND hWndPass = GetDlgItem(hWnd, ID_PASS);                        //Get handle of password EDIT window
			len = GetWindowTextLength(hWndPass);                              //Get lenght of text in EDIT
			TCHAR* pass = new TCHAR[len + sizeof(TCHAR)];                     //Allocate memory for save it
			GetWindowText(hWndPass, pass, len + sizeof(TCHAR));               //Save data to pass
			//==========================================================================================================


			//Connect to database using userName and pass......
			
			extern CSqlFramework* sqlODBC;  //allocating in main.cpp for working with database
			
			if (sqlODBC->OpenConnection(TEXT("Malinka"), userName, pass))  //Open connection to datasource "Malinka", using userName and pass
			{
				//if connection is open.....
				AutorisationClass autorisation;  //give control to AutorizationClass   
				DestroyWindow(hWnd);             //and destroy autentification window
				
			}
			else   //if error connection....
			{
				//message to user 
				MessageBox(NULL, TEXT("Неверный логин или пароль"), TEXT("Ошибка"), MB_OK);
			}

			//after using free memory and set pointers to no valid
			delete userName;
			userName = nullptr;
			delete pass;
			pass = nullptr;

			break;
		}

		case ID_CANCELBTN:        //if control is ID_CANCELBTN (defined in "COnstants.h")
		{
			PostQuitMessage(0);   //close aplication
			break;
		}
		}
		break;
	}
	case WM_PAINT:
	{
		HFONT hFont;
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);
		hFont = CreateFont(17, 0, 0, 0, 0, 0, 0, 0,
			DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH,
			TEXT("Time New Romans"));
		SelectObject(hDC, hFont);
		RECT rc;
		GetClientRect(hWnd, &rc);			
		LPTSTR str = TEXT("Для продолжения работы необходимо ввести имя пользователя и пароль");
		size_t len = _tcslen(str);	
		DrawText(hDC,
			str,
			len, &rc,
			DT_CENTER | DT_VCENTER | DT_NOCLIP | DT_WORDBREAK);
		EndPaint(hWnd, &ps);

		break;
	}
		// реакция на сообщение о прекращении работы программы
	case WM_DESTROY:
		DestroyWindow(hWnd);
		break;
		//Обработка всех остальных сообщений производится ОС по умолчанию
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam); //Просто вернем системе сообщение, которого нет в нашем обработчике
	}
	return 0;
}