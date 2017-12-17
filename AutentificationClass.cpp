#include "AutentificationClass.h"


AutentificationClass::AutentificationClass(HWND hWnd, UINT identifier)
{
	//Создаем и заполняем структуру для создания окна
	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = NULL;
	wcex.hInstance = reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE));
	wcex.lpfnWndProc = AutentificationProc;
	wcex.lpszClassName = L"AutentificationWindowClass";
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	//Регистрируем окно в системе
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Не удалось зарегистрировать окно авторизации", L"Ошибка", MB_OK);
	}
	//Создаем структуру и получаем координаты клиентской части родительского окна
	RECT rc;
	GetClientRect(hWnd, &rc);

	int width = 300;      //Ширина дочернего окна
	int height = 150;     //Высота дочернего окна

	//Вычисляем координаты для отрисовки дочернего окна для расположения его по центру родительского
	int xPos = (rc.right - 200) / 2;
	int yPos = (rc.bottom - height) / 2;

	//Создаем и отображаем само окно
	CreateWindow(L"AutentificationWindowClass",
		         L"Аутентификация",
				 WS_CHILD | WS_BORDER | WS_VISIBLE,
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
	case WM_CREATE:
	{
		HWND hUserName, hPass;
		LPTSTR strUser = L"Zhmenka";
		LPTSTR strPass = L"47dim9175rty";
		hUserName = CreateWindow(L"EDIT",
			                     strUser,
								 WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
								 10,
								 60,
								 280,
								 20,
								 hWnd,
								 (HMENU)ID_USER_NAME,
								 (HINSTANCE)GetWindowLong(NULL,GWLP_HINSTANCE),
								 NULL);
		HFONT hFont;
		hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
			DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH,
			L"Time New Romans");
		HWND userWnd = GetDlgItem(hWnd, ID_USER_NAME);
		SendMessage(userWnd, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(userWnd, EM_SETSEL, 0, wcslen(strUser));
		SetFocus(hUserName);
		hPass = CreateWindow(L"EDIT",
			                 strPass,
							 WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD | WS_TABSTOP,
			                 10,
			                 90,
			                 280,
			                 20,
			                 hWnd,
			                 (HMENU)ID_PASS,
			                 (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
			                 NULL);
		HWND passWnd = GetDlgItem(hWnd, ID_PASS);
		SendMessage(passWnd, WM_SETFONT, (WPARAM)hFont, NULL);
		MyButton okBtn;
		okBtn.CreateButton(hWnd, ID_OKBTN, L"Продолжить", 200, 125, 90, 20);
		MyButton cancelBtn;
		cancelBtn.CreateButton(hWnd, ID_CANCELBTN, L"Отмена", 100, 125, 90, 20);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_OKBTN:    //Обработка при нажатии кнопки продолжить в окне авторизации
		{
			//Получим данные для проверки
			HWND hWndUserName = GetDlgItem(hWnd, ID_USER_NAME);               //Получим дескриптор окна ввода имени пользователя
			size_t len = GetWindowTextLength(hWndUserName) ;                  //Получим длину, содержащегося в ней текста и сохраним в переменную 
			TCHAR* userName = new TCHAR[len + sizeof(TCHAR)];                                 //Выделим память для сохранения текста
			GetWindowText(hWndUserName, userName, len + sizeof(TCHAR));       //Получим сам текст и сохраним его в выделенной памяти
			HWND hWndPass = GetDlgItem(hWnd, ID_PASS);                        //Получим дескриптор окна ввода пароля
			len = GetWindowTextLength(hWndPass);                              //В ранее созданную переменную сохраним длину текста
			TCHAR* pass = new TCHAR[len + sizeof(TCHAR)];                     //Выделим память для сохранения текста
			GetWindowText(hWndPass, pass, len + sizeof(TCHAR));                               //Получим сам текст и сохраним его в выделенной памяти
			
			//Подключимся к базе данных.....
			extern CSqlFramework* sqlODBC;
			
			if (sqlODBC->OpenConnection(L"Malinka", userName, pass))  //Подключимся к источнику данных "Malinka", используя введенные логин и пароль
			{
				AutorisationClass autorisation;
				DestroyWindow(hWnd);
				
			}
			else
			{
				MessageBox(NULL, L"Неверный логин или пароль", L"Ошибка", MB_OK);
			}

                                   
			//После использования освободим память и установим указатель в nullptr
			delete userName;
			userName = nullptr;
			delete pass;
			pass = nullptr;

			break;
		}
		case ID_CANCELBTN:
		{
			PostQuitMessage(0);
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
			L"Time New Romans");
		SelectObject(hDC, hFont);
		RECT rc;
		GetClientRect(hWnd, &rc);			
		LPCWSTR str = L"Для продолжения работы необходимо ввести имя пользователя и пароль";
		size_t len = wcslen(str);	
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